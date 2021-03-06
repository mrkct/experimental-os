# The name that will appear in GRUB
OS_NAME := Experimental OS

# The '-g' adds debugging symbols
AS_FLAGS := -g
CC_FLAGS := -std=gnu11 -ffreestanding -Wall -Wextra -g
LD_FLAGS := -ffreestanding -nostdlib -lgcc -g

OUTF := out

# To add another file to the project just add the path to its source here
# If you don't want to specify all files you can change this into
# CSOURCES = $(shell find ./ -name "*.c")

CSOURCES = \
	src/kernel/arch/i386/boot/descriptor_tables.c \
	src/kernel/arch/i386/irq.c \
	src/kernel/arch/i386/paging.c \
	src/kernel/arch/i386/pic.c \
	src/kernel/arch/i386/cmos.c \
	src/kernel/devices/ps2kb/keyboard.c \
	src/kernel/devices/timer/timer.c \
	src/kernel/devices/tty/tty.c \
	src/kernel/devices/ramdisk/ramdisk.c \
	src/kernel/devices/ide/ide.c \
	src/kernel/devices/serial/serial.c \
	src/kernel/devices/framebuffer.c \
	src/kernel/devices/mouse.c \
	src/kernel/filesystems/vfs.c \
	src/kernel/filesystems/fat16/fat16.c \
	src/kernel/filesystems/fat16/fat16vfs.c \
	src/kernel/kernel.c \
	src/kernel/init.c \
	src/kernel/syscall.c \
	src/kernel/lib/kprintf.c \
	src/kernel/lib/read_string.c \
	src/kernel/lib/time.c \
	src/kernel/lib/graphics/text.c \
	src/kernel/lib/graphics/gfx.c \
	src/kernel/gui/window.c \
	src/kernel/gui/compositor.c \
	src/kernel/gui/cursor.c \
	src/kernel/memory/memory.c \
	src/kernel/memory/kheap.c \
	src/kernel/monitor.c \
	src/kernel/modules.c \
	src/kernel/process.c \
	src/klibc/string.c \
	src/klibc/ctype.c \

# ./kern/arch/i686/boot/interrupt.S is not included here because it is
# included directly in the file by boot.S .
# WARNING: If you need to build an assembly file adding it here is not enough:
# you also need to create a rule for it, otherwise it will be treated like a 
# C source file and compiled with gcc. Will fix later

ASMSOURCES = \
	./src/kernel/arch/i386/boot/boot.S \


OBJECT_FILES = $(patsubst %.c, %.o, $(CSOURCES)) $(patsubst %.S, %.o, $(ASMSOURCES))

.PHONY: build build-iso release run clean config create-sysroot

config:
	@. ./config.sh

create-sysroot: config
	@. ./create-sysroot.sh

build: kernel.bin

build-iso: kernel.bin
	@./build-iso.sh "kernel.bin" "$(OS_NAME)"

kernel.bin: create-sysroot $(OBJECT_FILES) 
	@$(CC) -T linker.ld -o kernel.bin $(patsubst %.o, $(OUTF)/%.o, $(OBJECT_FILES)) $(LD_FLAGS)

clean:
	rm -f -R sysroot/
	rm -f -R $(OUTF)/
	rm -f -R *.o
	rm -f -R *.bin
	rm -f -R *.iso

run: build-iso
	qemu-system-i386 \
		-cdrom "Experimental OS.iso" \
		-boot d \
		-serial stdio \
		-no-shutdown -d guest_errors

gdb: build-iso
	qemu-system-i386 \
		-cdrom "Experimental OS.iso" \
		-boot d \
		-serial stdio \
		-no-shutdown -d guest_errors \
		-s -S

run-disk: build-iso
	qemu-system-i386 \
		-cdrom "Experimental OS.iso" \
		-boot d \
		-serial stdio \
		-no-shutdown -d guest_errors \
		-drive file=isodir/boot/ramdisk.initrd,if=ide 


./src/kernel/arch/i386/boot/boot.o: config
	@$(AS) src/kernel/arch/i386/boot/boot.S -o $(OUTF)/src/kernel/arch/i386/boot/boot.o $(AS_FLAGS) -I src/kernel/arch/i386/boot/

%.o: %.c config create-sysroot
	@mkdir -p $(OUTF)/$(shell dirname $@)
	@$(CC) -c $(CC_FLAGS) $< -o $(OUTF)/$@ 
