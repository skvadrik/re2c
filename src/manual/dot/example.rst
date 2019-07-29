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
