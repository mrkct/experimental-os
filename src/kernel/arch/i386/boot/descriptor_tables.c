#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <kernel/lib/kassert.h>
#include <kernel/lib/kprintf.h>
#include <kernel/arch/i386/int.h>
#include <kernel/devices/tty/tty.h>
#include <kernel/arch/i386/boot/descriptor_tables.h>
#include <kernel/arch/i386/pic.h>
#include <kernel/arch/i386/irq.h>
#define GDT_ENTRIES 5
#define IDT_ENTRIES 256


extern void gdt_flush(uint32_t);
static void gdt_set_gate(int32_t, uint32_t, uint32_t, uint8_t, uint8_t);

gdt_entry_t gdt_entries[GDT_ENTRIES];
gdt_ptr_t   gdt_ptr;

void init_gdt()
{
    gdt_ptr.limit = (sizeof(gdt_entry_t) * GDT_ENTRIES) - 1;
    gdt_ptr.base  = (uint32_t)&gdt_entries;

    gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

    gdt_flush((uint32_t)&gdt_ptr);
}

// Set the value of one GDT entry.
static void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdt_entries[num].base_low    = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high   = (base >> 24) & 0xFF; 
    
    gdt_entries[num].limit_low   = (limit & 0xFFFF);
    gdt_entries[num].granularity = (limit >> 16) & 0x0F;    
    
    gdt_entries[num].granularity |= gran & 0xF0;
    gdt_entries[num].access      = access;
}

idt_entry_t idt_entries[IDT_ENTRIES];
idt_desc_t idt_desc;

extern void load_idt(uint32_t);

/*
    When this function is called this is on the stack:
    
    callee's %ds
    all registers --> pusha
    $0 / ERRCODE
    interrupt id
    %eip --> from now all this stuff is pushed by the CPU automatically
    %cs
    %eflags
    %esp --> the esp that was being used when the interrupt happened
    %ss

    All this stuff is represented by the intframe_t struct
*/

static int count = 0;

static long read_cr2() {
    unsigned long val;
    asm volatile ( "mov %%cr2, %0" : "=r"(val) );
    return val;
}

static long read_cr3() {
    unsigned long val;
    asm volatile ( "mov %%cr3, %0" : "=r"(val) );
    return val;
}

#include <kernel/process.h>

extern Process processes[MAX_PROCESSES];
extern Process *current_proc;

void interrupt_handler(struct intframe_t *frameptr)
{
    if (frameptr->int_no < IRQ_OFFSET) {
        kprintf(
            "[%d] %s: %d - %d\n", 
            count++, 
            get_exception_message(frameptr->int_no), 
            frameptr->int_no, 
            frameptr->err_code
        );
        kprintf("currently running process: %d\n", (current_proc - processes));
        kprintf("--- Printing intframe ---\n");
        kprintf("ds: %x\n", frameptr->ds);
        kprintf("edi: %x \n", frameptr->edi);
        kprintf("esi: %x \n", frameptr->esi);
        kprintf("ebp: %x \n", frameptr->ebp);
        kprintf("curresp: %x \n", frameptr->curresp);
        kprintf("ebx: %x \n", frameptr->ebx);
        kprintf("edx: %x \n", frameptr->edx);
        kprintf("ecx: %x \n", frameptr->ecx);
        kprintf("eax: %x \n", frameptr->eax);
        kprintf("int_no: %x \n", frameptr->int_no);
        kprintf("err_code: %x \n", frameptr->err_code);
        kprintf("eip: %x \n", frameptr->eip);
        kprintf("cs: %x \n", frameptr->cs);
        kprintf("eflags: %x \n", frameptr->eflags);
        kprintf("useresp: %x \n", frameptr->useresp);
        kprintf("ss: %x \n", frameptr->ss);
        if (frameptr->int_no == 14) {
            kprintf("\tcr2: %x\n", read_cr2());
            kprintf("\tcr3: %x\n\tkern_pgdir: %x\n", read_cr3(), paging_kernel_pgdir());
            while (true) {}
        }
    } else {
        dispatch_irq(frameptr);
        pic_ack(frameptr->int_no);
    }
}

extern uint32_t handlers[IDT_ENTRIES];


static void set_idt_gate(int i, uint16_t selector, uint8_t type, uint32_t isr) {
    idt_entries[i].zero = 0;
    idt_entries[i].selector = selector;
    idt_entries[i].type_attr = type;

    idt_entries[i].offset_low = isr & 0xffff;
    idt_entries[i].offset_high = (isr >> 16) & 0xffff;
}

void init_idt()
{
    kassert(sizeof(idt_entry_t) == 8);
    kassert(sizeof(idt_desc_t) == 6);

    idt_desc.size = (sizeof(idt_entry_t) * IDT_ENTRIES) - 1;
    idt_desc.ptr = (uint32_t) idt_entries;

    for (int i = 0; i < IDT_ENTRIES; i++) {
        set_idt_gate(i, 0x08, 0x8e, handlers[i]);
    }

    load_idt((uint32_t) &idt_desc);
    pic_init(IRQ_OFFSET);
    asm("sti");
}