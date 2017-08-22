Multiple blocks
---------------

This example demonstrates the use of multiple interrelated ``/*!re2c ... */`` blocks.
We pick a deliberately simple task (parsing integers),
so that all complexity is associated with relations between blocks and not with the lexical grammar.

:download:`[multiple_blocks.re] <04_parsing_integers_blocks.i.re>`

.. literalinclude:: 04_parsing_integers_blocks.i.re
    :language: cpp
    :linenos:

Notes:

* Configurations and definitions (lines 20 - 26) are not scoped to a single re2c block — they are global.
  Each block may override configurations, but this affects the global scope.
* Blocks don't have to be in the same function: they can be in separate functions or elsewhere
  as long as the exposed interface fits into the lexical scope.

Compile:

.. code-block:: bash

    $ re2c -o multiple_blocks.cc multiple_blocks.re
    $ g++ -o multiple_blocks multiple_blocks.cc

Run:

.. code-block:: bash

    $ ./multiple_blocks 0 12345678901234567890 0xFFFFffffFFFFffff 0x1FFFFffffFFFFffff 0xAbcDEf 0x00 007 0B0 0b110101010 ""
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


