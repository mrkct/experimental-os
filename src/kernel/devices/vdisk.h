#ifndef VDISK_H
#define VDISK_H

struct DiskInterface{
    int (*read_bytes)(int, int, char *);
    int (*write_bytes)(int, int, char *);
};

#endif