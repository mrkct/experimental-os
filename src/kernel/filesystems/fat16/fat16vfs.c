#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <kernel/filesystems/fat16/fat16.h>
#include <kernel/filesystems/fat16/fat16vfs.h>
#include <kernel/filesystems/vfs.h>
#include <kernel/devices/vdisk.h>
#include <kernel/memory/kheap.h>
#include <klibc/string.h>


static struct VFSInterface vfsinterface;


struct VFSInterface *fat16_get_vfsinterface(struct DiskInterface *diskinterface)
{
    if (vfsinterface.fopen == 0) {
        int result = fat16_read_filesystem(diskinterface);
        if (result < 0) return NULL;
        vfsinterface = (struct VFSInterface) {
            .fopen = &fat16vfs_fopen,
            .fread = &fat16vfs_fread,
            .fwrite = &fat16vfs_fwrite,
            .fclose = &fat16vfs_fclose,
            .opendir = &fat16vfs_opendir,
            .listdir = &fat16vfs_listdir,
            .closedir = &fat16vfs_closedir
        };
    }

    return &vfsinterface;
}

int fat16vfs_fopen(char *path, File *out)
{
    struct FAT16FileHandle *handle;
    handle = (struct FAT16FileHandle *) kmalloc(sizeof(struct FAT16FileHandle));
    if (handle == 0)    return -2;

    if (fat16_fopen(path, 'r', handle) != 0) {
        kfree(handle);
        return -1;
    }

    int last_slash = 0;
    int pathlen = strlen(path);
    for (int i = 0; i < pathlen; i++) {
        if (path[i] == '/') {
            last_slash = i;
        }
    }
    int filename_len = pathlen - last_slash;
    if (filename_len >= VFS_NAME_LEN) {
        filename_len = VFS_NAME_LEN;
    }
    memcpy(out->name, &path[last_slash], filename_len);
    out->name[filename_len] = '\0';
    // TODO: This is horrible
    out->filesize = handle->filesize;
    out->fs_defined = handle;

    return 0;
}

int fat16vfs_fread(char *buffer, int count, File *file)
{
    struct FAT16FileHandle *handle;
    handle = (struct FAT16FileHandle *) file->fs_defined;
    
    return fat16_fread(handle, count, buffer);
}

int fat16vfs_fwrite(char *buffer, int count, File *file)
{
    // TODO: Implement
    return -1;
}

int fat16vfs_fclose(File *file)
{
    kfree(file->fs_defined);
    return 0;
}

int fat16vfs_opendir(char *path, Dir *out)
{
    FAT16DirEntry folder;
    int offset = fat16_open(path, &folder);
    // The root is not a dir in FAT, but we want to consider it so
    int is_dir = !strcmp("/", path) || folder.attributes & FAT_ATTR_DIRECTORY;
    if (offset < 0 || !is_dir)
        return -1;
    out->fs_defined = (void *) offset;
    // TODO: Insert the dir name in out->name

    return 0;
}

int fat16vfs_listdir(Dir *dir, DirEntry *entry)
{
    int offset = (int) dir->fs_defined;
    FAT16DirEntry fatentry;
    int result = fat16_ls(&offset, &fatentry);
    if (result == 0)
        return 0;
    // TODO: Convert the fat16 filenames to normal ones
    // (remove the unnecessary spaces + add '.' to extension)
    memcpy(entry->name, fatentry.filename, 11);
    entry->name[12] = '\0';
    if (fatentry.attributes & FAT_ATTR_DIRECTORY) {
        entry->type = DIRECTORY;
    } else {
        entry->type = FILE;
    }
    entry->creation = (struct DateTime) {
        .hour = FAT16_GET_HOURS(fatentry.creationTime),
        .minute = FAT16_GET_MINUTES(fatentry.creationTime),
        .second = FAT16_GET_SECONDS(fatentry.creationTime),
        .year = FAT16_GET_YEAR(fatentry.creationDate),
        .month = FAT16_GET_MONTH(fatentry.creationDate),
        .day = FAT16_GET_DAY(fatentry.creationDate)
    };
    entry->lastUpdate = (struct DateTime) {
        .hour = FAT16_GET_HOURS(fatentry.lastModTime),
        .minute = FAT16_GET_MINUTES(fatentry.lastModTime),
        .second = FAT16_GET_SECONDS(fatentry.lastModTime),
        .year = FAT16_GET_YEAR(fatentry.lastModDate),
        .month = FAT16_GET_MONTH(fatentry.lastModDate),
        .day = FAT16_GET_DAY(fatentry.lastModDate)
    };
    dir->fs_defined = (void *) offset;

    return 1;
}

int fat16vfs_closedir(Dir *dir)
{
    // We don't do anything, we use fs_defined for a single int stored
    // in the pointer itself 
    return 0;
}