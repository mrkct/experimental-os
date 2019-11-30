#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <kernel/arch/multiboot.h>

/*
    This is the memory map for the OS

    [0, 1MB]: Not used, we save all the bios structures
    [1MB, kern_end]: The kernel text & static data
    [kern_end, end_modules]: GRUB's loaded modules
    [end_modules, end_modules+16MB]: Kernel heap space
    [end_modules+16MB, 0xffffffff]: Available to programs
*/
/*
    TODO: Change this into the memory address where the kernel ends in 
    memory. This will require adding a symbol 'end' to the linker script at 
    the end and using 'extern char *end' instead of this, but I couldn't get 
    it working last time
*/
#define TODO_FREE_MEMORY_START (11 * 1024 * 1024)
#define TODO_DETECTED_MEMORY   (64 * 1024 * 1024)

#define KERNEL_HEAP_SIZE (16 * 1024 * 1024)

typedef uint32_t paddr_t;
typedef uint32_t vaddr_t;

uint32_t multiboot_read_memory(multiboot_info_t *);
void memory_set_total(uint32_t);
uint32_t memory_get_total(void);
void *boot_alloc(size_t);

#endif