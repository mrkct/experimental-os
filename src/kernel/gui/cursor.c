#include <kernel/devices/framebuffer.h>
#include <kernel/gui/cursor.h>
#include <kernel/lib/graphics/gfx.h>
#include <kernel/lib/util.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


/*
    This contains a list of values representing an image of the cursor
    The first 2 values are width and height
    Then follows width*height numbers each representing a pixel.
    0 - Black, 1 - White, 2 - Transparent
*/
static unsigned char cursor_data[] = {
    #include <kernel/gui/cursor_data.h>
};


void draw_cursor(struct FrameBuffer *fb, int x, int y)
{
    const int width = cursor_data[0];
    const int height = cursor_data[1];

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            const unsigned dataoffset = 2 + (i * width + j);
            if (cursor_data[dataoffset] == 0) {
                put_pixel(fb, x + j, y + i, COLOR_BLACK);
            } else if (cursor_data[dataoffset] == 1) {
                put_pixel(fb, x + j, y + i, COLOR_WHITE);
            }
        }
    }
}

int cursor_width(void)
{
    return cursor_data[0];
}

int cursor_height(void)
{
    return cursor_data[1];
}