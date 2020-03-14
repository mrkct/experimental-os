#include <stdbool.h>
#include <kernel/gui/window.h>
#include <kernel/lib/graphics/gfx.h>
#include <kernel/lib/graphics/text.h>
#include <kernel/lib/kassert.h>
#include <kernel/memory/kheap.h>
#include <klibc/string.h>


struct Window *window_create(char *title, int x, int y, int width, int height)
{
    // TODO: Actually return NULL instead of panicking on "not enough memory"
    struct Window *w = kmalloc(sizeof(struct Window));
    kassert(w != NULL);
    const int title_length = strlen(title);
    w->title = kmalloc(title_length+1);
    kassert(w->title != NULL);
    strcpy(w->title, title);

    w->x = x;
    w->y = y;
    w->fb = fb_alloc(width, height);
    w->flags = WINDOW_UPDATED | WINDOW_MOVED;
    kassert(w->fb != NULL);

    return w;
}

void window_free(struct Window *window)
{
    kfree(window->title);
    fb_free(window->fb);
    kfree(window);
}

void draw_window(struct FrameBuffer *fb, struct Window *window)
{
    // save the current color to restore it later
    Color old_color = get_color();
    Color window_bar = make_color(
        WINDOW_BAR_COLOR_R, WINDOW_BAR_COLOR_G, WINDOW_BAR_COLOR_B
    );
    fill_rect(
        fb, 
        window->x, window->y, 
        window->fb->width, WINDOW_BAR_HEIGHT, 
        window_bar
    );
    draw_rect(
        fb, 
        window->x, window->y, 
        window->fb->width, WINDOW_BAR_HEIGHT, 
        COLOR_WHITE
    );
    draw_text(fb, window->x + 8, window->y + 4, window->title);
    set_color(old_color);
    
    fb_blit(
        fb, window->fb, 
        window->x, window->y + WINDOW_BAR_HEIGHT + 1, 
        window->fb->width, window->fb->height
    );
}