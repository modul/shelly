#include <stdio.h>
#include <avr/interrupt.h>
#include "stdio_wrapper.h"
#include "uart.h"

static int uart_putchar(char c, FILE *stream);
static int uart_getchar(FILE *stream);

static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
static FILE  mystdin = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);

static int uart_putchar(char c, FILE *stream)
{
	uart_putc(c);
	return 0;
}

static int uart_getchar(FILE *stream)
{
	unsigned u;
	while ((u = uart_getc()) == UART_NO_DATA);
	return u&0xFF;
}

int pending_input()
{
	uint8_t u = (uint8_t) uart_getc()&0xFF;
	if (u > 0) {
		ungetc(u, stdin);
		return 1;
	}
	return 0;
}

void init_stdio()
{
    uart_init(UART_BAUD_SELECT(BAUDRATE, F_CPU)); 
	sei();
	stdout = &mystdout;
	stdin  = &mystdin;
}
