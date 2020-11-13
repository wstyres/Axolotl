#include "tty.h"
#include <stdlib/stdio/stdio.h>
#include <shell/shell.h>
#include <stdlib/stdlib.h>
#include <drivers/kb.h>

void kernel_main() {
    create_terminal();

    printf("Initializing Memory...\n");
    initialize_memory();
    printf("Memory Initialized!\n");

    printf("Initializing PICS...\n");
    init_pics(0x20, 0x28);
    printf("PICS Initialized!\n");

	shell();
}