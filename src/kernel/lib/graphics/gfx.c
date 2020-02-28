#include <kernel/lib/graphics/gfx.h>

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