#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <kernel/i686/multiboot.h>

/*
    TODO: Setting this to the full 4GB makes the boot insanely slow. But if we 
    don't map the whole address space not all memory is available. Search for 
    a fix
*/
#define ADDRESS_SPACE_SIZE  (256 * 1024 * 1024)

typedef uint32_t paddr_t;
typedef uint32_t vaddr_t;

#define PGSIZE          4096
#define PGSHIFT         12
#define PGDIR_ENTRIES   1024
#define PGTABLE_ENTRIES 1024

#define PG_PAGESIZE     0x80
#define PG_ACCESSED     0x20
#define PG_CACHEDISABLE 0x10
#define PG_WRITETHROUGH 0x8
#define PG_USER         0x4
#define PG_RW           0x2
#define PG_PRESENT      0x1

#define PG_GLOBAL       0x200
#define PG_PAT          0x100
#define PG_DIRTY        0x40
#define PG_CACHED       0x10

/*
    These macros are from the JOS Operating System.

    PDX: Given a virtual address returns the bits that corresponds to the 
    index of the page directory entry
    PTX: Given a virtual address returns the bits that correspond to the 
    index of the page table entry
    PGOFF: Given a virtual address returns the bits that correspond to the 
    offset inside the page
    PTE_ADDR: Returns the 20 bits in a page directory/table entry with the
    physycal address of the table/frame
*/
#define PDX(la)		((((uint32_t) (la)) >> 22) & 0x3FF)
#define PTX(la)		((((uint32_t) (la)) >> 12) & 0x3FF)
#define PGOFF(la)	(((uint32_t) (la)) & 0xFFF)
#define PTE_ADDR(pte)	((paddr_t) (pte) & ~0xFFF)

struct PageInfo {
    bool reserved;
    int references;
    struct PageInfo *nextfree;
};

uint32_t get_total_memory(void);
void *boot_alloc(size_t);
void pages_init(multiboot_info_t*);
uint32_t multiboot_get_memory(multiboot_info_t*, uint32_t);
void memory_init(multiboot_info_t*, uint32_t);
void multiboot_detect_available_pages(multiboot_info_t*);

struct PageInfo *page_alloc(void);
void page_free(struct PageInfo*);

typedef uint32_t pde_t;
typedef uint32_t pte_t;
typedef uint32_t *pdir_t;

pde_t *pgdir_create(bool);
pte_t *pgdir_addr2entry(pdir_t, paddr_t);
void pgdir_map(pdir_t, uint32_t, unsigned long, uint32_t, uint16_t);
pte_t *pgdir_addr2entry(pdir_t, paddr_t);

void pgdir_print(pdir_t pgdir, int how_many);
void load_pgdir(pdir_t pgdir);

static inline uint32_t ROUNDUP(uint32_t value, uint32_t multiple)
{
    if (value % multiple == 0)
        return value;
    
    return value + (multiple - (value % multiple));
}

static inline uint32_t ROUNDDOWN(uint32_t value, uint32_t multiple)
{
    if (value % multiple == 0)
        return value;
    
    return value - (value % multiple);
}

/*
    Returns the corresponding physical address of a page index, using the 
    identity mapping
*/
static inline paddr_t pageindex2pa(int index)
{
    return index << PGSHIFT;
}

/*
    Returns the page index given a physical address using the identity 
    mapping
*/
static inline uint32_t pa2pageindex(paddr_t pa)
{
    return ROUNDDOWN(pa, PGSIZE) >> PGSHIFT;
}

#endif