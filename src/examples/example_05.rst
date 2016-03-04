Parsing integers (conditions)
-----------------------------

This example does exactly the same as `Parsing integers (multiple re2c blocks) <example_04.html>`_ example,
but in a slightly different manner: it uses re2c conditions instead of blocks.
Conditions allow to encode multiple interconnected lexers within a single re2c block.

:download:`[05_parsing_integers_conditions.re] <05_parsing_integers_conditions.re.txt>`

.. literalinclude:: 05_parsing_integers_conditions.re.txt
    :language: cpp
    :linenos:

Notes:

* Conditions are enabled with ``-c`` option.

* Conditions are only syntactic sugar, they can be translated into multiple blocks.

* Each condition is a standalone lexer (DFA).

* Each condition has a unique identifier: ``/*!types:re2c*/`` tells re2c to generate
  enumeration of all identifiers (names are prefixed with ``yyc`` by default).
  Lexer uses ``YYGETCONDITION`` to get the identifier of current condition
  and ``YYSETCONDITION`` to set it.

* Each condition has a unique label (prefixed with ``yyc_`` by default).

* Conditions are connected: transitions are allowed between final states of one condition
  and start state of another condition (but not between inner states of different conditions).
  The generated code starts with dispatch.
  Actions can either jump to the initial dispatch or jump directly to any condition.

* Rule ``<*>`` is merged to all conditions (low priority).

* Rules with multiple conditions are merged to each listed condition (normal priority).

* ``:=>`` jumps directly to the next condition (bypassing the initial dispatch).

Generate, compile and run:

.. code-block:: bash

    $ re2c -c -o example.cc 05_parsing_integers_conditions.re
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


