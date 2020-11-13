#include "kb.h"

#include <stdlib/sys/io.h>
#include <stdlib/stdlib.h>
#include <stdlib/string/string.h>
#include <kernel/tty.h>

unsigned char en_us_scancodes[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,

    '*',
    0,   /* Alt */
    ' ', /* Space bar */
    0,   /* Caps lock */
    0,   /* 59 - F1 key ... > */
    0, 0, 0, 0, 0, 0, 0, 0,
    0, /* < ... F10 */
    0, /* 69 - Num lock*/
    0, /* Scroll Lock */
    0, /* Home key */
    0, /* Up Arrow */
    0, /* Page Up */
    '-',
    0, /* Left Arrow */
    0,
    0, /* Right Arrow */
    '+',
    0, /* 79 - End key*/
    0, /* Down Arrow */
    0, /* Page Down */
    0, /* Insert Key */
    0, /* Delete Key */
    0, 0, 0,
    0, /* F11 Key */
    0, /* F12 Key */
    0, /* All other keys are undefined */
};

void init_pics(int pic1, int pic2) {
    /* send ICW1 */
    outb(PIC1, ICW1);
    outb(PIC2, ICW1);

    /* send ICW2 */
    outb(PIC1 + 1, pic1);
    outb(PIC2 + 1, pic2);

    /* send ICW3 */
    outb(PIC1 + 1, 4);
    outb(PIC2 + 1, 2);

    /* send ICW4 */
    outb(PIC1 + 1, ICW4);
    outb(PIC2 + 1, ICW4);

    /* disable all IRQs */
    outb(PIC1 + 1, 0xFF);
}

char *get_input() {
    char c = 0;
    char *ret = malloc(sizeof(char) * 256);

    init_pics(0x20, 0x28);
    do {
        if (inb(0x60) != c) {
            c = inb(0x60);
            if (c > 0) {
                strccat(ret, en_us_scancodes[(uint8_t)c]);
            }
        }

    } while (c != 28); // Read until enter is pressed

    char *asPointer = &ret[0];
    return asPointer;
}