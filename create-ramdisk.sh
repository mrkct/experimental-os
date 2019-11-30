#! /bin/sh

# TODO: This should read the content of the ramdisk folder
# and create a FAT32 image of it and store it in a file
# called ramdisk.initrd

mkdir -p src/ramdisk/
rm -f src/ramdisk/ramdisk.initrd
echo "This is your ramdisk" > src/ramdisk/ramdisk.initrd