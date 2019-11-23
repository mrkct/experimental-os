#ifndef IRQ_H
#define IRQ_H
#include <kernel/arch/i386/boot/descriptor_tables.h>


void dispatch_irq(struct intframe_t*);

#endif