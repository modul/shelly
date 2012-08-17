#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "shelly.h"

extern uint8_t tape[SHELLY_TAPESIZE];
extern unsigned short tp;

#define BUFSIZE 512

int main()
{
	int e = 0;
	char line[BUFSIZE];

	printf("Shelly");
#ifdef SHELLY_EXTENDED
	puts("Extended");
#else
	putchar(10);
#endif

	while (42) {
		printf(" [%c % 3u % 3u] ", e==0?'_':e, tp, tape[tp]);
		if (!fgets(line, BUFSIZE, stdin)) return 0;
		if ((e = strlen(line)) > 1 && line[e-2] == '\\') fgets(line+e-2, BUFSIZE-e, stdin);
		if (*line == 10) {e = 0; continue;}
		e = shelly(line);
	}
	return 0;
}
