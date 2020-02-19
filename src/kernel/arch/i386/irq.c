#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <kernel/arch/i386/boot/descriptor_tables.h>
#include <kernel/arch/i386/paging.h>
#include <kernel/arch/i386/x86.h>
#include <kernel/arch/i386/irq.h>
#include <kernel/arch/i386/int.h>
#include <kernel/devices/timer/timer.h>
#include <kernel/devices/ps2kb/keyboard.h>
#include <kernel/lib/kprintf.h>
#include <kernel/process.h>
#include <kernel/syscall.h>


static void keyboard_irq(__attribute__((unused)) struct intframe_t *intframe)
{
    unsigned char byte = inb(0x60);
    kbd_handle_byte(byte);
}

void dispatch_irq(struct intframe_t *intframe)
{   
    switch (intframe->int_no) {
    case IRQ_TIMER:
        __timer_tick();
        scheduler(intframe);
        break;
    case IRQ_KEYBOARD:
        keyboard_irq(intframe);
        break;
    case IRQ_ATA_PRIMARY:
    case IRQ_ATA_SECONDARY:
        // TODO: Handle these 2 interrupts
        break;
    case IRQ_SYSCALL:
        intframe->eax = syscall(
            intframe->eax, 
            intframe->ebx, 
            intframe->ecx, 
            intframe->edx, 
            intframe->esi, 
            intframe->edi
        );
        scheduler(intframe);
        break;
    default:
        kprintf("Unknown IRQ(%d - %d)\n", intframe->int_no, intframe->err_code);
    }
}