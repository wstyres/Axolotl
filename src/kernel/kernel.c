#include "tty.h"
#include <libc/stdio/stdio.h>

void kernel_main() {
    create_terminal();

    printf("Hello, World!\n");
}