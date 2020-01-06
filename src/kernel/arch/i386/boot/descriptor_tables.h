#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#ifndef DESCRIPTOR_TABLES_H
#define DESCRIPTOR_TABLES_H

#define DESC_NULL  0x0
#define DESC_KCODE 0x8
#define DESC_KDATA 0x10



struct gdt_entry_struct
{
    uint16_t limit_low;           // The lower 16 bits of the limit.
    uint16_t base_low;            // The lower 16 bits of the base.
    uint8_t  base_middle;         // The next 8 bits of the base.
    uint8_t  access;              // Access flags, determine what ring this segment can be used in.
    uint8_t  granularity;
    uint8_t  base_high;           // The last 8 bits of the base.
} __attribute__((packed));
typedef struct gdt_entry_struct gdt_entry_t; 

struct gdt_ptr_struct
{
    uint16_t limit;               // The upper 16 bits of all selector limits.
    uint32_t base;                // The address of the first gdt_entry_t struct.
}
 __attribute__((packed));
typedef struct gdt_ptr_struct gdt_ptr_t; 

void init_gdt(void);

struct idt_entry_struct {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_high;
} __attribute__((packed));

typedef struct idt_entry_struct idt_entry_t;

struct idt_desc_struct {
    uint16_t size;
    uint32_t ptr;
} __attribute__((packed));

typedef struct idt_desc_struct idt_desc_t;

void init_idt(void);

/*
    This struct represents the content of the stack when
    an interrupt happens and we reach 'interrupt_handler'
*/
struct intframe_t {
    uint32_t ds;
    /* 
        Note that 'curresp' is the esp as it is when we're
        in an interrupt handler. If you're looking for the
        esp of the program see 'useresp'
    */
    uint32_t edi, esi, ebp, curresp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
} __attribute__((packed));

typedef struct intframe_t intframe_t;
#endif