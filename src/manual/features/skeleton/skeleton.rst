Skeleton
--------

.. toctree::
    :hidden:

With ``-S, --skeleton`` option re2c ignores all non-re2c code and generates a self-contained C program
that can be further compiled and executed.
The program consists of lexer code and input data.
For each constructed DFA (block or condition) re2c generates a standalone lexer and two files:
``.input`` file with strings derived from the DFA and ``.keys`` file with expected match results.
The program runs each lexer on the corresponding ``.input`` file
and compares results with the expectations.

For encodings with 1-byte code units (such as ASCII, UTF-8 and EBCDIC) the generated data
covers all DFA transitions (in other words, skeleton program triggers each conditional jump in lexer).
For encodings with multibyte code units the generated data covers up to 256 transitions
of each disjoint character range in DFA (see `Generating data`_ section for details).


.. include:: example.rst
.. include:: failures.rst
.. include:: generating_data.rst
.. include:: use.rst



