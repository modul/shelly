#include "shelly.h"

extern unsigned short tp;
extern uint8_t tape[SHELLY_TAPESIZE];

#ifndef strict
int shelly_extra(const char *ip)
{
	if (*ip == '(') tape[tp] <<= 1;
	else if (*ip == ')') tape[tp] >>= 1;
	else if (*ip == '{') tape[tp] *= 10;
	else if (*ip == '}') tape[tp] /= 10;
	else if (*ip == '@') {
#ifdef __AVR_ARCH__
		srand(tape[tp]);
#endif
		tape[tp] = (uint8_t) rand();
	}
	return SHELLY_SUCCESS;
}
#endif
