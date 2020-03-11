#ifndef SYSCALL_H
#define SYSCALL_H

#include <stdint.h>

/*
    Dispatches to the correct system calls. The dispatching is done according 
    to the value in the %eax registers. For a list of the available system 
    calls and their value see the below enum
    Returns a value that is expected to be put in the %eax register of the 
    process that made the system call
*/
int syscall(uint32_t eax, uint32_t ebx, uint32_t ecx, uint32_t edx, uint32_t esi, uint32_t edi);

enum {
    SYS_EXIT = 1, 
    SYS_WRITE, 
    SYS_YIELD
};

#endif