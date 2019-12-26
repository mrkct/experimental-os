#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <kernel/lib/kassert.h>
#include <kernel/memory/kheap.h>
#include <kernel/arch/i386/paging.h>


void *kmalloc(size_t count)
{
    count += sizeof(struct MallocHeader);
    int required_pages = count / PGSIZE;
    if (count % PGSIZE != 0) {
        required_pages++;
    }
    struct PageInfo *page = page_alloc(required_pages);
    struct MallocHeader *head = (struct MallocHeader *) page2addr(page);
    head->magic = MALLOC_MAGIC;
    head->pageInfo = page;
    head->pages = required_pages;

    return (void *) (head + 1);
}

void kfree(void *addr)
{
    struct MallocHeader *head = (struct MallocHeader *) addr;
    head -= 1;
    kassert(head->magic == MALLOC_MAGIC);
    for (int i = 0; i < head->pages; i++) {
        page_free(&(head->pageInfo[i]));
    }
}