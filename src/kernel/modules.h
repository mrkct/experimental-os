#ifndef MODULES_H
#define MODULES_H

#include <kernel/arch/multiboot.h>

struct Module {
    bool loaded;
    char *start;
    uint32_t size;
};

#define EXPECTED_MODULES 1

enum ModuleID {
    MODULE_RAMDISK
};

int load_grub_modules(multiboot_info_t *);
struct Module *get_module(int id);

#endif