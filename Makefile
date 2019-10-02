build:
	./setpath.sh
	i686-elf-as boot.s -o boot.o
	i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -nostdlib boot.o kernel.o -lgcc

release:
	echo "guarda osdev barebones, non ho impostato"

run: build
	qemu-system-i386 -kernel myos.bin
