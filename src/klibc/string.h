#ifndef KSTRING_H
#define KSTRING_H

size_t strlen(const char *);
int strcmp(const char *, const char *);
char *strcpy(char *, const char*);
void *memset(void *, int, size_t);
void *memcpy(void *, const void *, size_t);

#endif