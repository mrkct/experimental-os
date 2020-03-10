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
#include <kernel/devices/ide/ide.h>
#include <klibc/string.h>
#include <kernel/filesystems/vfs.h>
#include <kernel/filesystems/fat16/fat16vfs.h>
#include <kernel/process.h>
#include <kernel/devices/serial/serial.h>
#include <kernel/devices/framebuffer.h>
#include <kernel/gui/compositor.h>


struct DiskInterface diskinterface;
VFSInterface *vfsinterface;


void kernel_setup(multiboot_info_t *header, unsigned int magic)
{
    terminal_initialize();

    kassert(magic == MULTIBOOT_BOOTLOADER_MAGIC);

    init_gdt();
    
    uint32_t memory = multiboot_read_memory(header);
    memory_set_total(memory);
    kprintf("Detected %d MB of total memory\n", memory / 1024 / 1024);

    int loaded = load_grub_modules(header);
    kprintf("Loaded %d grub modules\n", loaded);
    
    timer_init(1);
    serial_init();

    paging_init(header);
    paging_load(paging_kernel_pgdir());

    scheduler_init();
    init_idt();

    
    kassert(0 == fb_init(header));
    struct FrameBuffer *fb = get_screen_framebuffer();

    kprintf("Framebuffer: \n");
    kprintf("\tAddr: %p\n", fb->addr);
    kprintf(
        "\tWidth: %d, Height: %d, Bpp: %d, Pitch: %d\n", 
        fb->width, fb->height, fb->bytesPerPixel, fb->pitch);

    kprintf("Checking for an IDE device...");
    
    struct DiskInterface diskinterface;
    struct ide_identify_format id;
    int result = ide_identify_master(&id);
    if (result == 0) {
        kprintf("found\n");
        kprintf(
            "Using device %s - %dMB\n", 
            id.model, 
            id.lba_capacity * 512 / 1024 / 1024
        );
        kassert(0 == ide_get_diskinterface(&diskinterface));
    } else {
        kprintf("not found\n");
        kprintf("Checking for a ramdisk...");
        struct Module *mod_ramdisk = get_module(0);
        if (mod_ramdisk == NULL) {
            kprintf("not found\n");
            panic("Can't continue: no usable disk device found\n");
        }
        kassert(0 == ramdisk_init(mod_ramdisk->start, mod_ramdisk->size));
        kassert(0 == ramdisk_get_diskinterface(&diskinterface));
        kprintf("Ramdisk at %x with %d MB\n", mod_ramdisk->start, mod_ramdisk->size / 1024 / 1024);
    }
    
    vfsinterface = fat16_get_vfsinterface(&diskinterface);
    vfs_setroot(vfsinterface);

    kprintf("Starting Compositor Server");
    process_create("Compositor Server", __compositor_main, paging_kernel_pgdir());

    kprintf("All done. Ready to start!\n");
}