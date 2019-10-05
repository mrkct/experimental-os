/* Declare constants for the multiboot header. */
.set ALIGN,    1<<0             /* align loaded modules on page boundaries */
.set MEMINFO,  1<<1             /* provide memory map */
.set FLAGS,    ALIGN | MEMINFO  /* this is the Multiboot 'flag' field */
.set MAGIC,    0x1BADB002       /* 'magic number' lets bootloader find the header */
.set CHECKSUM, -(MAGIC + FLAGS) /* checksum of above, to prove we are multiboot */

/* Declare constants for memory spaces */
.set STACK_SIZE,	16384		# 16KB
.set TSS_SIZE,		1024		#  1KB

/* 
Declare a multiboot header that marks the program as a kernel. These are magic
values that are documented in the multiboot standard. The bootloader will
search for this signature in the first 8 KiB of the kernel file, aligned at a
32-bit boundary. The signature is in its own section so the header can be
forced to be within the first 8 KiB of the kernel file.
*/
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM
 
/*
The multiboot standard does not define the value of the stack pointer register
(esp) and it is up to the kernel to provide a stack. This allocates room for a
small stack by creating a symbol at the bottom of it, then allocating 16384
bytes for it, and finally creating a symbol at the top. The stack grows
downwards on x86. The stack is in its own section so it can be marked nobits,
which means the kernel file is smaller because it does not contain an
uninitialized stack. The stack on x86 must be 16-byte aligned according to the
System V ABI standard and de-facto extensions. The compiler will assume the
stack is properly aligned and failure to align the stack will result in
undefined behavior.
*/
.section .bss
.align 16
stack_bottom:
.skip STACK_SIZE
stack_top:
 
/*
The linker script specifies _start as the entry point to the kernel and the
bootloader will jump to this position once the kernel has been loaded. It
doesn't make sense to return from this function as the bootloader is gone.
*/
.section .text
.global _start
.type _start, @function
_start:

	mov $stack_top, %esp		# Setup stack so that we can call C functions from now on

	cli							# Disable interrupts, these need to be disabled until we setup the IDT
	call setup_gdt				# Call a C function that setups the GDT. The GDT is a space defined below
	jmp gdt_setup_ok			# Jump past the 'reload_gdt' function declaration below

	.global reload_gdt
	reload_gdt:
		
    	lgdt gdtdesc
    	jmp $0x08, $complete_flush

		complete_flush:
    		mov %ax, 0x10
			mov %ds, %ax
			mov %es, %ax
			mov %fs, %ax
			mov %gs, %ax
			mov %ss, %ax
		ret
	
	gdt_setup_ok:
	
	call kernel_main
 
	/*
		If the kernel returns (and it shouldn't) we halt the processor.
	*/

	cli
1:	hlt
	jmp 1b
 

.p2align 2
/**
	The GDT is set in setup_gdt in kernel.c
	Here we reserve the space and make it visible outside this file.
	It will have 3 segments: NULL, Code, Data and a TSS
**/

.global gdt
gdt:
	.skip 32			# 8 byte per segment * 4
gdtdesc:
	.word 0x1f			# sizeof(gdt) - 1 (31)
	.long gdt			# address of gdt

.global tss
tss: .skip TSS_SIZE		# sizeof(tss) = 1KB

/*
Set the size of the _start symbol to the current location '.' minus its start.
This is useful when debugging or when you implement call tracing.
*/
.size _start, . - _start