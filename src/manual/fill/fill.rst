The need for buffering arises when the input cannot be mapped in memory all at
once: either it is too large, or it comes in a streaming fashion (like reading
from a socket). The usual technique in such cases is to allocate a fixed-sized
memory buffer and process input in chunks that fit into the buffer. When the
current chunk is processed, it is moved out and new data is moved in. In
practice it is somewhat more complex, because lexer state consists not of a
single input position, but a set of interrelated posiitons:

- cursor: the next input character to be read (``YYCURSOR`` in default API or
  ``YYSKIP``/``YYPEEK`` in generic API)

- limit: the position after the last available input character (``YYLIMIT`` in
  default API, implicitly handled by ``YYLESSTHAN`` in generic API)

- marker: the position of the most recent match, if any (``YYMARKER`` in default
  API or ``YYBACKUP``/``YYRESTORE`` in generic API)

- token: the start of the current lexeme (implicit in re2c API, as it is not
  needed for the normal lexer operation and can be defined and updated by the
  user)

- context marker: the position of the trailing context (``YYCTXMARKER`` in
  default API or ``YYBACKUPCTX``/``YYRESTORECTX`` in generic API)

- tag variables: submatch positions (defined with ``/*!stags:re2c*/`` and
  ``/*!mtags:re2c*/`` directives and
  ``YYSTAGP``/``YYSTAGN``/``YYMTAGP``/``YYMTAGN`` in generic API)

Not all these are used in every case, but if used, they must be updated by
``YYFILL``. All active positions are contained in the segment between token and
cursor, therefore everything between buffer start and token can be discarded,
the segment from token and up to limit should be moved to the beginning of
buffer, and the free space at the end of buffer should be filled with new data.
In order to avoid frequent ``YYFILL`` calls it is best to fill in as many input
characters as possible (even though fewer characters might suffice to resume the
lexer). The details of ``YYFILL`` implementation are slightly different
depending on which EOF handling method is used: the case of EOF rule is somewhat
simpler than the case of bounds-checking with padding. Also note that if
``-f --storable-state`` option is used, ``YYFILL`` has slightly different
semantics (desrbed in the section about storable state).

YYFILL with EOF rule
--------------------

If EOF rule is used, ``YYFILL`` is a function-like primitive that accepts
no arguments and returns a value which is checked against zero. ``YYFILL``
invocation is triggered by condition ``YYLIMIT <= YYCURSOR`` in default API and
``YYLESSTHAN()`` in generic API. A non-zero return value means that ``YYFILL``
has failed. A successful ``YYFILL`` call must supply at least one character and
adjust input positions accordingly. Limit must always be set to one after the
last input position in buffer, and the character at the limit position must be
the sentinel symbol specified by ``re2c:eof`` configuration. The pictures below
show the relative locations of input positions in buffer before and after
``YYFILL`` call (sentinel symbol is marked with ``#``, and the second picture
shows the case when there is not enough input to fill the whole buffer).

.. code-block:: none

                   <-- shift -->
                 >-A~~~~~~~~~~~~B~~~~~~~~~C~~~~~~~~~~~~~D#-----------E->
                 buffer       token    marker         limit,
                                                      cursor
    >-A------------B~~~~~~~~~C~~~~~~~~~~~~~D~~~~~~~~~~~~E#->
                 buffer,  marker        cursor        limit
                 token

                   <-- shift -->
                 >-A~~~~~~~~~~~~B~~~~~~~~~C~~~~~~~~~~~~~D#--E (EOF)
                 buffer       token    marker         limit,
                                                      cursor
    >-A------------B~~~~~~~~~C~~~~~~~~~~~~~D~~~E#........
                 buffer,  marker       cursor limit
                 token


Here is an example of a program that reads input file ``input.txt`` in chunks of
4096 bytes and uses EOF rule.

.. literalinclude:: /manual/fill/02_fill.re
    :language: c

YYFILL with padding
-------------------

In the default case (when EOF rule is not used) ``YYFILL`` is a function-like
primitive that accepts a single argument and does not return any value.
``YYFILL`` invocation is triggered by condition ``(YYLIMIT - YYCURSOR) < n`` in
default API and ``YYLESSTHAN(n)`` in generic API. The argument passed to
``YYFILL`` is the minimal number of characters that must be supplied. If it
fails to do so, ``YYFILL`` must not return to the lexer (for that reason it is
best implemented as a macro that returns from the calling function on failure).
In case of a successfull ``YYFILL`` invocation the limit position must be set
either to one after the last input position in buffer, or to the end of
``YYMAXFILL`` padding (in case ``YYFILL`` has successfully read at least ``n``
characters, but not enough to fill the entire buffer). The pictures below show
the relative locations of input positions in buffer before and after ``YYFILL``
invocation (``YYMAXFILL`` padding on the second picture is marked with ``#``
symbols).

.. code-block:: none

                   <-- shift -->                 <-- need -->
                 >-A~~~~~~~~~~~~B~~~~~~~~~C~~~~~D~~~~~~~E---F--------G->
                 buffer       token    marker cursor  limit
                                                         
    >-A------------B~~~~~~~~~C~~~~~D~~~~~~~E~~~F~~~~~~~~G->
                 buffer,  marker cursor               limit
                 token

                   <-- shift -->                 <-- need -->
                 >-A~~~~~~~~~~~~B~~~~~~~~~C~~~~~D~~~~~~~E-F        (EOF)
                 buffer       token    marker cursor  limit
                                                         
    >-A------------B~~~~~~~~~C~~~~~D~~~~~~~E~F###############
                 buffer,  marker cursor                   limit
                 token                        <- YYMAXFILL ->

Here is an example of a program that reads input file ``input.txt`` in chunks of
4096 bytes and uses bounds-checking with padding.

.. literalinclude:: /manual/fill/01_fill.re
    :language: c

