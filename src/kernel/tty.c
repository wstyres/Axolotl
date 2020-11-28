#include <stddef.h>
#include <stdint.h>

#include <kernel/tty.h>
#include <stdlib/string/string.h>
#include <stdlib/sys/io.h>

// Size of the terminal
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row; // Current y position of terminal
size_t terminal_column; // Current x position of terminal
enum vga_color text_color; // Current text color of the terminal
enum vga_color background_color; // Current background color of the terminal
uint8_t terminal_color; // Current color of terminal, combination of text_color and background_color
uint16_t *terminal_buffer; // Terminal buffer array

uint8_t create_vga_color(enum vga_color foreground_color, enum vga_color background_color) {
    // Creates a VGA Color from a foreground color and a background color
    return foreground_color | background_color << 4;
}

void set_text_color(enum vga_color color) {
    text_color = color;
    terminal_color = create_vga_color(text_color, background_color);
}

void set_background_color(enum vga_color color) {
    background_color = color;
    terminal_color = create_vga_color(text_color, background_color);
}

uint16_t create_vga_character(char character, uint8_t color) {
    // Creates a VGA character with a text color
    return (uint16_t)character | (uint16_t)color << 8;
}

void create_terminal() {
    // Initializes the terminal
    terminal_row = 0;
    terminal_column = 0;
    set_text_color(VGA_COLOR_WHITE);
    set_background_color(VGA_COLOR_BLACK);
    terminal_buffer = (uint16_t *)0xB8000;

    // Since we don't have any memory allocation yet, we initialize the buffer to all blank.
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t i = y * VGA_WIDTH + x;
            terminal_buffer[i] = create_vga_character(' ', terminal_color);
        }
    }
}

void scroll_down() {
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            terminal_buffer[y * VGA_WIDTH + x] = terminal_buffer[(y + 1) * VGA_WIDTH + x];
        }
    }
    terminal_row--;
}

void addcursor() {
    writechar('_');
}

void removecursor() {
    deletechar();
}

void writecharat(char c, uint8_t color, size_t x, size_t y) {
    // Puts a character at a given location
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = create_vga_character(c, color);
}

void writechar(char c) {
    // Puts a character at the current terminal location
    if (c == '\n') {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT)
            scroll_down();
        return;
    } else if (c == '\t') {
        terminal_column += 4;
        if (terminal_column >= VGA_WIDTH) {
            terminal_column = 0;
            if (++terminal_row == VGA_HEIGHT)
                scroll_down();
        }
        return;
    }
        
    writecharat(c, terminal_color, terminal_column, terminal_row);
    if (++terminal_column == VGA_WIDTH) { 
        terminal_column = 0; // If the next column goes beyond the screen, reset it to 0
        if (++terminal_row == VGA_HEIGHT)
            scroll_down();
    }
}

void deletechar() {
    // Deletes the character at the current terminal location
    writecharat(' ', terminal_color, terminal_column - 1, terminal_row);
    terminal_column--;
}

void write(const char *s) {
    size_t length = strlen(s);
    for (size_t i = 0; i < length; i++) {
        writechar(s[i]);
    }
}