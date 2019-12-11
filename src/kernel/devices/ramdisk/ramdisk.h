#ifndef RAMDISK_H
#define RAMDISK_H

#include <kernel/devices/vdisk.h>

int ramdisk_init(char *disk, int size);
int ramdisk_get_diskinterface(struct DiskInterface *interface);
int read_bytes(int offset, int count, char *buffer);
int write_bytes(int offset, int count, char *buffer);

#endif