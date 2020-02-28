#ifndef TEXT_H
#define TEXT_H

#include <stdint.h>
#include <kernel/devices/framebuffer/framebuffer.h>

/*
    A PSF1 Font File has the following structure:
    - Header
    A series of bytes. Each group of 'charsize' bytes represents a single 
    character. The characters are ordered according to ascii. Each byte 
    represents a row of a character. Each '1' is a white pixel, '0' is black
*/
struct PSF1Header {
        #define PSF1_MAGIC	0x0436
    uint16_t magic;
        
        #define PSF1_MODE512    0x01
        #define PSF1_MODEHASTAB 0x02
        #define PSF1_MODEHASSEQ 0x04
        #define PSF1_MAXMODE    0x05
    uint8_t mode;
    uint8_t charsize; // the heigth of a single character
};

/*
    Draws a single character using the currently selected color on the 
    argument framebuffer at a given position. 
    Returns 0 on success, -1 if the current font doesn't have a drawable 
    representation for that character
*/
int draw_char(struct FrameBuffer *fb, int x, int y, char c);

/*
    Draws a string using the currently selected color at a position on the
    argument framebuffer, at a given position. This does no wrapping around 
    or any text transformation. 
    Returns 0 on success, -1 if any character has not been drawn because of an 
    error with draw_char
*/
int draw_text(struct FrameBuffer *fb, int x, int y, const char *text);

#endif