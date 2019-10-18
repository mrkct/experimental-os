# OS Testing Project
There is not much here.

## Next steps

anche se `interrupt.s` è compilato e linkato sembra che il suo contenuto non è neanche visto dagli altri.
per verificare se è vero:
    - forse gcc toglie tutto perchè non viene usato niente adesso?
    - aggiungi una funzione e chiamala dal C per verificare --> è vero
se effettivamente è ignorato possiamo:
    - buttare tutto in `boot.s`
    - cercare di fixare, magari con .include
        - prima non andava .include "interrupt.s" dicendo che non trova il file
        - leggiti la documentazione

## How to run
Prepare a cross-compiler for i686-elf.  
Add to your variables

    export PREFIX="$HOME/opt/cross"
    export TARGET=i686-elf
    export PATH="$PREFIX/bin:$PATH"

Change the variables to point to where your cross-compiler is.  
Before all run `source config.sh`, this is necessary or building will fail. 
You need to run this every time you open a new terminal. 
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