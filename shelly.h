#ifndef _SHELLY_
#define _SHELLY_

#define SHELLY_EOF '$'
#define SHELLY_REAL_EOF 0
#define SHELLY_TAPESIZE 256

#define SHELLY_UNDRFLW 'U'
#define SHELLY_OVERFLW 'O'
#define SHELLY_UNMATCH 'B'
#define SHELLY_TAPELIM 'M'
#define SHELLY_USREXIT 'E'
#define SHELLY_SUCCESS  0

void forget();
int shelly(const char *input);

#endif
