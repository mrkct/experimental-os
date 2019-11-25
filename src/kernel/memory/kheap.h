#ifndef KHEAP_H
#define KHEAP_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

struct Interval {
    char *from;
    char *end;
    struct Interval *next;
};

struct UsedMemoryHeader {
    uint32_t magic;
    uint32_t size;
};

void interval_insert(char *, char *);
void *interval_alloc(size_t, bool);
void interval_defragment();
void *kmalloc(size_t);
void kfree(void *);
void kmalloc_init(char *, uint32_t);

#endif