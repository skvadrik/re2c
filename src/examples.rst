.. _Recognizing integers: the sentinel method:

Recognizing integers: the sentinel method
-----------------------------------------

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
  In this case we can use ``NULL`` character as a sentinel:
  all arguments are ``NULL``-terminated and none of the rules matches ``NULL`` in the middle.
  Lexer will inevitably stop when it sees ``NULL``.
  It's a common practice to use ``re2c:yyfill:enable = 0;``
  in cases when input character set is restricted and one special
  character can be chosen to indicate the end of input.
  **But do make sure that the sentinel character is not allowed in the middle of a rule!**

* ``YYMARKER`` (line 6) is needed because rules overlap:
  it backups input position of the longest successful match.
  Say, we have overlapping rules ``"a"`` and ``"abc"`` and input string ``"abd"``:
  by the time ``"a"`` matches there's still a chance to match ``"abc"``,
  but when lexer sees ``'d'`` it must rollback.
  (You might wonder why ``YYMARKER`` is exposed at all: why not make it a local variable like ``yych``?
  The reason is, all input pointers must be updated by ``YYFILL``
  as explained in example `Arbitrary large input and YYFILL`_.)

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
Strings may contain *any* characters in the range ``[0 - 0xFF]`` except quotes ``"`` and escape ``\`` (they must be escaped).
It means that (unlike the previous example, `Recognizing integers: the sentinel method`_)
we cannot use ``NULL`` or any other character as a sentinel:
strings like ``"aha\0ha"\0`` are perfectly valid, but ``"aha\0`` is also possible and shouldn't crash lexer.

By default re2c-generated lexers contain explicit checks for the end of input
(these checks can be suppressed with ``re2c:yyfill:enable = 0;`` configuration).
A naive approach is to check on each character (before advancing input position), but it's very slow.
Instead, re2c inserts checks only at certain points in the generated program.
Each check ensures that there is enough input to proceed until the next checkpoint.
If the check fails, lexer calls ``YYFILL``:

    ``if ((YYLIMIT - YYCURSOR) < n) YYFILL(n);``

``YYLIMIT`` must point at the end of input (so that ``YYLIMIT[-1]`` is the last input character).
``YYFILL(n)`` can either supply at least ``n`` more input characters or stop
(see example `Arbitrary large input and YYFILL`_ for details about ``YYFILL`` implementation).

For those interested in the internal re2c algorithm used to determine checkpoints,
here is a quote from the original paper
`"RE2C: a more versatile scanner generator" <1994_bumbulis_cowan_re2c_a_more_versatile_scanner_generator.pdf>`_
by Peter Bumbulis, Donald D. Cowan, 1994, ACM Letters on Programming Languages and Systems (LOPLAS):

    *A set of key states can be determined by discovering the strongly-connected components (SCCs) of the
    DFA. An SCC is a maximal subset of states such that there exists a path from any state in the subset to any
    other. The set of key states consists of all of the states in non-trivial SCCs, together with the start state.
    Note that for each SCC S, we actually only have to include a subset of states of S such that when the subset
    is removed, S becomes acyclic.*

This approach reduces the number of checks significantly, but it has a downside.
Since the lexer checks for multiple characters at once, the last few input characters may become unreachable.
Common hack is to pad input with a few fake characters that **do not form a valid lexeme or lexeme suffix**.
The length of padding depends on the maximal argument to ``YYFILL``
(this value is called ``YYMAXFILL`` and can be generated using ``/*!max:re2c*/`` directive).

.. include:: examples/02_recognizing_strings.re
    :code: cpp
    :number-lines:

Notes:

* ``/*!max:re2c*/`` (line 4) tells re2c to generate ``#define YYMAXFILL n``.
* Input string is padded with ``YYMAXFILL`` characters ``'a'`` (line 15).
  Sequence of ``'a'`` does not form a valid lexeme suffix (but padding like ``"\0`` would cause false match on incorrect input like ``"aha``).
* ``YYLIMIT`` points to the end of padding (line 26).
* ``YYFILL`` simply stops: there's nothing more to lex (line 30).
* We have to use ``re2c:define:YYFILL:naked = 1;`` (line 31)
  in order to suppress passing parameter to ``YYFILL``.
  (It was an unfortunate idea to make ``YYFILL`` a call expression by default:
  ``YYFILL`` has to stop the lexer eventually, that's why it has to be a macro and not a function.
  One should either set ``re2c:define:YYFILL:naked = 1;`` or define ``YYFILL(n)`` as a macro.)

Generate, compile and run:

.. code-block:: bash

    $ re2c -o example.cc example.re
    $ g++ -o example example.cc
    $ ./example \"a\ momentary\" \"\" \"lap\"se\" \"of \"rea\\\"son\" ""
    str: "a momentary"
    str: ""
    err: "lap"se"
    err: "of
    str: "rea\"son"
    err: 

.. _Arbitrary large input and YYFILL:

Arbitrary large input and YYFILL
--------------------------------

Suppose that for some reason the whole input cannot be mapped in memory:
either it is very big or its size cannot be determined in advance.
The usual thing to do in such case is to allocate a buffer
and process input in chunks that fit into buffer.
For that we will need ``YYFILL``.

See the previous example (`Recognizing strings: the need for YYMAXFILL`_)
for details about program points and conditions that trigger ``YYFILL`` invocation.
The idea of ``YYFILL`` is fairly simple: lexer is stuck upon the fact that
``(YYLIMIT - YYCURSOR) < n`` and ``YYFILL`` must either invert this condition or stop lexing.
Disaster will happen if ``YYFILL`` fails to provide at least ``n`` characters, yet resumes lexing.

Technically ``YYFILL`` must somehow "extend" input for at least ``n`` characters:
after ``YYFILL`` all input pointers must point to exact same characters,
except ``YYLIMIT``: it must be advanced at least ``n`` positions.
Since we want to use a fixed amount of memory, we have to shift buffer contents:
discard characters that are already lexed,
move the remaining characters at the beginning of the buffer
and fill the vacant space with new characters.
All the pointers must be decreased by the length of discarded input,
except ``YYLIMIT`` (it must point at the end of buffer):

.. code-block:: bash

    <--- discarded -->                              <----- n ----->
    oxxxxxxxxxxxxxxxxxo----------o-----------------o--------o.....o..........o... (more input)
    buffer          lexeme    YYMARKER          YYCURSOR YYLIMIT *          *
    |             *          *                 *            | *          *
    |          *          *                 *              *|         *
    |       *          *                 *              *   |      *
    |    *          *                 *              *      |   *
    | *          *                 *              *         |*
    o-----------o-----------------o--------------o----------o
    buffer,  YYMARKER          YYCURSOR                  YYLIMIT
    lexeme

End of input is a special case: as explained in the previous example (`Recognizing strings: the need for YYMAXFILL`_),
the input must be padded with ``YYMAXFILL`` fake characters.
In this case ``YYLIMIT`` must point at the end of padding:

.. code-block:: bash

    <--- discarded -->                              <----- n ----->
    oxxxxxxxxxxxxxxxxxo----------o-----------------o---o0000000000000000o
    buffer          lexeme    YYMARKER          YYCURSOR YYLIMIT       *
    |             *          *                 *   *        |       *
    |          *          *                 *   *           |    *
    |       *          *                 *   *              | *
    |    *          *                 *   *                *|
    | *          *                 *   <-- YYMAXFILL -->*   |
    o-----------o-----------------o---o0000000000000000o    |
    buffer,  YYMARKER          YYCURSOR             YYLIMIT
    lexeme

Which part of input can be discarded?
The answer is, all input up to the leftmost meaningful pointer.
Intuitively it seems that it must be ``YYMARKER``: it backups input position of the latest match,
so it's always less than or equal to ``YYCURSOR``.
However, ``YYMARKER`` usage depends on the input:
not all control flow paths in lexer ever initialize it.
Thus for some inputs ``YYMARKER`` is meaningless
and should be used with care.

In practice input rarely consists of one giant lexeme: it is usually a sequence of small lexemes.
In that case lexer runs in a loop and it is convenient to have a special "lexeme start" pointer.
It can be used as boundary in ``YYFILL``.

Our example program will lex a file with strings (probably separated by whitespaces)
and count the total number of strings:

.. include:: examples/03_arbitrary_large_input.re
    :code: cpp
    :number-lines:

Notes:

* ``YYMAXFILL`` bytes at the end of buffer are reserved for padding (line 9).
  This memory is unused most of the time, but ``YYMAXFILL`` is usually negligably small compared to buffer size.

* There is only one successsful way out (line 71):
  lexer must recognize a standalone end of input lexeme ``'a'`` right at the beginning of padding.
  Unlike the sentinel method, ``'a'`` in the middle of a rule is not recognized as end of input.
  Standalone ``'a'`` in input (not in padding) is a lexing error.
  ``YYFILL`` failure is also a lexing error: if the input was correct,
  lexer should have stopped at the beginning of padding.

* ``YYFILL`` may fail for two reasons:
  either there is no more input (line 30),
  or lexeme is too big: it occupies the whole buffer and nothing can be discarded (line 35).
  We treat both cases as error, but a real-world program might handle them differently
  (e.g. resize buffer in the second case).

* ``@@`` in ``YYFILL`` definition (line 63) is a formal parameter: re2c substitutes it with the actual argument to ``YYFILL``.

* There is a special ``tok`` pointer: it points at the beginning of lexeme (line 57)
  and serves as a boundary in ``YYFILL`` (line 33).

Generate, compile and run:

.. code-block:: bash

    $ re2c -o example.cc example.re
    $ g++ -o example example.cc
    $ cat > input.txt
    "a""momentary"
     "lap\"se"      "o\\f"
    
        "rea""son"
     ""
    $ ./example input.txt
    glorious 7 strings!

