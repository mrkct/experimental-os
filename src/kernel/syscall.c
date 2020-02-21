#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <kernel/process.h>
#include <kernel/syscall.h>
#include <kernel/lib/kassert.h>
#include <klibc/string.h>


static int SYS_exit(uint32_t exitcode)
{
    Process *running_proc = get_running_process();
    kprintf("process %d exited with code %d\n", running_proc->pid, exitcode);
    process_set_dead(running_proc);

    return 0;
}

static int SYS_write(uint32_t filedesc, uint32_t string, uint32_t length)
{
    /*
        Filedesc is useless for now, but it might be useful if we implement 
        stdout as a file
    */
    kassert(filedesc == 1);
    char buffer[length+1];
    memcpy(buffer, (char *) string, length);
    buffer[length] = '\0';
    kprintf("%s", buffer);

    return 0;
}

int syscall(uint32_t eax, uint32_t ebx, uint32_t ecx, uint32_t edx, uint32_t esi, uint32_t edi)
{
    (void) esi;
    (void) edi;
    switch(eax) {
    case SYS_EXIT:
        return SYS_exit(ebx);
    case SYS_WRITE:
        return SYS_write(ebx, ecx, edx);
    default:
        return 0;
    }
}
