#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <kernel/tty.h>
#include <kernel/kprintf.h>
#include <kernel/i686/descriptor_tables.h>
#include <kernel/timer.h>
#include <lib/input/keyboard.h>
#include <kernel/kassert.h>
#include <kernel/i686/x86.h>
#include <kernel/i686/memory.h>


/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif



#include <kernel/i686/multiboot.h>

void kernel_setup(multiboot_info_t *mbd, unsigned int magic)
{
    terminal_initialize();

    kprintf("Setting up the GDT...");
    init_gdt();
    kprintf("done!\n");
    kprintf("Setting up the IDT...");
    init_idt();
    kprintf("done\n");
    timer_init(1000);

    memory_init(mbd, magic);

    kprintf("-----------------------------\n");
}

void kernel_main(void) 
{
	kprintf("Hello, kernel World!\n");
    kprintf("How are you?\n");

    struct KeyAction action;
    while (true) {
        if (kbd_get_keyaction(&action) && action.pressed && action.character != 0) {
            kprintf("%c", action.character);
        }
    }

    kprintf("Reached end of kernel. Halting...");
}
