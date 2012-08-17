#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "stdio_wrapper.h"
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
	unsigned short tmp;
	unsigned short loop = 0;

	while (*ip) {
		if (*ip == '+') {
			tape[tp] += 1;
#ifndef SHELLY_WRAPPING_CELL
			if (tape[tp] == 0)
				return SHELLY_OVERFLW;
#endif
		}
		else if (*ip == '-') {
			tape[tp] -= 1;
#ifndef SHELLY_WRAPPING_CELL
			if (tape[tp] == 255)
				return SHELLY_UNDRFLW;
#endif
		}
		else if (*ip == '>') {
			if (tp < SHELLY_TAPESIZE-1)
				tp++;
			else
#ifndef SHELLY_WRAPPING_TAPE
				return SHELLY_TAPELIM;
#else
				tp = 0;
#endif
		}
		else if (*ip == '<') {
			if (tp > 0)
				tp--;
			else
#ifndef SHELLY_WRAPPING_TAPE
				return SHELLY_TAPELIM;
#else
				tp = SHELLY_TAPESIZE-1;
#endif
		}
		else if (*ip == '.') 
			putchar((char) tape[tp]);
		else if (*ip == ',') {
			tape[tp] = (uint8_t) getchar();
			if (tape[tp] == SHELLY_EOF) tape[tp] = SHELLY_REAL_EOF;
		}
		else if (*ip == '[' && tape[tp] == 0) {
			loop = 1;
			while (loop) {
				if (*(++ip) == ']') loop--;
				else if (*ip == '[') loop++;
				else if (*ip == 0) return SHELLY_UNMATCH;
			}
		}
		else if (*ip == ']' && tape[tp]) {
			loop = 1;
			while (loop) {
				if (*(++ip) == ']') loop++;
				else if (*ip == '[') loop--;
				else if (*ip == 0) return SHELLY_UNMATCH;
			}
		}

			/* totally extended commands */

		else if (*ip == '_') 
			for (tmp=0; tmp<tape[tp]; tmp++, _delay_ms(10));
		else if (*ip == '(') tape[tp] <<= 1;
		else if (*ip == ')') tape[tp] >>= 1;
		else if (*ip == '{') tape[tp] /= 10;
		else if (*ip == '}') tape[tp] *= 10;
		else if (*ip == '@') {
			srand(tape[tp]);
			tape[tp] = (uint8_t) rand();
		}
		ip++;
	}
	return SHELLY_SUCCESS;
}
