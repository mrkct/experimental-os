#include <kernel/lib/graphics/gfx.h>
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
    const int bpp = fb->bytesPerPixel;
    if (!outlined) {
        char *addr = (char *) (fb->addr + y * fb->pitch);
        for (int i = 0; i < height; i++) {
            const int end_offset = bpp * (x + width);
            for (int xpos = bpp * x; xpos < end_offset; xpos += bpp) {
                SET_RGB(addr[xpos], r, g, b);
            }
            addr += fb->pitch;
        }
    } else {
        char *top = (char *) (fb->addr + y * fb->pitch + bpp * x);
        char *bottom = top + fb->pitch * height;
        for (int xpos = x; xpos < x + width; xpos++) {
            SET_RGB(*top, r, g, b);
            SET_RGB(*bottom, r, g, b);
            top += bpp;
            bottom += bpp;
        }

        char *left = (char *) fb->addr + fb->pitch * y + bpp * x;
        char *right = left + bpp * width;
        for (int ypos = y; ypos < y + height; ypos++) {
            SET_RGB(*left, r, g, b);
            SET_RGB(*right, r, g, b);
            left += fb->pitch;
            right += fb->pitch;
        }
    }
}