#include "stdlib.h"

static char memory[32768];
static char *mem_end;

void initialize_memory() {
    mem_end = memory;
}

void *malloc(int size) {
    char *temp = mem_end;
    mem_end += size;
    return (void*)temp;
}