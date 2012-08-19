#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "shelly.h"

extern uint8_t tape[SHELLY_TAPESIZE];
extern unsigned short tp;

int exec(FILE *f, size_t len)
{
	char *b = (char *) malloc(len);
	char c, *s = b;
	int r;

	memset(b, 0, len);
	while ((c = getc(f)) > 0 && c != '!') {
		if (!len--) { free(s); exit(255); }
		*b++ = c;
	}
	r = shelly(s);
	free(s);
	return r;
}

int main(int argc, const char *argv[])
{
	if (argc == 1)
		return exec(stdin, 65535);
	else {
		if (strcmp(argv[1], "-h") == 0) {
			printf("Usage: %s [-i|-h|FILE]\n", argv[0]);
			return 0;
		}
		else if (strcmp(argv[1], "-i") == 0) {
			int e = 0;
			char line[BUFSIZ] = {0};

			while (42) {
				printf(" [%c % 3u % 3u] ", e==0?'_':e, tp, tape[tp]);
				if (!fgets(line, BUFSIZ, stdin)) return 0;
				if ((e = strlen(line)) > 1 && line[e-2] == '\\') fgets(line+e-2, BUFSIZ-e, stdin);
				if (*line == 10) {e = 0; continue;}
				e = shelly(line);
			}
		}
		else {
			FILE *fp;
			size_t len;
			if (!(fp = fopen(argv[1], "r"))) {
				perror(argv[1]);
				return 128;
			}
			fseek(fp, 0, SEEK_END);
			len = ftell(fp);
			rewind(fp);
			return exec(fp, len);
		}
	}
	return 0;
}
