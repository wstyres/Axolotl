#include "tty.h"
#include <libc/stdio/stdio.h>
#include <kernel/gdt/gdt.h>
#include <kernel/interrupts/interrupts.h>

void kernel_main() {
    create_terminal();
}