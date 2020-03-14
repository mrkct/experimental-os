#include <stdint.h>
#include <kernel/lib/graphics/gfx.h>
#include <kernel/lib/util.h>
#include <kernel/devices/framebuffer.h>


static Color global_color = 0xffffffff;

void set_color(Color color)
{
    global_color = color;
}

Color get_color(void)
{
    return global_color;
}

void draw_rect(
    struct FrameBuffer *fb, 
    int x, int y, 
    int width, int height, 
    Color color
)
{
    /*
        TODO: Optimize this to avoid all those IFs in the loops
    */
    const int screenw = fb->width;
    const int screenh = fb->height;
    const int bpp = fb->bytesPerPixel;
    
    uint32_t *top = (uint32_t *) (fb->addr + y * fb->pitch + bpp * x);
    uint32_t *bottom = top;
    MOVE_PTR(bottom, uint32_t, fb->pitch * height);
    for (int xpos = x; xpos < x + width; xpos++) {
        if (xpos >= screenw)
            break;
        if (xpos >= 0) {
            if (y >= 0 && y < screenh)
                *top = color;
            if (y + height >= 0 && y + height < screenh)
                *bottom = color;
        }
        top++;
        bottom++;
    }

    uint32_t *left = (uint32_t *) (fb->addr + fb->pitch * y + bpp * x);
    uint32_t *right = left;
    MOVE_PTR(right, uint32_t, bpp * width);
    for (int ypos = y; ypos < y + height; ypos++) {
        if (ypos >= screenh)
            break;
        if (ypos > 0) {
            if (x >= 0 && x < screenw)
                *left = color;
            if (x+width >= 0 && x+width <= screenw)
                *right = color;
        }
        
        MOVE_PTR(left, uint32_t, fb->pitch);
        MOVE_PTR(right, uint32_t, fb->pitch);
    }
}

void fill_rect(
    struct FrameBuffer *fb, 
    int x, int y, 
    int width, int height, 
    Color color
)
{
    /*
        TODO: Optimize this to avoid all those IFs in the loops
    */
    const int screenw = fb->width;
    const int screenh = fb->height;

    uint32_t *addr = (uint32_t *) (fb->addr + y * fb->pitch);
    for (int i = 0; i < height; i++) {
        if (y + i >= screenh)
            break;
        if (y + i >= 0) {
            for (int j = 0; j < width; j++) {
                if (x + j < 0)
                    continue;
                if (x + j >= screenw)
                    break;
                addr[x+j] = color;
            }
        }
        MOVE_PTR(addr, uint32_t, fb->pitch);
    }
}