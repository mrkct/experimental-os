#! /bin/sh

# This scripts assumes there already exists a .bin file with the kernel
# and creates a grub.cfg file and the .iso image from the .bin.
# This takes 2 arguments: the first is the .bin file, the second is the
# name that will appear in the GRUB entry. This will also be the filename
# of the created .iso

rm grub.cfg -f
echo "
# Warning: this file is auto-generated by ./build-iso.sh
# Any changes here will be deleted next time you 'make build-iso'
menuentry \"$2\" {
	multiboot /boot/$1
}" > grub.cfg

mkdir -p isodir/boot/grub
cp $1 isodir/boot/$1
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o "$2.iso" isodir