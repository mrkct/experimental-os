#include <stddef.h>
#include <stdint.h>
#include <kernel/devices/vdisk.h>
#include <kernel/devices/ramdisk/ramdisk.h>
#include <klibc/string.h>


static char *ramdisk;
static int ramdisk_size;

int ramdisk_init(char *disk, int size)
{
    ramdisk = disk;
    ramdisk_size = size;

    return 0;
}

/*
    Returns a DiskInterface struct for the loaded disk. Before calling this 
    you need first to call ramdisk_init.

    Returns 0 on success, -1 if the disk was not initialised
*/
int ramdisk_get_diskinterface(struct DiskInterface *interface)
{
    if (ramdisk == NULL)
        return -1;
    
    interface->read_bytes = &read_bytes;
    interface->write_bytes = &write_bytes;

    return 0;
}

/*
    Reads 'count' bytes from a given offset in the ramdisk and stores them in 
    'buffer'. These are NOT null terminated

    Returns -1 if the offset or count is not valid, for example it goes 
    after the end of the disk, 0 on success 
*/
int read_bytes(int offset, int count, char *buffer)
{
    if (offset < 0 || offset + count > ramdisk_size)
        return -1;

    memcpy(buffer, ramdisk + offset, count);
    return 0;
}

/*
    Writes 'count' bytes in the ramdisk at a given 'offset', copied from a 
    'buffer'. 
    Returns 0 on success, -1 if the offset or count is not valid
*/
int write_bytes(int offset, int count, char *buffer)
{
    if (offset < 0 || offset + count > ramdisk_size)
        return -1;
    
    memcpy(ramdisk + offset, buffer, count);

    return 0;
}