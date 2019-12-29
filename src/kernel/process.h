#ifndef PROCESS_H
#define PROCESS_H

#include <kernel/arch/i386/paging.h>
#include <kernel/arch/i386/boot/descriptor_tables.h>

#define MAX_PROCESSES 64

#define PROC_STATE_UNUSED 0
#define PROC_STATE_INITIALIZED 1
#define PROC_STATE_READY 2
#define PROC_STATE_RUNNING 3

typedef int Pid;

typedef struct Process {
    Pid pid;
    int state;
    pdir_t pgdir;
    intframe_t intframe;
    // idk
} Process;

/*
    Creates a new process loading the program stored in 'binary'. 
    @param binary: An area in memory containing an ELF image representing 
    an executable program. Note that this will be copied, you can free this 
    after the process has been loaded
    @returns the Pid of the process on success, which is a number > 0. -1 if 
    the system cannot create anymore processes, -2 if the binary image is not 
    valid
*/
Pid process_create(char *binary);

/*
    Finds the corresponding process and writes it in proc.
    Returns 0 on success, -1 if the process could not be found
*/
int process_find(Pid pid, Process *proc);

/*
    Adds the process to the list of currently running processes
*/
int process_enqueue(Pid pid);

/*
    Removes a process from the currently running list, freeing its resources.
*/
int process_destroy(Pid pid);

/*
    Runs the argument process. This function gives control to the process, but 
    when the time slice is over will receive back control
*/
void process_run(Process *proc);

int process_setup(Process *proc, char *binary);

#endif