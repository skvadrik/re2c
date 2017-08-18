Strings
-------

This example is about recognizing strings.
Strings (in the generic sense) are different from other kinds of lexemes: they can contain *arbitrary* characters.
That makes them way more difficult to lex: unlike in the `Numbers <example_01.html>`_ example,
we cannot use a sentinel character to stop at the end of input.
Suppose, for example, that our strings may be single or double-quoted
and may contain any character in range ``[0 - 0xFF]`` except quotes of the appropriate type.
This time we cannot use ``\0`` as a sentinel: input strings such as ``"aha\0ha"`` are perfectly valid,
but ill-formed strings such as ``"aha\0`` are also possible and shouldn't crash the lexer.
Any other character cannot be used for the same reason
(including quotes: each type of string may contain quotes of the opposite type).

By default, re2c-generated lexers use the following approach to check for the end of the input buffer:
they assume that ``YYLIMIT`` is a pointer to the end of the input buffer, and they check by simply comparing ``YYCURSOR`` and ``YYLIMIT``.
The obvious way to accomplish this is by checking on each input character (before advancing to the next character), but that's very slow.
Instead, re2c inserts checks only at certain points in the generated program.
Each check ensures that there is enough input to proceed until the next check.
If the check fails, the lexer calls ``YYFILL(n)``, which may either supply at least ``n`` characters or stop:

    ``if ((YYLIMIT - YYCURSOR) < n) YYFILL(n);``

For those interested in the internal re2c algorithm used to determine checkpoints,
here is a quotation from the original paper
`"RE2C: a more versatile scanner generator" <../1994_bumbulis_cowan_re2c_a_more_versatile_scanner_generator.pdf>`_
*by Peter Bumbulis, Donald D. Cowan, 1994, ACM Letters on Programming Languages and Systems (LOPLAS)*:

    *A set of key states can be determined by discovering the strongly-connected components (SCCs) of the
    DFA. An SCC is a maximal subset of states such that there exists a path from any state in the subset to any
    other. The set of key states consists of all of the states in non-trivial SCCs, together with the start state.
    Note that for each SCC S, we actually only have to include a subset of states of S such that when the subset
    is removed, S becomes acyclic.*

This approach reduces the number of checks significantly, but it has a downside.
Since the lexer checks for multiple characters at once, the last few input characters may become unreachable.
A common hack is to pad the input with a few fake characters that **do not form a valid lexeme or lexeme suffix**.
The length of the padding depends on the maximum argument to ``YYFILL``
(this value is called ``YYMAXFILL`` and can be generated with the ``/*!max:re2c*/`` directive).

:download:`[strings.re] <02_recognizing_strings.re.txt>`

.. literalinclude:: 02_recognizing_strings.re.txt
    :language: cpp
    :linenos:

Notes:

* ``/*!max:re2c*/`` (line 4) tells re2c to generate ``#define YYMAXFILL n``.

* The input string is padded with ``YYMAXFILL`` ``'a'`` characters (line 15).
  The sequence of ``'a'`` does not form a valid lexeme or lexeme suffix
  (but padding with quotes would cause false matches on ill-formed inputs such as ``"aha``).

* ``YYLIMIT`` points at the end of the padding (line 26).

* ``YYFILL`` returns an error (line 29): if the input was correct, the lexer should have stopped
  at the beginning of the padding.

* If the rule matched (line 36), we ensure that the lexer has consumed *all* input characters
  and stopped exactly at the beginning of the padding.

* We have to use ``re2c:define:YYFILL:naked = 1;`` (line 30)
  in order to suppress passing a parameter to ``YYFILL``.
  (It was an unfortunate idea to make ``YYFILL`` a call expression by default:
  ``YYFILL`` has to stop the lexer eventually. That's why it has to be a macro and not a function.
  One should either set ``re2c:define:YYFILL:naked = 1;`` or define ``YYFILL(n)`` as a macro.)

Compile:

.. code-block:: bash

    $ re2c -o strings.cc strings.re
    $ g++ -o strings strings.cc

Run:

.. code-block:: bash

    $ ./strings '"a momentary"' '""' '"lap"se"' '"of' '"' '"rea""son"' ''
    str: "a momentary"
    str: ""
    err: "lap"se"
    err: "of
    err: "
    err: "rea""son"
    err: 

