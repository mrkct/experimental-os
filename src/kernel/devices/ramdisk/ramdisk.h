#ifndef RAMDISK_H
#define RAMDISK_H

#define SECTOR_SIZE 512

#define ERR_RAMDISK_NOT_LOADED -1
#define ERR_RAMDISK_SECTOR_OUT_OF_RANGE -2

int read_sector(int sector, char *buffer);
int write_sector(int sector, char *buffer);

#endif