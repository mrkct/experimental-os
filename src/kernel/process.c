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

static uint32_t load_elf(Process *process, char *binary) 
{
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
            return &processes[i];
        }
    }

    return NULL;
}

int process_start(char *binary)
{
    Process *p = find_free_process();
    kassert(p != NULL);
    p->state = PROC_STATE_READY;
    p->pgdir = pgdir_create();
    p->pid = get_next_pid();

    char *stack = (char *) kmalloc(PROCESS_KERNEL_STACK_SIZE);
    p->registers.esp = (uint32_t) (stack + PROCESS_KERNEL_STACK_SIZE -1);
    
    /*
        load_elf needs to write directly to the specific memory addresses 
        where the programs wants to be put at. Before doing that it allocs 
        the memory and maps it there. As such we load the process page dir 
        so that page dir is changed instead of the current one. We restore 
        the current one before going ahead though
    */
    pdir_t current_pgdir = (pdir_t) read_cr3();
    paging_load(p->pgdir);
    uint32_t entry = load_elf(p, binary);
    paging_load(current_pgdir);

    // We need to fake the stack as if the process has already been interrupted once
    uint32_t *p_esp = (uint32_t *) p->registers.esp;
    // The data pushed by the cpu when an interrupt happens 
    // (and popped by 'iret')
    *p_esp = 0x206;               // eflags
    *(p_esp-1) = 0x8;                 // cs
    *(p_esp-2) = entry;    // eip
    // This is automatically pushed by us when an interrupt happens, see the
    // isr stubs in arch/i386/boot/interrupt.S
    *(p_esp-3) = 0;                   // err_code
    *(p_esp-4) = 0;                   // int_no

    p->registers.esp -= 16;
    p->registers.ebp = p->registers.esp;

    p->next = running_proc->next;
    running_proc->next = p;

    return 0;
}

void scheduler_init(void)
{
    // We set the kernel as the first process running
    Process *p = find_free_process();
    p->state = PROC_STATE_RUNNING;
    p->pid = get_next_pid();
    p->pgdir = paging_kernel_pgdir();
    p->next = p;
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
    old->state = PROC_STATE_READY;
    Process *new = running_proc->next;
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
    paging_load(new->pgdir);
}