#include "string.h"

int strcmp(const char *lhs, const char *rhs) {
	size_t ch = 0;
	size_t ch2 = 0;

	while (lhs[ch] != 0 && rhs[ch2] != 0) {
		if (lhs[ch] != rhs[ch2]) {
			return -1;
		}
		ch++;
		ch2++;
	}
	return 0;
}