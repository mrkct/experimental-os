#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <kernel/i686/x86.h>
#include <kernel/i686/pic.h>

#define PIC1_COMMAND	0x20
#define PIC1_DATA		0x21
#define PIC2_COMMAND	0xA0
#define PIC2_DATA		0xA1


static uint32_t irq_offset = 0;

/*
	Reprograms the PIC to route the 16 external interrupts from the 
	argument offset. This is required, as the PIC 8259 by defaults routes 
	those in the first 16 interrupts, which are reserved by Intel. As such, 
	offset needs to be a number between [32, 255 - 16]
*/
void pic_init(uint8_t offset)
{
	if (offset < 16 || offset > 256 - 16) {
		// TODO: Warn that this is not legal
		return ;
	}
	uint8_t mask1, mask2;

	mask1 = inb(PIC1_DATA);
	mask2 = inb(PIC2_DATA);

	outb(PIC1_COMMAND, 0x11);
	outb(PIC2_COMMAND, 0x11);
	outb(PIC1_DATA, offset);
	outb(PIC2_DATA, offset + 8);
	outb(PIC1_DATA, 0x04);
	outb(PIC2_DATA, 0x02);
	outb(PIC1_DATA, 0x01);
	outb(PIC2_DATA, 0x01);

	outb(PIC1_DATA, mask1);
	outb(PIC2_DATA, mask2);

	irq_offset = offset;
}

/*
	Use this to signal to the PIC that you have acknowledged the last interrupt 
	Note that before calling this you must have called pic_init at least once 
	before.
	irq_number: The number of the IRQ, without considering the offset
*/ 

void pic_ack(uint32_t irq_number)
{
	if (irq_offset == 0) {
		// TODO: Warning, you have not called pic_init before this
		return ;
	}
	if (irq_number >= irq_offset + 8) {
		outb(PIC2_COMMAND, 0x20);
	}
	outb(PIC1_COMMAND, 0x20);
}