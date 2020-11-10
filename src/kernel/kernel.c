#include "tty.h"

void kernel_main() {
    create_terminal();

    write("Hello, World!");
}