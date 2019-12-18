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
        vfsinterface.fopen = &fat16vfs_fopen;
        vfsinterface.fread = &fat16vfs_fread;
        vfsinterface.fwrite = &fat16vfs_fwrite;
        vfsinterface.fclose = &fat16vfs_fclose;
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
    if (filename_len >= VFS_FILE_LEN) {
        filename_len = VFS_FILE_LEN;
    }
    memcpy(out->filename, &path[last_slash], filename_len);
    out->filename[filename_len] = '\0';
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