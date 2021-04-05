C++98 lexer
-----------

This is an example of a big, real-world re2c program: a C++98 lexer.
It conforms to the C++98 standard (except for a couple of hacks that simulate the preprocessor).
All nontrivial lexemes (integers, floating-point constants, strings, and character literals)
are parsed (not only recognized): numeric literals are converted to numbers, and strings are unescaped.
Some additional checks described in the standard (e.g., overflows in integer literals) are also done.
In fact, C++ is an easy language to lex: unlike in many other languages, the C++98 lexer can proceed without feedback from the parser.

:download:`[cxx98.re] <cxx98.re>`

.. literalinclude:: cxx98.re
    :language: cpp

Compile as ``re2c -o cxx98.cc cxx98.re``. Notes:

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

* The most difficult part is parsing floating-point literals.
