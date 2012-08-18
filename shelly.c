#include "shelly.h"

unsigned short tp = 0;
uint8_t tape[SHELLY_TAPESIZE];

void forget()
{
	tp = 0;
	memset(tape, 0, SHELLY_TAPESIZE);
}

int shelly(const char *ip)
{
#if !defined(strict) && !defined(__AVR_ARCH__)
	srand(time(0));
#endif
	while (*ip) {
		if (*ip == '+') {
			if (tape[tp] < 255)
				tape[tp] += 1;
			else return SHELLY_OVERFLW;
		}
		else if (*ip == '-') {
			if (tape[tp] > 0)
				tape[tp] -= 1;
			else return SHELLY_UNDRFLW;
		}
		else if (*ip == '>') {
			if (tp < SHELLY_TAPESIZE-1)
				tp++;
			else return SHELLY_TAPELIM;
		}
		else if (*ip == '<') {
			if (tp > 0)
				tp--;
			else return SHELLY_TAPELIM;
		}
		else if (*ip == '.') 
			putchar((char) tape[tp]);
		else if (*ip == ',') {
			char c = getchar();
			if (c == SHELLY_EOF || c == EOF) tape[tp] = SHELLY_REAL_EOF;
			else tape[tp] = (uint8_t) c;
		}
		else if (*ip == '[' && tape[tp] == 0) {
			unsigned short loop = 1;
			while (loop) {
				if (*(++ip) == ']') loop--;
				else if (*ip == '[') loop++;
				else if (*ip == 0) return SHELLY_UNMATCH;
			}
		}
		else if (*ip == ']' && tape[tp]) {
			unsigned short loop = 1;
			while (loop) {
				if (*(--ip) == ']') loop++;
				else if (*ip == '[') loop--;
				else if (*ip == 0) return SHELLY_UNMATCH;
			}
		}
#if !defined(strict) || defined(__AVR_ARCH__)
		else {
			int r; 
#ifndef strict
			if ((r = shelly_extra(&ip)) != SHELLY_SUCCESS) return r;
#endif
#ifdef __AVR_ARCH__
			if ((r = shelly_avr(&ip)) != SHELLY_SUCCESS) return r;
#endif
		}
#endif
		ip++;
	}
	return SHELLY_SUCCESS;
}
