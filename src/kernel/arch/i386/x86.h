#ifndef X86_H
#define X86_H
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>


static inline void outb(uint16_t port, uint8_t val)
{
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}

static inline unsigned long read_cr0(void)
{
    unsigned long val;
    asm volatile ( "mov %%cr0, %0" : "=r"(val) );
    return val;
}

static inline unsigned long read_cr2(void)
{
    unsigned long val;
    asm volatile ( "mov %%cr2, %0" : "=r"(val) );
    return val;
}

static inline unsigned long read_cr3(void)
{
    unsigned long val;
    asm volatile ( "mov %%cr3, %0" : "=r"(val) );
    return val;
}

static inline void load_cr0(unsigned long cr0)
{
    asm volatile ( 
        "mov %0, %%eax\n\t"
        "mov %%eax, %%cr0"
        :
        : "a" (cr0)
    );
}

static inline void load_cr3(unsigned long cr3)
{
    asm volatile ( 
        "mov %0, %%eax\n\t"
        "mov %%eax, %%cr3"
        :
        : "a" (cr3)
    );
}

#endif