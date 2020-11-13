#ifndef TTY_H
#define TTY_H

#include <stddef.h>

void create_terminal();
void writechar(char c);
void deletechar();
void write(const char* data);

#endif