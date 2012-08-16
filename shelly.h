#ifndef _SHELLY_
#define _SHELLY_

#define SHELLY_EOF '$'
#define SHELLY_REAL_EOF 0
#define SHELLY_TAPESIZE 256

void forget();
int shelly(const char *input);

#endif
