#ifndef GFX_H
#define GFX_H

/*
    Sets the color that will be used by all drawing functions from now on
*/
void set_color(unsigned char r, unsigned char g, unsigned char b);

/*
    Returns the currently used color for all drawing functions, RGB
*/
void get_color(unsigned char *r, unsigned char *g, unsigned char *b);

#endif