#include <stdint.h>
#include <stddef.h>
#include <kernel/arch/i386/x86.h>
#include <kernel/arch/i386/cmos.h>


uint8_t cmos_read_register(uint8_t index)
{
    #define NMI_ENABLE 1
    outb(CMOS_PORT_SELECT, (NMI_ENABLE << 7) | index);

    uint8_t prev, curr;
    do{
        prev = curr;
        curr = inb(CMOS_PORT_READ);
    } while (prev != curr);
    
    return curr;
}

uint8_t from_bcd(uint8_t bcd)
{
    return ((bcd / 16) * 10) + (bcd & 0xf);
}