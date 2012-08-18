#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include <string.h>
#include <stdio.h>

#include "stdio_wrapper.h"
#include "uart.h"
#include "shelly.h"

extern uint8_t tape[SHELLY_TAPESIZE];
extern unsigned short tp;

void setup();

#define DEBUG

int main()
{
	int e;
	char line[512];
	setup();

	while (42) {
		gets(line); e = strlen(line);
		if (line[e-1] == '\\') gets(line+e);
		if (!*line) continue;
		e = shelly(line);
#ifdef DEBUG
		printf_P(PSTR(" [%c % 3u % 3u]\n"), e==0?'_':e, tp, tape[tp]);
#endif
	}
	return 0;
}

void setup()
{
    cli();

    /* I/O setup */
#if defined(__AVR_ATmega8__)
    PORTD = 0x00;
    DDRD  = 0xFC; // outputs PD2..PD7
	PORTC = 0x30; // pull-ups PC5, PC4
	DDRC  = 0x00; // inputs PC0..PC5 (5..4 digital, 3..0 analog)

    /* PWM setup */
	DDRB = (1<<PB1)|(1<<PB2);
    TCCR1A = (1<<COM1B1)|(1<<COM1A1)|(1<<WGM10);
	TCCR1B = (1<<CS11);
   	OCR1A = OCR1B = 0;

#elif defined(__AVR_ATtiny85__)
#endif

    /* ADC setup */
    ADCSRA = (1<<ADEN)|(1<<ADPS1)|(1<<ADPS0);
	
	/* Terminal I/O setup */
	init_stdio();
}
