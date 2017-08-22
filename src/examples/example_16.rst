Fake sentinel
-------------

This example explores the case when we know the *length* of input,
but there is no terminating character and buffering is not possible.
In such cases we cannot use the usual sentinel method; and we cannot use ``YYLIMIT``-based method as it requires ``YYMAXFILL`` padding.
The choiche then is to use generic API:
disable the default cheching mechanism with ``re2c:yyfill:enable = 0;``
and use one of the primitives ``YYPEEK`` and ``YYSKIP`` to check for the end of input.

In this example we use ``YYPEEK`` to emulate *fake sentinel*:
every time the lexer peeks a new character, it first checks for the end of input:
if it has already been reached, ``YYPEEK`` returns ``NULL`` (though the actual string has no terminating ``NULL``).
Checking on every ``YYPEEK`` is less efficient than the usual sentinel method
(which performs no checking at all), but it can be more efficient than copying input to buffer and padding it with a real sentinel character.

Note that fake sentinel method also relies on the fact that sentinel cannot appear in the middle of well-formed input.
If the input can contain arbitrary characters, then one should utilize ``YYSKIP`` as shown in `this example <example_15.html>`_.

:download:`[fake_sentinel.re] <16_fake_sentinel.i--input(custom).re>`

.. literalinclude:: 16_fake_sentinel.i--input(custom).re
    :language: cpp
    :linenos:

Compile:

.. code-block:: bash

    $ re2c --input custom -o fake_sentinel.cc fake_sentinel.re
    $ g++ -o fake_sentinel fake_sentinel.cc

Run:

.. code-block:: bash

    $ ./fake_sentinel somestring
    somestring;
