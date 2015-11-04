.. _Recognizing integers: the sentinel method:

Recognizing integers: the sentinel method
-----------------------------------------

This example is very simple, yet practical.
We assume that the input is small (fits in one continuous piece of memory).
We also assume that some characters never occur in well-formed input (but may occur in ill-formed input).
This is often the case in simple real-world tasks like parsing program options,
converting strings to numbers, determining binary file type based on magic in the first few bytes,
efficiently switching on a string and many others.
Our example program simply loops over its commad-line arguments
and tries to match each argument against one of the four patterns:
binary, octal, decimal and hexadecimal integer literals.
The numbers are not *parsed* (their numeric value is not retrieved), they are merely *recognized*.

`[01_recognizing_integers.re] <examples/01_recognizing_integers.re>`_

.. include:: examples/01_recognizing_integers.re
    :code: cpp
    :number-lines:

A couple of things should be noted:

* Default case (when none of the rules matched) is handled properly with ``*`` rule (line 16).
  **Never forget to handle default case, otherwise control flow in lexer will be undefined for some input strings.**
  Use [-Wundefined-control-flow] re2c warning: it will warn you about unhandled default case and
  show input patterns that are not covered by the rules.

* We use the *sentinel* method to stop at the end of input (``re2c:yyfill:enable = 0;`` at line 8).
  Sentinel is a special character that can never occur in well-formed input.
  It is appended to the end of input and serves as a stop signal for the lexer.
  In out case sentinel is ``NULL``: all arguments are ``NULL``-terminated and none of the rules matches ``NULL`` in the middle.
  Lexer will inevitably stop when it sees ``NULL``.
  Note that we make no assumptions about the input, it may contain any characters.
  **But do make sure that the sentinel character is not allowed in the middle of a rule.**

* ``YYMARKER`` (line 5) is needed because rules overlap:
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
    dec: 12345678901234567890
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
Strings (in generic sense) are different from other kinds of lexemes: they can contain *arbitrary* characters.
It makes them a way more difficult to lex: unlike the previous example (`Recognizing integers: the sentinel method`_),
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


.. _Arbitrary large input and YYFILL:

Arbitrary large input and YYFILL
--------------------------------

In this example we make the following assumptions:

1. Input cannot be mapped in memory at once (it is very large, its size cannot be determined in advance, etc.).

The usual thing to do in such case is to allocate a buffer and lex input in chunks that fit into buffer.
re2c allows us to refill buffer using ``YYFILL``: see example `Recognizing strings: the need for YYMAXFILL`_
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
However, ``YYMARKER`` is not always used and even when it is, its usage depends on the input:
not all control flow paths in lexer ever initialize it.
Thus for some inputs ``YYMARKER`` is meaningless
and should be used with care.
In practice input rarely consists of one giant lexeme: it is usually a sequence of small lexemes.
In that case lexer runs in a loop and it is convenient to have a special "lexeme start" pointer.
It can be used as boundary in ``YYFILL``.

Our example program reads ``stdin`` in chunks of 16 bytes (in real word buffer size is usually ~4Kb)
and tries to lex numbers separated by newlines.

`[03_arbitrary_large_input.re] <examples/03_arbitrary_large_input.re>`_

.. include:: examples/03_arbitrary_large_input.re
    :code: cpp
    :number-lines:

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


.. _Parsing integers (multiple re2c blocks):

Parsing integers (multiple re2c blocks)
---------------------------------------

This example is based on `Recognizing integers: the sentinel method`_ example,
only now integer literals are parsed rather than simply recognized.
Parsing integers is simple: one can easily do it by hand.
However, re2c-generated code *does* look like a simple handwritten parser:
a couple of dereferences and conditional jumps. No overhead. ``:)``

`[04_parsing_integers_blocks.re] <examples/04_parsing_integers_blocks.re>`_

.. include:: examples/04_parsing_integers_blocks.re
    :code: cpp
    :number-lines:

Notes:

* Configurations and definitions (lines 20 - 26) are not scoped to a single re2c block --- they are global.
  Each block may override configurations, but this affects global scope.
* Blocks don't have to be in the same function: they can be in separate functions or elsewhere
  as long as the exposed interface fits into lexical scope.

Generate, compile and run:

.. code-block:: bash

    $ re2c -o example.cc 04_parsing_integers_blocks.re
    $ g++ -o example example.cc
    $ ./example 0 12345678901234567890 0xFFFFffffFFFFffff 0x1FFFFffffFFFFffff 0xAbcDEf 0x00 007 0B0 0b110101010 ""
    0
    12345678901234567890
    18446744073709551615
    error
    11259375
    0
    7
    0
    426
    error


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

* Each condition has a unique identifier: ``/*!types:re2c*/`` tells re2c to generate
  enumeration of all identifiers (names are prefixed with ``yyc`` by default).
  Lexer uses ``YYGETCONDITION`` to get the identifier of current condition
  and ``YYSETCONDITION`` to set it.

* Each condition has a unique label (prefixed with ``yyc_`` by default).

* Conditions are connected: transitions are allowed between final states of one condition
  and start state of another condition (but not between inner states of different conditions).
  The generated code starts with dispatch.
  Actions can either jump to the initial dispatch or jump directly to any condition.

* Rule ``<*>`` is merged to all conditions (low priority).

* Rules with multiple conditions are merged to each listed condition (normal priority).

* ``:=>`` jumps directly to the next condition (bypassing the initial dispatch).

Generate, compile and run:

.. code-block:: bash

    $ re2c -c -o example.cc 05_parsing_integers_conditions.re
    $ g++ -o example example.cc
    $ ./example 0 12345678901234567890 0xFFFFffffFFFFffff 0x1FFFFffffFFFFffff 0xAbcDEf 0x00 007 0B0 0b110101010 ""
    0
    12345678901234567890
    18446744073709551615
    error
    11259375
    0
    7
    0
    426
    error


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
Convert it into UTF-16, UTF-32 or UCS-2:

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
* In reuse mode re2c expects a single ``/*!rules:re2c ... */`` block
  followed by multiple ``/*!use:re2c ... */`` blocks.
  All blocks can have their own configurations, definitions and rules.
* Encoding can be enabled either with command-line option or with configuration.
* Each encoding needs an appropriate code unit type (``YYCTYPE``).
* We use conditions to switch between numeric and normal modes.

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

This is an example of a big real-world re2c program: C++98 lexer.
It confirms to the C++98 standard (except for a couple of hacks to simulate preprocessor).
All nontrivial lexemes (integers, floating-point constants, strings and character literals)
are parsed (not only recognized): numeric literals are converted to numbers, strings are unescaped.
Some additional checks described in standard (e.g. overflows in integer literals) are also done.
In fact, C++ is an easy language to lex: unlike many other languages, lexer can proceed without feedback from parser.

`[07_c++98.re] <examples/07_c++98.re>`_

.. include:: examples/07_c++98.re
    :code: cpp
    :number-lines:

Notes:

* The main lexer is used to lex all trivial lexemes (macros, whitespaces, boolean literals, keywords, operators and punctuators, identifiers),
  recognize numeric literals (which are further parsed by a bunch of auxilary lexers),
  and recognize the start of string and character literals (which are further recognized and parsed by an auxilary lexer).
  Numeric literals are thus lexed twice: this approach may be deemed inefficient,
  but it takes much more effort to validate and parse them at once.
  Besides, a real-world lexer would rather recognize ill-formed lexemes (e.g. overflowed integer literals),
  report them and resume lexing.

* The main lexer and string lexer both use ``re2c:yyfill:enable = 1;``, other lexers use ``re2c:yyfill:enable = 0;``.
  This is very important: both main lexer and string lexer advance input position to new (yet unseen) input characters,
  so they must check for the end of input and call ``YYFILL``. In conrast, other lexers only parse lexemes that
  have been already recognized by the main lexer: these lexemes are guaranteed to be within buffer bounds
  (they are guarded by ``in.tok`` on the left and ``in.lim`` on the right).

* The hardest part is (unsurprisingly) floating-point literals.
  They are just as hard to lex as to use. ``:)``

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


