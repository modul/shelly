Shelly
======
a shiny (extended, embeddable) brainfuck shell
----------------------------------------------

This is a simple brainfuck interpreter, with (always more 
extendable) extended functionality (which can be turned off by
compiling to a strict version).

It runs on x86 or microcontroller architectures. On micros,
more extended commands can be added to do hardware specific
tasks, e.g. like reading out analog input, setting analog output,
setting digital outputs and so on.

For each architecture there should be an appropriate frontend
to handle program input. The x86 frontend (main.c) features
an interactive mode (like a shell, good for debugging), reading
from a file or stdin. 

A microcontroller frontend could also implement the task
to store brainfuck scripts on some memory and execute them
without user interaction. It’s intended to be embedded
in any way suitable.

Strictly Brainfuck Instructions
-------------------------------
`+ - < > [ ] , .` -- as usual

The x86 frontend also supports `!` to separate program code
from program input, when reading code from stdin.
On any architecture, when reading user input (`,` instruction),
the system EOF or a `$` will get converted to zero. So the code
`,[.,]` will terminate on EOF or when a $ was read.
This can be changed through `SHELLY_REAL_EOF` and `SHELLY_EOF`
in `shelly.h`.

Extended Instructions - `shelly_extra.c`
--------------------------------------
These features can be turned off by defining 'strict'.

So far:
* `:` -- print cell value (decimal)
* `;` -- read number to current memory cell (decimal)
* `@` -- write a random integer in current memory cell
* `(` -- binary shift left current memory cell
* `)` -- binary shift right current memory cell
* `{` -- decimal shift left current memory cell
* `}` -- decimal shift right current memory cell

Any decimal number in the code is directly read into the 
current memory cell, so `128+` sets the current value to 129, 
`0` zeroes a cell and so on.

AVR Instructions - `shelly_avr.c`
-------------------------------

So far:
* `_` -- delay for the current cell value in milliseconds

If there is a pending `$` on the input line between two instructions,
the execution stops (because CTRL-C or CTRL-D won't work).

