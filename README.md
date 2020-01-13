# OS Testing Project
This is an unnamed operating system I'm creating mostly to try out stuff for fun.
There is not much it can do and it was not tested on real hardware (yet).

## How to try it
The quickest way is to download the latest build from the release tab. Right now the os 
only has support for the qemu virtual machine hardware, so it might not work in other emulators.
To run with qemu just run

    qemu-system-i386 -cdrom 'Experimental OS.iso'

If everything went right you should see a console where you can type. Remember the layout is the US one. 
To start try typing `help`. Also since relative paths are not (yet) implemented you need to write each 
path from the root, for example `ls /disk`

## How to run
Prepare a cross-compiler for i686-elf. See [here](https://wiki.osdev.org/GCC_Cross-Compiler) if you don't know how.  
Add to your enviroments variables

    export PREFIX="path/to/cross/compiler"
    export TARGET=i686-elf
    export PATH="$PREFIX/bin:$PATH"

Change the variables to point to where your cross-compiler is.  
Before all run `source config.sh`, this is necessary or the build will fail. 
You need to run this every time you open a new terminal. 
Run `make build` to create a .bin you can run with qemu.
Run `make build-iso` to create a .iso image. Requires having xorriso installed though.   
Run `make run-iso` to build and execute from the iso. This is necessary if we are using grub modules (and we are )
Run `make run` to build and run qemu with that bin.   

Note that to run using grub modules you will need to create an iso and run from that. Since we are using a 
ramdisk for now, running `make run` won't load the disk. Use `make run-iso` instead.

If you need to add another source file to the codebase you can just edit the Makefile and add the path to the new 
source code to the CSOURCES variable. 

You will also need a FAT 16 disk image that will act as a disk in ram. Create one and put it in `src/ramdisk/ramdisk.initrd`. It will be automatically included in the iso by make. 

## Notes

- This is NOT a higher-half kernel: the kernel is mapped in the lower 128MB, programs are expected to load 
after that
- Programs are to be statically linked: there is no support for dynamic linking in the ELF loader


## Done stuff
- Setups a GDT & IDT
- External interrupt support
- Clock & PS2 Keyboard drivers with the PIC 8259
- Paging, even though it's only a simple identity mapping
- Dynamic memory allocator (kernel only)
- Read only FAT16 file system with a virtual file system layer
    - Note that this works from a ramdisk for now

## In the future...
- A real memory allocator
- Long file names support for FAT16
- An ATA disk driver
- Some sort of stdin/stdout for each program
- Reading datetime from CMOS
- Relative pathnames
- More syscalls for stuff such as: reading keyboard input, file IO, allocating memory ...
- A graphical interface
- A driver for the mouse 

## Bugs/FixMes
### Keyboard related
- Not all keyboard keys are mapped
- Sometimes random keyboard events are incorrectly mapped as ENTER presses
- Keyboard modifiers are not implemented
### Multitasking related
- The program stacks need to be allocated in the low 120MB, but right now we just allocate 
and hope it allocates there. This always works on machines with 128MB or less
- When a process ends we don't actually free it's memory
### 