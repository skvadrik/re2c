[-Wuseless-escape]
--------------------------

Sometimes people escape characters that don't need to be escaped --- either
because they (mistakenly) think that the character is special and must be
escaped in the given context, or because they think that this escape sequence
means something (when it actually doesn't), or just by pure accident. With
``-Wuseless-escape`` option re2c warns about ignored escapes. Consider this
example (escapes.re):

.. code-block:: cpp

    /*!re2c
        *                        {}
        "\a\A\"\'\[\]\-\x5d\377" {}
        '\a\A\"\'\[\]\-\x5d\377' {}
        [\a\A\"\'\[\]\-\x5d\377] {}
    */

Re2c reports a bunch of warnings:

.. code-block:: none

    $ re2c -Wuseless-escape escapes.re -o escapes.c
    escapes.re:3:7: warning: escape has no effect: '\A' [-Wuseless-escape]
    escapes.re:3:11: warning: escape has no effect: '\'' [-Wuseless-escape]
    escapes.re:3:13: warning: escape has no effect: '\[' [-Wuseless-escape]
    escapes.re:3:15: warning: escape has no effect: '\]' [-Wuseless-escape]
    escapes.re:3:17: warning: escape has no effect: '\-' [-Wuseless-escape]
    escapes.re:4:7: warning: escape has no effect: '\A' [-Wuseless-escape]
    escapes.re:4:9: warning: escape has no effect: '\"' [-Wuseless-escape]
    escapes.re:4:13: warning: escape has no effect: '\[' [-Wuseless-escape]
    escapes.re:4:15: warning: escape has no effect: '\]' [-Wuseless-escape]
    escapes.re:4:17: warning: escape has no effect: '\-' [-Wuseless-escape]
    escapes.re:5:7: warning: escape has no effect: '\A' [-Wuseless-escape]
    escapes.re:5:9: warning: escape has no effect: '\"' [-Wuseless-escape]
    escapes.re:5:11: warning: escape has no effect: '\'' [-Wuseless-escape]
    escapes.re:5:13: warning: escape has no effect: '\[' [-Wuseless-escape]

This is because the ``\A`` and ``\[`` escapes are meaningless in all rules,
``\-`` makes sense only in a character class, 
and each type of closing quotes (``"``, ``'`` and ``]``) should only be escaped inside of a string delimited with the same quotes.
Useless escapes are ignored: the escaped symbol is treated as not escaped (``\A`` becomes ``A``, etc.).
The above example should be fixed as follows:

.. code-block:: cpp

    /*!re2c
        *                    {}
        "\aA\"'[]-\x5d\377"  {}
        '\aA"\'[]-\x5d\377'  {}
        [\aA"'[\]\-\x5d\377] {}
    */

More generally, re2c recognizes escapes in the following lexemes:

* double-quoted strings ``" ... "``
* single-quoted strings ``' ... '``
* character classes ``[ ... ]`` and ``[^ ... ]``

The following escapes are recognized:

* Closing quotes (``\"`` for double-quoted strings, ``\'`` for single-quoted strings, and ``\]`` for character classes).
* Dash ``\-`` in character classes.
* Octal escapes: ``\ooo``, where ``o`` is in range ``[0 - 7]``
  (the largest octal escape is ``\377``, which equals ``0xFF``).
* Hexadecimal escapes: ``\xhh``, ``\Xhhhh``, ``\uhhhh``, and ``\Uhhhhhhhh``,
  where ``h`` is in range ``[0 - 9]``, ``[a - f]``, or ``[A - F]``.
* Miscellaneous escapes: ``\a``, ``\b``, ``\f``, ``\n``, ``\r``, ``\t``, ``\v``, ``\\``.

Ill-formed octal and hexadecimal escapes are treated as errors.
An escape followed by a newline is also an error: multiline strings and character classes are not allowed.
Any other ill-formed escapes are ignored.


