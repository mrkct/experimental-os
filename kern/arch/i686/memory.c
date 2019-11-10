#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <kernel/kassert.h>
#include <kernel/i686/memory.h>
#include <kernel/i686/x86.h>


/*
    TODO: Change this into the memory address where the kernel ends in 
    memory. This will require adding a symbol 'end' to the linker script at 
    the end and using 'extern char *end' instead of this, but I couldn't get 
    it working last time
*/
#define TODO_FREE_MEMORY_START (11 * 1024 * 1024)
#define TODO_DETECTED_MEMORY   (64 * 1024 * 1024)


static uint32_t base_memory;

static uint32_t npages;
static struct PageInfo *pages;
static struct PageInfo *page_free_list;

static pde_t *kern_pgdir;

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

/*
    Creates the 'pages' data structure, creates the kernel page directory and 
    maps it using an identity mapping.
*/
void pages_init(multiboot_info_t *mbh)
{
    npages = get_total_memory() / PGSIZE;
    pages = (struct PageInfo *) boot_alloc(sizeof(struct PageInfo) * npages);
    multiboot_detect_available_pages(mbh);
    kern_pgdir = pgdir_create(true);
    pgdir_map(kern_pgdir, 0, ADDRESS_SPACE_SIZE, 0, PG_PRESENT | PG_USER);
}

/*
    Returns the total installed memory in the system. Note that the current 
    implementation depends on the 'base_memory' global, as such you need to
    set it manually to the result of 'multiboot_get_memory' before calling 
    this
*/
uint32_t get_total_memory(void)
{
    return base_memory;
}

/*
    Reads the total installed memory in the GNU multiboot header. This also 
    does a sanity check for the magic number
*/
uint32_t multiboot_get_memory(__attribute__((unused)) multiboot_info_t *mbh, __attribute__((unused)) uint32_t magic)
{
    // TODO: Change this to real detection
    return TODO_DETECTED_MEMORY;
}

/*
    Setups paging and other memory related stuff. 
*/
void memory_init(multiboot_info_t *mbh, uint32_t magic)
{
    base_memory = multiboot_get_memory(mbh, magic);
    pages_init(mbh);
    load_pgdir(kern_pgdir);
}

/*
    Reads the multiboot header and sets which pages in the 'pages' array are 
    actually available to be used.
*/
void multiboot_detect_available_pages(__attribute__((unused)) multiboot_info_t *mbh)
{
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
}

/*
    Allocates a page from the free list. Note that this function does NOT 
    increment the 'references' field of the returned structure, it is the 
    caller's job to do that. Returns NULL if no pages are free
*/
struct PageInfo *page_alloc(void)
{
    if (page_free_list == NULL)
        return NULL;
    struct PageInfo *page = page_free_list;
    page_free_list = page->nextfree;

    page->references = 0;
    page->nextfree = NULL;

    return page;
}

/*
    Returns a page to the free list. Check that the 'references' field is 
    equal to 0 when you want to free a page, otherwise this function will 
    panic
*/
void page_free(struct PageInfo *page)
{
    kassert(page != NULL);
    kassert(page->references == 0);
    page->nextfree = page_free_list;
    page_free_list = page;
}

/*
    Returns a new page directory, uninitialized. If 'create_table' is true 
    it will also allocate a page table for all entries
*/
pde_t *pgdir_create(bool create_tables)
{
    struct PageInfo *page = page_alloc();
    kassert(page != NULL);
    page->references++;
    pde_t *pgdir = (pde_t*) pageindex2pa((paddr_t) (page - pages));

    if (create_tables) {
        for (int i = 0; i < PGDIR_ENTRIES; i++) {
            struct PageInfo *page = page_alloc();
            page->references++;
            kassert(page != NULL);
            paddr_t pa = pageindex2pa((paddr_t) (page - pages));
            pgdir[i] = pa | PG_PRESENT | PG_USER;
        }
    }

    return (pde_t*) pgdir;
}

/*
    Navigates the page directory and returns the correspondant page table 
    entry to the argument virtual address. Returns NULL if there is no page 
    table for the address frame
*/
pte_t *pgdir_addr2entry(pdir_t pgdir, paddr_t va)
{
    pde_t e = pgdir[PDX(va)];
    if (!(e & PG_PRESENT) || !PTE_ADDR(e)) {
        return NULL;
    }
    pte_t *table = (pte_t*) PTE_ADDR(e);
    
    return &table[PTX(va)];
}

/*
    Maps in a page directory all addresses in the ranges ['va' -> 'va+size'] 
    to ['pa' -> 'pa+size'] using the 'permissions' bits for each page table entry.
    Make sure 'permissions' is just 12 bits and that 'pa' and 'va' are aligned 
    to PGSIZE, or this function will panic
*/
void pgdir_map(pdir_t pgdir, vaddr_t va, unsigned long size, paddr_t pa, uint16_t permissions)
{
    kassert(pa % PGSIZE == 0);
    kassert(va % PGSIZE == 0);
    kassert(permissions >> 12 == 0);
    for (unsigned long i = 0; i < size; i += PGSIZE) {
        pte_t *entry = pgdir_addr2entry(pgdir, va + i);
        *entry = (pa + i) | permissions;
    }
}

/*
    Loads the argument page directory and flushes the TLB. This also enables 
    paging, if it was not set already
*/
void load_pgdir(pdir_t pgdir)
{
    load_cr3((uint32_t) pgdir);
    unsigned long cr0 = read_cr0();
    cr0 |= 0x80000001;
    load_cr0(cr0);
    // TODO: Invalidate TLB. This is important or this function will cause 
    // problems when called the second time!!!
}