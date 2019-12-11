#ifndef VFS_H
#define VFS_H

struct DiskInterface{
    int (*read_bytes)(int, int, char *);
    int (*write_bytes)(int, int, char *);
};

#endif