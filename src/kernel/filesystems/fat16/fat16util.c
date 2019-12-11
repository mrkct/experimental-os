#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "fat16.h"
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


int fat16_filenamecmp(char *a, char *b) {
    char buffer1[FAT_FILENAME_LENGTH+1];
    char buffer2[FAT_FILENAME_LENGTH+1];
    
    int i = 0;
    int j = 0;
    while (i < FAT_FILENAME_LENGTH) {
        if (a[i] != ' ' && a[i] != '.') {
            buffer1[j++] = toupper(a[i]);
        }
        i++;
    }
    buffer1[j] = '\0';

    i = 0;
    j = 0;
    while (i < FAT_FILENAME_LENGTH) {
        if (b[i] != ' ' && b[i] != '.') {
            buffer2[j++] = toupper(b[i]);
        }
        i++;
    }
    buffer2[j] = '\0';
    
    return strcmp(buffer1, buffer2);
}