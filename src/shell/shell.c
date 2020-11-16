#include "shell.h"

#include <stdlib/string/string.h>
#include <kernel/tty.h>
#include <drivers/kb.h>
#include <stdlib/stdlib.h>

enum Commands {
    HelpCommand,
    CommandCount
};

typedef struct {
    char *name;
    char *description;
    void *function;
} command_t;

command_t *commands;

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

void help_command() {
    write("\nAvailable commands:\n");
    write("Type \'help\' to see this list\n");
    for (int i = 0; i < CommandCount; i++) {
        write("\n\t");
        write(commands[i].name);
        write("\t");
        write(commands[i].description);
    }
    write("\n\n");
}

void initialize_commands() {
    commands = malloc(sizeof(command_t) * CommandCount);

    commands[HelpCommand].name = "help";
    commands[HelpCommand].description = "Display help information";
    commands[HelpCommand].function = help_command;
}

void perform_command(const char *command) {
    for (int i = 0; i < CommandCount; i++) {
        if (strcmp(command, commands[i].name) == 0) {
            void(*command_function)(void) = commands[i].function;
            command_function();
        }
    }
}

void shell() {
    initialize_commands();

    while (1) {
        write("axolotl> ");

        char *input = getinput();
        perform_command(input);
    }
}