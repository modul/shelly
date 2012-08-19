#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>

#include <string.h>
#include <stdio.h>

#include "stdio_wrapper.h"
#include "uart.h"
#include "shelly.h"

#define MAX 512
#define cleartape(...) memset(tape, 0, SHELLY_TAPESIZE);

extern uint8_t tape[SHELLY_TAPESIZE];
extern unsigned short tp;

char eebuf[MAX] EEMEM = {0};
char line[MAX] = {0};

void run();
void load();
void setup();

int main()
{
	int e = 0;

	setup();
	load();
	run();
	cleartape();

	while (42) {
		gets(line); e = strlen(line);
		if (!*line) continue;
		else if (line[e-1] == '\\') gets(line+e);
		else if (*line == '$') {
			if (e == 1) {
				char c; e = 0;
				while ((c=getchar()) != '$' && e<MAX-1) if (c > 32) line[e++] = c;
				if (e < MAX-1) {
					line[e++] = 0;
					cli();
					eeprom_update_block(line, eebuf, e);
					sei();
					continue;
				}
				else {puts_P(PSTR("BUFF")); continue;}
			}
			else if (e == 2 && line[1] == '$') {
				load();
				cleartape();
			}
			else if (e == 3 && line[2] == '$') {
				load();
				printf("%s\n\n", line);
				continue;
			}
		}
		run();
	}
	return 0;
}

void run()
{
	int e = shelly(line);
	printf_P(PSTR(" [%c % 3u % 3u] "), e==0?'_':e, tp, tape[tp]);
}

void load()
{
	cli();
	eeprom_read_block(line, eebuf, MAX);
	sei();
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
