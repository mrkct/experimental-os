#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <kernel/lib/kprintf.h>
#include <kernel/lib/read_string.h>
#include <kernel/monitor.h>


void kernel_main(void) 
{
    #define BUFFER_SIZE 1024
    char buffer[BUFFER_SIZE];
    while (true) {
        kprintf("> ");
        switch (read_string(buffer, BUFFER_SIZE)) {
            case -1:
                kprintf("You can't have commands THAT long\n");
                break;
            /*
                As not all modifiers are implemented in the ps2 keyboard 
                driver the ctrl flag might contain random data. This could 
                trigger this event if the user is unlucky while pressing 'c'. 
                For now we comment this
            */
            case -2:
                kprintf("\nCTRL-C\n");
                break;
            
            default:
                if (!monitor_handle(buffer))
                    kprintf("No commands with that name\n");
        }
    }

    kprintf("Reached end of kernel. Halting...");
}
