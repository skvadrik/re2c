Braille patterns
----------------

This example is about encoding support in re2c.
It's a partial decoder from Grade-1 (uncontracted) Unicode English Braille to plain English.
Grade-1 Braille is quite simple (compared to Grade-2 Braille).
Patterns map directly to symbols (letters, digits, and punctuators) except for a couple of special patterns:
the numeric mode indicator (⠼), the letter mode indicator (⠰), the capital letter indicator (⠠) 
and some others, which we omit here for the sake of simplicity (as well as a few ambiguous punctuation patterns).
Grade-2 Braille allows contractions; those obey some rather complex rules (like those of a natural language)
and are much harder to implement.

The input may be encoded in UTF-8, UTF-16, UTF-32, or UCS-2:
all of these encodings are capable of representing Braille patterns (code points ``[0x2800 - 0x28ff]``).
We use the ``-r`` option to reuse the same block of re2c rules with different encodings.
The input to the example is the same Braille message
in different encodings:
:download:`braille.utf8.txt <braille.utf8.txt>`,
:download:`braille.utf16.txt <braille.utf16.txt>`,
:download:`braille.utf32.txt <braille.utf32.txt>` and
:download:`braille.ucs2.txt <braille.ucs2.txt>`:

.. include:: braille.utf8.txt

It means *"All human beings are born free and equal in dignity and rights. 
They are endowed with reason and conscience and should act towards 
one another in a spirit of brotherhood."*

:download:`[braille.re] <braille.re>`

.. literalinclude:: braille.re
    :language: cpp

Compile as ``re2c -cr -o braille.cc braille.re``. Notes:

* The reuse mode is enabled with the ``-r`` option.
* In the reuse mode, re2c expects a single ``/*!rules:re2c ... */`` block
  followed by multiple ``/*!use:re2c ... */`` blocks.
  All blocks can have their own configurations, definitions, and rules.
* Encoding can be enabled either with a command-line option or a configuration.
* Each encoding needs the appropriate code unit type (``YYCTYPE``).
* We use conditions to switch between numeric and normal modes.
