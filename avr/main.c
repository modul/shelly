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

#define DEBUG

int main()
{
	int e;
	char line[512];
	init_stdio();

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
