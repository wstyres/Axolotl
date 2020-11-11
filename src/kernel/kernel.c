#include "tty.h"
#include <libc/stdio/stdio.h>
#include <kernel/gdt/gdt.h>

void kernel_main() {
    create_terminal();

    write("Initializing GDT Tables...\n");
    gdt_table_initialize();
    write("GDT Tables Initialized.\n");
}