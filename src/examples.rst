.. _Recognizing integer literals:

Recognizing integer literals
----------------------------

This program simply loops over its commad-line arguments
and tries to match each argument against one of the four patterns:
binary, octal, decimal and hexadecimal integer literals.
The numbers are not *parsed* (their numeric value is not retrieved), they are merely *recognized*.

.. include:: examples/01_recognizing_integer_literals.re
    :code: cpp
    :number-lines:

A couple of things should be noted:

* Default case (when none of the patterns matched) is handled properly (line 17).

* Check for the end of input is disabled (line 9).
  In this case it is safe, because all arguments are ``NULL``-terminated
  and none of the rules matches ``NULL`` in the middle:
  when lexer reaches end of input, it will see ``NULL`` and stop.
  It's a common practice to use ``re2c:yyfill:enable = 0;``
  in cases when input character set is restricted and one special
  character can be chosen to indicate end of input.
  **But do make sure that the terminating character is not allowed in the middle of a rule!**

* ``YYMARKER`` (line 6) is needed because rules overlap:
  it backups input position of the longest successful match.
  Say, we have overlapping rules ``"a"`` and ``"abc"`` and input string ``"abd"``:
  by the time ``"a"`` matches there's still a chance to match ``"abc"``.
  But when lexer sees ``'d'`` it must rollback.
  (You might wonder why the programmer has to bother with ``YYMARKER`` at all: couldn't re2c generate a local variable ``YYMARKER``?
  The thing is, all input pointers must be updated syncronously by ``YYFILL``).

Generate, compile and run:

.. code-block:: bash

    $ re2c -o example.cc example.re
    $ g++ -o example example.cc
    $ ./example 0 -12 +345 12345678901234567890 0xAbcDEf 0x00 007 0B0 0b110101010 0x 0b a ? ""
    dec: 0
    dec: -12
    dec: +345
    dec: 12345678901234567890
    hex: 0xAbcDEf
    hex: 0x00
    oct: 007
    bin: 0B0
    bin: 0b110101010
    err: 0x
    err: 0b
    err: a
    err: ?
    err: 

.. _Recognizing strings: the need for YYMAXFILL:

Recognizing strings: the need for YYMAXFILL
-------------------------------------------

This example is about recognizing strings.
Strings may contain *any* characters in the range [0 - 0xFF] except quotes (quotes should be escaped).
It means that (unlike the previous example, `Recognizing integer literals`_)
we cannot use ``NULL`` or any other character as a terminator.
We must explicitely check for end of input.

So how does it work?
The simplest possible way is to check on each character (right before advancing input position).
But this is very slow.
Instead, re2c estimates maximal lexeme length ``YYMAXFILL`` (disregarding loops)
and generates check if there's at least ``YYMAXFILL`` characters left:

.. code-block:: cpp

    if ((YYLIMIT - YYCURSOR) < YYMAXFILL)
        YYFILL(YYMAXFILL);

``YYLIMIT`` must point at the end of input (so that ``YYLIMIT[-1]`` is the last input character).
These checks are inserted at start and before loops.
If there's not enough input characters, the generated lexer calls ``YYFILL(YYMAXFILL)``
so that the programmer can supply more input or stop.

The common practice is to pad input with ``YYMAXFILL`` fake characters.
**The padding should not form a valid lexeme suffix!**

.. include:: examples/02_recognizing_strings.re
    :code: cpp
    :number-lines:

Notes:

* ``/*!max:re2c*/`` (line 4) tells re2c to generate ``#define YYMAXFILL <n>``.
* Input string is padded with ``YYMAXFILL`` zeroes (line 15).
  Zeroes do not form a valid lexeme suffix (but padding with quotes would confuse the lexer ``;)``).
* ``YYFILL`` simply stops: there's nothing more to lex (line 30).
* We have to use ``re2c:define:YYFILL:naked = 1;`` (line 31)
  in order to suppress passing parameter to ``YYFILL``.
  (It was an unfortunate idea to make ``YYFILL`` a call expression by default:
  ``YYFILL`` has to stop the lexer eventually, that's why it has to be a macro and not a function.
  One should either set ``re2c:define:YYFILL:naked = 1;``, or define ``YYFILL(n)`` as a macro.)

Generate, compile and run:

.. code-block:: bash

    $ re2c -o example.cc example.re
    $ g++ -o example example.cc
    $ ./example \"a\ momentary\" \"\" \"lap\"se\" \"of \"rea\\\"son\"
    str: "a momentary"
    str: ""
    err: "lap"se"
    err: "of
    str: "rea\"son"

.. _Arbitrary large input and YYFILL:

Arbitrary large input and YYFILL
--------------------------------

Suppose the input cannot be mapped in memory at once.
The usual thing to do is to allocate a reasonably sized buffer and to read
input chunk by chunk.
