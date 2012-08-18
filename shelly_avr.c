#include "shelly.h"

extern unsigned short tp;
extern uint8_t tape[SHELLY_TAPESIZE];

#ifdef __AVR_ARCH__
int shelly_avr(const char **ip)
{
	if (**ip == '_') {
		unsigned tmp;
		for (tmp=0; tmp<tape[tp]; tmp++, _delay_ms(10));
	}

	if (pending_input()) {
		char c = getchar();
		if (c == SHELLY_EOF) return SHELLY_USREXIT;
		else ungetc(c, stdin);
	}
	return SHELLY_SUCCESS;
}
#endif
