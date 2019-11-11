#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <kernel/monitor.h>
#include <kernel/kprintf.h>
#include <kernel/timer.h>
#include <lib/klibc/string.h>
#include <kernel/i686/memory.h>


struct MonitorCommand commands[] = {
    {"help", "Displays all available commands with their descriptions", monitor_help},
    {"ticks", "Displays how many CPU ticks have occurred since boot", monitor_ticks},
    {"system", "Displays various info about the system", monitor_system}
};

int monitor_handle(char *command)
{
    for (int i = 0; i < sizeof(commands) / sizeof(commands[0]); i++) {
        if (strcmp(commands[i].name, command) == 0) {
            commands[i].function(command);
            return 1;
        }
    }

    return 0;
}

void monitor_help(char *arguments)
{
    kprintf("Here is a list of all availables commands:\n");
    for (int i = 0; i < sizeof(commands) / sizeof(commands[0]); i++) {
        kprintf("%s - %s\n", commands[i]);
    }
}

void monitor_ticks(char *arguments)
{
    kprintf("%d\n", timer_get_ticks());
}

void monitor_system(char *arguments)
{
    kprintf("Detected memory: %d MB\n", get_total_memory() / 1024 / 1024);
}