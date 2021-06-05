#include "tty.h"
#include <stdlib/stdio/stdio.h>
#include <shell/shell.h>
#include <stdlib/stdlib.h>
#include <drivers/kb.h>
#include "desc_tables.h"

void kernel_main() {
    create_terminal();

    printf("Initializing Memory...\n");
    initialize_memory();
    printf("Memory Initialized!\n");

    // printf("Initializing Keyboard Driver...\n");
    // initialize_keyboard();
    // printf("PICS Initialized!\n");

    printf("Initializing Interrupt Tables...\n");
    init_descriptor_tables();
    printf("Descriptor Tables Initialized!\n");

    printf("Testing Interrupts...\n");
    asm volatile("int $0x3");
    asm volatile("int $0x4");

    // create_terminal();
	// shell();
}