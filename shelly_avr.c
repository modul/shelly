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

#ifdef __AVR_ARCH__
int shelly_avr(const char **ip)
{
	if (**ip == 'o') 
		PORTD = (tape[tp]<<2)&0xFC;
	else if (**ip == 'a') {
		ADMUX = (tape[tp]&3)|(1<<REFS1)|(1<<REFS0);
		ADCSRA |= (1<<ADSC);        
		while (ADCSRA & (1<<ADSC)); 
		tape[tp] = (uint8_t) (ADCW>>2);
	}
	else if (**ip == 'p')
		OCR1A = tape[tp];
	else if (**ip == 'P')
		OCR1B = tape[tp];

	return SHELLY_SUCCESS;
}
#endif
