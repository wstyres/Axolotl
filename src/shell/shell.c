#include "shell.h"

#include <stdlib/string/string.h>
#include <kernel/tty.h>
#include <drivers/kb.h>

void shell() {
    write("axolotl> ");

    char *input = get_input();
    write("\n got input");
    write(input);
}