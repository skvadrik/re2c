State
-----

.. toctree::
    :hidden:

When the ``-f`` flag is specified, ``re2c`` generates a scanner that can
store its current state, return to the caller, and later resume
operations exactly where it left off.

The default operation of ``re2c`` is a
"pull" model, where the scanner asks for extra input whenever it needs it. However, this mode of operation assumes that the scanner is the "owner"
the parsing loop, and that may not always be convenient.

Typically, if there is a preprocessor ahead of the scanner in the
stream, or for that matter any other procedural source of data, the
scanner cannot "ask" for more data unless both scanner and source
live in a separate threads.

The ``-f`` flag is useful for just this situation: it lets users design
scanners that work in a "push" model, i.e. where data is fed to the
scanner chunk by chunk. When the scanner runs out of data to consume, it
just stores its state, and return to the caller. When more input data is
fed to the scanner, it resumes operations exactly where it left off.

Changes needed compared to the "pull" model:

* User has to supply macros ``YYSETSTATE ()`` and ``YYGETSTATE (state)``.

* The ``-f`` option inhibits declaration of ``yych`` and ``yyaccept``. So the
  user has to declare these. Also the user has to save and restore these.
  In the example ``examples/push_model/push.re`` these are declared as
  fields of the (C++) class of which the scanner is a method, so they do
  not need to be saved/restored explicitly. For C they could e.g. be made
  macros that select fields from a structure passed in as parameter.
  Alternatively, they could be declared as local variables, saved with
  ``YYFILL (n)`` when it decides to return and restored at entry to the
  function. Also, it could be more efficient to save the state from
  ``YYFILL (n)`` because ``YYSETSTATE (state)`` is called unconditionally.
  ``YYFILL (n)`` however does not get ``state`` as parameter, so we would have
  to store state in a local variable by ``YYSETSTATE (state)``.

* Modify ``YYFILL (n)`` to return (from the function calling it) if more input is needed.

* Modify caller to recognise if more input is needed and respond appropriately.

* The generated code will contain a switch block that is used to
  restores the last state by jumping behind the corrspoding ``YYFILL (n)``
  call. This code is automatically generated in the epilog of the first ``/*!re2c */``
  block. It is possible to trigger generation of the ``YYGETSTATE ()``
  block earlier by placing a ``/*!getstate:re2c*/`` comment. This is especially useful when the scanner code should be
  wrapped inside a loop.

Please see ``examples/push_model/push.re`` for "push" model scanner. The
generated code can be tweaked using inplace configurations ``state:abort``
and ``state:nextlabel``.

