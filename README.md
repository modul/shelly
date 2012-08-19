Shelly
======
a shiny (extended, embeddable) brainfuck shell
----------------------------------------------

This is a simple brainfuck interpreter, with (always more 
extendable) extended functionality (which can be turned off by
compiling to a strict version).

It runs on x86 (which means any PC here, architecture mostly irrelevant)
or microcontroller. On micros, more extended commands can be added 
to do hardware specific tasks, e.g. reading/writing analog/digital input/output,
communicate via SPI or whatever task you need your application/device to be
able to do.

For each architecture there should be an appropriate frontend
to handle program input. The x86 frontend (x86/main.c) features
an interactive mode (like a shell, good for debugging) and reading
from a file or stdin. It’s really a quite good and useable
brainfuck interpreter.

A microcontroller frontend could also implement the task
to store brainfuck scripts on some memory and execute them
without user interaction. It’s intended to be embedded
in any way suitable.

Strictly Brainfuck Instructions
-------------------------------
`+ - < > [ ] , .` -- as usual

The x86 frontend also supports `!` to separate program code
from program input when reading code from stdin.
Anytime, when getting user input (`,` instruction),
the system EOF or a dollar sign (`$`) will be converted to zero. 
So the code `,[.,]` will terminate on EOF or when a `$` was read.
This can be changed through `SHELLY_REAL_EOF` and `SHELLY_EOF`
in `shelly.h`.

Extended Instructions - `shelly_extra.c`
--------------------------------------
These features can be turned off by defining 'strict'.

So far:
* `:` -- print cell value (decimal)
* `;` -- read number to current memory cell (decimal)
* `0`..`255` -- any decimal number is directly put into the current cell
* `_` -- delay for the current cell value in milliseconds
* `(` -- binary shift left current memory cell
* `)` -- binary shift right current memory cell
* `{` -- decimal shift left current memory cell
* `}` -- decimal shift right current memory cell
* `@` -- write a random integer in current memory cell

AVR Instructions - `shelly_avr.c`
-------------------------------

So far:
* `o` -- set digital outputs to bitmask in current cell
* `p` -- set PWM1 to cell value
* `P` -- set PWM2 to cell value
* `a` -- current cell selects the analog channel to be read, ADC 
         value is then written to the current cell

If there is a pending `$` on the input line between two instructions,
the execution stops (because CTRL-C or CTRL-D won't work).

These are all just some ideas and can be completely changed, removed,
rewritten or whatever, to fit your needs. Shelly should only give 
some kind of a foundation. One that can be shaped to anything you 
need - that’s the idea.

