#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <kernel/tty.h>

 
/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif


void kernel_setup(void)
{
    terminal_initialize();
    terminal_writestring("Setting up the GDT...");
    init_gdt();
    terminal_writestring("done!\n");
}

void kernel_main(void) 
{
	terminal_writestring("Hello, kernel World!\n");
}