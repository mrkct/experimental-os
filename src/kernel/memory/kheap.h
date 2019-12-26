#ifndef KHEAP_H
#define KHEAP_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define MALLOC_MAGIC 0x1a2b3c4d

struct MallocHeader {
    uint32_t magic;
    struct PageInfo *pageInfo;
    int pages;
};

void *kmalloc(size_t count);
void kfree(void *);

#endif