#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>
#include <kernel/arch/i386/boot/descriptor_tables.h>
#include <kernel/arch/i386/paging.h>

#define MAX_PROCESSES       16

#define PROC_STATE_UNUSED   0
#define PROC_STATE_READY    1
#define PROC_STATE_RUNNING  2
#define PROC_STATE_WAITING  3
#define PROC_STATE_DEAD     4

#define PROCESS_KERNEL_STACK_SIZE   (64 * 1024)

#define E_PROCESSLIMITREACHED   1
#define E_OUTOFMEMORY           2
#define E_NOTELF                3

/*
    This contains all the registers in x86 that we save each context switch. 
    Not all registers are included, this is because some of those are saved 
    on the process stack itself, such as %eip, %cs and eflags
*/
struct X86Registers {
    uint32_t edi, esi, ebp, ebx, edx, ecx, eax;
    uint32_t esp;
};

typedef struct Process {
    struct X86Registers registers;
    pdir_t pgdir;
    
    int pid;
    int state;
    char *name;
    struct Process *next;
} Process;

/*
    Call this BEFORE interrupts are initialised. Adds the kernel as the 
    initial process to the process list. Do NOT call this more than once 
    in the entire execution of the kernel
*/
void scheduler_init(void);

/*
    Creates a new process that will be scheduled to run next. 
    @param name: The name of the process, this string will be copied so you 
    can free it after use.
    @param entryPoint: The entry point in memory where the program starts. 
    This is a virtual address when the argument page directory is loaded
    @param pagedir: The page directory that needs to be loaded when the 
    process runs. This does NOT get copied, it is your responsability to not 
    free it until the process is dead
    @returns 0 on success, otherwise one of these:
        1. E_OUTOFMEMORY: There is not enough memory to run the program
        2. E_PROCESSLIMIT: The maximum amount of processes running has been 
        reached. 
*/
int process_create(char *name, uint32_t entryPoint, pdir_t pagedir);

/*
    Sets the process state as dead. This means this process will not be 
    scheduled again. Even though the process' resources will be freed this 
    will probably not happen instantly
*/
void process_set_dead(Process *proc);

/*
    Returns the currently running process. Note that this changes with time, 
    so it might not be valid for all the time you need. Be sure to be in code 
    that cannot be context switched
*/
Process *get_running_process(void);

/*
    Starts a new process from a program stored on disk.
    @param name: The name of the process.
    @param binary: Where in memory the binary ELF image to load is stored
    @returns 0 on success, otherwise one of these:
        1. E_NOTELF: The file opened is not an ELF image
        2. E_OUTOFMEMORY: There is not enough memory to run the program
        3. E_PROCESSLIMIT: The maximum amount of processes running has been 
        reached. 
*/
int execv(char *name, char *binary);

/*
    Do NOT call this function outside the interrupt handler. This executes one 
    step of the scheduler, this might cause a context switch. This only works 
    if called from an interrupt handler, otherwise it might corrupt your stack
*/
void scheduler(struct intframe_t *frame);

#endif