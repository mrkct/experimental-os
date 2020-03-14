#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdint.h>
#include <kernel/arch/multiboot.h>


struct FrameBuffer {
    void *addr;
    int width;
    int height;
    int pitch, bytesPerPixel;
};

int fb_init(multiboot_info_t *header);

struct FrameBuffer *fb_alloc(int width, int height);

void fb_free(struct FrameBuffer *fb);

/*
    Copies an area from the 'src' framebuffer to the 'dest' framebuffer. 
    The area is defined as a rectangle from the 'src' framebuffer that is
    copied as a whole, with no transformations

    TODO: Allow to copy out-of-bounds
*/
void fb_blit(
    struct FrameBuffer *dest, struct FrameBuffer *src, 
    int x, int y, int width, int height
);

struct FrameBuffer *get_screen_framebuffer(void);

/*
    Returns the screen width in pixels. This is a constant
*/
int screen_width(void);

/*
    Returns the screen height in pixels. This is a constant
*/
int screen_height(void);

/*
    Updates an area of the screen, causing a redraw
*/
void screen_update(int x, int y, int width, int height);

/*
    Updates the whole screen. This is equivalent to calling 
    screen_update(0, 0, screen_width(), screen_height())
*/
void screen_refresh(void);

/*
    Returns the offset in the framebuffer from which the pixel at a given 
    positions starts.
    Careful: do not recalculate repeatedly the offset for pixel close to each 
    other. Do it once and add fb->bytesPerPixel to move it right and add 
    fb->pitch to move it 1 row down
    Returns -1 if the pixel is out of bounds
*/
int fb_offset(struct FrameBuffer *fb, int x, int y);

typedef uint32_t Color;

/*
    Returns the color value made with the 3 components
*/
Color make_color(unsigned char r, unsigned char g, unsigned char b);

#endif