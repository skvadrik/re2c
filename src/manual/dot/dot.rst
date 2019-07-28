With the ``-D, --emit-dot`` option, re2c does not generate C/C++ code. Instead,
it dumps the generated DFA in the
`DOT format <https://en.wikipedia.org/wiki/DOT_%28graph_description_language%29>`_.
One can convert this dump to an image of the DFA using
`graphviz <http://www.graphviz.org/>`_ or another library.
Note that this option shows the final DFA after it has gone through a number of
optimizations and transformations. Earlier stages can be dumped with various debug
options, such as ``--dump-nfa``, ``--dump-dfa-raw`` etc. (see the full
`list of options </manual/manual.html#command-line-options>`_).
Below is an example of generating a picture of DFA that accepts any UTF-8 code point
(``utf8_any.re``):

.. literalinclude:: /manual/dot/utf8_any.re
    :language: cpp

Generate and render:

.. code-block:: none

    $ re2c -D -8 utf8_any.re | dot -Tpng -o utf8_any.png

Here is the picture:

.. image:: /manual/dot/utf8_any.png
    :width: 90%
