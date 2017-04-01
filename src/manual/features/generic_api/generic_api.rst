Generic API
-----------

.. toctree::
    :hidden:

``re2c`` usually operates on input with pointer-like primitives
``YYCURSOR``, ``YYMARKER``, ``YYCTXMARKER``, and ``YYLIMIT``.

The generic input API (enabled with the ``--input custom`` switch) allows 
customizing input operations. In this mode, ``re2c`` will express all
operations on input in terms of the following primitives:

    +---------------------+-----------------------------------------------------+
    | ``YYPEEK ()``       | get current input character                         |
    +---------------------+-----------------------------------------------------+
    | ``YYSKIP ()``       | advance to next character                           |
    +---------------------+-----------------------------------------------------+
    | ``YYBACKUP ()``     | back up current input position                      |
    +---------------------+-----------------------------------------------------+
    | ``YYBACKUPCTX ()``  | back up current input position for trailing context |
    +---------------------+-----------------------------------------------------+
    | ``YYRESTORE ()``    | restore current input position                      |
    +---------------------+-----------------------------------------------------+
    | ``YYRESTORECTX ()`` | restore current input position for trailing context |
    +---------------------+-----------------------------------------------------+
    | ``YYLESSTHAN (n)``  | check if less than ``n`` input characters are left  |
    +---------------------+-----------------------------------------------------+

This `article <http://skvadrik.github.io/aleph_null/posts/re2c/2015-01-13-input_model.html>`_
has more details, and you can find some usage examples
`here <http://skvadrik.github.io/aleph_null/posts/re2c/2015-01-15-input_model_custom.html>`_.

