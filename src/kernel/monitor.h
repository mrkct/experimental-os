#ifndef MONITOR_H
#define MONITOR_H


struct MonitorCommand {
    const char *name;
    const char *description;
    int (*function)(int argc, char** argv);
};

int monitor_handle(char *);

int monitor_help(int, char **);
int monitor_ticks(int, char **);
int monitor_system(int, char **);
int monitor_echo(int, char **);

#endif