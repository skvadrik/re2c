Generic API
-----------

.. toctree::
    :hidden:

``re2c`` usually operates on input using pointer-like primitives
``YYCURSOR``, ``YYMARKER``, ``YYCTXMARKER`` and ``YYLIMIT``.

Generic input API (enabled with ``--input custom`` switch) allows to
customize input operations. In this mode, ``re2c`` will express all
operations on input in terms of the following primitives:

    +---------------------+-----------------------------------------------------+
    | ``YYPEEK ()``       | get current input character                         |
    +---------------------+-----------------------------------------------------+
    | ``YYSKIP ()``       | advance to the next character                       |
    +---------------------+-----------------------------------------------------+
    | ``YYBACKUP ()``     | backup current input position                       |
    +---------------------+-----------------------------------------------------+
    | ``YYBACKUPCTX ()``  | backup current input position for trailing context  |
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

