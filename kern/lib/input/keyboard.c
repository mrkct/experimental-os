#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <lib/input/scancode.h>
#include <kernel/i686/x86.h>
#include <kernel/kassert.h>


/*
    Called by the interrupt handler every time a keyboard scancode is received.
    Do not call this outside the interrupt handler
*/
void __keyboard_irq()
{
    kassert(!ScancodeQueue_full());
    Scancode read = inb(0x60);
    ScancodeQueue_add(read);
}