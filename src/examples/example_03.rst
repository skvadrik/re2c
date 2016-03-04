Arbitrary large input and YYFILL
--------------------------------

In this example we suppose that input cannot be mapped in memory at once:
either it's too large or its size cannot be determined in advance.
The usual thing to do in such case is to allocate a buffer and lex input in chunks that fit into buffer.
re2c allows us to refill buffer using ``YYFILL``: see `Recognizing strings: the need for YYMAXFILL <example_02.html>`_ example
for details about program points and conditions that trigger ``YYFILL`` invocation.
Currently re2c provides no way to combine ``YYFILL`` with the sentinel method:
we have to enable ``YYLIMIT``-based checks for the end of input and pad input with ``YYMAXFILL`` fake characters.
This may be changed in later versions of re2c.

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

End of input is a special case: as explained in `Recognizing strings: the need for YYMAXFILL <example_02.html>`_ example,
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
However, ``YYMARKER`` is not always used and even when it is, its usage depends on the input:
not all control flow paths in lexer ever initialize it.
Thus for some inputs ``YYMARKER`` is meaningless
and should be used with care.
In practice input rarely consists of one giant lexeme: it is usually a sequence of small lexemes.
In that case lexer runs in a loop and it is convenient to have a special "lexeme start" pointer.
It can be used as boundary in ``YYFILL``.

Our example program reads ``stdin`` in chunks of 16 bytes (in real word buffer size is usually ~4Kb)
and tries to lex numbers separated by newlines.

:download:`[03_arbitrary_large_input.re] <03_arbitrary_large_input.re.txt>`

.. literalinclude:: 03_arbitrary_large_input.re.txt
    :language: cpp
    :linenos:

Notes:

* ``YYMAXFILL`` bytes at the end of buffer are reserved for padding.
  This memory is unused most of the time, but ``YYMAXFILL`` is usually negligably small compared to buffer size.

* There is only one successsful way out (line 60): lexer must recognize a standalone
  "end of input" lexeme (``NULL``) exactly at the beginning of padding.
  ``YYFILL`` failure is an error: if the input was correct, lexer should have already stopped.

* ``YYFILL`` may fail for two reasons:
  either there is no more input (line 23),
  or lexeme is too long: it occupies the whole buffer and nothing can be discarded (line 27).
  We treat both cases in the same way (as error), but a real-world program might handle them differently
  (resize buffer, cut long lexeme in two, etc.).

* ``@@`` in ``YYFILL`` definition (line 52) is a formal parameter: re2c substitutes it with the actual argument to ``YYFILL``.

* There is a special ``tok`` pointer: it points at the beginning of lexeme (line 47)
  and serves as a boundary in ``YYFILL``.

Generate, compile and run:

.. code-block:: bash

    $ re2c -o example.cc 03_arbitrary_large_input.re
    $ g++ -o example example.cc
    $ ./example
    0
    11
    222
    3333
    44444
    555555
    6666666
    77777777
    888888888
    9999999999
    glorious 10 numbers!
    $ seq 123456789 | ./example
    glorious 123456789 numbers!
    $ seq 123456789 | wc -l
    123456789


