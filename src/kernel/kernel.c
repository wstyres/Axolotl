#include "tty.h"
#include <stdlib/stdio/stdio.h>
#include <shell/shell.h>
#include <stdlib/stdlib.h>

void kernel_main() {
    create_terminal();

    printf("Initializing Memory...\n");
    initialize_memory();
    printf("Memory Initialized!\n");

	shell();
}