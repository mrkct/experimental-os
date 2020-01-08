#include <cpuid.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <kernel/devices/timer/timer.h>
#include <kernel/filesystems/vfs.h>
#include <kernel/lib/kprintf.h>
#include <kernel/lib/kassert.h>
#include <kernel/memory/memory.h>
#include <kernel/monitor.h>
#include <klibc/string.h>
#include <kernel/memory/kheap.h>
#include <kernel/process.h>


// TODO: Avoid fixed max size arguments
#define MAX_ARGS 25

#define UNUSED __attribute__((unused))

struct MonitorCommand commands[] = {
    {"help", "Displays all available commands with their descriptions", monitor_help},
    {"ticks", "Displays how many CPU ticks have occurred since boot", monitor_ticks},
    {"system", "Displays various info about the system", monitor_system},
    {"echo", "Writes all the argument again", monitor_echo},
    {"ls", "Lists the content of a directory", monitor_ls},
    {"cat", "Prints the content of a file", monitor_cat},
    {"run", "Runs a program", monitor_run},
    {"ps", "Shows all the currently running processes in order of execution", monitor_ps}
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
    // We want to loop also over the '\0'
    int command_len = strlen(command) + 1;
    for (int i = 0; i < command_len; i++) {
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



int monitor_help(UNUSED int argc, UNUSED char **args)
{
    kprintf("Here is a list of all availables commands:\n");
    int commands_length = (int) (sizeof(commands) / sizeof(commands[0]));
    for (int i = 0; i < commands_length; i++) {
        kprintf("%s - %s\n", commands[i]);
    }

    return 0;
}

int monitor_ticks(UNUSED int argc, UNUSED char **arguments)
{
    kprintf("%d\n", timer_get_ticks());
    return 0;
}

int monitor_system(UNUSED int argc, UNUSED char **arguments)
{
    uint32_t eax, ebx, ecx, edx;
    __get_cpuid(0, &eax, &ebx, &ecx, &edx);
    char cpuvendor[13];
    uint32_t *c = (uint32_t *) cpuvendor;
    c[0] = ebx;
    c[1] = edx;
    c[2] = ecx;
    cpuvendor[12] = '\0';
    kprintf("CPU Vendor: %s\n", cpuvendor);
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

int monitor_ls(int argc, char **args)
{
    Dir dir;
    int result = kopendir(argc == 1 ? "/" : args[1], &dir);
    if (result != 0) {
        kprintf("could not open folder\n");
        return -1;
    }

    DirEntry dirent;
    while (klistdir(&dir, &dirent)) {
        if (dirent.type == DIRECTORY)
            kprintf("/");
        kprintf("%s\n", dirent.name);
    }
    kclosedir(&dir);

    return 0;
}

int monitor_cat(int argc, char **args)
{
    const int buffsize = 64;
    char buffer[buffsize];

    int read;
    FileDesc file;

    for (int i = 1; i < argc; i++) {
        file = kfopen(args[i], "r");
        if (file == NULL) {
            kprintf("could not open %s\n", args[i]);
            continue;
        }
        while ( (read = kfread(buffer, buffsize-1, file))) {
            buffer[read] = '\0';
            kprintf("%s", buffer);
        }
        kfclose(file);
    }
    
    return 0;
}

int monitor_run(int argc, char **argv)
{
    for (int i = 1; i < argc; i++) {
        FileDesc fd = kfopen(argv[i], "r");
        if (fd == NULL) {
            kprintf("could not open %s", argv[i]);
            continue;
        }
        char *binary = (char *) kmalloc(fd->filesize);
        kassert(fd->filesize == kfread(binary, fd->filesize, fd));
        if (execv(argv[i], binary)) {
            kprintf("an error happened while opening %s\n", argv[i]);
        }
    }

    return 0;
}

extern Process *running_proc;

int monitor_ps(int argc, char **argv)
{
    kprintf("Running processes: \n");
    kprintf("%d: %s (running)\n", running_proc->pid, running_proc->name);
    Process *p = running_proc->next;
    while (p != running_proc) {
        kprintf("%d: %s\n", p->pid, p->name);
        p = p->next;
    }

    return 0;
}