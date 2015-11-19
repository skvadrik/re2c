Skeleton
--------

.. include:: ../home.rst
.. include:: ../../../contents.rst


With ``-S, --skeleton`` option re2c ignores all non-re2c code and generates a self-contained C-90 program
that can be further compiled and executed.
The program consists of lexer code and input data.
For each constructed DFA (block or condition) re2c generates a standalone lexer and two files:
``.input`` file with strings derived from the DFA and ``.keys`` file with expected match results.
The program runs each lexer on the corresponding ``.input`` file
and compares results with the expectations.


.. include:: example.rst
.. include:: failures.rst
.. include:: generating_data.rst
.. include:: use.rst



