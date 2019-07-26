Re2c provides a number of ways to handle end-of-input situation. Which way to
use depends on the complexity of regular expressions, performance
considerations, the need for input buffering and various other factors. EOF
handling is probably the most complex part of re2c user interface --- it
definitely requires a bit of understanding of how the generated lexer works.
But in return is allows the user to customize lexer for a particular environment
and avoid the unnecessary overhead of generic methods when a simpler method is
sufficient. Roughly speaking, there are four main methods:

- using sentinel symbol (simple and efficient, but limited)
- bounds checking with padding (generic, but complex)
- EOF rule: a combination of sentinel symbol and bounds checking (generic and
  simple, can be more or less efficient than bounds checking with padding
  depending on the grammar)
- using generic API (user-defined, so may be incorrect ;])

Using sentinel symbol
---------------------
This is the simplest and the most efficient method. It is applicable in cases
when the input is small enough to fit into a continuous memory buffer and there
is a natural "sentinel" symbol --- a code unit that is not allowed by any of the
regular expressions in grammar (except possibly as a terminating character).
Sentinel symbol never appears in well-formed input, therefore it can be appended
at the end of input and used as a stop signal by the lexer. A good example of
such input is a null-terminated C-string, provided that the grammar does not
allow ``NULL`` in the middle of lexemes. Sentinel method is very efficient,
because the lexer does not need to perform any additional checks for the end of
input --- it comes naturally as a part of processing the next character.

Below is an example of using sentinel method. Configuration
``re2c:yyfill:enable = 0;`` suppresses generation of end-of-input checks and
``YYFILL`` calls.

.. literalinclude:: /manual/features/eof/01_sentinel.re
    :language: c

Bounds checking with padding
----------------------------

Bounds checking is a generic method: it can be used with any input grammar.
The basic idea is simple: we need to check for the end of input before reading
the next input character. However, if implemented in a straightforward way, this
would be quite inefficient: checking on each input character would cause a major
slowdown. Re2c avoids slowdown by generating checks only in certain key states
of the lexer, and letting it run without checks in-between the key states.
More precisely, re2c computes strongly connected components (SCCs) of
the underlying DFA (which roughly correspond to loops), and generates only a few
checks per each SCC (usually just one, but in general enough to make the SCC
acyclic). The check is of the form ``(YYLIMIT - YYCURSOR) < n``, where ``n``
is the maximal length of a simple path in the corresponding SCC. If this
condiiton is true, the lexer calls ``YYFILL(n)``, which must either supply at
least ``n`` input characters, or do not return. When the lexer continues after
the check, it is certain that the next ``n`` characters can be read safely
without checks.

This approach reduces the number of checks significantly (and makes the lexer
much faster as a result), but it has a downside. Since the lexer checks for
multiple characters at once, it may end up in a situation when there are a few
remaining input characters (less than ``n``) corresponding to a short path in
the SCC, but the lexer cannot proceed because of the check, and ``YYFILL``
cannot supply more character because it is the end of input. To solve this
problem, re2c requires that additional padding consisting of fake characters is
appended at the end of input. The length of padding should be ``YYMAXFILL``,
which equals to the maximum ``n`` parameter to ``YYFILL`` and must be generated
by re2c using ``/*!max:re2c*/`` directive. The fake characters should not form a
valid lexeme suffix, otherwise the lexer may be fooled into matching a fake
lexeme. Usually it's a good idea to use ``NULL`` characters for padding.

Below is an example of using bounds checking with padding. Note that the grammar
rule for single-quoted strings allows arbitrary symbols in the middle of lexeme,
so there is no natural sentinel in the grammar. Strings like ``"aha\0ha"`` are
perfectly valid, but ill-formed strings like ``"aha\0`` are also possible and
shouldn’t crash the lexer. In this example we do not use buffer refilling,
therefore ``YYFILL`` definition simply returns an error. Note that ``YYFILL``
will only be called after the lexer reaches padding, because only then will the
check condition be satisfied.

.. literalinclude:: /manual/features/eof/02_bounds_checking.re
    :language: c

EOF rule
--------

EOF rule ``$`` was introduced in version 1.2. It is a hybrid approach that tries
to take the best of both worlds: simplicity and efficiency of the sentinel
method combined with the generality of bounds-checking method. The idea is to
appoint an arbitrary symbol to be the sentinel, and only perform further bounds
checking if the sentinel symbol matches (more precisely, if the symbol class that
contains it matches). The check is of the form ``YYLIMIT <= YYCURSOR``.
If this condition is not satisfied, then the sentinel is just an ordinary input
character and the lexer continues. Otherwise this is a real sentinel, and the
lexer calls ``YYFILL()``. If ``YYFILL`` returns zero, the lexer assumes that it
has more input and tries to re-match. Otherwise ``YYFILL`` returns non-zero and
the lexer knows that it has reached the end of input. At this point there are
three possibilities. First, it might have already matched a shorter lexeme ---
in this case it just rolls back to the last accepting state. Second, it might
have consumed some characters, but failed to match --- in this case it falls
back to default rule ``*``. Finally, it might be in the initial state --- in
this (and only this!) case it matches EOF rule ``$``.

Below is an example of using EOF rule. Configuration ``re2c:yyfill:enable = 0;``
suppresses generation of ``YYFILL`` calls (but not the bounds checks).

.. literalinclude:: /manual/features/eof/03_eof_rule.re
    :language: c

Using generic API
-----------------

Generic API can be used with any of the above methods. It also allows to use a
user-defined method by placing EOF checks in one of the basic primitives.
Usually this is either ``YYSKIP`` (the check is performed when advancing to the
next input character), or ``YYPEEK`` (the check is performed when reading the
next input character). The resulting methods are inefficient, as they check on
each input character. However, they can be useful in cases when the input cannot
be buffered or padded and does not contain a sentinel character at the end. One
should be cautious when using such ad-hoc methods, as it is easy to overlook
some corner cases and come up with a method that only partially works. Also it
should be noted that not everything can be expressed via generic API: for
example, it is impossible to reimplement the way EOF rule works (in particular,
it is impossible to re-match the character after successfull ``YYFILL``).

Below is an example of using ``YYSKIP`` to perform bounds checking without
padding. ``YYFILL`` generation is suppressed using ``re2c:yyfill:enable = 0;``
configuration. Note that if the grammar was more complex, this method might not
work in case when two rules overlap and EOF check fails after a shorter lexeme
has already been matched (as it happens in our example, there are no overlapping
rules).

.. literalinclude:: /manual/features/eof/04_generic_api.re
    :language: c
