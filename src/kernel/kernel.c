#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <kernel/lib/kprintf.h>
#include <kernel/lib/read_string.h>
#include <kernel/monitor.h>
#include <kernel/devices/ide/ide.h>


void kernel_main(void) 
{
    struct ide_identify_format id;
    if (ide_identify_master(&id)) {
        kprintf("ERROR identifying master IDE device\n");
    } else {
        kprintf(
            "IDENTIFY Model: %s, capacity: %dMB\n", 
            id.model, 
            id.lba_capacity * 512 / 1024 / 1024
        );
    }

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
