#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <kernel/tty.h>


int kprintf(char *format, ...)
{
    va_list args;
    va_start(args, format);

    int printed = 0;
    char *current = format;
    bool in_format = false;
    while (*current) {
        if (in_format) {
            switch (*current) {
            case 'd':
                terminal_writeint(va_arg(args, int), 10);
                break;
            case '%':
                terminal_putchar('%');
                break;
            case 'x':
            case 'X':
                terminal_writeint(va_arg(args, int), 16);
                break;
            case 'b':
                terminal_writeint(va_arg(args, int), 2);
                break;
            case 's':
                terminal_writestring(va_arg(args, char*));
                break;
            case 'c':
                // This is correct as 'int'. 
                // 'char' gets promoted to 'int' when passed through '...'
                terminal_putchar(va_arg(args, int));
                break;
            default:
                terminal_writestring("[kprintf: unknown specifier]");
                break;
            }
            in_format = false;
            printed++;
        } else {
            if (*current == '%') {
                in_format = true;
            } else {
                terminal_putchar(*current);
            }
        }
        current++;
    }

    va_end(args);

    return printed;
}