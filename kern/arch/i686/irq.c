#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <kernel/i686/descriptor_tables.h>
#include <kernel/kprintf.h>
#include <kernel/i686/irq.h>
#include <kernel/i686/int.h>
#include <kernel/timer.h>
#include <lib/input/keyboard.h>


void dispatch_irq(struct intframe_t *intframe)
{
    switch (intframe->int_no) {
    case IRQ_TIMER:
        __timer_tick();
        break;
    case IRQ_KEYBOARD:
        __keyboard_irq();
        break;
    default:
        kprintf("Unknown IRQ(%d - %d)\n", intframe->int_no, intframe->err_code);
        
    }
}