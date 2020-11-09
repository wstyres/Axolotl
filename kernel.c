#include <stddef.h>
#include <stdint.h>

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

// Size of the terminal
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row; // Current y position of terminal
size_t terminal_column; // Current x position of terminal
uint8_t terminal_color; // Current color of terminal
uint16_t *terminal_buffer; // Terminal buffer array

uint8_t create_vga_color(enum vga_color foreground_color, enum vga_color background_color) {
    // Creates a VGA Color from a foreground color and a background color
    return foreground_color | background_color << 4;
}

uint16_t create_vga_character(char character, uint8_t color) {
    // Creates a VGA character with a text color
    return (uint16_t)character | (uint16_t)color << 8;
}

size_t strlen(const char *s) {
    // Re-implementation of stdlib strlen since we don't have access to stdlib
    size_t len = 0;
    while (s[len])
        len++;
    return len;
}

void create_terminal() {
    // Initializes the terminal
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = create_vga_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    terminal_buffer = (uint16_t *)0xB8000;

    // Since we don't have any memory allocation yet, we initialize the buffer to all blank.
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t i = y * VGA_WIDTH + x;
            terminal_buffer[i] = create_vga_character(' ', terminal_color);
        }
    }
}

void putcharat(char c, uint8_t color, size_t x, size_t y) {
    // Puts a character at a given location
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = create_vga_character(c, color);
}

void putchar(char c) {
    // Puts a character at the current terminal location
    if (c == '\n') {
        terminal_column = 0;
        terminal_row++;
        return;
    }
        
    putcharat(c, terminal_color, terminal_column, terminal_row);
    if (++terminal_column == VGA_WIDTH) { 
        terminal_column = 0; // If the next column goes beyond the screen, reset it to 0
        if (++terminal_row == VGA_HEIGHT) 
            terminal_row = 0; // If the next row goes beyond the screen, reset it to 0
    }
}

void print(const char *s) {
    size_t length = strlen(s);
    for (size_t i = 0; i < length; i++) {
        putchar(s[i]);
    }
}

void kernel_main() {
    create_terminal();

    for (int i = 0; i < VGA_HEIGHT; i++) {
        print("Hello, World!\n");
    }
}