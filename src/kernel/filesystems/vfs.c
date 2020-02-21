#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <kernel/filesystems/vfs.h>
#include <kernel/memory/kheap.h>


static VFSInterface *rootvfs;

int vfs_setroot(VFSInterface *vfsinterface)
{
    rootvfs = vfsinterface;
    return 0;
}

FileDesc kfopen(char *path, char *mode)
{
    (void) mode;
    // TODO: Check if the file is already opened for write
    // if we want to open for read, or if it is already opened for read if we 
    // want to write. 
    File *file = (File *) kmalloc(sizeof(File));
    if (file == NULL) {
        return NULL;
    }
    int result = rootvfs->fopen(path, file);
    if (result != 0) {
        kfree(file);
        return NULL;
    }

    return file;
}

int kfread(char *buffer, int count, FileDesc fd)
{
    return rootvfs->fread(buffer, count, fd);
}

int kfwrite(char *buffer, int count, FileDesc fd)
{
    return rootvfs->fwrite(buffer, count, fd);
}

int kfclose(FileDesc fd)
{
    rootvfs->fclose(fd);
    kfree(fd);
    return 0;
}

int kopendir(char *path, Dir *dir)
{
    return rootvfs->opendir(path, dir);
}

int klistdir(Dir *dir, DirEntry *entry)
{
    return rootvfs->listdir(dir, entry);
}

int kclosedir(Dir *dir)
{
    return rootvfs->closedir(dir);
}