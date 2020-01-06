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
    struct Process *next;
} Process;

void scheduler_init(void);

int process_start(char *binary);

void scheduler(struct intframe_t *frame);

#endif