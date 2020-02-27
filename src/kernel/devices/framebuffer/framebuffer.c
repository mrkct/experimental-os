#include <kernel/devices/framebuffer/framebuffer.h>
#include <kernel/arch/i386/paging.h>
#include <kernel/lib/kassert.h>
#include <kernel/arch/multiboot.h>


static struct FrameBuffer main_fb;

int framebuffer_init(multiboot_info_t *header)
{
    pdir_t kernel_pgdir = paging_kernel_pgdir();
    if (kernel_pgdir == NULL) {
        panic("before calling framebuffer_init you need to setup paging!");
    }

    main_fb = (struct FrameBuffer) {
        .addr = header->framebuffer_addr, 
        .pitch = header->framebuffer_pitch, 
        .bitsPerPixel = header->framebuffer_bpp, 
        .width = header->framebuffer_width, 
        .height = header->framebuffer_height
    };

    unsigned fb_size = main_fb.pitch * main_fb.height;

    pgdir_map(
        kernel_pgdir, 
        ROUNDDOWN(main_fb.addr, PGSIZE), 
        ROUNDUP(fb_size, PGSIZE), 
        ROUNDDOWN(main_fb.addr, PGSIZE), 
        PG_PRESENT | PG_USER | PG_RW
    );

    return 0;
}

int framebuffer_get(struct FrameBuffer *fb)
{
    *fb = main_fb;

    return 0;
}