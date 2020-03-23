#include <kernel/devices/framebuffer.h>
#include <kernel/devices/mouse.h>
#include <kernel/gui/compositor.h>
#include <kernel/gui/cursor.h>
#include <kernel/gui/window.h>
#include <kernel/lib/graphics/gfx.h>
#include <kernel/lib/kassert.h>
#include <kernel/lib/util.h>
#include <kernel/memory/kheap.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


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

static void set_background(struct Window *window)
{
    struct WindowID *id = kmalloc(sizeof(struct WindowID));
    id->next = drawlist.head;
    id->window = window;
    drawlist.head = id;
    drawlist.size++;
}

void __compositor_main(void)
{
    struct FrameBuffer *screen = get_screen_framebuffer();
    struct Window *background = window_create(
        "Background", 
        0, -WINDOW_BAR_HEIGHT, 
        screen->width, screen->height
    );
    Color bck = make_color(0, 128, 127);
    fill_rect(background->fb, 0, 0, screen->width, screen->height, bck);
    background->flags |= WINDOW_UPDATED;
    set_background(background);
    
    struct MouseStatus previous = (struct MouseStatus) {0};

    while (true) {
        struct {
            int tlx, tly;
            int brx, bry;
        } update_area;
        update_area.tlx = screen->width;
        update_area.tly = screen->height;
        update_area.brx = 0;
        update_area.bry = 0;

        /*
            Here we try to decide if we should redraw the whole screen 
            or we can just update parts of it. If a window was moved we 
            need to redraw everything, otherwise we might be able to avoid it. 
            I expect that there will be not many windows open at the same time 
            (less than 20) therefore looping twice is not bad
        */
        struct WindowID *id = drawlist.head;
        bool full_update = false;
        bool needs_redraw = false;
        while (id) {
            if (id->window->flags & WINDOW_MOVED) {
                full_update = true;
                needs_redraw = true;
            }
            
            if (needs_redraw || id->window->flags & WINDOW_UPDATED) {
                needs_redraw = true;
                update_area.tlx = MIN(update_area.tlx, id->window->x);
                update_area.tly = MIN(update_area.tly, id->window->y);
                update_area.brx = MAX(
                    update_area.brx, 
                    id->window->x + id->window->fb->width
                );
                update_area.bry = MAX(
                    update_area.bry, 
                    id->window->y + id->window->fb->height + WINDOW_BAR_HEIGHT
                );
            }
            
            id = id->next;
        }
        
        if (needs_redraw) {
            id = drawlist.head;
            while (id) {
                const int flags = id->window->flags;
                if (full_update || flags & (WINDOW_UPDATED | WINDOW_MOVED)) {
                    draw_window(screen, id->window);
                    id->window->flags = flags & ~(WINDOW_UPDATED | WINDOW_MOVED);
                }

                id = id->next;
            }
        }
        
        screen_update(
            update_area.tlx, update_area.tly, 
            update_area.brx - update_area.tlx, 
            update_area.bry - update_area.tly);
        
        struct MouseStatus mouse = mouse_status();
        if (mouse.x != previous.x || mouse.y != previous.y) {
            screen_update(
                previous.x, previous.y, 
                cursor_width(), cursor_height()
            );
            draw_cursor(get_main_framebuffer(), mouse.x, mouse.y);
            previous = mouse;
        }
    }
}