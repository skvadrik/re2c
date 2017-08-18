Floating-point
--------------

This example demonstrates how tags can be used to lex floating-point numbers.

:download:`[float.re] <12_float.re.txt>`

.. literalinclude:: 12_float.re.txt
    :language: cpp
    :linenos:

Compile:

.. code-block:: bash

    $ re2c --tags -o float.cc float.re
    $ g++ -o float float.cc

Run:

.. code-block:: bash

    $ ./float 10.123e34 1 22. .123 e2 1e3 .
    1.0123e+35
    1
    22
    0.123
    nan
    1000
    nan



