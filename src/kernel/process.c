#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <kernel/arch/i386/paging.h>
#include <kernel/arch/i386/boot/descriptor_tables.h>
#include <kernel/lib/kassert.h>
#include <kernel/process.h>
#include <kernel/elf.h>
#include <klibc/string.h>


Process processes[MAX_PROCESSES];
Process *current_proc;

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
static void set_initial_intframe(Process *process)
{
    const int stack_size = (USER_STACK_TOP - USER_STACK_BOTTOM);
    region_alloc(process->pgdir, USER_STACK_BOTTOM, stack_size);

    // TODO: Actually put real values there instead of copying
    process->procState.cs = 0x8;
    process->procState.eflags = 0x206;
    process->procState.esp = USER_STACK_TOP;
    process->procState.ss = 0x4;
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
    process->procState.eip = head->entry;
    paging_load(paging_kernel_pgdir());

    return 0;
}

Process *process_create(char *binary)
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

    if (proc == NULL || load_elf(proc, binary) < 0)
        return NULL;
    
    set_initial_intframe(proc);
    proc->state = PROC_STATE_READY;

    return proc;
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
    if (current_proc != NULL) {
        current_proc->state = PROC_STATE_READY;
    }
    proc->state = PROC_STATE_RUNNING;
    current_proc = proc;
}

static void copy_procstate2intframe(
    ProcessState *state, 
    struct intframe_t *intframe
)
{
    intframe->edi = state->edi;
    intframe->esi = state->esi;
    intframe->ebp = state->ebp;
    intframe->ebx = state->ebx;
    intframe->edx = state->edx;
    intframe->ecx = state->ecx;
    intframe->eax = state->eax;
    intframe->eip = state->eip;
    intframe->cs  = state->cs;
    intframe->eflags = state->eflags;
    intframe->useresp = state->esp;
    intframe->ss = state->ss;
}

static void copy_intframe2procstate(
    struct intframe_t *intframe,
    ProcessState *state
)
{
    state->edi = intframe->edi;
    state->esi = intframe->esi;
    state->ebp = intframe->ebp;
    state->ebx = intframe->ebx;
    state->edx = intframe->edx;
    state->ecx = intframe->ecx;
    state->eax = intframe->eax;
    state->eip = intframe->eip;
    state->cs  = intframe->cs;
    state->eflags = intframe->eflags;
    state->esp = intframe->useresp;
    state->ss = intframe->ss;
}

void scheduler_init()
{
    current_proc = &processes[0];
    current_proc->state = PROC_STATE_RUNNING;
    current_proc->pgdir = paging_kernel_pgdir();
    current_proc->pid = 0;
    
}

void wait() {
    volatile uint64_t i = 0;
    while (i < 40000000) {
        i++;
    }
}

void scheduler_tick(struct intframe_t *intframe)
{
    /*
    kprintf("--- Printing intframe ---\n");
    kprintf("ds: %x\n", intframe->ds);
    kprintf("edi: %x \n", intframe->edi);
    kprintf("esi: %x \n", intframe->esi);
    kprintf("ebp: %x \n", intframe->ebp);
    kprintf("curresp: %x \n", intframe->curresp);
    kprintf("ebx: %x \n", intframe->ebx);
    kprintf("edx: %x \n", intframe->edx);
    kprintf("ecx: %x \n", intframe->ecx);
    kprintf("eax: %x \n", intframe->eax);
    kprintf("int_no: %x \n", intframe->int_no);
    kprintf("err_code: %x \n", intframe->err_code);
    kprintf("eip: %x \n", intframe->eip);
    kprintf("cs: %x \n", intframe->cs);
    kprintf("eflags: %x \n", intframe->eflags);
    kprintf("useresp: %x \n", intframe->useresp);
    kprintf("ss: %x \n", intframe->ss);
    */
    /*
        This is called by the interrupt handler at every timer tick. The 
        argument is a pointer to what is on the stack when the handler 
        was called. When this function returns the handler will restore the 
        stuff on the stack. We change what is on the stack so that instead of 
        going back to what it was doing another process gets run
    */
    // Simple round robin scheduler
    current_proc->state = PROC_STATE_READY;
    int to_run = (1 + (current_proc - processes)) % MAX_PROCESSES;
    for (int i = 0; i < MAX_PROCESSES; i++) {
        if (processes[to_run].state == PROC_STATE_READY) {
            // kprintf("cambio da proc %d a proc %d\n", (current_proc - processes), to_run);
            copy_intframe2procstate(intframe, &current_proc->procState);
            processes[to_run].state = PROC_STATE_RUNNING;
            current_proc = &processes[to_run];
            copy_procstate2intframe(&current_proc->procState, intframe);
            paging_load(current_proc->pgdir);
            return;
        }
        to_run = (to_run + 1) % MAX_PROCESSES;
    }
    panic("nothing to execute in scheduler. did you kill the monitor?");
}