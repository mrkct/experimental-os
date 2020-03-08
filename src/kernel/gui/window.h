#ifndef WINDOW_H
#define WINDOW_H

#include <kernel/devices/framebuffer.h>

#define WINDOW_BAR_HEIGHT   24

#define WINDOW_BAR_COLOR_R  0
#define WINDOW_BAR_COLOR_G  0
#define WINDOW_BAR_COLOR_B  255


#define WINDOW_UPDATED         0x1
#define WINDOW_MOVED           0x2

struct Window {
    char *title;
    int x, y;
    struct FrameBuffer *fb;

    int flags;
};

/*
    Allocates a new window with a framebuffer of the given size. 
    Returns a pointer to the newly allocated window on success, NULL otherwise
*/
struct Window *window_create(char *title, int x, int y, int width, int height);

/*
    Frees a previously allocated window
*/
void window_free(struct Window *window);

/*
    Draws a window and its framebuffer on another framebuffer. Note that 
    this does NOT set the update_* flags to false
*/
void draw_window(struct FrameBuffer *fb, struct Window *window);

#endif