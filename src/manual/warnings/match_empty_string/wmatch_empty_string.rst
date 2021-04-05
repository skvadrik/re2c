[-Wmatch-empty-string]
--------------------------

``[-Wmatch-empty-string]`` warns when a rule is nullable (matches an empty
string). It was intended to prevent infinite looping in cases like the
:download:`[hang.re] </manual/warnings/match_empty_string/hang.re>`
example below. The program loops over its arguments (the outer ``for`` loop)
and tries to lex each argument (the inner ``for`` loop). The lexer stops when
all input has been consumed and it sees the terminating ``NULL``. Arguments must
consist of lowercase letters only.

.. literalinclude:: /manual/warnings/match_empty_string/hang.re
    :language: cpp

On well-formed input the program runs as expected. However, if one of the
arguments contains a symbol diffrerent from lowercase letter, the program hangs
forever:

.. code-block:: none

    $ re2c -Wmatch-empty-string hang.re -o hang.c
    hang.re:11:19: warning: rule matches empty string [-Wmatch-empty-string]
    $ c++ -o hang hang.c
    $
    $ ./hang only lowercase letters
    argv[1]: only
    argv[2]: lowercase
    argv[3]: letters
    $
    $ ./hang right ?
    argv[1]: right
    ^C

Note that if we add default rule ``*``, the lexer won't hang anymore: it will
match the default rule instead of the nullable rule. The fix is easy: make the
rule non-nullable (say, ``[a-z]+``) and add default rule ``*``.

In some cases matching an empty string makes perfect sense: for example, it
might be used as a non-consuming default rule, or it might be used to lex an
optional lexeme (if the corresponding rule doesn't match, the lexer jumps to
another block and resumes lexing at the same input position). All these cases
are valid, so if ``[-Wmatch-empty-string]`` becomes annoying, it can be silenced
with ``[-Wno-match-empty-string]``.

