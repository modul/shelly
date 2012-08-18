#include "shelly.h"

extern unsigned short tp;
extern uint8_t tape[SHELLY_TAPESIZE];

#ifndef strict
int shelly_extra(const char **ip)
{
	char i = **ip;
	if (i == ':')
		printf("%u", tape[tp]);
	else if (i == ';') {
		unsigned short x;
		if (scanf("%hu", &x) == 1) tape[tp] = (uint8_t) x;
		else tape[tp] = 0;
	}
	else if (i >= '0' && i <= '9') {
		uint8_t num = 0;
		do { num *= 10; num += i-'0';
		} while ((i=*(++(*ip))) >= '0' && i <= '9');
		--(*ip);
		tape[tp] = num;
	}
	else if (i == '(') tape[tp] <<= 1;
	else if (i == ')') tape[tp] >>= 1;
	else if (i == '{') tape[tp] *= 10;
	else if (i == '}') tape[tp] /= 10;
	else if (i == '@') {
#ifdef __AVR_ARCH__
		srand(tape[tp]);
#endif
		tape[tp] = (uint8_t) rand();
	}
	return SHELLY_SUCCESS;
}
#endif
