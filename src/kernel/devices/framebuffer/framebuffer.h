#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <kernel/arch/multiboot.h>

struct FrameBuffer {
    void *addr;
    int pitch;
    int bitsPerPixel;
    int width;
    int height;

    int (*draw_pixel)(struct FrameBuffer *, int, int, unsigned char, unsigned char, unsigned char);
};

/*
    Initializes the framebuffer created by the GRUB bootloader. This needs 
    to be called before doing anything on the framebuffer but AFTER paging 
    has been initialized. This maps some pages in the kernel page directory
*/
int framebuffer_init(multiboot_info_t *header);

/*
    Writes an usable framebuffer in the argument points
    Returns 0 on success, -1 otherwise
*/
int framebuffer_get(struct FrameBuffer *fb);

#endif