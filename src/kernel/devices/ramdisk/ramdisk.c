#include <stddef.h>
#include <stdint.h>
#include <kernel/modules.h>
#include <kernel/devices/ramdisk/ramdisk.h>
#include <klibc/string.h>


/*
    Reads the argument sector and copies into the argument buffer. 
    Buffer is expected to be at least SECTOR_SIZE bytes long
    Returns:
        0 on success
        ERR_RAMDISK_NOT_LOADED
        ERR_RAMDISK_SECTOR_OUT_OF_RANGE
*/
int read_sector(int sector, char *buffer)
{
    struct Module *ramdisk = get_module(MODULE_RAMDISK);
    
    if (!ramdisk->loaded) {
        return ERR_RAMDISK_NOT_LOADED;
    } else if (sector < 0 || ramdisk->size <= sector * SECTOR_SIZE) {
        return ERR_RAMDISK_SECTOR_OUT_OF_RANGE;
    }

    void *s = (void *) (ramdisk->start + sector * SECTOR_SIZE);
    memcpy((void *) buffer, s, SECTOR_SIZE);

    return 0;
}

/*
    Copies the content of buffer in the sector. Buffer is expected to 
    be at least SECTOR_SIZE big.
    Returns:
        0 on success
        ERR_RAMDISK_NOT_LOADED
        ERR_RAMDISK_SECTOR_OUT_OF_RANGE
*/
int write_sector(int sector, char *buffer)
{
    struct Module *ramdisk = get_module(MODULE_RAMDISK);
    
    if (!ramdisk->loaded) {
        return ERR_RAMDISK_NOT_LOADED;
    } else if (sector < 0 || ramdisk->size <= sector * SECTOR_SIZE) {
        return ERR_RAMDISK_SECTOR_OUT_OF_RANGE;
    }

    void *s = (void *) (ramdisk->start + sector * SECTOR_SIZE);
    memcpy(s, (void *) buffer, SECTOR_SIZE);

    return 0;
}