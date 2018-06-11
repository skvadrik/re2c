Numbers
-------

This example is very simple, yet practical.
We assume that the input is small (fits in one continuous block of memory).
We also assume that some characters never occur in well-formed input (but may occur in input that's ill-formed).
This is often the case in simple real-world tasks such as parsing program options,
converting strings to numbers, determining binary file types based on some magic in the first few bytes, or
efficiently switching on a string.
Our example program simply loops over its command-line arguments
and tries to match each argument against one of four patterns:
binary, octal, decimal, and hexadecimal integer literals.
The numbers are not *parsed* (their numeric value is not retrieved), they are merely *recognized*.

:download:`[integers.re] <01_recognizing_integers.i.re>`

.. literalinclude:: 01_recognizing_integers.i.re
    :language: cpp
    :linenos:

A couple of things should be noted:

* The default case (when none of the rules matched) is handled properly with the ``*`` rule (line 18).
  **Never forget to handle the default case, otherwise control flow in the lexer for some input strings will be undefined .**
  Use the `[-Wundefined-control-flow] <../manual/warnings/undefined_control_flow/wundefined_control_flow.html>`_ re2c warning:
  it will warn you about the unhandled default case and show the input patterns that are not covered by the rules.

* We use the *sentinel* method to stop at the end of input (``re2c:yyfill:enable = 0;`` at line 10).
  A sentinel is a special character that can never occur in well-formed input.
  It is appended to the end of input and serves as a stop signal for the lexer.
  In our case, the sentinel is ``NULL``: all arguments are ``NULL``-terminated and none of the rules matches ``NULL`` in the middle.
  The lexer will inevitably stop when it sees a ``NULL``.
  Note that we make no assumptions about the input; it may contain any characters.
  **But do make sure that the sentinel character is not allowed in the middle of a rule.**

* ``YYMARKER`` (line 7) is needed because rules overlap:
  it backs up the input position of the longest successful match.
  Imagine we have overlapping rules ``"a"`` and ``"abc"`` and input string ``"abd"``:
  by the time ``"a"`` matches, there's still a chance to match ``"abc"``,
  but when the lexer sees ``'d'``, it must roll back.
  (You might wonder why ``YYMARKER`` is exposed at all: why not make it a local variable like ``yych``?
  The reason is, all input pointers must be updated by ``YYFILL``
  as explained in the `Large input <example_03.html>`_ example.)

Compile:

.. code-block:: bash

    $ re2c -o integers.cc integers.re
    $ g++ -o integers integers.cc

Run:

.. code-block:: bash

    $ ./integers 123 0xfF 010 0B101 oO0
    decimal
    hexadecimal
    octal
    binary
    error

