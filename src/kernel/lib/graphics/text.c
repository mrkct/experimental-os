#include <stdbool.h>
#include <kernel/lib/graphics/gfx.h>
#include <kernel/devices/framebuffer.h>
#include <kernel/lib/graphics/text.h>
#include <kernel/lib/kassert.h>


static char fontdata[] = {
    #include <kernel/lib/graphics/fdump.h>
};

/*
    Returns the offset in a PSF1 Font File from where the data for the given 
    character starts
*/
static int psf_charoffset(char *font, char c) {
    struct PSF1Header *header = (struct PSF1Header *) font;
    kassert(header->magic == PSF1_MAGIC);
    return sizeof(struct PSF1Header) + ( (int) c * header->charsize);
}

static int psf_charheight(char *font) {
    struct PSF1Header *header = (struct PSF1Header *) font;
    kassert(header->magic == PSF1_MAGIC);
    return header->charsize;;
}

int draw_char(struct FrameBuffer *fb, int x, int y, char c)
{
    const int screenw = fb->width;
    const int screenh = fb->height;
    int charoffset = psf_charoffset(fontdata, c);
    if (charoffset < 0)
        return -1;
    int charheight = psf_charheight(fontdata);
    /*
        TODO: Optimize this to avoid all these IFs in the loop
    */
    Color color = get_color();
    for (int row = 0; row < charheight; row++) {
        if (y+row < 0)
            continue;
        if (y+row >= screenh)
            break;
        for (int j = 7; j >= 0; j--) {
            if (x + (7 - j) < 0)
                continue;
            if (x + (7 - j) >= screenw)
                break;
            if ((fontdata[charoffset + row] >> j) & 0x1) {
                int offset = fb_offset(fb, x + (7 - j), y + row);
                uint32_t *addr = (uint32_t *) (fb->addr + offset);
                *addr = color;
            }
        }
    }

    return 0;
}

int draw_text(struct FrameBuffer *fb, int x, int y, const char *text)
{
    for (int i = 0; text[i]; i++) {
        if (draw_char(fb, x + 12 * i, y, text[i]) != 0)
            return -1;
    }

    return 0;
}