#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <kernel/arch/multiboot.h>
#include <kernel/modules.h>
#include <kernel/memory/memory.h>
#include <kernel/lib/kassert.h>
#include <klibc/string.h>



struct Module modules[EXPECTED_MODULES];
static int total_modules = 0;

/*
    Reads all the loaded GRUB modules from the multiboot header and 
    copies each one into a safe memory location
*/
int load_grub_modules(multiboot_info_t *header)
{
    multiboot_module_t *curr_mod;
    total_modules = (int) header->mods_count;
    curr_mod = (multiboot_module_t *) header->mods_addr;
    
    int loaded = 0;

    for (int i = 0; i < total_modules; i++) {
        uint32_t size;
        size = (uint32_t) (curr_mod->mod_end - curr_mod->mod_start);
        char *m = boot_alloc(size);
        memcpy(
            (void *) m, 
            (void *) curr_mod->mod_start, 
            size
        );

        modules[i].loaded = true;
        modules[i].start = m;
        modules[i].size = size;

        curr_mod = curr_mod->mod_end;
        loaded++;
    }

    return loaded;
}

struct Module *get_module(int id) {
    return &modules[id];
}