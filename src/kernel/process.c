#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <kernel/arch/i386/paging.h>
#include <kernel/arch/i386/boot/descriptor_tables.h>
#include <kernel/lib/kassert.h>
#include <kernel/process.h>
#include <kernel/elf.h>
#include <klibc/string.h>

int current_pid = 1;

/*
    Allocates 'count' bytes and maps from 'vaddr' to 'vaddr' + count to that 
    allocated memory in the argument page directory.
*/
static void region_alloc(pdir_t pgdir, vaddr_t vaddr, size_t count)
{
    vaddr = ROUNDDOWN(vaddr, PGSIZE);
    count = ROUNDUP(count, PGSIZE);
    for (size_t i = 0; i < count; i += PGSIZE) {
        // We do this 1 page at a time so that even if a physical contiguous 
        // space in memory is not there we can still map it
        struct PageInfo *page = page_alloc(1);
        pgdir_map(
            pgdir, 
            vaddr + i, 
            PGSIZE, 
            (uint32_t) page2addr(page), 
            PG_PRESENT | PG_USER | PG_RW
        );
    }
}

/*
    Prepares some of the registers in the intframe of the process for 
    execution. In particular this allocates the stack and sets the %cs, %ds, 
    %ss, %esp and eflags registers. This does NOT set the %eip register as 
    it needs to read the entry point of the program. This is the job of 
    'read_elf'
*/
static void set_intframe(Process *process)
{
    const int stack_size = (USER_STACK_TOP - USER_STACK_BOTTOM);
    region_alloc(process->pgdir, USER_STACK_BOTTOM, stack_size);
    process->intframe.cs = 1;   // code segment in gdt
    process->intframe.ds = 2;   // data segment in gdt
    process->intframe.ss = process->intframe.ds;
    // asm volatile ("pushfd\npopfd %0" : "=r"(process->intframe.eflags));

    process->intframe.useresp = USER_STACK_TOP;
}

static int load_elf(Process *process, char *binary) 
{
    paging_load(process->pgdir);
    ELFHeader *head = (ELFHeader *) binary;
    ELFProgHeader *prog = (ELFProgHeader *) (binary + head->progHeader);
    for (size_t i = 0; i < head->progEntries; i++) {
        if (prog[i].type == ELF_PROG_LOAD) {
            region_alloc(
                process->pgdir, 
                prog[i].vAddr, 
                prog[i].memSize
            );
            memcpy(
                (void *) prog[i].vAddr, 
                (void *) (binary + prog[i].dataOffset), 
                prog[i].
                fileSize
            );
            /*
                The filesize can be less than the size in memory. As such we 
                need to set to 0 all the bytes after the end of filesize, 
                since they contain thrash anyway
            */
            memset(
                (void *) (prog[i].vAddr + prog[i].fileSize), 
                0, 
                prog[i].memSize - prog[i].fileSize
            );
        }
    }
    process->intframe.eip = head->entry;
    paging_load(paging_kernel_pgdir());

    return 0;
}

Process processes[MAX_PROCESSES];

Pid process_create(char *binary)
{
    Process *proc = NULL;
    for (int i = 0; i < MAX_PROCESSES; i++) {
        if (processes[i].state == PROC_STATE_UNUSED) {
            processes[i].pgdir = pgdir_create();
            processes[i].pid = i;
            proc = &processes[i];
            break;
        }
    }

    if (proc == NULL)
        return -1;
    if (process_setup(proc, binary) < 0)
        return -2;

    return proc->pid;
}

int process_find(Pid pid, Process *proc)
{
    if (pid < 0 || pid >= MAX_PROCESSES)
        return -1;
    *proc = processes[pid];
    
    return 0;
}

int process_enqueue(Pid pid)
{
    if (pid < 0 || pid >= MAX_PROCESSES)
        return -1;
    processes[pid].state = PROC_STATE_READY;
    
    return 0;
}

int process_destroy(Pid pid)
{
    // TODO: Assert that the currently loaded pgdir is NOT the one
    // being deleted
    if (pid < 0 || pid >= MAX_PROCESSES)
        return -1;
    // TODO: Probably free some memory? idk
    // pgdir_free(processes[pid].pgdir);
    processes[pid].state = PROC_STATE_UNUSED;

    return 0;
}

void process_run(Process *proc)
{
    proc->state = PROC_STATE_RUNNING;
    ((void (*)(void)) proc->intframe.eip)();
}

int process_setup(Process *proc, char *binary)
{
    if (load_elf(proc, binary) < 0)
        return -1;
    set_intframe(proc);
    
    return 0;
}