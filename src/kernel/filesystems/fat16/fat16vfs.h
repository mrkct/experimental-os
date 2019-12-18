#ifndef FAT16VFS_H
#define FAT16VFS_H

#include <kernel/filesystems/vfs.h>

struct VFSInterface *fat16_get_vfsinterface();

int fat16vfs_fopen(char *path, File *out);
int fat16vfs_fread(char *buffer, int count, File *file);
int fat16vfs_fwrite(char *buffer, int count, File *file);
int fat16vfs_fclose(File *file);

int fat16vfs_opendir(char *path, Dir *out);
int fat16vfs_listdir(Dir *dir, DirEntry *entry);
int fat16vfs_closedir(Dir *dir);

#endif