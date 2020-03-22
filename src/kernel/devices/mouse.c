#include <kernel/arch/i386/x86.h>
#include <kernel/devices/framebuffer.h>
#include <kernel/devices/mouse.h>
#include <kernel/devices/timer/timer.h>
#include <kernel/lib/kassert.h>
#include <kernel/lib/util.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define MOUSE_STATUS_READ_READY     false
#define MOUSE_STATUS_WRITE_READY    true


static struct MouseStatus status;
static int skip_next = 0;
static bool mouse_initialized = false;

/*
    Polls the status port until
    - If write is true until the 'busy' bit is clear
    - If write is false until the 'ready for read' bit is set

    Returns true when the condition is met, false if a timeout occurs
*/
static bool mouse_wait_for_status(bool write) {
    uint32_t start = timer_get_ticks();
    while (timer_get_ticks() - start < MOUSE_WAIT_TIMEOUT) {
        unsigned char byte = inb(0x64);
        if ( (write && (byte & 0x2) == 0) || (!write && byte & 0x1)) {
            return true;
        }
    }
    return false;
}

/*
    Sends a command to the mouse. 
    Returns 0 on success, -1 if a timeout occurs while waiting for 
    the mouse to be ready
*/
int mouse_send_command(unsigned char command) {
    if (!mouse_wait_for_status(MOUSE_STATUS_WRITE_READY))
        return -1;
    outb(0x64, 0xd4);
    if (!mouse_wait_for_status(MOUSE_STATUS_WRITE_READY))
        return -1;
    outb(0x60, command);

    return 0;
}

/*
    Reads a single byte from the mouse and returns it. 
    Returns 0 if a timeout happens while reading
*/
static unsigned char mouse_read(void) {
    if (!mouse_wait_for_status(MOUSE_STATUS_READ_READY))
        return 0;
    
    return inb(0x60);
}

static void mouse_handle_packets(
    unsigned char flags, 
    unsigned char unsigned_xdelta, 
    unsigned char unsigned_ydelta
)
{
    if (flags & (MOUSE_FLAGS_XOVERFLOW | MOUSE_FLAGS_YOVERFLOW))
        return;

    int xdelta = unsigned_xdelta;
    if (flags & MOUSE_FLAGS_XSIGN)
        xdelta = -1 * (((~unsigned_xdelta) & 0xff) + 1);
        
    
    int ydelta = -1 * unsigned_ydelta;
    if (flags & MOUSE_FLAGS_YSIGN)
        ydelta = (((~unsigned_ydelta) & 0xff) + 1);
    
    const int screenw = screen_width();
    const int screenh = screen_height();
    status = (struct MouseStatus) {
        .connected = true,
        .x = MAX(0, MIN(status.x + xdelta, screenw)), 
        .y = MAX(0, MIN(status.y + ydelta, screenh)), 
        .left = flags & MOUSE_FLAGS_LEFTBTN, 
        .middle = flags & MOUSE_FLAGS_MIDDLEBTN, 
        .right = flags & MOUSE_FLAGS_RIGHTBTN
    };
}

void mouse_wait_ack(void) {
    unsigned char ack = mouse_read();
    if (ack != 0xfa) {
        kprintf("WARN: Didn't receive mouse ACK (%x)\n", ack);
    }
}

int mouse_init(void)
{
    asm volatile("cli");
    status = (struct MouseStatus) {
        .connected = false,
        .x = screen_width() / 2,
        .y = screen_height() / 2, 
        .left = false,
        .right = false, 
        .middle = false
    };

    // Enable the auxiliary mouse device
    mouse_wait_for_status(MOUSE_STATUS_WRITE_READY);
    outb(0x64, 0xA8);

    // Enable the interrupts
    // "Get Compaq Status Byte" command
    mouse_wait_for_status(MOUSE_STATUS_WRITE_READY);
    outb(0x64, 0x20);
    mouse_wait_for_status(MOUSE_STATUS_READ_READY);
    unsigned char statb = (inb(0x60) | 2);
    mouse_wait_for_status(MOUSE_STATUS_WRITE_READY);
    outb(0x64, 0x60);
    mouse_wait_for_status(MOUSE_STATUS_WRITE_READY);
    outb(0x60, statb);

    // Tell the mouse to use default settings
    mouse_send_command(0xF6);
    mouse_wait_ack();

    // Enable the mouse
    mouse_send_command(0xF4);
    mouse_wait_ack();

    mouse_send_command(0xeb);
    mouse_wait_ack();

    mouse_initialized = true;
    asm volatile("sti");

    return 0;
}

struct MouseStatus mouse_status(void)
{
    return status;
}

void __mouse_irq(void)
{
    static enum {
        WAITING_FIRST_PACKET, 
        WAITING_SECOND_PACKET, 
        WAITING_THIRD_PACKET
    } irq_status;
    static unsigned char packets[3];

    if (!mouse_initialized) {
        return;
    }

    unsigned char byte = inb(0x60);
    if (skip_next) {
        skip_next--;
        return;
    }

    switch (irq_status) {
    case WAITING_FIRST_PACKET:
        if (byte & MOUSE_FLAGS_ALWAYS1) {
            irq_status = WAITING_SECOND_PACKET;
            packets[0] = byte;
        }
        break;
    case WAITING_SECOND_PACKET:
        irq_status = WAITING_THIRD_PACKET;
        packets[1] = byte;
        break;
    case WAITING_THIRD_PACKET:
        irq_status = WAITING_FIRST_PACKET;
        packets[2] = byte;
        mouse_handle_packets(packets[0], packets[1], packets[2]);
        break;
    }
}