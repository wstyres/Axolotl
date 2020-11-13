#include "shell.h"

#include <stdlib/string/string.h>
#include <kernel/tty.h>
#include <drivers/kb.h>
#include <stdlib/stdlib.h>

char *getinput() {
    char *input = malloc(sizeof(char) * 256);
    char c = 0;
    do {
        c = getchar();
        if (c == '\b') { // Backspace
            size_t length = strlen(input);
            if (length > 0) {
                input[length - 1] = '\0';
                deletechar();
            }
        }
        else {
            strccat(input, c);
            writechar(c);
        }
    } while (c != '\n');
    return input;
}

void shell() {
    write("axolotl> ");

    char *input = getinput();
}