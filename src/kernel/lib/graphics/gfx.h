#ifndef GFX_H
#define GFX_H

#include <kernel/devices/framebuffer.h>
#include <stdbool.h>

/*
    Sets the color that will be used by all drawing functions from now on
*/
void set_color(unsigned char r, unsigned char g, unsigned char b);

/*
    Returns the currently used color for all drawing functions, RGB
*/
void get_color(unsigned char *r, unsigned char *g, unsigned char *b);


void draw_rectangle(struct FrameBuffer *, int, int, int, int, unsigned char, unsigned char, unsigned char, bool);

// void draw_rect(...);
// void fill_rect(...);

#endif