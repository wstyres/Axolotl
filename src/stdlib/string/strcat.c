#include "string.h"

char* strcat(char *dest, const char *src) {
	size_t i,j;
	for (i = 0; dest[i] != '\0'; i++)
			;
	for (j = 0; src[j] != '\0'; j++)
			dest[i+j] = src[j];
	dest[i+j] = '\0';
	return dest;
}

char* strccat(char* dest, char src) {
	size_t i;
	for (i = 0; dest[i] != '\0'; i++)
		;
	dest[i] = src;
	dest[i+1] = '\0';
	return dest;
}