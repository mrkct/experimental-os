#include <stdio.h>
#include "fat16util.h"


void print_s(char *s, int size)
{
    for (int i = 0; i < size; i++) {
        printf("%c", s[i]);
    }
}

void print_filename(char *filename) {
    print_s(filename, 11);
}