#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

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
	unsigned short loop = 0;

	while (*input) {
		switch (*input) 
		{
			case '+':
				tape[tp] += 1;
#ifndef BSE_WRAPPING_CELL
				if (tape[tp] == 0)
					tape[tp] -= 1;
#endif
			break;

			case '-':
				tape[tp] -= 1;
#ifndef BSE_WRAPPING_CELL
				if (tape[tp] == 255)
					tape[tp] += 1;
#endif
			break;

			case '>':
				if (tp < SHELLY_TAPESIZE-1)
					tp++;
#ifdef BSE_WRAPPING_TAPE
				else
					tp = 0;
#endif
			break;

			case '<':
				if (tp > 0)
					tp--;
#ifdef BSE_WRAPPING_TAPE
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
				loop = 1;
				if (tape[tp]) {
					while (loop) {
						if (*(--input) == '[') 
							loop--;
						else if (*input == ']')
							loop++;
						else if (*input == 0) {
							puts_P(PSTR("a lonesome ] ..."));
						}
					}
				}
			break;
		}
		input++;
	}
	return 0;
}
