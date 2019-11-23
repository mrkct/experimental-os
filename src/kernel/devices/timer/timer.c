#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <kernel/arch/i386/x86.h>
#include <kernel/devices/timer/timer.h>


uint32_t ticks = 0;

uint32_t timer_get_ticks()
{
    return ticks;
}

/*
    Called every timer tick by the interrupt handler.
    DO NOT CALL THIS OUTSIDE OF 'irq_dispatch'
*/
void __timer_tick()
{
    ticks++;
}

/*
    Sets the timer to send an interrupt every 'milliseconds' ms. Note that 
    it is not accurate
*/
void timer_init(uint16_t frequency)
{
    /*
        The PIC 8259 by default sends an interrupt every 1193180Hz, to change 
        this we can send a number to divide this frequency. 
        See: https://wiki.osdev.org/Programmable_Interval_Timer
    */
    uint32_t divisor = 1193182 / frequency;

    outb(0x43, 0x36);
    outb(0x40, (uint8_t) (divisor & 0xff));
    outb(0x40, (uint8_t) ((divisor >> 8) & 0xff));
}