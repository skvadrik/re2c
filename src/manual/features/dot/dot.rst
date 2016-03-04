.dot
----

.. toctree::
    :hidden:

With ``-D, --emit-dot`` option re2c does not generate C/C++ code.
Instead, it dumps the generated DFA in `DOT format <https://en.wikipedia.org/wiki/DOT_%28graph_description_language%29>`_.
One can convert this dump to an image of DFA using `graphviz <http://www.graphviz.org/>`_ or another library.

Say we want a picture of DFA that accepts any UTF-8 code point, ``utf8_any.re``:

.. literalinclude:: utf8_any.re.txt
    :language: cpp

Generate and render :

.. code-block:: none

    $ re2c -D8 -o utf8_any.dot utf8_any.re
    $ dot -Tpng -o utf8_any.png utf8_any.dot

Here is the picture:

.. image:: utf8_any.png
    :width: 70%

Note that re2c performs additional transformations on the DFA:
inserts ``YYFILL`` `checkpoints <../../../examples/example_02.html>`_,
binds actions, applies basic code deduplication.
During the transformations it splits certain states and adds lambda transitions.
Lambda transitions correspond to the unlabeled edges on the picture.

A real-world example (JSON lexer, all non-re2c code stripped out), ``php_json.re``:

.. literalinclude:: php_json.re.txt
    :language: cpp

Generate .dot file:

.. code-block:: none

    $ re2c -Dc -o php_json.dot php_json.re

Render with ```dot -Gratio=0.3 -Tpng -o php_json_dot.png php_json.dot```:

.. image:: php_json_dot.png
    :width: 100%

Render with ```neato -Elen=4 -Tpng -o php_json_neato.png php_json.dot```:

.. image:: php_json_neato.png
    :width: 70%

The generated graph is sometimes very large and requires careful tuning of rendering paratemeters.



