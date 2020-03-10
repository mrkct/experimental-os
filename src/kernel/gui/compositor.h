#ifndef COMPOSITOR_H
#define COMPOSITOR_H

#include <kernel/gui/window.h>

/*
    Adds the window to the list of windows that will be drawn each frame 
    by the window
*/
int register_window(struct Window *window);

/*
    Removes a previously register window from the list of window that are 
    drawn each frame
*/
int unregister_window(struct Window *window);

/*
    Moves the argument window on top of all other.
    Returns 0 on success or -1 if the window could not be found
*/
int focus_window(struct Window *window);

/*
    DO NOT CALL THIS DIRECTLY:
    The compositor is a normal application, except its code is written in the 
    kernel. At startup a process is started with this function as its entry 
    point. You should not call this function directly but only by creating a 
    new process
*/
void __compositor_main(void);

#endif