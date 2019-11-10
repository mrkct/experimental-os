#ifndef MONITOR_H
#define MONITOR_H


struct MonitorCommand {
    const char *name;
    const char *description;
    void (*function)(char* argument);
};

int monitor_handle(char *);

void monitor_help(char *);
void monitor_ticks(char *);

#endif