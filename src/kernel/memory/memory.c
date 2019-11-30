#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <kernel/lib/kassert.h>
#include <kernel/memory/memory.h>
#include <kernel/arch/i386/paging.h>


static uint32_t base_memory;

/*
    Setups all memory related stuff. In order this does:
    - Read info about the available memory from the multiboot header
    - Initializes paging in x86 systems
    - Setups virtual memory with an identity mapping 
*/
// void memory_init(multiboot_info_t *mbh, uint32_t magic)
// {
//     base_memory = multiboot_read_available_memory(mbh, magic);
//     
//     int grub_mods = mbd->mods_count;
//     multiboot_module_t *current_module;
//     current_module = (multiboot_module_t *) mbd->mods_addr;
//     while (grub_mods > 0) {
//         
//         grub_mods--;
//     }
// 
//     kmalloc_init(boot_alloc(KERNEL_HEAP_SIZE), KERNEL_HEAP_SIZE);
//     /*
//         Calling paging init sets all the memory allocated with boot_alloc to 
//         'reserved', as such it needs to be the last thing done
//     */
//     paging_init(mbh);
//     paging_load(paging_kernel_pgdir());
// }

/*
    A simple memory allocator, to be used only to setup paging. This might 
    return more memory than asked, all memory returned is guaranteed to be 
    aligned to PGSIZE bytes. Note that memory allocated this way cannot 
    be free'd. If called with 0 bytes returns the current address up until 
    memory is used.
*/
void *boot_alloc(size_t bytes)
{
    static char *nextfree;
    if (!nextfree) {
        // TODO: Change this to the real end of the kernel in memory
        nextfree = (char*) ROUNDUP(TODO_FREE_MEMORY_START, PGSIZE);
    }
    size_t blocks = ROUNDUP(bytes, PGSIZE) / PGSIZE;

    char *result = nextfree;
    kassert((uint32_t) (nextfree + PGSIZE * blocks) <= memory_get_total());
    nextfree += PGSIZE * blocks;
    
    return (void*) result;
}

/*
    Returns the total installed memory in the system. This is the same value 
    passed before to memory_set_total, if that was not called this will 
    return 0
*/
uint32_t memory_get_total(void)
{
    return base_memory;
}

/*
    Sets the total installed memory size in the system. This is required 
    before calling any other functions
*/
void memory_set_total(uint32_t memory)
{
    base_memory = memory;
}

/*
    Returns the detected memory from the multiboot heade r
*/
uint32_t multiboot_read_memory(multiboot_info_t *header)
{
    return 1024 * (header->mem_lower + header->mem_upper);
}