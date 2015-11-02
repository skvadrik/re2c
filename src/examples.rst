.. _Recognizing integers: the sentinel method:

Recognizing integers: the sentinel method
-----------------------------------------

This program simply loops over its commad-line arguments
and tries to match each argument against one of the four patterns:
binary, octal, decimal and hexadecimal integer literals.
The numbers are not *parsed* (their numeric value is not retrieved), they are merely *recognized*.

`[01_recognizing_integers.re] <examples/01_recognizing_integers.re>`_

.. include:: examples/01_recognizing_integers.re
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

    $ re2c -o example.cc 01_recognizing_integers.re
    $ g++ -o example example.cc
    $ ./example 0 12345678901234567890 0xAbcDEf 0x00 007 0B0 0b110101010 0x 0b ? ""
    oct: 0
    dec: 1234567890
    hex: 0xAbcDEf
    hex: 0x00
    oct: 007
    bin: 0B0
    bin: 0b110101010
    err: 0x
    err: 0b
    err: ?
    err: 

.. _Recognizing strings: the need for YYMAXFILL:

Recognizing strings: the need for YYMAXFILL
-------------------------------------------

This example is about recognizing strings.
Our strings are very simple: they are single-quoted and may contain any character in range ``[0 - 0xFF]``, except sinle quotes ``'``.
Yet this time (unlike the previous example, `Recognizing integers: the sentinel method`_)
we cannot use ``NULL`` or any other character as a sentinel:
input strings like ``'aha\0ha'\0`` are perfectly valid,
but incorrect input like ``'aha\0`` is also possible and shouldn't crash lexer.

By default re2c generates explicit checks for the end of input,
so we must simply omit ``re2c:yyfill:enable = 0;`` configuration.
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

`[02_recognizing_strings.re] <examples/02_recognizing_strings.re>`_

.. include:: examples/02_recognizing_strings.re
    :code: cpp
    :number-lines:

Notes:

* ``/*!max:re2c*/`` (line 4) tells re2c to generate ``#define YYMAXFILL n``.
* Input string is padded with ``YYMAXFILL`` characters ``'a'`` (line 15).
  Sequence of ``'a'`` does not form a valid lexeme suffix (but padding like ``"\0`` would cause false match on incorrect input like ``"aha``).
* ``YYLIMIT`` points to the end of padding (line 26).
* ``YYFILL`` returns an error (line 30): if the input was correct, lexer should have stopped
  at the beginning of padding.
* Lexer should consume *all* input characters (line 37).
* We have to use ``re2c:define:YYFILL:naked = 1;`` (line 31)
  in order to suppress passing parameter to ``YYFILL``.
  (It was an unfortunate idea to make ``YYFILL`` a call expression by default:
  ``YYFILL`` has to stop the lexer eventually, that's why it has to be a macro and not a function.
  One should either set ``re2c:define:YYFILL:naked = 1;`` or define ``YYFILL(n)`` as a macro.)

Generate, compile and run:

.. code-block:: bash

    $ re2c -o example.cc 02_recognizing_strings.re
    $ g++ -o example example.cc
    $ ./example "'a momentary'" "''" "'lap'se'" "'of" "'" "'rea''son'" ""
    str: 'a momentary'
    str: ''
    err: 'lap'se'
    err: 'of
    err: '
    err: 'rea''son'
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

`[03_arbitrary_large_input.re] <examples/03_arbitrary_large_input.re>`_

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

    $ re2c -o example.cc 03_arbitrary_large_input.re
    $ g++ -o example example.cc
    $ cat > input.txt
    "a""momentary"
     "lap\"se"      "o\\f"
    
        "rea""son"
     ""
    $ ./example input.txt
    glorious 7 strings!

.. _Parsing integers (multiple re2c blocks):

Parsing integers (multiple re2c blocks)
---------------------------------------

This example is based on `Recognizing integers: the sentinel method`_ example,
only now integer literals are parsed rather than simply recognized.
The aim of this example is to show how to use multiple re2c blocks,
not how to parse integers (overflows are not handled). ``:)``

`[04_parsing_integers_blocks.re] <examples/04_parsing_integers_blocks.re>`_

.. include:: examples/04_parsing_integers_blocks.re
    :code: cpp
    :number-lines:

Notes:

* Configurations and definitions (lines 9 - 15) are not scoped to a single re2c block --- they are global.
  Each block may override configurations, but this affects global scope.
* Blocks don't have to be in the same function: they can be in separate functions or elsewhere
  as long as the exposed interface fits into lexical scope.

Generate, compile and run:

.. code-block:: bash

    $ re2c -o example.cc 04_parsing_integers_blocks.re
    $ g++ -o example example.cc
    $ ./example "" 0 0b11100001 012345 67890 0xffE 0x 0b
    error :[
    0
    225
    5349
    67890
    4094
    error :[
    error :[


.. _Parsing integers (conditions):

Parsing integers (conditions)
-----------------------------

This example does exactly the same as `Parsing integers (multiple re2c blocks)`_ example,
but in a slightly different manner: it uses re2c conditions instead of blocks.
Conditions allow to encode multiple interconnected lexers within a single re2c block.

`[05_parsing_integers_conditions.re] <examples/05_parsing_integers_conditions.re>`_

.. include:: examples/05_parsing_integers_conditions.re
    :code: cpp
    :number-lines:

Notes:

* Conditions are enabled with ``-c`` option.
* Conditions are only syntactic sugar, they can be translated into multiple blocks.
* Each condition is a standalone lexer (DFA).
* Conditions are interconnected: transitions are allowed between final states of one DFA
  and start state of another DFA (but no transitions between inner states of different DFAs).
  The generated code starts with dispatch on conditions.
* Each condition has a unique identifier: ``/*!types:re2c*/`` directive (line 3)
  tells re2c to generate enumeration of them (names are prefixed with ``yyc`` by default).
  These identifiers are used in the initial dispatch on conditions:
  lexer uses ``YYGETCONDITION`` to get current condition (line 16)
  and ``YYSETCONDITION`` to set it (line 18).
* Each condition has a unique label (prefixed with ``yyc_`` by default).
  Actions can use these labels to jump between conditions.
  Alternatively the whole block may be enclosed in a loop:
  then lexer will go through the initial dispatch on each iteration (but this might be slow).
* Star rule ``<*>`` (line 21) is merged to all conditions (low priority).
* Rule with multiple conditions (line 28) is merged to each listed condition (normal priority).
* ``:=>`` (lines 23, 24, 25, 26) implies immediate transition
  (bypassing initial dispatch).

Generate, compile and run:

.. code-block:: bash

    $ re2c -c -o example.cc 05_parsing_integers_conditions.re
    $ g++ -o example example.cc
    $ ./example "" 0 0b11100001 012345 67890 0xffE 0x 0b
    error :[
    0
    225
    5349
    67890
    4094
    error :[
    error :[


.. Braille patterns (encodings):

Braille patterns (encodings)
----------------------------

This example is about encoding support in re2c.
It's a partial decoder from Grade-1 (uncontracted) Unicode English Braille to plain English.
The input may be encoded in UTF-8, UTF-16, UTF-32 or UCS-2:
all of these encodings are capable of representing Braille patterns (code points ``[0x2800 - 0x28ff]``).
We use ``-r`` option to reuse the same block of re2c rules with different encodings.

So. The hardest part is to get some input.
Here is a message out of the void:

.. include:: examples/06_braille.utf8.txt

It appears to be UTF-8 encoded `[06_braille.utf8.txt] <examples/06_braille.utf8.txt.html>`_.
Now translate it into UTF-16, UTF-32 or UCS-2:

.. code-block:: bash

    $ iconv -f utf8 -t utf16le 06_braille.utf8.txt > 06_braille.utf16.txt
    $ iconv -f utf8 -t utf32le 06_braille.utf8.txt > 06_braille.utf32.txt
    $ iconv -f utf8 -t ucs2 06_braille.utf8.txt > 06_braille.ucs2.txt

And the input is ready.

Grade-1 Braille is quite simple (compared to Grade-2 Braille).
Patterns map directly to symbols (letters, digits and punctuators) except for a couple of special patterns:
numeric mode indicator (⠼), letter mode indicator (⠰), capital letter (⠠)
and some other, which we omit for simplicity (as well as a few ambiguous punctuation patterns).
Grade-2 Braille allows contractions; they obey complex rules (like those of a natural language)
and are much harder to implement.

`[06_braille.re] <examples/06_braille.re>`_

.. include:: examples/06_braille.re
    :code: cpp
    :number-lines:

Notes:

* Reuse mode is enabled with ``-r`` option.
* In reuse mode re2c expects a single ``/*!rules:re2c ... */`` block (line 49)
  followed by multiple ``/*!use:re2c ... */`` blocks (lines 140, 157 and 176).
  All blocks can have their own configurations, definitions and rules.
* Encoding can be enabled either with command-line option or with configuration.
* Each encoding needs an appropriate code unit type (``YYCTYPE``).
* We use conditions to switch between numeric and normal modes (lines 76 and 104).

Generate, compile and run:

.. code-block:: bash

    $ re2c -cr8 -o example.cc 06_braille.re
    $ g++ -o example example.cc
    $ ./example
    utf8:
    All human beings are born free and equal in dignity and rights. 
    They are endowed with reason and conscience and should act towards 
    one another in a spirit of brotherhood.
    
    utf16:
    All human beings are born free and equal in dignity and rights. 
    They are endowed with reason and conscience and should act towards 
    one another in a spirit of brotherhood.
    
    utf32:
    All human beings are born free and equal in dignity and rights. 
    They are endowed with reason and conscience and should act towards 
    one another in a spirit of brotherhood.
    
    ucs2:
    All human beings are born free and equal in dignity and rights. 
    They are endowed with reason and conscience and should act towards 
    one another in a spirit of brotherhood.


.. C++98 lexer:

C++98 lexer
-----------

`[07_c++98.re] <examples/07_c++98.re>`_

.. include:: examples/07_c++98.re
    :code: cpp
    :number-lines:

Generate, compile and run:

.. code-block:: bash

    $ re2c -o example.cc 07_c++98.re
    $ g++ -o example example.cc
    $ ./example 07_c++98.re | fold
     STATIC CONST size_t SIZE = 64 * 1024; STRUCT input_t { UNSIGNED CHAR buf[SIZE +
     YYMAXFILL]; UNSIGNED CHAR *lim; UNSIGNED CHAR *cur; UNSIGNED CHAR *mar; UNSIGNE
    D CHAR *tok; BOOL eof; FILE *CONST file; input_t(FILE *f) : buf() , lim(buf + SI
    ZE) , cur(lim) , mar(lim) , tok(lim) , eof(false) , file(f) {} BOOL fill(size_t 
    need) { IF (eof) { RETURN false; } CONST size_t free = tok - buf; IF (free < nee
    d) { RETURN false; } memmove(buf, tok, lim - tok); lim -= free; cur -= free; mar
     -= free; tok -= free; lim += fread(lim, 1, free, file); IF (lim < buf + SIZE) {
     eof = true; memset(lim, 0, YYMAXFILL); lim += YYMAXFILL; } RETURN true; } }; TE
    MPLATE<INT base> STATIC BOOL adddgt(UNSIGNED LONG &u, UNSIGNED LONG d) { IF (u >
     (ULONG_MAX - d) / base) { RETURN false; } u = u * base + d; RETURN true; } STAT
    IC BOOL lex_int_sfx(CONST UNSIGNED CHAR *s, UNSIGNED LONG u) { } STATIC BOOL lex
    _oct(CONST UNSIGNED CHAR *s, BOOL sfx, UNSIGNED LONG &u) { FOR (u = 0, ++s;;) { 
    } } STATIC BOOL lex_dec(CONST UNSIGNED CHAR *s, BOOL sfx, UNSIGNED LONG &u) { FO
    R (u = 0;;) { } } STATIC BOOL lex_hex(CONST UNSIGNED CHAR *s, BOOL sfx, UNSIGNED
     LONG &u) { FOR (u = 0, s += 2;;) { } } STATIC BOOL lex_str(input_t &in, UNSIGNE
    D CHAR q) { printf("\x25\x63", q); FOR (UNSIGNED LONG u = q;; printf("\x5c\x78\x
    25\x6c\x78", u)) { in.tok = in.cur; } printf("\x25\x63", q); RETURN true; } STAT
    IC BOOL lex_flt(CONST UNSIGNED CHAR *s) { DOUBLE d = 0; DOUBLE x = 1; INT e = 0;
     mant_int: mant_frac: exp_sign: exp: sfx: end: printf("\x25\x67", d); RETURN tru
    e; } STATIC BOOL lex(input_t &in) { UNSIGNED LONG u; FOR (;;) { in.tok = in.cur;
     } } INT main(INT argc, CHAR **argv) { IF (argc != 2) { printf ("\x75\x73\x61\x6
    7\x65\x3a\x20\x2e\x2f\x65\x78\x61\x6d\x70\x6c\x65\x20\x3c\x66\x69\x6c\x65\x6e\x6
    1\x6d\x65\x3e\xa"); RETURN 1; } FILE *file = fopen(argv[1], "\x72\x62"); IF (!fi
    le) { printf("\x65\x72\x72\x6f\x72\x3a\x20\x63\x61\x6e\x6e\x6f\x74\x20\x6f\x70\x
    65\x6e\x20\x66\x69\x6c\x65\x3a\x20\x25\x73\xa", argv[1]); RETURN 1; } input_t in
    (file); IF (!lex(in)) { printf("\x2e\x2e\x2e\x20\x65\x72\x72\x6f\x72\xa"); } ELS
    E { printf("\xa"); } fclose(file); RETURN 0; }


