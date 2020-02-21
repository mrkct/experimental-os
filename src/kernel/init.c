#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <kernel/devices/tty/tty.h>
#include <kernel/devices/timer/timer.h>
#include <kernel/devices/ps2kb/keyboard.h>
#include <kernel/arch/i386/boot/descriptor_tables.h>
#include <kernel/arch/i386/x86.h>
#include <kernel/arch/i386/paging.h>
#include <kernel/memory/memory.h>
#include <kernel/memory/kheap.h>
#include <kernel/lib/kprintf.h>
#include <kernel/lib/read_string.h>
#include <kernel/lib/kassert.h>
#include <kernel/arch/multiboot.h>
#include <kernel/monitor.h>
#include <kernel/modules.h>
#include <kernel/devices/vdisk.h>
#include <kernel/devices/ramdisk/ramdisk.h>
#include <klibc/string.h>
#include <kernel/filesystems/vfs.h>
#include <kernel/filesystems/fat16/fat16vfs.h>
#include <kernel/process.h>


struct DiskInterface ramdisk_interface;
struct DiskInterface ide_interface;
VFSInterface *vfsinterface;


void kernel_setup(multiboot_info_t *header, unsigned int magic)
{
    terminal_initialize();

    kassert(magic == MULTIBOOT_BOOTLOADER_MAGIC);

    init_gdt();
    
    uint32_t memory = multiboot_read_memory(header);
    memory_set_total(memory);
    kprintf("Detected %d bytes of total memory\n", memory);

    int loaded = load_grub_modules(header);
    kprintf("Loaded %d grub modules\n", loaded);
    
    paging_init(header);
    paging_load(paging_kernel_pgdir());

    // struct Module *modRamdisk = get_module(0);
    // kassert(0 == ramdisk_init(modRamdisk->start, modRamdisk->size));
    // kassert(0 == ramdisk_get_diskinterface(&ramdisk_interface));
    kassert(0 == ide_get_diskinterface(&ide_interface));
    vfsinterface = fat16_get_vfsinterface(&ide_interface);
    vfs_setroot(vfsinterface);

    scheduler_init();
    init_idt();
    timer_init(1);
}