# foop

Functional Object-Oriented Programming

## What is it?

This is a toy program to demonstrate that a program can be _both_ Functional _and_ Object-Oriented.

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

If _foop_ is compiled with `BE_MORE_FUNCTIONAL` defined, it will not print its results. Instead, you'll have to ask your shell to print the results for you.

For example:

    $ foop 2 2 + ; echo $?
    4

## Why do you say it is Object-Oriented?

For me, the key feature of object-oriented programming is _polymorphism_.

The `expression` class is an abstract base class that defines a pure virtual member function: `eval`. Subclasses of `expression` represent the operands and operators. These classes override the `eval` member function to implement their specific behavior.

Now, I could say that Object-Oriented Programming is much more than this, but for the purposes of showing that a program can be _both_ Object-Oriented _and_ functional, I think this is enough.

## Why do you say it is Functional?

Functional Programming is programming with _pure_ functions.

Pure functions do not change state, do not depend upon global state, have no side-effects, and always return the same result for the same arguments.

With the exception of a couple of uses of C++ `iostreams`, all the code in this _foop_ is pure. If you define `BE_MORE_FUNCTIONAL` when compiling it, even those uses of `iostreams` will be removed. (Then you will need to have your shell print out the results.)

The C++ runtime and standard library that _foop_ depends upon certainly do non-Functional things. But that is true of the runtime support for any Functional language running on non-Functional hardware.

Now, I could say that Functional Programming is much more than this, but for the purposes of showing that a program can be _both_ Object-Oriented _and_ functional, I think this is enough.
