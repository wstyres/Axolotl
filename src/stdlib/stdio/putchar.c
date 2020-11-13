#include "stdio.h"
#include <kernel/tty.h>

int putchar(int ic) {
	char c = (char) ic;
	writechar(c);

	return ic;
}
