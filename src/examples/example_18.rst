Push model
----------

By default re2c generates *pull-model* lexers:
it assumes that the lexer runs without interrupts and calls ``YYFILL`` to "pull" more input.
In some cases it might be necessary to generate a *push-model* lexer
that stops when it runs out of input and returns control to the outer program.
Later, when the outer program obtains more input, it resumes lexer and continues lexing from the point where it stopped.

In order to function in this manner lexer must be able to store its inner state before returning to the caller.
This can be done with re2c ``-f`` ``--storable-state`` option `described here </manual/features/state/state.html>`_.
The example below reads chunks of input from ``stdin`` and counts the number of words in it.
Note that the parsing loop is located in the ``main`` function,
and ``YYFILL`` merely returns instead of refilling buffer.
Lexer state is represented with variables ``state``, ``yych`` and ``yyaccept``.
Dispatch on ``state`` is generated with the help of ``/*!getstate:re2c*/`` directive.
In this example explicit use of the directive is necessary, because we need to put entry code between state dispatch and lexer start.
If the directive is omitted, re2c emits state dispatch right before lexer start
(in this case ``yy0`` should be used as the start label).

:download:`[push_model.re] <18_push_model.if.re>`

.. literalinclude:: 18_push_model.if.re
    :language: cpp
    :linenos:

Compile:

.. code-block:: bash

    $ re2c --storable-state -o push_model.cc push_model.re
    $ g++ -o push_model push_model.cc

Run:

.. code-block:: bash

    $ ./push_model
    Lorem ipsum dolor sit amet^D
    word count: 5


