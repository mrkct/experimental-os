#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <kernel/memory/kheap.h>
#include <kernel/arch/i386/boot/descriptor_tables.h>
#include <kernel/arch/i386/paging.h>
#include <kernel/arch/i386/x86.h>
#include <kernel/lib/kassert.h>
#include <kernel/elf.h>
#include <klibc/string.h>
#include <kernel/process.h>


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
    Loads an ELF file, allocating and mapping memory in the argument page 
    directory. 
    Returns the entry point of the program on success, 0 if the file is not an 
    ELF file
*/
static uint32_t load_elf(pdir_t pagedir, char *binary) 
{
    ELFHeader *head = (ELFHeader *) binary;
    if (head->magic != ELF_MAGIC) {
        return 0;
    }

    ELFProgHeader *prog = (ELFProgHeader *) (binary + head->progHeader);
    for (size_t i = 0; i < head->progEntries; i++) {
        if (prog[i].type == ELF_PROG_LOAD) {
            region_alloc(
                pagedir, 
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

    return head->entry;
}


Process processes[MAX_PROCESSES];
Process *running_proc;

static int get_next_pid(void)
{
    static int pid = 0;
    return pid++;
}

static Process *find_free_process(void)
{
    for (int i = 0; i < MAX_PROCESSES; i++) {
        if (processes[i].state == PROC_STATE_UNUSED) {
            processes[i].state = PROC_STATE_UNUSED;
            return &processes[i];
        }
    }

    return NULL;
}

int process_create(char *name, uint32_t entryPoint, pdir_t pagedir)
{
    Process *p = find_free_process();
    if (p == NULL) {
        return -E_PROCESSLIMITREACHED;
    }

    p->name = kmalloc(strlen(name));
    if (p->name == NULL) {
        return -E_OUTOFMEMORY;
    }
    strcpy(p->name, name);
    p->state = PROC_STATE_READY;
    p->pgdir = pagedir;
    p->pid = get_next_pid();

    char *stack = (char *) kmalloc(PROCESS_KERNEL_STACK_SIZE);
    if (stack == NULL) {
        kfree(p->name);
        return -E_OUTOFMEMORY;
    }
    kassert(stack < 128 * 1024 * 1024);
    p->registers.esp = (uint32_t) (stack + PROCESS_KERNEL_STACK_SIZE -1);

    uint32_t *p_esp = (uint32_t *) p->registers.esp;
    // The data pushed by the cpu when an interrupt happens (popped by 'iret')
    *p_esp = 0x206;             // eflags
    *(p_esp-1) = 0x8;           // cs
    *(p_esp-2) = entryPoint;    // eip
    // This is automatically pushed by us when an interrupt happens, see the
    // isr stubs in arch/i386/boot/interrupt.S
    *(p_esp-3) = 0;         // err_code
    *(p_esp-4) = 0;         // int_no

    p->registers.esp -= 16;
    p->registers.ebp = p->registers.esp;

    p->next = running_proc->next;
    running_proc->next = p;

    return 0;
}

void process_set_dead(Process *proc)
{
    proc->state = PROC_STATE_DEAD;
}

Process *get_running_process(void)
{
    return running_proc;
}

/*
    Frees a process resources. This function should not be called unless you 
    are sure the process is not in the free list and it is not being executed. 
    If you are looking for how to kill a process see 'process_set_dead'
*/
static void process_free(Process *proc)
{
    proc->state = PROC_STATE_UNUSED;
    // TODO: Free the memory used by the code, stack & heap
    // if (proc->pgdir != paging_kernel_pgdir()) {
    //     pgdir_free(proc->pgdir);
    // }
}

int execv(char *name, char *binary)
{
    /*
        load_elf needs to write directly to the specific memory addresses 
        where the programs wants to be put at. Before doing that it allocs 
        the memory and maps it there. As such we load the process page dir 
        so that page dir is changed instead of the current one. We restore 
        the current one before going ahead though
    */
    pdir_t pagedir = pgdir_create();
    pdir_t current_pagedir = (pdir_t) read_cr3();
    paging_load(pagedir);
    uint32_t entry = load_elf(pagedir, binary);
    paging_load(current_pagedir);

    if (entry == 0) {
        // TODO: Destroy pagedir
        return E_NOTELF;
    }

    int result = process_create(name, entry, pagedir);
    if (result < 0) {
        // TODO: Destroy pagedir
    }

    return result;
}

void scheduler_init(void)
{
    // We set the kernel as the first process running
    Process *p = find_free_process();
    p->state = PROC_STATE_RUNNING;
    p->pid = get_next_pid();
    p->pgdir = paging_kernel_pgdir();
    p->next = p;
    p->name = "Monitor";
    running_proc = p;

    /*
        We don't need to set the registers, the first time a context 
        switch will happen the current state of the registers will be 
        saved. It would also be impossible to store the right initial values 
        anyway...
    */
}


void scheduler(struct intframe_t *frame)
{
    // Avoid all this if there is only 1 process running...
    if (running_proc->next == running_proc) {
        return;
    }

    // Simple round robin, inefficient but works for now
    Process *old = running_proc;
    Process *new = old->next;
    while (new->state == PROC_STATE_DEAD) {
        Process *new_next = new->next;
        process_free(new);
        new = new_next;
    }

    old->next = new;
    // The process might be dead, without this check we would revive it
    if (old->state == PROC_STATE_RUNNING) {
        old->state = PROC_STATE_READY;
    }
    new->state = PROC_STATE_RUNNING;

    // Save the running process registers
    old->registers.edi = frame->edi;
    old->registers.esi = frame->esi;
    old->registers.ebp = frame->ebp;
    old->registers.ebx = frame->ebx;
    old->registers.edx = frame->edx;
    old->registers.ecx = frame->ecx;
    old->registers.eax = frame->eax;
    
    old->registers.esp = frame->curresp;

    // Restore the newly running process's ones
    frame->edi = new->registers.edi;
    frame->esi = new->registers.esi;
    frame->ebp = new->registers.ebp;
    frame->ebx = new->registers.ebx;
    frame->edx = new->registers.edx;
    frame->ecx = new->registers.ecx;
    frame->eax = new->registers.eax;

    frame->curresp = new->registers.esp;
    
    running_proc = new;
    if (old->pgdir != new->pgdir) {
        paging_load(new->pgdir);
    }
}