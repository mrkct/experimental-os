## Createdisk 

Creates a disk image where each sector is a repeated consecutive byte. This is used to create a disk for testing the IDE reading code. See `__ide_test_readsect` in `kernel/devices/ide/` for more info.  
For example:
00000....512 times
11111....512 times
22222....512 times
.....

To build just:

    gcc createdisk.c -o sd

To run:

    ./sd <size of the disk in MB> <filename>

For example: `./sd 1 disk.img`

