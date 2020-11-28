#include "shell.h"

#define SHELL_VERSION "0.1.0"

#include <stdlib/string/string.h>
#include <kernel/tty.h>
#include <drivers/kb.h>
#include <stdlib/stdlib.h>
#include <kernel/clock.h>
#include <stdlib/stdio/stdio.h>

enum Commands {
    TimeCommand,
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

void time_command() {
    printf("The current time is %s\n", date_time());
}

void help_command() {
    printf("Axolotl Shell, version " SHELL_VERSION " (i386)\n");
    printf("These shell commands are defined internally.  Type 'help' to see this list.\n");
    printf("Type 'help name' to find out more about the function 'name'.\n");
    for (int i = 0; i < CommandCount; i++) {
        printf("\n\t");
        printf(commands[i].name);
        printf("\t");
        printf(commands[i].description);
    }
    printf("\n\n");
}

void initialize_commands() {
    commands = malloc(sizeof(command_t) * CommandCount);

    commands[TimeCommand].name = "time";
    commands[TimeCommand].description = "Display the current system time";
    commands[TimeCommand].function = time_command;

    commands[HelpCommand].name = "help";
    commands[HelpCommand].description = "Display help information";
    commands[HelpCommand].function = help_command;
}

void perform_command(const char *command) {
    for (int i = 0; i < CommandCount; i++) {
        if (strcmp(command, commands[i].name) == 0) {
            void(*command_function)(void) = commands[i].function;
            command_function();
            return;
        }
    }

    printf("command not found: %s\n", command);
}

void shell() {
    initialize_commands();

    while (1) {
        printf("axolotl> ");

        char *input = getinput();
        perform_command(input);
    }
}