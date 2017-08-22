Braille patterns
----------------

This example is about encoding support in re2c.
It's a partial decoder from Grade-1 (uncontracted) Unicode English Braille to plain English.
The input may be encoded in UTF-8, UTF-16, UTF-32, or UCS-2:
all of these encodings are capable of representing Braille patterns (code points ``[0x2800 - 0x28ff]``).
We use the ``-r`` option to reuse the same block of re2c rules with different encodings.

So. The hardest part is to get some input.
Here is a message out of the void:

.. include:: 06_braille.utf8.txt

It appears to be UTF-8 encoded :download:`[braille.utf8.txt] <06_braille.utf8.txt>`.
Let's convert it into UTF-16, UTF-32, and UCS-2:

.. code-block:: bash

    $ iconv -f utf8 -t utf16le 06_braille.utf8.txt > 06_braille.utf16.txt
    $ iconv -f utf8 -t utf32le 06_braille.utf8.txt > 06_braille.utf32.txt
    $ iconv -f utf8 -t ucs2 06_braille.utf8.txt > 06_braille.ucs2.txt

And the input is ready.

Grade-1 Braille is quite simple (compared to Grade-2 Braille).
Patterns map directly to symbols (letters, digits, and punctuators) except for a couple of special patterns:
the numeric mode indicator (⠼), the letter mode indicator (⠰), the capital letter indicator (⠠) 
and some others, which we omit here for the sake of simplicity (as well as a few ambiguous punctuation patterns).
Grade-2 Braille allows contractions; those obey some rather complex rules (like those of a natural language)
and are much harder to implement.

:download:`[braille.re] <06_braille.cr8i.re>`

.. literalinclude:: 06_braille.cr8i.re
    :language: cpp
    :linenos:

Notes:

* The reuse mode is enabled with the ``-r`` option.
* In the reuse mode, re2c expects a single ``/*!rules:re2c ... */`` block
  followed by multiple ``/*!use:re2c ... */`` blocks.
  All blocks can have their own configurations, definitions, and rules.
* Encoding can be enabled either with a command-line option or a configuration.
* Each encoding needs the appropriate code unit type (``YYCTYPE``).
* We use conditions to switch between numeric and normal modes.

Compile:

.. code-block:: bash

    $ re2c -cr8 -o braille.cc braille.re
    $ g++ -o braille braille.cc

Run:

.. code-block:: bash

    $ ./braille
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


