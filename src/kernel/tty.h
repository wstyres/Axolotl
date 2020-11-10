#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>

void create_terminal();
void putchar(char c);
void write(const char* data);

#endif