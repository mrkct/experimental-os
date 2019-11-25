# OS Testing Project
This is an unnamed operating system I'm creating mostly to try out stuff for fun.
There is not much it can do and it was not tested on real hardware (yet).

## How to try it
The quickest way is to download the latest build from the release tab. Right now the os 
only has support for the qemu virtual machine hardware, so it might not work in other emulators.
To run with qemu just run

    qemu-system-i386 -cdrom 'Experimental OS.iso'

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
Run `make run` to build and run qemu with that bin.  
Run `make build-iso` to create a .iso image. Requires having xorriso installed though.  

If you need to add another source file to the codebase you can just edit the Makefile and add the path to the new 
source code to the CSOURCES variable. 

## Done stuff
- Setups a GDT & IDT
- External interrupt support
- Clock & PS2 Keyboard drivers with the PIC 8259
- Paging, even though it's only a simple identity mapping
- Dynamic memory allocator (kernel only)

## Todo
- A filesystem:
    - At first a virtual one, in RAM
- Able to load & run programs