# OS Testing Project
There is not much here.

## How to run
Prepare a cross-compiler for i686-elf.  
Add to your variables

    export PREFIX="$HOME/opt/cross"
    export TARGET=i686-elf
    export PATH="$PREFIX/bin:$PATH"

Change the variables to point to where your cross-compiler is.  
Run `make build` to create a .bin you can run with qemu.  
Run `make run` to build and run qemu with that bin.  
Run `make build-iso` to create a .iso image. Requires having xorriso installed though.  

## Done stuff
- It boots
- It setups a GDT
- It has basic support for writing to a terminal

## Todo
- Load the rest of the kernel from disk
- Setup an IDT
- Setup a few drivers for clock, keyboard and even mouse?
- Create a FAT filesystem driver
- Run a programming language like LUA