
PROJECTS = kern

CC_FLAGS = -std=gnu11 -ffreestanding -O2 -Wall -Wextra
LD_FLAGS = -ffreestanding -nostdlib -lgcc

OBJF = out

OBJECT_FILES = \
$(OBJF)/boot.o \
$(OBJF)/kernel.o \
$(OBJF)/tty.o

.PHONY: build release run clean config create-sysroot

config:
	. ./config.sh

create-sysroot: config
	. ./create-sysroot.sh

build: myos.bin

myos.bin: create-sysroot boot.o kernel.o tty.o
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
	qemu-system-i386 -kernel myos.bin

boot.o: config
	$(AS) kern/arch/i686/boot/boot.s -o $(OBJF)/boot.o

kernel.o: config
	$(CC) -c kern/kernel/kernel.c -o $(OBJF)/kernel.o $(CC_FLAGS)

tty.o: config
	$(CC) -c kern/arch/i686/tty.c -o $(OBJF)/tty.o $(CC_FLAGS)