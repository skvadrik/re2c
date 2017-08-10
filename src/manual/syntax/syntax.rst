======
Syntax
======

.. toctree::
    :hidden:

Code for ``re2c`` consists of a set of `rules`_, `definitions`_ and
`configurations`_.

Rules
----------

Each rule consist of a `regular expressions`_ accompanied with a block of C/C++ code
which is to be executed when the associated regular expression is
matched. You can either start the code with an opening curly brace or
the sequence ``:=``. If you use an opening curly brace, ``re2c`` will count brace depth
and stop looking for code automatically. Otherwise, curly braces are not
allowed and ``re2c`` stops looking for code at the first line that does
not begin with whitespace. If two or more rules overlap, the first rule
is preferred.

.. include:: rules.rst_

Definitions
-----------

Named definitions are of the form:

    ``name = regular-expression;``

If ``-F`` is active, then named definitions are also of the form:

    ``name { regular-expression }``

Configurations
--------------

.. include:: configurations.rst_

Regular expressions
-------------------

.. include:: regular_expressions.rst_

Interface
----------

The user must supply interface code either in the form of C/C++ code
(macros, functions, variables, etc.) or in the form of `configurations`_.
Which symbols must be defined and which are optional
depends on the particular use case.

.. include:: interface.rst_
