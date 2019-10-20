
PROJECTS = kern

# The '-g' adds debugging symbols
AS_FLAGS = -g
CC_FLAGS = -std=gnu11 -ffreestanding -Wall -Wextra -g
LD_FLAGS = -ffreestanding -nostdlib -lgcc -g

OBJF = out

OBJECT_FILES = \
$(OBJF)/boot.o \
$(OBJF)/kernel.o \
$(OBJF)/tty.o \
$(OBJF)/kprintf.o \
$(OBJF)/descriptor_tables.o \
$(OBJF)/pic.o \
$(OBJF)/irq.o \
$(OBJF)/timer.o \

.PHONY: build release run clean config create-sysroot

config:
	. ./config.sh

create-sysroot: config
	. ./create-sysroot.sh

build: myos.bin

myos.bin: create-sysroot boot.o kernel.o tty.o kprintf.o descriptor_tables.o pic.o irq.o timer.o 
	$(CC) -T linker.ld -o myos.bin $(OBJECT_FILES) $(LD_FLAGS)

build-iso: myos.bin
	echo "guarda osdev barebones, non ho impostato"

clean:
	rm -f -R sysroot/
	rm -f -R $(OBJF)/
	rm -f -R *.o
	rm -f -R *.bin
	rm -f -R *.iso

run: myos.bin
	qemu-system-i386 -kernel myos.bin -d guest_errors

run-gdb: myos.bin
	qemu-system-i386 -kernel myos.bin -d guest_errors -s -S

boot.o: config
	$(AS) kern/arch/i686/boot/boot.S -o $(OBJF)/boot.o $(AS_FLAGS) -I kern/arch/i686/boot

interrupt.o: config
	$(AS) kern/arch/i686/boot/interrupt.S -o $(OBJF)/interrupt.o $(AS_FLAGS)

kernel.o: config
	$(CC) -c kern/kernel/kernel.c -o $(OBJF)/kernel.o $(CC_FLAGS)

tty.o: config
	$(CC) -c kern/arch/i686/tty.c -o $(OBJF)/tty.o $(CC_FLAGS)

descriptor_tables.o: config
	$(CC) -c kern/arch/i686/boot/descriptor_tables.c -o $(OBJF)/descriptor_tables.o $(CC_FLAGS)

kprintf.o: config
	$(CC) -c kern/kernel/kprintf.c -o $(OBJF)/kprintf.o $(CC_FLAGS)

pic.o: config
	$(CC) -c kern/arch/i686/pic.c -o $(OBJF)/pic.o $(CC_FLAGS)

irq.o: config
	$(CC) -c kern/arch/i686/irq.c -o $(OBJF)/irq.o $(CC_FLAGS)

timer.o: config
	$(CC) -c kern/arch/i686/timer.c -o $(OBJF)/timer.o $(CC_FLAGS)