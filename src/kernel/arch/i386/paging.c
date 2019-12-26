#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <kernel/lib/kassert.h>
#include <kernel/memory/memory.h>
#include <kernel/arch/i386/x86.h>
#include <kernel/arch/i386/paging.h>


static uint32_t npages;
static struct PageInfo *pages;

static pde_t *kern_pgdir;

/*
    The multiboot header contains a section to index which memory ranges are 
    actually available for use and which are reserved for hardware mapped 
    devices. Here we set which pages are actually available for use and which 
    are not
    TODO: It would be nice to separate an operation on the multiboot from the 
    paging code. 
*/
static void multiboot_detect_available_pages(__attribute__((unused)) multiboot_info_t *mbh)
{
    int reserved_pages = ((int) boot_alloc(0)) / PGSIZE;
    for (int i = 0; i < reserved_pages; i++) {
        pages[i].reserved = true;
        pages[i].available = false;
    }

    for (unsigned i = reserved_pages; i < npages; i++) {
        pages[i].reserved = false;
        pages[i].available = true;
    }
}

void paging_init(multiboot_info_t *mbh)
{
    uint32_t total_memory = memory_get_total();
    npages = total_memory / PGSIZE;
    pages = (struct PageInfo *) boot_alloc(sizeof(struct PageInfo) * npages);
    multiboot_detect_available_pages(mbh);
    kern_pgdir = pgdir_create();
    pgdir_map(kern_pgdir, 0, ADDRESS_SPACE_SIZE, 0, PG_PRESENT | PG_USER);
}

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

struct PageInfo *page_alloc(size_t count) {
    // TODO: This is terrible
    for (int i = 0; i < (int) (npages - (count-1)); i++) {
        bool valid = true;
        for (size_t k = 0; k < count; k++) {
            if (!pages[i + k].available) {
                valid = false;
                break;
            }
        }
        if (valid) {
            for (size_t k = 0; k < count; k++)
                pages[i + k].available = false;
            
            return &pages[i];
        }
    }

    return NULL;
}

void page_free(struct PageInfo *page)
{
    page->available = true;
}

pde_t *pgdir_create(void)
{
    struct PageInfo *page = page_alloc(1);
    kassert(page != NULL);
    pde_t *pgdir = (pde_t*) pageindex2pa((paddr_t) (page - pages));

    for (int i = 0; i < PGDIR_ENTRIES; i++) {
        struct PageInfo *page = page_alloc(1);
        kassert(page != NULL);
        paddr_t pa = pageindex2pa((paddr_t) (page - pages));
        pgdir[i] = pa | PG_PRESENT | PG_USER;
    }

    return (pde_t*) pgdir;
}

pte_t *pgdir_addr2entry(pdir_t pgdir, paddr_t va)
{
    pde_t e = pgdir[PDX(va)];
    if (!(e & PG_PRESENT) || !PTE_ADDR(e)) {
        return NULL;
    }
    pte_t *table = (pte_t*) PTE_ADDR(e);
    
    return &table[PTX(va)];
}

void 
pgdir_map(
    pdir_t pgdir, 
    vaddr_t va, 
    unsigned long size, 
    paddr_t pa, 
    uint16_t permissions)
{
    kassert(pa % PGSIZE == 0);
    kassert(va % PGSIZE == 0);
    kassert(permissions >> 12 == 0);
    for (unsigned long i = 0; i < size; i += PGSIZE) {
        pte_t *entry = pgdir_addr2entry(pgdir, va + i);
        *entry = (pa + i) | permissions;
    }
}

void *page2addr(struct PageInfo *page) {
    return pageindex2pa(page - pages);
}