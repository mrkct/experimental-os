#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <kernel/devices/ps2kb/keyboard.h>
#include <kernel/lib/kprintf.h>
#include <kernel/lib/read_string.h>


/*
    Reads a string either until the user presses ENTER or when the buffer is 
    full. Returns 0 if the user ended with an ENTER presses, -1 if it ended 
    because the buffer was full, -2 if the user pressed CTRL-C
*/
int read_string(char *buffer, int size)
{
    int index = 0;
    struct KeyAction action;
    while (index < size-1) {
        int read_success = kbd_get_keyaction(&action);
        if (read_success && action.pressed && action.character != 0) {
            if ((action.character == 'c' || action.character == 'C') && action.modifiers.ctrl ) {
                buffer[index] = '\0';
                return -2;
            }
            
            if (action.character != '\b' || index > 0 )
                kprintf("%c", action.character);
            
            if (action.character == '\n') {
                buffer[index] = '\0';
                return 0;
            } else if (action.character == '\b') {
                if (index > 0)
                    index--;
                continue;
            }
            buffer[index++] = action.character;
        }
    }
    buffer[index] = '\0';
    kprintf("\n");

    return -1;
}