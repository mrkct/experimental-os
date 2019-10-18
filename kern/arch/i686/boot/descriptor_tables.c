#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <kernel/tty.h>
#include <kernel/i686/descriptor_tables.h>
#define GDT_ENTRIES 5
#define IDT_ENTRIES 256


int kprintf(char*, ...);
void kassert(bool, char *);

static inline const char *get_exception_message(uint32_t code)
{
    const char *messages[] = {
        "Divide-by-zero Error",
        "Debug",
        "Non-maskable Interrupt",
        "Breakpoint",
        "Overflow",
        "Bound Range Exceeded",
        "Invalid Opcode",
        "Device Not Available",
        "Double Fault",
        "Coprocessor Segment Overrun",
        "Invalid TSS",
        "Segment Not Present",
        "Stack-Segment Fault",
        "General Protection Fault",
        "Page Fault",
        "[Intel Reserved]",
        "x87 Floating-Point Exception",
        "Alignment Check",
        "Machine Check",
        "SIMD Floating-Point Exception",
        "Virtualization Exception",
        "[Intel Reserved]",
        "Security Exception",
        "[Intel Reserved]",
        "Triple Fault",
        "FPU Error Interrupt"
    };
    if (code < 26) {
        return messages[code];
    } else {
        return "Unknown Interrupt";
    }
}


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

void interrupt_handler(struct intframe_t *frameptr)
{
    struct intframe_t frame = *frameptr;
    kprintf(
        "[%d] %s: %d - %d\n", 
        count++, 
        get_exception_message(frame.int_no), 
        frame.int_no, 
        frame.err_code
    );
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
    kassert(sizeof(idt_entry_t) == 8, "sizeof(idt_entry_t) != 8");
    kassert(sizeof(idt_desc_t) == 6, "sizeof(idt_desc_it) != 6");

    idt_desc.size = (sizeof(idt_entry_t) * IDT_ENTRIES) - 1;
    idt_desc.ptr = (uint32_t) idt_entries;

    for (int i = 0; i < IDT_ENTRIES; i++) {
        set_idt_gate(i, 0x08, 0x8e, handlers[i]);
    }

    load_idt((uint32_t) &idt_desc);
}