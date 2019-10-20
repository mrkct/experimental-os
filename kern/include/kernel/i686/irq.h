#ifndef IRQ_H
#define IRQ_H
#include <kernel/i686/descriptor_tables.h>


void dispatch_irq(struct intframe_t*);

#endif