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

void *memset(void *str, int c, size_t n)
{
    char *from = (char *) str;
    char *end = (char *) (from + n);
    while (from < end) {
        *from = (unsigned char) c;
        from++;
    }

    return str;
}

void *memcpy(void *str1, const void *str2, size_t n)
{
    char *s1 = (char *) str1;
    char *s2 = (char *) str2;
    for (size_t i = 0; i < n; i++) {
        s1[i] = s2[i]; 
    }

    return str1;
}