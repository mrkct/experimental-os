#ifndef CURSOR_H
#define CURSOR_H

#include <kernel/devices/framebuffer.h>

/*
    Draws a mouse cursor on the framebuffer at a given position
*/
void draw_cursor(struct FrameBuffer *framebuffer, int x, int y);

#endif