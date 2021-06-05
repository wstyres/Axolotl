#include "isr.h"
#include "tty.h"
#include <stdlib/string/string.h>

void handle_isr(registers_t regs) {
    write("recieved interrupt: ");

    char buf[24];
    itoa(regs.int_no, buf);
    write(buf);
    write("\n");
}