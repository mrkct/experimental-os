#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <kernel/memory/kheap.h>
#include <kernel/gui/compositor.h>
#include <kernel/gui/window.h>
#include <kernel/lib/kassert.h>
#include <kernel/devices/framebuffer.h>


struct WindowID {
    struct Window *window;
    struct WindowID *next;
};

/*
    This list represents the windows that need to be drawn. This is guaranteed 
    to be always ordered in a descending depth order. 
    This means the first items is the last one that needs to be drawn 
    (the window below all the others) and the last the one above all others. 

*/
static struct {
    struct WindowID *head;
    struct WindowID *tail;
    int size;
} drawlist = {0};

/*
    Adds a window to the drawlist at the end 
    (therefore it will be drawn above all others). 
    Returns 0 on success, -1 if failed to allocated a WindowID struct
*/
static int drawlist_add(struct Window *window)
{
    struct WindowID *w_id = kmalloc(sizeof(struct WindowID));
    if (w_id == NULL)
        return -1;
    
    w_id->window = window;
    w_id->next = NULL;

    if (drawlist.tail == NULL) {
        drawlist.head = w_id;
        drawlist.tail = w_id;
        drawlist.size = 1;
    } else {
        drawlist.tail->next = w_id;
        drawlist.tail = w_id;
        drawlist.size++;
    }

    return 0;
}

/*
    Moves a window last in the list so that it gets drawn above all others. 
    Returns 0 on success, -1 if the window could not be found
*/
static int drawlist_focus(struct Window *window) {
    if (drawlist.tail->window == window)
        return 0;
    
    struct WindowID *w_id = drawlist.head;
    while (w_id != NULL) {
        if (w_id->next != NULL && w_id->next->window == window) {
            struct WindowID *curr = w_id;
            struct WindowID *wind = w_id->next;
            curr->next = wind->next;
            wind->next = NULL;
            drawlist.tail->next = wind;
            drawlist.tail = wind;
            return 0;
        }
        w_id = w_id->next;
    }

    return -1;
}

/*
    Removes a window from the drawlist completely. Note that this does not 
    free the actual window itself, just the corresponding WindowID struct.
    Returns 0 on success, -1 if the window could not be found
*/
static int drawlist_remove(struct Window *window) {
    if (drawlist.head == drawlist.tail && drawlist.head->window == window) {
        drawlist.head = drawlist.tail = NULL;
        drawlist.size = 0;
        
        return 0;
    }

    struct WindowID *w_id = drawlist.head;
    while (w_id != NULL) {
        if (w_id->next != NULL && w_id->next->window == window) {
            struct WindowID *curr = w_id;
            struct WindowID *to_remove = w_id->next;
            curr->next = to_remove->next;
            
            if (drawlist.tail == to_remove)
                drawlist.tail = curr;
            kfree(to_remove);
            drawlist.size--;
            
            return 0;
        }
        w_id = w_id->next;
    }

    return -1;
}

int register_window(struct Window *window)
{
    return drawlist_add(window);
}

int unregister_window(struct Window *window)
{
    return drawlist_remove(window);
}

int focus_window(struct Window *window)
{
    return drawlist_focus(window);
}

void __compositor_main(void)
{
    struct FrameBuffer *screen = get_screen_framebuffer();
    while (true) {
        struct WindowID *id = drawlist.head;
        bool needs_redraw = false;
        while (id != drawlist.tail) {
            if (id->window->flags & WINDOW_UPDATED) {
                needs_redraw = true;
            }
            if (needs_redraw) {
                draw_window(screen, id->window);
                id->window->flags = id->window->flags & ~(WINDOW_UPDATED | WINDOW_MOVED);
            }
            id = id->next;
        }
        /*
            Since the most common case is that the focused window is updated 
            we handle it in a special way so that we only redraw its portion 
            of the screen
        */
        struct WindowID *last = drawlist.tail;
        if (last == NULL)
            continue;
        if (last->window->flags & WINDOW_UPDATED) {
            last->window->flags = last->window->flags & ~(WINDOW_UPDATED | WINDOW_MOVED);
            draw_window(screen, last->window);
            if (needs_redraw) {
                screen_refresh();
            } else {
                screen_update(
                    last->window->x, 
                    last->window->y, 
                    last->window->fb->width, 
                    last->window->fb->height + WINDOW_BAR_HEIGHT);
            }
        } else if (needs_redraw) {
            screen_refresh();
        }
    }
}