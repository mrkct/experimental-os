#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <kernel/devices/serial/serial.h>
#include <kernel/arch/i386/x86.h>
#include <kernel/devices/timer/timer.h>
#include <kernel/lib/kassert.h>


void serial_init(void) {
    uint16_t divisor = timer_get_divisor();
    if (divisor == 0) {
        panic("serial_init should only be called AFTER timer_init!");
    }

    outb(SERIAL_PORT_COM1_INTENABLE, 0x00);      // Disable all interrupts
    outb(SERIAL_PORT_COM1_LINECONTROL, 0x80);    // Enable DLAB (set baud rate divisor)
    // Send timer divisor (low & high byte)
    outb(SERIAL_PORT_COM1_LOWBAUD, 
            (divisor) & 0xff);
    outb(SERIAL_PORT_COM1_HIGHBAUD, 
            (divisor >> 8) & 0xff);
    outb(SERIAL_PORT_COM1_LINECONTROL, 0x03);    // 8 bits, no parity, one stop bit
    outb(SERIAL_PORT_COM1_FIFO, 0xc7);           // Enable FIFO, clear them, with 14-byte threshold
    outb(SERIAL_PORT_COM1_MODEMCONTROL, 0x0b);   // IRQs enabled, RTS/DSR set
}

static bool serial_can_transmit(void)
{
    return inb(SERIAL_PORT_COM1_LINESTATUS) & 0x20;
}

static int serial_writechar(char c)
{
    uint32_t start = timer_get_ticks();
    do {
        uint32_t passed_time = timer_get_ticks() - start;
        if (passed_time > SERIAL_TIMEOUT)
            return -1;
    } while (!serial_can_transmit());

    outb(SERIAL_PORT_BASE_COM1, c);

    return 0;
}

int serial_write(const char *data)
{
    for (int i = 0; data[i]; i++) {
        if (serial_writechar(data[i]) != 0)
            return -1;
    }
    
    return 0;
}