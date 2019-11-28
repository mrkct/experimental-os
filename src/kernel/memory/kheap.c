#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <kernel/lib/kassert.h>
#include <kernel/memory/kheap.h>


struct Interval *interval_list;

/*
    Initializes the kernel heap allocator. freespace is a pointer to the 
    memory space that will be used as the kernel heap and size is the size 
    of the memory space in bytes.
*/
void kmalloc_init(char *freespace, uint32_t size)
{
    interval_insert(freespace, freespace+size);
}

/*
    Tries to merge a memory interval to an already free one. If if cannot be 
    done it adds the interval to the free intervals list
*/
void interval_insert(char *from, char *end)
{
    // Before adding a new entry to the list we check if we can merge this
    // interval to another
    struct Interval *i = interval_list;
    while (i) {
        if (end == i->from) {
            i->from = from;
            return;
        }
        if (i->end == from) {
            i->end = end;
            return;
        }
        i = i->next;
    }
    struct Interval *interval = (struct Interval *) from;
    interval->from = from;
    interval->end = end;
    interval->next = interval_list;
    interval_list = interval;
}

/*
    Tries to find an interval of memory of at least the requested size.
    If found it shrinks it and return an address of free memory, otherwise 
    if the try_defragment argument is true and enough free memory is available 
    in the system it merges consecutive intervals and tries again. If it fails 
    again returns NULL
*/

void *interval_alloc(size_t requested, bool try_defragment)
{
    struct Interval *interval = interval_list;
    struct Interval *previous = NULL;
    uint32_t total_free_memory = 0;
    while (interval) {
        int available = (int) (interval->end - interval->from);
        total_free_memory += total_free_memory;
        if (available - sizeof(struct Interval) > requested) {
            interval->end -= requested;
            return (void*) interval->end;
        } else if (available >= requested) {
            if (previous != NULL) {
                previous->next = interval->next;
            } else {
                interval_list = interval->next;
            }
            return (void*) interval->from;
        }
        previous = interval;
        interval = interval->next;
    }

    if (try_defragment && total_free_memory >= requested) {
        interval_defragment();
        return interval_alloc(requested, false);
    } else {
        return NULL;
    }
}

/*
    Merges all adjacents memory intervals that were split because of 
    calls to free.
*/
void interval_defragment()
{
    struct Interval *interval = interval_list;
    struct Interval *interval2;

    /*
        We do a first pass and attach the intervals with adjacents 
        starting/ending addresses into one. We always extend the end, as we 
        want the Interval struct to be at the beginning of the memory segment. 
        Each time a merge happens one of the 2 segments need to be deleted. We 
        set the from address = to the end address and do another pass after to 
        delete all those intervals
    */
    while (interval) {
        interval2 = interval_list;
        while (interval2) {
            if (interval->from == interval2->end) {
                interval2->end = interval->end;
                // Set 'interval' as empty
                interval->from = interval->end;
            } else if (interval->end == interval2->from) {
                interval->end = interval2->end;
                // Set 'interval2' as empty
                interval2->from = interval2->end;
            }
            interval2 = interval2->next;
        }

        interval = interval->next;
    }

    interval = interval_list;
    struct Interval *previous = NULL;
    while (interval) {
        if (interval->from == interval->end) {
            if (interval == interval_list) {
                interval_list = interval->next;
            } else {
                previous->next = interval->next;
            }
        }
        previous = interval;
        interval = interval->next;
    }
}

#define KMALLOC_MAGIC 0xa1b2c3d4

/*
    Tries to alloc a memory space of the requested size. Returns NULL if it 
    fails.
    WARNING: This allocates from the kernel heap space, this should not be 
    used outside of the kernel.
*/
void *kmalloc(size_t requested)
{
    size_t needed = requested + sizeof(struct UsedMemoryHeader);
    void *allocated = interval_alloc(needed, true);
    if (allocated == NULL)
        return NULL;
     
    struct UsedMemoryHeader *header = (struct UsedMemoryHeader *) allocated;
    header->magic = KMALLOC_MAGIC;
    header->size = requested;

    return (void*) &header[1];
}

#define KFREE_DEFRAGMENT_CALLS 10

/*
    Frees a memory space allocated with kmalloc
*/
void kfree(void *allocated)
{
    struct UsedMemoryHeader *header = (struct UsedMemoryHeader *) allocated;
    header -= 1;
    kassert(header->magic == KMALLOC_MAGIC);
    interval_insert((char *) header, (char*) header + header->size + sizeof(struct UsedMemoryHeader));
    
    static int calls = 0;
    if (++calls > KFREE_DEFRAGMENT_CALLS) {
        interval_defragment();
        calls = 0;
    }
}