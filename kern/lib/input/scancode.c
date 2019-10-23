#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <lib/input/scancode.h>
#include <kernel/i686/x86.h>


struct ScancodeQueue scancodeQueue = { 0 };

/*
    Adds the argument scancode to the global scancodes queue. 
    Before adding you should the queue is not full with ScancodeQueue_empty 
    Returns:
        0 on success
        -E_SCANCODEQ_FULL when the queue is full
*/
int ScancodeQueue_add(Scancode scancode)
{
    if (scancodeQueue.size == SCANCODEQ_SIZE) {
        return -E_SCANCODEQ_FULL;
    }
    int newindex = (scancodeQueue.from + scancodeQueue.size) % SCANCODEQ_SIZE;
    scancodeQueue.data[newindex] = scancode;
    scancodeQueue.size++;

    return 0;
}

/*
    Reads one scancode and puts it in the argument. Before calling this check 
    the queue is not empty.
    Returns:
        0 on success
        -E_SCANCODEQ_EMPTY when there is nothing that can be returned
*/
int ScancodeQueue_read(Scancode *out)
{
    if (ScancodeQueue_empty()) {
        return -E_SCANCODEQ_EMPTY;;
    }
    *out = scancodeQueue.data[scancodeQueue.from];
    scancodeQueue.size--;
    scancodeQueue.from = (scancodeQueue.from + 1) % SCANCODEQ_SIZE;

    return 0;
}

/*
    Returns whenever the scancode queue is empty
*/
bool ScancodeQueue_empty()
{
    return scancodeQueue.size == 0;
}

/*
    Returns whenever the scancode queue is full
*/
bool ScancodeQueue_full()
{
    return scancodeQueue.size == SCANCODEQ_SIZE;
}