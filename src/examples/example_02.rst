Recognizing strings: the need for YYMAXFILL
-------------------------------------------

This example is about recognizing strings.
Strings (in generic sense) are different from other kinds of lexemes: they can contain *arbitrary* characters.
It makes them a way more difficult to lex: unlike `Recognizing integers: the sentinel method <example_01.html>`_ example,
we cannot use sentinel character to stop at the end of input.
Suppose, for example, that our strings may be single or double-quoted
and may contain any character in range ``[0 - 0xFF]`` except quotes of the appropriate type.
This time we cannot use ``NULL`` as a sentinel: input strings like ``"aha\0ha"`` are perfectly valid,
but ill-formed strings like ``"aha\0`` are also possible and shouldn't crash lexer.
Any other character cannot be used for the same reason
(including quotes: each type of strings can contain quotes of the opposite type).

By default re2c-generated lexers use the following approach to check for the end of input:
they assume that ``YYLIMIT`` is a pointer to the end of input and check by simply comparing ``YYCURSOR`` and ``YYLIMIT``.
The obvious way is to check on each input character (before advancing to the next character), but it's very slow.
Instead, re2c inserts checks only at certain points in the generated program.
Each check ensures that there is enough input to proceed until the next check.
If the check fails, lexer calls ``YYFILL(n)``, which can either supply at least ``n`` characters or stop:

    ``if ((YYLIMIT - YYCURSOR) < n) YYFILL(n);``

For those interested in the internal re2c algorithm used to determine checkpoints,
here is a quote from the original paper
:download:`"RE2C: a more versatile scanner generator" <../about/1994_bumbulis_cowan_re2c_a_more_versatile_scanner_generator.pdf>`
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

:download:`[02_recognizing_strings.re] <02_recognizing_strings.re.txt>`

.. literalinclude:: 02_recognizing_strings.re.txt
    :language: cpp
    :linenos:

Notes:

* ``/*!max:re2c*/`` (line 4) tells re2c to generate ``#define YYMAXFILL n``.

* Input string is padded with ``YYMAXFILL`` characters ``'a'`` (line 15).
  Sequence of ``'a'`` does not form a valid lexeme or lexeme suffix
  (but padding with quotes would cause false match on ill-formed input like ``"aha``).

* ``YYLIMIT`` points at the end of padding (line 26).

* ``YYFILL`` returns an error (line 29): if the input was correct, lexer should have stopped
  at the beginning of padding.

* If the rule matched (line 36), we ensure that lexer consumed *all* input characters
  and stopped exactly at the beginning of padding.

* We have to use ``re2c:define:YYFILL:naked = 1;`` (line 30)
  in order to suppress passing parameter to ``YYFILL``.
  (It was an unfortunate idea to make ``YYFILL`` a call expression by default:
  ``YYFILL`` has to stop the lexer eventually, that's why it has to be a macro and not a function.
  One should either set ``re2c:define:YYFILL:naked = 1;`` or define ``YYFILL(n)`` as a macro.)

Generate, compile and run:

.. code-block:: bash

    $ re2c -o example.cc 02_recognizing_strings.re
    $ g++ -o example example.cc
    $ ./example '"a momentary"' '""' '"lap"se"' '"of' '"' '"rea""son"' ''
    str: "a momentary"
    str: ""
    err: "lap"se"
    err: "of
    err: "
    err: "rea""son"
    err: 
    $ ./example "'a momentary'" "''" "'lap'se'" "'of" "'" "'rea''son'" ""
    str: 'a momentary'
    str: ''
    err: 'lap'se'
    err: 'of
    err: '
    err: 'rea''son'
    err: 


