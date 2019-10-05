
PROJECTS = kern

CC_FLAGS = -std=gnu11 -ffreestanding -O2 -Wall -Wextra
LD_FLAGS = -ffreestanding -nostdlib -lgcc

.PHONY: build release run clean

build: boot.o kernel.o tty.o
	$(CC) -T linker.ld -o myos.bin boot.o kernel.o tty.o $(LD_FLAGS)

release:
	echo "guarda osdev barebones, non ho impostato"

clean:
	rm -f -R sysroot/
	rm -f -R *.o
	rm -f -R *.bin
	rm -f -R *.iso

run: build
	qemu-system-i386 -kernel myos.bin

boot.o:
	$(AS) kern/arch/i686/boot/boot.s -o boot.o

kernel.o:
	$(CC) -c kern/kernel/kernel.c -o kernel.o $(CC_FLAGS)

tty.o:
	$(CC) -c kern/arch/i686/tty.c -o tty.o $(CC_FLAGS)