# Declare constants for the multiboot header.
.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

# Declare a header as in the Multiboot Standard.
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Reserve a stack for the initial thread.
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

# The kernel entry point.
.section .text

.include "interrupt.S"

.global _start
.type _start, @function
_start:
	movl $stack_top, %esp
   
   /*
      GRUB puts in %eax and %ebx a pointer to a data structure useful for 
      detecting the available memory on the system. We push these 2 registers 
      before everything else, so that we avoid accidentaly deleting them
   */
   push %eax
   push %ebx

	# Prepare the terminal, so that we can write to debug easier
	call kernel_setup

	# Transfer control to the main kernel.
	call kernel_main

	# Hang if kernel_main unexpectedly returns.
	cli
1:	hlt
	jmp 1b

.global gdt_flush

gdt_flush:
   mov 4(%esp), %eax
   lgdt (%eax)

   mov $0x10, %ax
   mov %ax, %ds
   mov %ax, %es
   mov %ax, %fs
   mov %ax, %gs
   mov %ax, %ss
   jmp $0x08, $flush
flush:
   ret

.global load_idt

load_idt:
   mov 4(%esp), %eax
   lidt (%eax)
   ret

.size _start, . - _start