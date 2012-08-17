#ifndef _SHELLY_
#define _SHELLY_

#define SHELLY_EOF '$'
#define SHELLY_REAL_EOF 0
#define SHELLY_TAPESIZE 256

#define SHELLY_UNDRFLW 1
#define SHELLY_OVERFLW 2
#define SHELLY_UNMATCH 3
#define SHELLY_TAPELIM 4
#define SHELLY_SUCCESS 5

//#define SHELLY_WRAPPING_TAPE
//#define SHELLY_WRAPPING_CELL

void forget();
int shelly(const char *input);

#endif
