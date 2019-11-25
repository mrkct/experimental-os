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
void memory_init(multiboot_info_t *mbh, uint32_t magic)
{
    base_memory = multiboot_read_available_memory(mbh, magic);
    kmalloc_init(boot_alloc(KERNEL_HEAP_SIZE, PGSIZE), KERNEL_HEAP_SIZE);
    /*
        Calling paging init sets all the memory allocated with boot_alloc to 
        'reserved', as such it needs to be the last thing done
    */
    paging_init(mbh);
    paging_load(paging_kernel_pgdir());
    
}

/*
    A simple memory allocator, to be used only to setup paging. This might 
    return more memory than asked, all memory returned is guaranteed to be 
    aligned to blocksize. Note that memory allocated this way cannot be free'd..
    If called with 0 bytes returns the current address up until memory is used
*/
void *boot_alloc(size_t bytes, uint32_t blocksize)
{
    static char *nextfree;
    if (!nextfree) {
        // TODO: Change this to the real end of the kernel in memory
        nextfree = (char*) ROUNDUP(TODO_FREE_MEMORY_START, blocksize);
    }
    size_t blocks = ROUNDUP(bytes, blocksize) / blocksize;

    char *result = nextfree;
    kassert((uint32_t) (nextfree + blocksize * blocks) <= memory_get_total());
    nextfree += blocksize * blocks;
    
    return (void*) result;
}

/*
    Returns the total installed memory in the system. Note that the current 
    implementation depends on the 'base_memory' global, as such you need to
    set it manually to the result of 'multiboot_get_memory' before calling 
    this
*/
uint32_t memory_get_total(void)
{
    return base_memory;
}

/*
    Reads the total installed memory in the GNU multiboot header. This also 
    does a sanity check for the magic number
*/
uint32_t multiboot_read_available_memory(__attribute__((unused)) multiboot_info_t *mbh, __attribute__((unused)) uint32_t magic)
{
    // TODO: Change this to real detection
    return TODO_DETECTED_MEMORY;
}

/*
    Reads the multiboot header and sets which pages in the 'pages' array are 
    actually available to be used.
*/
void multiboot_detect_available_pages(__attribute__((unused)) multiboot_info_t *mbh)
{
    /*
    // TODO: Actually detect available pages
    int reserved_pages = TODO_FREE_MEMORY_START / PGSIZE;
    for (int i = 0; i < reserved_pages; i++) {
        pages[i].reserved = true;
        pages[i].references = 0;
        pages[i].nextfree = NULL;
    }

    page_free_list = NULL;
    for (unsigned i = reserved_pages; i < npages; i++) {
        pages[i].reserved = false;
        pages[i].references = 0;
        pages[i].nextfree = page_free_list;
        page_free_list = &pages[i];
    }
    */
}