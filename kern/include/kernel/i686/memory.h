#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <kernel/i686/multiboot.h>

#define PGSIZE      4096
#define PGSHIFT     12


struct PageInfo {
    bool reserved;
    int references;
    struct PageInfo *nextfree;
};

uint32_t get_total_memory();
void *boot_alloc(size_t);
void pages_init();
uint32_t multiboot_get_memory(multiboot_info_t*, uint32_t);
void memory_init(multiboot_info_t*, uint32_t);
void multiboot_detect_available_pages(multiboot_info_t*);

struct PageInfo *page_alloc();
void page_free(struct PageInfo*);


#endif