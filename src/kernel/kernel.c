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
    char buffer[1024];
    int buffer_pos = 0;
    struct KeyAction action;
    while (true) {
        if (kbd_get_keyaction(&action) && action.pressed && action.character != 0) {
            kprintf("%c", action.character);
            if (action.character == '\n') {
                buffer[buffer_pos] = '\0';
                if (!monitor_handle(buffer))
                    kprintf("No commands with that name\n");
                kprintf("> ");
                buffer_pos = 0;
            } else {
                buffer[buffer_pos++] = action.character;
            }
        }
    }

    kprintf("Reached end of kernel. Halting...");
}
