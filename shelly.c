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

int shelly(const char *input)
{
	unsigned short tmp;
	unsigned short loop = 0;

	while (*input) {
		switch (*input) 
		{
			case '+':
				tape[tp] += 1;
#ifndef SHELLY_WRAPPING_CELL
				if (tape[tp] == 0)
					tape[tp] -= 1;
#endif
			break;

			case '-':
				tape[tp] -= 1;
#ifndef SHELLY_WRAPPING_CELL
				if (tape[tp] == 255)
					tape[tp] += 1;
#endif
			break;

			case '>':
				if (tp < SHELLY_TAPESIZE-1)
					tp++;
#ifdef SHELLY_WRAPPING_TAPE
				else
					tp = 0;
#endif
			break;

			case '<':
				if (tp > 0)
					tp--;
#ifdef SHELLY_WRAPPING_TAPE
				else
					tp = SHELLY_TAPESIZE-1;
#endif
			break;

			case '.':
				putchar((char) tape[tp]);
			break;

			case ',':
				tape[tp] = (uint8_t) getchar();
				if (tape[tp] == SHELLY_EOF)
					tape[tp] = SHELLY_REAL_EOF;
			break;

			case '[':
				loop = 1;
				if (tape[tp] == 0) {
					while (loop) {
						if (*(++input) == '[')
							loop++;
						else if (*input == ']')
							loop--;
						else if (*input == 0) {
							puts_P(PSTR("a lonesome [ ..."));
							return -1;
						}
					}
				}
			break;

			case ']':
				if (tape[tp]) {
					loop = 1;
					while (loop) {
						if (*(--input) == '[') 
							loop--;
						else if (*input == ']')
							loop++;
						else if (*input == 0) {
							puts_P(PSTR("a lonesome ] ..."));
							return -1;
						}
					}
				}
			break;

			/* totally extended commands */

			case '_': // delay 
				for (tmp=0; tmp<tape[tp]; tmp++) {
					_delay_ms(10);
				}
			break;

			case '(': // binary left shift
				tape[tp] <<= 1;
			break;

			case ')': // binary right shift
				tape[tp] >>= 1;
			break;

			case '{': // decimal left shift
				tape[tp] /= 10;
			break;

			case '}': // decimal right shift
				tape[tp] *= 10;
			break;

			case '@': // random integer
				srand(tape[tp]);
				tape[tp] = (uint8_t) rand();
			break;
		}
		input++;
	}

	if (loop > 0) {
		puts_P(PSTR("unmatched loops"));
		return -1;
	}
	return 0;
}
