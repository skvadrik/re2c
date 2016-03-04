Parsing integers (multiple re2c blocks)
---------------------------------------

This example is based on `Recognizing integers: the sentinel method <example_01.html>`_ example,
only now integer literals are parsed rather than simply recognized.
Parsing integers is simple: one can easily do it by hand.
However, re2c-generated code *does* look like a simple handwritten parser:
a couple of dereferences and conditional jumps. No overhead. ``:)``

:download:`[04_parsing_integers_blocks.re] <04_parsing_integers_blocks.re.txt>`

.. literalinclude:: 04_parsing_integers_blocks.re.txt
    :language: cpp
    :linenos:

Notes:

* Configurations and definitions (lines 20 - 26) are not scoped to a single re2c block — they are global.
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


