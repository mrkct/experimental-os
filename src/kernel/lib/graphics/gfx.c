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
    /*
        TODO: Optimize this to avoid all those IFs in the loops
    */
    const int screenw = fb->width;
    const int screenh = fb->height;

    const int bpp = fb->bytesPerPixel;
    if (!outlined) {
        char *addr = (char *) (fb->addr + y * fb->pitch);
        for (int i = 0; i < height; i++) {
            if (y + i >= screenh)
                break;
            if (y + i >= 0) {
                const int end_offset = bpp * (x + width);
                for (int j = 0; j < width; j++) {
                    if (x + j < 0)
                        continue;
                    if (x + j >= screenw)
                        break;
                    SET_RGB(addr[bpp * (x+j)], r, g, b);
                }
            }
            addr += fb->pitch;
        }
    } else {
        char *top = (char *) (fb->addr + y * fb->pitch + bpp * x);
        char *bottom = top + fb->pitch * height;
        for (int xpos = x; xpos < x + width; xpos++) {
            if (xpos >= screenw)
                break;
            if (xpos >= 0) {
                if (y >= 0 && y < screenh)
                    SET_RGB(*top, r, g, b);
                if (y + height >= 0 && y + height < screenh)
                    SET_RGB(*bottom, r, g, b);
            }
            top += bpp;
            bottom += bpp;
        }

        char *left = (char *) fb->addr + fb->pitch * y + bpp * x;
        char *right = left + bpp * width;
        for (int ypos = y; ypos < y + height; ypos++) {
            if (ypos >= screenh)
                break;
            if (ypos > 0) {
                if (x >= 0 && x < screenw)
                    SET_RGB(*left, r, g, b);
                if (x+width >= 0 && x+width <= screenw)
                    SET_RGB(*right, r, g, b);
            }
            
            left += fb->pitch;
            right += fb->pitch;
        }
    }
}