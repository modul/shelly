/*
 * 
 * Copyright (c) 2012, Remo Giermann <mo@liberejo.de>
 * 
 * Permission to use, copy, modify, and/or distribute this software for any purpose
 * with or without fee is hereby granted, provided that the above copyright notice
 * and this permission notice appear in all copies.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH 
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND 
 * FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT,
 * OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
 * ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 * 
 */

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
