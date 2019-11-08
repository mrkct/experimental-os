#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <kernel/kassert.h>
#include <kernel/kprintf.h>
#include <kernel/i686/memory.h>

/*
    TODO: Change this into the memory address where the kernel ends in 
    memory. This will require adding a symbol `end` to the linker script at 
    the end and using `extern char *end` instead of this, but I couldn't get 
    it working last time
*/
#define TODO_FREE_MEMORY_START (8 * 1024 * 1024)
#define TODO_DETECTED_MEMORY   (64 * 1024 * 1024)


static uint32_t base_memory;

static uint32_t npages;
static struct PageInfo *pages;
static struct PageInfo *page_free_list;

uint32_t ROUNDUP(uint32_t value, uint32_t multiple)
{
    if (value % multiple == 0)
        return value;
    
    return value + (multiple - (value % multiple));
}

uint32_t ROUNDDOWN(uint32_t value, uint32_t multiple)
{
    if (value % multiple == 0)
        return value;
    
    return value - (value % multiple);
}

/*
    A simple memory allocator, to be used only to setup paging. This might 
    return more memory than asked, all memory returned is guaranteed to be 
    aligned to PGSIZE. Note that memory allocated this way cannot be free'd.
*/
void *boot_alloc(size_t bytes)
{
    static char *nextfree;
    if (!nextfree) {
        // TODO: Change this to the real end of the kernel in memory
        nextfree = (char*) ROUNDUP(TODO_FREE_MEMORY_START, PGSIZE);
    }
    size_t pages = ROUNDUP(bytes, PGSIZE) / PGSIZE;

    char *result = nextfree;
    kassert((uint32_t) (nextfree + PGSIZE * pages) <= get_total_memory());
    nextfree += PGSIZE * pages;
    

    return (void*) result;
}

void pages_init(multiboot_info_t *mbh)
{
    npages = get_total_memory() / PGSIZE;
    pages = (struct PageInfo *) boot_alloc(sizeof(struct PageInfo) * npages);
    multiboot_detect_available_pages(mbh);
}

uint32_t get_total_memory()
{
    return base_memory;
}

uint32_t multiboot_get_memory(multiboot_info_t *mbh, uint32_t magic)
{
    // TODO: Change this to real detection
    return TODO_DETECTED_MEMORY;
}

void memory_init(multiboot_info_t *mbh, uint32_t magic)
{
    base_memory = multiboot_get_memory(mbh, magic);
    pages_init(mbh);
}

void multiboot_detect_available_pages(multiboot_info_t *mbh)
{
    // TODO: Actually detect available pages
    int reserved_pages = TODO_FREE_MEMORY_START / PGSIZE;
    for (int i = 0; i < reserved_pages; i++) {
        pages[i].reserved = true;
        pages[i].references = 0;
        pages[i].nextfree = NULL;
    }

    page_free_list = NULL;
    for (int i = reserved_pages; i < npages; i++) {
        pages[i].reserved = false;
        pages[i].references = 0;
        pages[i].nextfree = page_free_list;
        page_free_list = &pages[i];
    }
}

struct PageInfo *page_alloc()
{
    if (page_free_list == NULL)
        return NULL;
    struct PageInfo *page = page_free_list;
    page_free_list = page->nextfree;

    page->nextfree = NULL;

    return page;
}

void page_free(struct PageInfo *page)
{
    kassert(page != NULL);
    kassert(page->references == 0);
    page->nextfree = page_free_list;
    page_free_list = page;
}