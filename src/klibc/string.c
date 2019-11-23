#include <stddef.h>
#include <stdint.h>
#include <klibc/string.h>



size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

int strcmp(const char *a, const char *b)
{
    while (*a && *b && *a++ == *b++) {
        ;
    }
    if (*a == '\0' && *b == '\0')
        return 0;
    else if (*a - *b < 0)
        return -1;
    else
        return +1;
}

char *strcpy(char *destination, const char *source)
{
    char *r = destination;
    while (*source) {
        *destination++ = *source++;
    }
    *destination = '\0';


    return r;
}