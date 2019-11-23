#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <kernel/arch/i386/boot/descriptor_tables.h>
#include <kernel/lib/kprintf.h>
#include <kernel/arch/i386/x86.h>
#include <kernel/arch/i386/irq.h>
#include <kernel/arch/i386/int.h>
#include <kernel/devices/timer/timer.h>
#include <kernel/devices/ps2kb/keyboard.h>


void keyboard_irq(__attribute__((unused)) struct intframe_t *intframe)
{
    unsigned char byte = inb(0x60);
    kbd_handle_byte(byte);
}

void dispatch_irq(struct intframe_t *intframe)
{
    switch (intframe->int_no) {
    case IRQ_TIMER:
        __timer_tick();
        break;
    case IRQ_KEYBOARD:
        keyboard_irq(intframe);
        break;
    default:
        kprintf("Unknown IRQ(%d - %d)\n", intframe->int_no, intframe->err_code);
        
    }
}