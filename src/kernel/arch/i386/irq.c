#include <kernel/arch/i386/boot/descriptor_tables.h>
#include <kernel/arch/i386/int.h>
#include <kernel/arch/i386/irq.h>
#include <kernel/arch/i386/paging.h>
#include <kernel/arch/i386/x86.h>
#include <kernel/devices/mouse.h>
#include <kernel/devices/ps2kb/keyboard.h>
#include <kernel/devices/timer/timer.h>
#include <kernel/lib/kprintf.h>
#include <kernel/lib/kassert.h>
#include <kernel/process.h>
#include <kernel/syscall.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


static void keyboard_irq(__attribute__((unused)) struct intframe_t *intframe)
{
    unsigned char status = inb(0x64);
    unsigned char byte = inb(0x60);
    /*
        It can happen that a mouse packet ends up while a kb interrupt 
        happens. Mouse packets have the 1st and 6th bit set in port 0x64. 
        We just throw them away
    */
    if (status & 0x1 && status & 0x20) {
        return;
    }
    
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
    case IRQ_PS2MOUSE:
        __mouse_irq();
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