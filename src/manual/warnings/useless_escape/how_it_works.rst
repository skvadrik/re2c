How it works
~~~~~~~~~~~~

re2c recognizes escapes in the following lexemes:

* double-quoted strings ``" ... "``
* single-quoted strings ``' ... '``
* character classes ``[ ... ]`` and ``[^ ... ]``

The following escapes are recognized:

* Closing quotes (``\"`` for double-quoted strings, ``\'`` for single-quoted strings and ``\]`` for character classes).
* Dash ``\-`` in character classes.
* Octal escapes: ``\ooo``, where ``o`` is in range ``[0 - 7]``
  (maximal octal escape is ``\377``, which equals ``0xFF``).
* Hexadecimal escapes: ``\xhh``, ``\Xhhhh``, ``\uhhhh`` and ``\Uhhhhhhhh``,
  where ``h`` is in range ``[0 - 9]``, ``[a - f]`` or ``[A - F]``.
* Miscellaneous escapes: ``\a``, ``\b``, ``\f``, ``\n``, ``\r``, ``\t``, ``\v``, ``\\``.

Ill-formed octal and hexadecimal escapes are treated as errors.
Escape followed by a newline is also an error: multiline strings and classes are not allowed
(this is very inconvenient; hopefully it will be fixed in future).
Any other ill-formed escapes are ignored.
If ``[-Wuseless-escape]`` is enabled, re2c warns about ignored escapes.

