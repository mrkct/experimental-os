#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <kernel/devices/timer/timer.h>
#include <kernel/lib/kprintf.h>
#include <kernel/memory/memory.h>
#include <kernel/monitor.h>
#include <klibc/string.h>

// TODO: Avoid fixed max size arguments
#define MAX_ARGS 25

struct MonitorCommand commands[] = {
    {"help", "Displays all available commands with their descriptions", monitor_help},
    {"ticks", "Displays how many CPU ticks have occurred since boot", monitor_ticks},
    {"system", "Displays various info about the system", monitor_system},
    {"echo", "Writes all the argument again", monitor_echo},
    {"ls", "Lists the content of a directory", monitor_ls},
    {"cat", "Prints the content of a file", monitor_cat}
};

/*
    Parses a command and extracts the arguments into an array. Each argument 
    is dynamically allocated, you will need to free each string after use. 
    The first argument is always the command name. Each argument is a space 
    separated string.

    Returns the number of arguments on success, -1 if there are too many 
    arguments to be stored
*/
int parse_args(char *command, char **args)
{
    int arg_pos = 0;
    int last_space = 0;
    for (int i = 0; i < strlen(command)+1; i++) {
        if (command[i] == ' ' || command[i] == '\0') {
            if (arg_pos == MAX_ARGS) {
                return -1;
            }
            int arg_len = i - last_space;
            args[arg_pos] = (char *) kmalloc(1 + sizeof(char) * arg_len);
            memcpy(args[arg_pos], &command[last_space], arg_len);
            args[arg_pos][arg_len] = '\0';
            last_space = i+1;
            arg_pos++;
        }
    }

    return arg_pos;
}

int monitor_handle(char *command)
{
    char *args[MAX_ARGS];
    int argc = parse_args(command, args);

    int commands_length = (int) (sizeof(commands) / sizeof(commands[0]));
    for (int i = 0; i < commands_length; i++) {
        if (strcmp(commands[i].name, args[0]) == 0) {
            commands[i].function(argc, args);
            return 1;
        }
    }

    for (int i = 0; i < argc; i++) {
        kfree(args[i]);
    }

    return 0;
}

int monitor_help(int argc, char **arguments)
{
    kprintf("Here is a list of all availables commands:\n");
    int commands_length = (int) (sizeof(commands) / sizeof(commands[0]));
    for (int i = 0; i < commands_length; i++) {
        kprintf("%s - %s\n", commands[i]);
    }

    return 0;
}

int monitor_ticks(int argc, char **arguments)
{
    kprintf("%d\n", timer_get_ticks());
    return 0;
}

int monitor_system(int argc, char **arguments)
{
    kprintf("Detected memory: %d MB\n", memory_get_total() / 1024 / 1024);
    return 0;
}

int monitor_echo(int argc, char **args)
{
    for (int i = 1; i < argc; i++) {
        kprintf("%s ", args[i]);
    }
    kprintf("\n");

    return 0;
}

#include <kernel/filesystems/fat16/fat16.h>

int monitor_ls(int argc, char **args)
{
    FAT16DirEntry entry;
    int offset;
    if (argc == 1) {
        offset = fat16_open("/", NULL);
    } else {
        offset = fat16_open(args[1], NULL);
    }
    if (offset < 0) {
        kprintf("could not open folder\n");
        return -1;
    }
    char filename[12];
    while (fat16_ls(&offset, &entry)) {
        memcpy(filename, entry.filename, 11);
        filename[11] = '\0';
        if (entry.filesize == 0) {
            kprintf("/");
        }
        kprintf("%s\n", filename);
    }

    return 0;
}

int monitor_cat(int argc, char **args)
{
    struct FAT16FileHandle handle;
    if (fat16_fopen(args[1], 'r', &handle)) {
        kprintf("could not open file\n");
        return -1;
    }

    const int buffsize = 64;
    char buffer[buffsize];
    
    int read;
    while (read = fat16_fread(&handle, buffsize-1, buffer)) {
        buffer[read] = '\0';
        kprintf("%s", buffer);
    }
    kprintf("\n");

    return 0;
}