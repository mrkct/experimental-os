#ifndef GFX_H
#define GFX_H

#include <kernel/devices/framebuffer.h>
#include <stdbool.h>

/*
    Sets the color that will be used by all drawing functions from now on
*/
void set_color(Color);

/*
    Returns the currently used color for all drawing functions, RGB
*/
Color get_color(void);

/*
    Draws the outline of a rectangle on a framebuffer with the given sizes 
    and color
*/
void draw_rect(struct FrameBuffer *, int, int, int, int, Color);

/*
    Draws a filled rectangle on a framebuffer with the given sizes and color
*/
void fill_rect(struct FrameBuffer *, int, int, int, int, Color);


#define COLOR_WHITE     0x00ffffff
#define COLOR_BLACK     0x00000000
#define COLOR_RED       0x00ff0000
#define COLOR_GREEN     0x0000ff00
#define COLOR_BLUE      0x000000ff
#define COLOR_YELLOW    0x00ffff00
#define COLOR_AQUA      0x0000ffff
#define COLOR_PURPLE    0x00ff00ff

#endif