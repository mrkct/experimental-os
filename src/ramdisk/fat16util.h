#ifndef FAT16UTIL_H
#define FAT16UTIL_H

void print_s(char*, int);
void print_filename(char *filename);
int fat16_filenamecmp(char *a, char *b);

#endif