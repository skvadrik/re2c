======
Syntax
======

.. toctree::
    :hidden:

Code for ``re2c`` consists of a set of `rules`_, `definitions`_ and
`configurations`_.

.. include:: rules.rst_

Definitions
-----------

Named definitions are of the form:

    ``name = regular-expression;``

If ``-F`` is active, then named definitions are also of the form:

    ``name { regular-expression }``

.. include:: configurations.rst_
.. include:: regular_expressions.rst_
.. include:: interface.rst_
