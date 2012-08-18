#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "shelly.h"

#define BUFSIZE 512

void exec(FILE *f) 
{
	char line[BUFSIZE] = {0}, c = 0;
	int p = 0;
	while ((c = getc(f)) > 0 && c != '!')
		line[p++] = c;
	shelly(line);
}

int main(int argc, const char *argv[])
{
	FILE *fp = stdin;
	if (argc > 1) {
		if (strcmp(argv[1], "-i") == 0) {
			extern uint8_t tape[SHELLY_TAPESIZE];
			extern unsigned short tp;
			char line[BUFSIZE] = {0};
			int e = 0;

			while (42) {
				printf(" [%c % 3u % 3u] ", e==0?'_':e, tp, tape[tp]);
				if (!fgets(line, BUFSIZE, stdin)) return 0;
				if ((e = strlen(line)) > 1 && line[e-2] == '\\') fgets(line+e-2, BUFSIZE-e, stdin);
				if (*line == 10) {e = 0; continue;}
				e = shelly(line);
			}
		}
		else if (strcmp(argv[1], "-h") == 0) {
			printf("Usage: %s [-i|-h|FILE]\n", argv[0]);
			return 0;
		}
		else {
			if (!(fp = fopen(argv[1], "r"))) {
				perror(argv[1]);
				return 128;
			}
			exec(fp);
		}
	}
	else exec(stdin);
	return 0;
}
