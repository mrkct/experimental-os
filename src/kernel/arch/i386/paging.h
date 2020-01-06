#ifndef PAGING_H
#define PAGING_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <kernel/memory/memory.h>


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
    bool available;
};

typedef uint32_t pde_t;
typedef uint32_t pte_t;
typedef uint32_t *pdir_t;

/*
    Initializes pagination in the system and setups an identity mapping for 
    the whole memory.
    TODO WARNING: Not all mapping for the memory is done, see TODO in paging.h
*/
void paging_init(multiboot_info_t *);

/*
    Returns true if a page is available for use, false othewise
*/
bool page_available(struct PageInfo *page);

/*
    Finds the first page in the 'pages' array that starts a contiguous area 
    of at least 'count' pages.
    Returns NULL if no area at least 'count' pages big was found, otherwise 
    returns the pointer of the first page at the start of the area. 
*/
struct PageInfo *page_alloc(size_t count);

/*
    Sets the argument page as available to be re-allocated
*/
void page_free(struct PageInfo *page);

/*
    Returns a new page directory, where only the addresses under KERNEL_END
    are mapped to the kernel. The rest of the addresses will have 0 in their 
    pgdir entry.
*/
pde_t *pgdir_create(void);

/*
    Navigates the page directory and returns the correspondant page table 
    entry to the argument virtual address. Returns NULL if there is no page 
    table for the address frame
*/
pte_t *pgdir_addr2entry(pdir_t, paddr_t);

/*
    Maps in a page directory all addresses in the ranges ['va' -> 'va+size'] 
    to ['pa' -> 'pa+size'] using the 'permissions' bits for each page table entry.
    Make sure 'permissions' is just 12 bits and that 'pa' and 'va' are aligned 
    to PGSIZE, or this function will panic
*/
void pgdir_map(pdir_t, uint32_t, unsigned long, uint32_t, uint16_t);

/*
    Loads the argument page directory and flushes the TLB. This also enables 
    paging, if it was not set already
*/
void paging_load(pdir_t pgdir);

/*
    Returns the kernel pgdir, a page directory where an identity mapping 
    is setup for every address available
*/
pdir_t paging_kernel_pgdir();

/*
    Returns the address where the space of a page starts
*/
void *page2addr(struct PageInfo *page);

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