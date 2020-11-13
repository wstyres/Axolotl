#include "shell.h"

#include <stdlib/string/string.h>
#include <kernel/tty.h>
#include <drivers/kb.h>
#include <stdlib/stdlib.h>

void addcursor() {
    writechar('_');
}

void removecursor() {
    deletechar();
}

char *getinput() {
    char *input = malloc(sizeof(char) * 256);
    char c = 0;
    addcursor();
    do {
        c = getchar();
        if (c == '\b') { // Backspace
            size_t length = strlen(input);
            if (length > 0) {
                input[length - 1] = '\0';
                removecursor();
                deletechar();
                addcursor();
            }
        }
        else {
            removecursor();
            strccat(input, c);
            writechar(c);
            addcursor();
        }
    } while (c != '\n');
    removecursor();

    return input;
}

void shell() {
    write("axolotl> ");

    char *input = getinput();
}