Conditions
----------

This example demonstrates the use of conditions.
It is similar in functionality to the `Multiple blocks <example_04.html>`_ example,
except that individual sub-lexers are connected usding conditions rather than multiple blocks.
Conditions allow to encode multiple interconnected lexers within a single re2c block.

:download:`[conditions.re] <05_parsing_integers_conditions.ci.re>`

.. literalinclude:: 05_parsing_integers_conditions.ci.re
    :language: cpp
    :linenos:

Notes:

* Conditions are enabled with the ``-c`` option.

* Conditions are only syntactic sugar; they can be translated into multiple blocks.

* Each condition is a standalone lexer (DFA).

* Each condition has a unique identifier: ``/*!types:re2c*/`` tells re2c to generate
  an enumeration of all the identifiers (the names are prefixed with ``yyc`` by default).
  The lexer uses ``YYGETCONDITION`` to get the identifier of the current condition
  and ``YYSETCONDITION`` to set it.

* Each condition has a unique label (prefixed with ``yyc_`` by default).

* Conditions are connected: transitions are allowed between the final states of one condition
  and the start state of another condition (but not between inner states of different conditions).
  The generated code starts with dispatch.
  Actions can either jump to the initial dispatch or jump directly to a condition.

* The ``<*>`` rule is merged to all conditions (low priority).

* Rules with multiple conditions are merged to each listed condition (normal priority).

* ``:=>`` jumps directly to the next condition (bypassing the initial dispatch).

Compile:

.. code-block:: bash

    $ re2c -c -o conditions.cc conditions.re
    $ g++ -o conditions conditions.cc

Run:

.. code-block:: bash

    $ ./conditions 0 12345678901234567890 0xFFFFffffFFFFffff 0x1FFFFffffFFFFffff 0xAbcDEf 0x00 007 0B0 0b110101010 ""
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


