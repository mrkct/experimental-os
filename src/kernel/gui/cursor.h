#ifndef CURSOR_H
#define CURSOR_H

#include <kernel/devices/framebuffer.h>

/*
    Returns the width of the cursor image
*/
int cursor_width(void);

/*
    Returns the height of the cursor image
*/
int cursor_height(void);

/*
    Draws a mouse cursor on the framebuffer at a given position
*/
void draw_cursor(struct FrameBuffer *framebuffer, int x, int y);

#endif