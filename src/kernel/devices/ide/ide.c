#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <kernel/lib/kassert.h>
#include <kernel/lib/kprintf.h>
#include <kernel/arch/i386/x86.h>
#include <kernel/memory/kheap.h>
#include <kernel/devices/ide/ide.h>
#include <kernel/devices/timer/timer.h>


/* Parts of this code is adapted from the Protura OS
    https://github.com/mkilgore/protura
*/

/*
    Waits for the status port to not be busy and returns its value. 
    Returns the content of the status register or IDE_STATUS_TIMEOUT if 
    after 200 timer ticks the status is still busy
*/
static int ide_wait_for_status(int status, int timeout)
{
    int ret;

    uint32_t time = timer_get_ticks();

    do {
        ret = inb(IDE_PORT_COMMAND_STATUS);
        if (timer_get_ticks() - time > timeout)
            return IDE_STATUS_TIMEOUT;
    } while ((ret & (IDE_STATUS_BUSY | status)) != status);

    return ret;
}

/*
    Reads a single sector into the buffer using PIO. The buffer is expected to 
    be at least ATA_SECTOR_SIZE bytes long (usually 512 bytes)
*/
static void ide_do_pio_read(uint16_t *buf)
{
    const int sector_reads = IDE_SECTOR_SIZE / sizeof(uint16_t);
    for (int i = 0; i < sector_reads; i++) {
        buf[i] = inw(IDE_PORT_DATA);
    }
}

/*
    For some reason in the IDENTIFY ide data block the model string 
    is written with each 2 characters swapped: for example
    QEMU HARDDISK is written EQUMH RADDSI K\0
    This functions rewrites a string in a normal form, removing the extra 
    final space (if present) and setting all the other ending bytes to \0
*/ 
static void ide_fix_string(uint8_t *s, size_t len)
{
    if (len % 2)
        panic("Non mod 2 length passed to ide_fix_string()!\n");

    uint16_t *t = (uint16_t *)s;

    size_t i;
    for (i = 0; i < len / 2; i++)
        t[i] = (t[i] << 8) | (t[i] >> 8);

    size_t end = 0;
    for (i = 0; i < len; i++)
        if (s[i] && s[i] != ' ')
            end = i;

    for (i = end + 1; i < len; i++)
        s[i] = '\0';
}

/*
    Sends an IDENTIFY command to the IDE device selected and writes the 
    response in the argument structure on success. Note that before calling 
    this function you should send a byte to the IDE device selecting the 
    device you want to identify. 
    This is done in the 'ide_identify_master/slave' functions.
    Returns 0 if a valid data structure was written, -1 if while reading the 
    status register a timeout or a drive fault happens
*/
static int ide_identify(struct ide_identify_format *id)
{
    outb(IDE_PORT_COMMAND_STATUS, IDE_COMMAND_IDENTIFY);

    int ret = ide_wait_for_status(IDE_STATUS_READY, IDE_READSTATUS_TIMEOUT);
    if (ret & (IDE_STATUS_DRIVE_FAULT | IDE_STATUS_TIMEOUT) || !(ret & IDE_STATUS_READY)) {
        return -1;
    }
    
    /*
        I have no idea why but I can't just pass the struct as to where 
        to write into from the pio_read. It causes a lot of weird stuff 
        like pagefaults and stack corruptions
    */
    uint16_t *b = (uint16_t *) kmalloc(sizeof(struct ide_identify_format));
    ide_do_pio_read(b);
    *id = *((struct ide_identify_format *) b);
    ide_fix_string(id->model, 40);
    kfree(b);

    return 0;
}

/*
    Sends an IDENTIFY command to the master IDE device and writes its repsonse 
    to the argument structure.
    Returns 0 if the device responded with success and valid data was written, 
    -1 if the device returned a drive fault error or it timed out responding.
*/
int ide_identify_master(struct ide_identify_format *response)
{
    outb(IDE_PORT_DRIVE_HEAD, IDE_DH_SHOULD_BE_SET | IDE_DH_LBA);
    return ide_identify(response);
}

// TODO: ide_identify_slave