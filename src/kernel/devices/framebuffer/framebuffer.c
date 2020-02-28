#include <kernel/devices/framebuffer/framebuffer.h>
#include <kernel/arch/i386/paging.h>
#include <kernel/lib/kassert.h>
#include <kernel/arch/multiboot.h>


static struct FrameBuffer main_fb;

/*
    Draws a single pixel onto the framebuffer. 
    Returns 0 on success
*/
static int draw_pixel(
    struct FrameBuffer *fb, 
    int x, int y, 
    unsigned char r, unsigned char g, unsigned char b
)
{
    char *addr = (char *) fb->addr;
    int offset = y * fb->pitch + 3 * x;
    addr[offset] = b;
    addr[offset + 1] = g;
    addr[offset + 2] = r;

    return 0;
}

int framebuffer_init(multiboot_info_t *header)
{
    pdir_t kernel_pgdir = paging_kernel_pgdir();
    if (kernel_pgdir == NULL) {
        panic("before calling framebuffer_init you need to setup paging!");
    }

    main_fb = (struct FrameBuffer) {
        .addr = (void *) header->framebuffer_addr, 
        .pitch = header->framebuffer_pitch, 
        .bitsPerPixel = header->framebuffer_bpp, 
        .width = header->framebuffer_width, 
        .height = header->framebuffer_height,
        .draw_pixel = &draw_pixel
    };

    unsigned fb_size = main_fb.pitch * main_fb.height;

    pgdir_map(
        kernel_pgdir, 
        ROUNDDOWN((uint32_t) main_fb.addr, PGSIZE), 
        ROUNDUP(fb_size, PGSIZE), 
        ROUNDDOWN((uint32_t) main_fb.addr, PGSIZE), 
        PG_PRESENT | PG_USER | PG_RW
    );

    return 0;
}

int framebuffer_get(struct FrameBuffer *fb)
{
    *fb = main_fb;

    return 0;
}