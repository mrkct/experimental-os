#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <kernel/devices/tty/tty.h>
#include <kernel/lib/kprintf.h>
#include <kernel/arch/i386/boot/descriptor_tables.h>
#include <kernel/devices/timer/timer.h>
#include <kernel/devices/ps2kb/keyboard.h>
#include <kernel/lib/kassert.h>
#include <kernel/arch/i386/x86.h>
#include <kernel/memory/memory.h>
#include <kernel/monitor.h>
#include <kernel/lib/read_string.h>
#include <kernel/arch/multiboot.h>

void kernel_setup(multiboot_info_t *mbd, unsigned int magic)
{
    terminal_initialize();

    kprintf("Setting up the GDT...");
    init_gdt();
    kprintf("done\n");
    kprintf("Setting up the IDT...");
    init_idt();
    kprintf("done\n");
    kprintf("Setting up the timer...");
    timer_init(1000);
    kprintf("done\n");
    kprintf("Setting up paging...");
    memory_init(mbd, magic);
    kprintf("done\n");
    kprintf("Detected %d MB of total memory\n", (memory_get_total() / 1024) / 1024);

    kprintf("-----------------------------\n");
}

void kernel_main(void) 
{
    #define BUFFER_SIZE 1024
    char buffer[BUFFER_SIZE];
    while (true) {
        kprintf("> ");
        switch (read_string(buffer, BUFFER_SIZE)) {
            case -1:
                kprintf("You can't have commands THAT long\n");
                break;
            /*
                As not all modifiers are implemented in the ps2 keyboard 
                driver the ctrl flag might contain random data. This could 
                trigger this event if the user is unlucky while pressing 'c'. 
                For now we comment this

            case -2:
                kprintf("\nCTRL-C\n");
                break;
            */
            default:
                if (!monitor_handle(buffer))
                    kprintf("No commands with that name\n");
        }
    }

    kprintf("Reached end of kernel. Halting...");
}
