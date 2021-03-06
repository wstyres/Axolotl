#ifndef STRING_H
#define STRING_H

#include <stddef.h>

size_t strlen(const char*);
int strcmp(const char *lhs, const char *rhs);
char *strcat(char *dest, const char *src);
char *strccat(char* dest, char src);
char* itoa(int i, char b[]);
void* memset(void* bufptr, int value, size_t size);

#endif