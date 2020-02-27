#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <kernel/devices/tty/tty.h>
#include <kernel/devices/serial/serial.h>

/*
    Copies 'str' into 'dest' and returns how many characters have been copied
*/
static int append_string(char *dest, char *str)
{
    int copied = 0;
    while (*str) {
        *dest = *str;
        str++;
        dest++;
        copied++;
    }

    return copied;
}

/*
    Writes a signed int in its string form into 'dest' and returns how many 
    characters have been written.
*/
static int append_signed_int(char *dest, int data, int base) 
{
    int characters = 0;
    bool is_negative = false;
	if (data < 0 && base == 10) {
		is_negative = true;
		data *= -1;
	}
	
	uint8_t digits[10] = {0};
	int i = 9;
	do {
		digits[i--] = data % base;
		data /= base;
	} while (data != 0); 
	
	if (is_negative && base == 10) {
        *dest = '-';
        dest++;
        characters++;
    }
	
	for (i = i+1; i < 10; i++) {
		if (digits[i] < 10)
            *dest = '0' + digits[i];
		else
            *dest = 'a' + (digits[i] - 10);
        dest++;
        characters++;
	}

    return characters;
}

/*
    Writes an unsigned int in its string form into 'dest' and returns how 
    many characters have been written
*/
static int append_unsigned_int(char *dest, unsigned data, int base) 
{
    int characters = 0;
	
	uint8_t digits[10] = {0};
	int i = 9;
	do {
		digits[i--] = data % base;
		data /= base;
	} while (data != 0); 
	
	for (i = i+1; i < 10; i++) {
		if (digits[i] < 10)
            *dest = '0' + digits[i];
		else
            *dest = 'a' + (digits[i] - 10);
        dest++;
        characters++;
	}

    return characters;
}

static int kvprintf(char *str, char *format, va_list args)
{
    char *start_of_string = str;

    char *current = format;
    bool in_format = false;
    while (*current) {
        if (in_format) {
            switch (*current) {
            case 'd':
                str += append_signed_int(str, va_arg(args, int), 10);
                break;
            case 'u':
                str += append_unsigned_int(str, va_arg(args, int), 10);
                break;
            case '%':
                *str++ = '%';
                break;
            case 'x':
            case 'X':
                str += append_unsigned_int(str, va_arg(args, int), 16);
                break;
            case 'p':
                *str++ = '0';
                *str++ = 'x';
                str += append_unsigned_int(str, va_arg(args, int), 16);
                break;
            case 'b':
                str += append_unsigned_int(str, va_arg(args, int), 2);
                break;
            case 's':
                str += append_string(str, va_arg(args, char*));
                break;
            case 'c':
                // This is correct as 'int'. 
                // 'char' gets promoted to 'int' when passed through '...'
                *str++ = (char) va_arg(args, int);
                break;
            default:
                str += append_string(str, "[ksprintf: unknown specifier]");
                break;
            }
            in_format = false;
        } else {
            if (*current == '%') {
                in_format = true;
            } else {
                *str++ = *current;
            }
        }
        current++;
    }
    *str++ = '\0';

    return str - start_of_string;
}

char buffer[4096];

int kprintf(char *format, ...)
{
    va_list args;
    va_start(args, format);
    /*
        We don't dynamically allocate this buffer because when we call 
        kprintf we might have not setup paging yet
    */
    int printed = kvprintf(buffer, format, args);
    terminal_writestring(buffer);
    serial_write(buffer);
    va_end(args);

    return printed;
}