C++98 lexer
-----------

This is an example of a big, real-world re2c program: a C++98 lexer.
It conforms to the C++98 standard (except for a couple of hacks that simulate the preprocessor).
All nontrivial lexemes (integers, floating-point constants, strings, and character literals)
are parsed (not only recognized): numeric literals are converted to numbers, and strings are unescaped.
Some additional checks described in the standard (e.g., overflows in integer literals) are also done.
In fact, C++ is an easy language to lex: unlike in many other languages, the C++98 lexer can proceed without feedback from the parser.

:download:`[cxx98.re] <07_cxx98.i.re>`

.. literalinclude:: 07_cxx98.i.re
    :language: cpp
    :linenos:

Notes:

* The main lexer is used to lex all trivial lexemes (macros, whitespace, boolean literals, keywords, operators, punctuators, and identifiers),
  recognize numeric literals (which are further parsed by a bunch of auxiliary lexers),
  and recognize the start of a string and character literals (which are further recognized and parsed by an auxiliary lexer).
  Numeric literals are thus lexed twice: this approach may be deemed inefficient,
  but it takes much more effort to validate and parse them in one go.
  Besides, a real-world lexer would rather recognize ill-formed lexemes (e.g., overflown integer literals),
  report them, and resume lexing.

* We don't use re2c in cases where a hand-written parser looks simpler: when parsing octal and decimal literals
  (though a re2c-based parser would do exactly the same, without the slightest overhead).
  However, hexadecimal literals still require some lexing, which looks better with re2c.
  Again, it's only a matter of taste: a re2c-based implementation adds no overhead.
  Look at the generated code to make sure.

* The main lexer and string lexer both use ``re2c:yyfill:enable = 1;``, other lexers use ``re2c:yyfill:enable = 0;``.
  This is very important: both the main lexer and string lexer advance input position to new (yet unseen) input characters,
  so they must check for the end of input and call ``YYFILL``. In contrast, other lexers only parse lexemes that
  have already been recognized by the main lexer: these lexemes are guaranteed to be within buffer bounds
  (they are guarded by ``in.tok`` on the left and ``in.lim`` on the right).

* The hardest part is (unsurprisingly) floating-point literals.
  They are just as hard to lex as they are to use. ``:)``

Generate, compile, and run:

.. code-block:: bash

    $ re2c -o cxx98.cc cxx98.re
    $ g++ -o cxx98 cxx98.cc

Run:

.. code-block:: bash

    $ ./cxx98 07_cxx98.re | fold
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
    IC BOOL lex_oct(CONST UNSIGNED CHAR *s, CONST UNSIGNED CHAR *e, UNSIGNED LONG &u
    ) { FOR (u = 0, ++s; s < e; ++s) { IF (!adddgt<8>(u, *s - 48)) { RETURN false; }
     } RETURN true; } STATIC BOOL lex_dec(CONST UNSIGNED CHAR *s, CONST UNSIGNED CHA
    R *e, UNSIGNED LONG &u) { FOR (u = 0; s < e; ++s) { IF (!adddgt<10>(u, *s - 48))
     { RETURN false; } } RETURN true; } STATIC BOOL lex_hex(CONST UNSIGNED CHAR *s, 
    CONST UNSIGNED CHAR *e, UNSIGNED LONG &u) { FOR (u = 0, s += 2; s < e;) { } RETU
    RN true; } STATIC BOOL lex_str(input_t &in, UNSIGNED CHAR q) { printf("\x25\x63"
    , q); FOR (UNSIGNED LONG u = q;; printf("\x5c\x78\x25\x6c\x78", u)) { in.tok = i
    n.cur; } printf("\x25\x63", q); RETURN true; } STATIC BOOL lex_flt(CONST UNSIGNE
    D CHAR *s) { DOUBLE d = 0; DOUBLE x = 1; INT e = 0; mant_int: mant_frac: exp_sig
    n: exp: sfx: end: printf("\x25\x67", d); RETURN true; } STATIC BOOL lex(input_t 
    &in) { UNSIGNED LONG u; FOR (;;) { in.tok = in.cur; sfx: } } INT main(INT argc, 
    CHAR **argv) { IF (argc != 2) { printf ("\x75\x73\x61\x67\x65\x3a\x20\x2e\x2f\x6
    5\x78\x61\x6d\x70\x6c\x65\x20\x3c\x66\x69\x6c\x65\x6e\x61\x6d\x65\x3e\xa"); RETU
    RN 1; } FILE *file = fopen(argv[1], "\x72\x62"); IF (!file) { printf("\x65\x72\x
    72\x6f\x72\x3a\x20\x63\x61\x6e\x6e\x6f\x74\x20\x6f\x70\x65\x6e\x20\x66\x69\x6c\x
    65\x3a\x20\x25\x73\xa", argv[1]); RETURN 1; } input_t in(file); IF (!lex(in)) { 
    printf("\x2e\x2e\x2e\x20\x65\x72\x72\x6f\x72\xa"); } ELSE { printf("\xa"); } fcl
    ose(file); RETURN 0; }


