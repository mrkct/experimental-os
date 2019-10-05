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

void kernel_main(void) 
{
	terminal_initialize();
	terminal_writestring("Hello, kernel World!\n");
}

void set_gdt_entry (
    char *gdt, 
    const int index, 
    const uint32_t base, 
    const uint32_t limit, 
    const uint8_t type
) 
{
    const int offset = 8 * index;
    // Encoding the limit
    gdt[offset]     = limit & 0xff;
    gdt[offset + 1] = (limit >> 8) & 0xff;
    gdt[offset + 6] = 0xc0 | ((limit >> 16 ) & 0xf);
    
    // Encoding the base
    gdt[offset + 2] = base & 0xff;
    gdt[offset + 3] = (base >> 8) & 0xff;
    gdt[offset + 4] = (base >> 16) & 0xff;
    gdt[offset + 7] = (base >> 24) & 0xff;

    // Type byte
    gdt[offset + 5] = type;
}

void setup_gdt(void)
{
	#define TSS_SIZE 1024
	// Note: The size of the TSS is also defined in boot.s
	// If you need to change it don't forget to also change it in boot.s
    extern char *gdt;
	extern char *tss;

    set_gdt_entry(gdt, 0, 0, 0, 0);                 		// SEG_NULL
	set_gdt_entry(gdt, 1, 0x0, 0xffffffff, 0x9a);   		// SEG_CODE    
	set_gdt_entry(gdt, 2, 0x0, 0xffffffff, 0x89);   		// SEG_DATA
	set_gdt_entry(gdt, 3, (uint32_t) tss, TSS_SIZE, 0x89); 	// SEG_TSS0
}