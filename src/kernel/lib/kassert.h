#ifndef KASSERT_H
#define KASSERT_H
#include <kernel/lib/kprintf.h>
#define panic(error) do { _panic(__FILE__, __LINE__, error); } while (0)

#define kassert(cond) do { if(!(cond)) panic(#cond); } while(0)


static void 
_panic(const char *file, const int line, const char *error)
{
    kprintf("panic: %s at line %d. %s\n", file, line, error);
    asm("cli; cld");
    while (true) {}
}

static void 
_kassert(const char *file, const int line, const bool cond, const char *strcond)
{
    kprintf("kernel assert: %s at line %d. %s == false\n", file, line, strcond);
    asm("cli; cld");
    while (true) {}
}

#endif