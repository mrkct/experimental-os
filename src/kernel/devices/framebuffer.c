#include <stdbool.h>
#include <kernel/lib/kassert.h>
#include <kernel/arch/i386/paging.h>
#include <kernel/memory/kheap.h>
#include <kernel/arch/multiboot.h>
#include <kernel/devices/framebuffer.h>


struct FrameBuffer main_buffer;
struct FrameBuffer double_buffer;

int fb_init(multiboot_info_t *header)
{
    pdir_t kernel_pgdir = paging_kernel_pgdir();
    if (kernel_pgdir == NULL) {
        panic("before calling framebuffer_init you need to setup paging!");
    }

    void *addr = (void *) (header->framebuffer_addr & 0x00000000ffffffff);
    main_buffer = (struct FrameBuffer) {
        .addr = addr, 
        .pitch = header->framebuffer_pitch, 
        .bytesPerPixel = header->framebuffer_bpp / 8, 
        .width = header->framebuffer_width, 
        .height = header->framebuffer_height
    };
    if (main_buffer.bytesPerPixel != 3) {
        panic(
            "We only support 3 bytes per pixel depth for now.\n"
            "Change the value in kernel/arch/i386/boot.S"
        );
    }

    unsigned fb_size = main_buffer.pitch * main_buffer.height;

    pgdir_map(
        kernel_pgdir, 
        ROUNDDOWN((uint32_t) main_buffer.addr, PGSIZE), 
        ROUNDUP(fb_size, PGSIZE), 
        ROUNDDOWN((uint32_t) main_buffer.addr, PGSIZE), 
        PG_PRESENT | PG_USER | PG_RW
    );

    void *allocated = kmalloc(fb_size);
    if (allocated == NULL) {
        panic("could not allocate for double buffering");
        return -1;
    }
    double_buffer = main_buffer;
    double_buffer.addr = allocated;

    return 0;
}

struct FrameBuffer *fb_alloc(int width, int height)
{
    unsigned size = width * main_buffer.bytesPerPixel * height;
    void *addr = kmalloc(size);
    if (addr == NULL) {
        return NULL;
    }
    struct FrameBuffer *fb = kmalloc(sizeof(struct FrameBuffer));
    if (fb == NULL) {
        kfree(addr);
        return NULL;
    }

    fb->bytesPerPixel = main_buffer.bytesPerPixel;
    fb->addr = addr;
    fb->width = width;
    fb->height = height;
    fb->pitch = width * main_buffer.bytesPerPixel;

    return fb;
}

void fb_free(struct FrameBuffer *fb)
{
    kassert(fb != NULL);
    kfree(fb->addr);
    kfree(fb);
}

void fb_blit(
    struct FrameBuffer *dest, struct FrameBuffer *src, 
    int x, int y, int width, int height
)
{
    /*
        TODO: Rewrite this to avoid checking IFs at every iteration. 
        This is terrible
    */
    const int bpp = dest->bytesPerPixel;
    const int screenw = dest->width;
    const int screenh = dest->height;
    char *fb_dest = (char *) dest->addr;
    char *fb_src = (char *) src->addr;

    fb_dest += y * dest->pitch;
    for (int i = 0; i < height; i++) {
        if (y+i >= screenh)
            break;
        if (y+i >= 0) {
            for (int j = 0; j < width; j++) {
                if (x+j < 0)
                    continue;
                if (x+j >= screenw)
                    break;
                const unsigned dest_offset = bpp * (x+j);
                const unsigned src_offset = bpp * j;

                fb_dest[dest_offset] = fb_src[src_offset];
                fb_dest[dest_offset + 1] = fb_src[src_offset + 1];
                fb_dest[dest_offset + 2] = fb_src[src_offset + 2];
            }
        }
        fb_dest += dest->pitch;
        fb_src += src->pitch;
    }
}

struct FrameBuffer *get_screen_framebuffer(void)
{
    return &double_buffer;
}

int screen_width(void)
{
    return main_buffer.width;
}

int screen_height(void)
{
    return main_buffer.height;
}

void screen_update(int x, int y, int width, int height)
{
    char *mainb = (char *) main_buffer.addr;
    char *doubleb = (char *) double_buffer.addr;
    const int bpp = main_buffer.bytesPerPixel;
    const unsigned offset = y * main_buffer.pitch + x * bpp;
    
    const int screenw = screen_width();
    const int screenh = screen_height();

    mainb += offset;
    doubleb += offset;

    /*
        TODO: Optimize this, all those IFs are terrible for performance
    */
    for (int i = 0; i < height; i++) {
        if (y + i >= screenh)
            break;
        
        if (y + i >= 0) {
            for (int j = 0; j < width; j++) {
                if (x + j < 0)
                    continue;
                if (x + j >= screenw)
                    break;

                const unsigned off = bpp * j;
                mainb[off]     = doubleb[off];
                mainb[off + 1] = doubleb[off + 1];
                mainb[off + 2] = doubleb[off + 2];
            }
        }
        mainb += main_buffer.pitch;
        doubleb += double_buffer.pitch;
    }
}

void screen_refresh(void)
{
    screen_update(0, 0, screen_width(), screen_height());
}

int fb_offset(struct FrameBuffer *fb, int x, int y)
{
    return fb->pitch * y + fb->bytesPerPixel * x;
}

void setpixel(
    char *pixel, 
    unsigned char r, unsigned char g, unsigned char b
)
{
    pixel[0] = b; 
    pixel[1] = g;
    pixel[2] = r;
}