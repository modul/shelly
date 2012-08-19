#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "shelly.h"
#define LINE 256

void exec(FILE *f, char *b, size_t len)
{
	char c, *s = b;
	memset(b, 0, len);
	while ((c = getc(f)) > 0 && c != '!') {
		*b++ = c;
		if (!len--) {
			puts("BUFFULL");
			free(s);
			exit(255);
		}
	}
	shelly(s);
}

int main(int argc, const char *argv[])
{
	FILE *fp = stdin;
	if (argc > 1) {
		if (strcmp(argv[1], "-i") == 0) {
			extern uint8_t tape[SHELLY_TAPESIZE];
			extern unsigned short tp;
			char line[LINE] = {0};
			int e = 0;

			while (42) {
				printf(" [%c % 3u % 3u] ", e==0?'_':e, tp, tape[tp]);
				if (!fgets(line, LINE, stdin)) return 0;
				if ((e = strlen(line)) > 1 && line[e-2] == '\\') fgets(line+e-2, LINE-e, stdin);
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
			else {
				char *buf;
				size_t len;
				fseek(fp, 0, SEEK_END);
				len = ftell(fp);
				buf = (char *) malloc(len);
				rewind(fp);
				exec(fp, buf, len);
			}
		}
	}
	else {
		char *buf = malloc(65535);
		exec(stdin, buf, 1);
	}
	return 0;
}
