#include <stdint.h>
#include <stdbool.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

uint16_t *screen = (uint16_t *) 0xb8000;
unsigned char color = 0;
int pos = 0;

void terminal_putchar(char c)
{
	screen[pos++] = (uint16_t) c | (color << 8);
}

void terminal_writeint(int data, const int base)
{
	bool is_negative = false;
	if (data < 0) {
		is_negative = true;
		data *= -1;
	}
	
	uint8_t digits[10] = {0};
	int i = 9;
	do {
		digits[i--] = data % base;
		data /= base;
	} while (data != 0); 
	
	if (is_negative && base == 10)
		terminal_putchar('-');
	
	for (i = i+1; i < 10; i++) {
		if (digits[i] < 10)
			terminal_putchar('0' + digits[i]);
		else
			terminal_putchar('a' + (digits[i] - 10));
	}
	pos = 0;
}

void _start() {
	int i = 0;
	while (1) {
		terminal_writeint(i++, 10);
		color++;
	};
}
