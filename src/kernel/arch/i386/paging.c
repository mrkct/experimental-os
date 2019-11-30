#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <kernel/lib/kassert.h>
#include <kernel/memory/memory.h>
#include <kernel/arch/i386/x86.h>
#include <kernel/arch/i386/paging.h>


static uint32_t npages;
static struct PageInfo *pages;
static struct PageInfo *page_free_list;

static pde_t *kern_pgdir;

/*
    The multiboot header contains a section to index which memory ranges are 
    actually available for use and which are reserved for hardware mapped 
    devices. Here we set which pages are actually available for use and which 
    are not
    TODO: This actually also creates the page_free_list. Also it would be nice 
    to separate an operation on the multiboot from the paging code. 
*/
static void multiboot_detect_available_pages(multiboot_info_t *mbh)
{
    int reserved_pages = ((int) boot_alloc(0)) / PGSIZE;
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
    Initializes pagination in the system and setups an identity mapping for 
    the whole memory.
    TODO WARNING: Not all mapping for the memory is done, see TODO in paging.h
*/
void paging_init(multiboot_info_t *mbh)
{
    uint32_t total_memory = memory_get_total();
    npages = total_memory / PGSIZE;
    pages = (struct PageInfo *) boot_alloc(sizeof(struct PageInfo) * npages);
    multiboot_detect_available_pages(mbh);
    kern_pgdir = pgdir_create(true);
    pgdir_map(kern_pgdir, 0, ADDRESS_SPACE_SIZE, 0, PG_PRESENT | PG_USER);
}

/*
    Loads the argument page directory and flushes the TLB. This also enables 
    paging, if it was not set already
*/
void paging_load(pdir_t pgdir)
{
    load_cr3((uint32_t) pgdir);
    unsigned long cr0 = read_cr0();
    cr0 |= 0x80000001;
    load_cr0(cr0);
    // TODO: Invalidate TLB. This is important or this function will cause 
    // problems when called the second time!!!
}

pdir_t paging_kernel_pgdir()
{
    return kern_pgdir;
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