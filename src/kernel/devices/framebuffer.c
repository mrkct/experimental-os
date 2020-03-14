#include <stdbool.h>
#include <kernel/arch/i386/paging.h>
#include <kernel/arch/multiboot.h>
#include <kernel/devices/framebuffer.h>
#include <kernel/lib/kassert.h>
#include <kernel/lib/util.h>
#include <kernel/memory/kheap.h>


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
    if (main_buffer.bytesPerPixel != 4) {
        panic(
            "We only support 32 bit pixel depth for now.\n"
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
    const int screenw = dest->width;
    const int screenh = dest->height;
    uint32_t *fb_dest = (uint32_t *) (dest->addr + y * dest->pitch);
    uint32_t *fb_src = (uint32_t *) src->addr;

    for (int i = 0; i < height; i++) {
        if (y+i >= screenh)
            break;
        if (y+i >= 0) {
            for (int j = 0; j < width; j++) {
                if (x+j < 0)
                    continue;
                if (x+j >= screenw)
                    break;

                fb_dest[x+j] = fb_src[j];
            }
        }
        MOVE_PTR(fb_dest, uint32_t, dest->pitch);
        MOVE_PTR(fb_src, uint32_t, src->pitch);
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
    uint32_t *mainb = (uint32_t *) main_buffer.addr;
    uint32_t *doubleb = (uint32_t *) double_buffer.addr;
    const int bpp = main_buffer.bytesPerPixel;
    const unsigned offset = y * main_buffer.pitch + x * bpp;
    
    const int screenw = screen_width();
    const int screenh = screen_height();

    MOVE_PTR(mainb, uint32_t, offset);
    MOVE_PTR(doubleb, uint32_t, offset);

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

                mainb[j] = doubleb[j];
            }
        }
        MOVE_PTR(mainb, uint32_t, main_buffer.pitch);
        MOVE_PTR(doubleb, uint32_t, double_buffer.pitch);
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

Color make_color(unsigned char r, unsigned char g, unsigned char b)
{
    return ((b << 0) & 0xff) | ((g << 8) & 0xff00) | ((r << 16) & 0xff0000);
}