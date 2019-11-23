#ifndef PIC_H
#define PIC_H
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>


void pic_init(uint8_t);
void pic_ack(uint32_t);


#endif