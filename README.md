# foop

Functional Object-Oriented Programming

## What is it?

This is a toy program to demonstrate that a program can be both Functional and Object-Oriented.

## What does it do?

It is a simple [RPN](https://en.wikipedia.org/wiki/Reverse_Polish_notation) calculator that supports integers and the basic arithmetic operators: addition, subtraction, multiplication, and division.

## How would I use it?

Each argument should be either an integer or one of `+`, `-`, `x`, or `/`. A lowercase X (`x`) indicates multiplication, and a slash (`/`) indicates division. The operands of an operator must precede it. Each operator takes exactly two operands.

(You can use asterisk (`*`) for multiplicaton, but the shell may treat it as a meta-character, so you may need to quote it.)

For example:

    $ foop 5 5 +
    10

    $ foop 5 5 -
    0

    $ foop 5 5 x
    25

    $ foop 5 5 /
    1

    $ foop 5 10 x 5 +
    55

    $ foop 5 2 /
    2

Note that division simply truncates any fractional part.

If `foop` is compiled with `BE_MORE_FUNCTIONAL` defined, it will not print its results. Instead, you'll have to ask your shell to print the results for you.

For example:

    $ foop 2 2 + ; echo $?
    4

## Caveats

There are two uses of the standard C++ iostreams which are certainly not Functional. Define `BE_MORE_FUNCTIONAL` when compiling in order to eliminate those.

The C++ runtime and standard library that foop depends upon certainly do non-Functional things. But that is true of the runtime support for any Functional language running on non-Functional hardware.

