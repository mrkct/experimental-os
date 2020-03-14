#include <stdint.h>
#include <kernel/lib/graphics/gfx.h>
#include <kernel/lib/util.h>
#include <kernel/devices/framebuffer.h>


#define SET_RGB(x, r, g, b) {(&(x))[0] = b; (&(x))[1] = g; (&(x))[2] = r;}

static unsigned char def_r = 255, def_g = 255, def_b = 255;

void set_color(unsigned char r, unsigned char g, unsigned char b)
{
    def_r = r;
    def_g = g;
    def_b = b;
}

void get_color(unsigned char *r, unsigned char *g, unsigned char *b)
{
    *r = def_r;
    *g = def_g;
    *b = def_b;
}

void draw_rectangle(
    struct FrameBuffer *fb, 
    int x, int y, 
    int width, int height, 
    unsigned char r, unsigned char g, unsigned char b, 
    bool outlined
)
{
    /*
        TODO: Optimize this to avoid all those IFs in the loops
    */
    const int screenw = fb->width;
    const int screenh = fb->height;

    Color color = make_color(r, g, b);
    const int bpp = fb->bytesPerPixel;
    if (!outlined) {
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
    } else {
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
}