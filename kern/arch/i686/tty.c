#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <kernel/tty.h>
#include <kernel/i686/x86.h>

#define TAB_SIZE 4
 
size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

static void update_cursor(void);

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
 
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
 
void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}
 
void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
	update_cursor();
}
 
/**
 * Moves the terminal cursor to the next line. If there are no more
 * rows availabled it moves all the content before up one row to make space
**/
void terminal_nextline(void)
{
    terminal_column = 0;
    if (++terminal_row == VGA_HEIGHT) {
        terminal_row = VGA_HEIGHT - 1;
        for (size_t row = 1; row < VGA_HEIGHT; row++) {
            for (size_t col = 0; col < VGA_WIDTH; col++) {
                terminal_buffer[VGA_WIDTH * (row-1) + col] = terminal_buffer[VGA_WIDTH * row + col];
            }
        }
		for (size_t col = 0; col < VGA_WIDTH; col++) {
			terminal_putentryat(' ', terminal_color, col, VGA_HEIGHT-1);
		}
    }
}

void terminal_putchar(char c) 
{
    if (c == '\n') {
        terminal_nextline();
        return;
    } else if (c == '\t') {
        int spaces = VGA_WIDTH - terminal_column;
        if (spaces > TAB_SIZE)
            spaces = TAB_SIZE;
        for (int i = 0; i < TAB_SIZE; i++)
            terminal_putchar(' ');
        return;
    } else if (c == '\b') {
		terminal_column = terminal_column > 0 ? terminal_column - 1 : 0 ;
		terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
		return;
	}
    
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_nextline();
	}
}
 
void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}
 
void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}

/**
 * Prints an integer, note that this only supports integers
 * up to 4 bytes. This is only guaranteed to support up-to base 16
 */
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
}

void terminal_clear(void)
{
	terminal_row = 0;
	terminal_column = 0;
	for (size_t i = 0; i < VGA_WIDTH; i++)
		for (size_t j = 0; j < VGA_HEIGHT; j++)
			terminal_putentryat(' ', terminal_color, i, j);
}

static void update_cursor(void)
{
	uint16_t pos = terminal_row * VGA_WIDTH + (terminal_column+1);
 
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}