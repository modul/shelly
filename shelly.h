#ifndef _SHELLY_
#define _SHELLY_

#define SHELLY_EOF '$'
#define SHELLY_REAL_EOF 0
#define SHELLY_TAPESIZE 256

#define SHELLY_UNDRFLW 'U'
#define SHELLY_OVERFLW 'O'
#define SHELLY_UNMATCH 'B'
#define SHELLY_TAPELIM 'M'
#define SHELLY_SUCCESS  0

//#define SHELLY_WRAPPING_TAPE
//#define SHELLY_WRAPPING_CELL

void forget();
int shelly(const char *input);

#endif
