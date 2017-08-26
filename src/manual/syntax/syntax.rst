======
Syntax
======

.. toctree::
    :hidden:

A program can contain any number of re2c blocks.
Each block consists of a sequence of `definitions`_,
`configurations`_ and `rules`_ that contain `regular expressions`_.
The generated lexers communicate with the outer world using the `interface code`_.

Rules
----------

.. include:: rules.rst_

Regular expressions
-------------------

.. include:: regular_expressions.rst_

Definitions
-----------

.. include:: named_definitions.rst_

Interface code
--------------

.. include:: interface.rst_

Configurations
--------------

.. include:: configurations.rst_
