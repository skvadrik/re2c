++++++++++++++++++++++++++
User manual (re2c)
++++++++++++++++++++++++++


.. toctree::
    :hidden:

    warnings/warnings

|

.. raw:: html

    <p style="color:gray";><i></i></p>

.. include:: /manual/syntax/syntax.rst_

Here is an example program that shows various aspects of re2c syntax:

.. literalinclude:: ../examples/c/01_basic.re
    :language: c

This is the generated output:

.. literalinclude:: ../examples/c/01_basic.c
    :language: c


Command-line options
====================
.. include:: /manual/options/options.rst_

|

Debug options:

.. include:: /manual/options/debug.rst_

|

Internal options:

.. include:: /manual/options/internal.rst_

|

Warnings:

.. include:: /manual/warnings/warnings_general.rst_

|

Individual warnings (see the `detailed descriptions <warnings/warnings.html>`_):

.. include:: /manual/warnings/warnings_list.rst_

Program interface
=================
.. include:: /manual/api/api.rst_

API primitives
--------------

.. include:: /manual/api/interface.rst_

Directives
----------
.. include:: /manual/directives/directives.rst_

Configurations
--------------
.. include:: /manual/configurations/configurations.rst_

Regular expressions
===================
.. include:: /manual/regexps/regular_expressions.rst_

EOF handling
============
.. include:: /manual/eof/eof.rst_
.. include:: /manual/eof/01_sentinel.rst_
.. literalinclude:: ../examples/c/eof/01_sentinel.re
    :language: c
.. include:: /manual/eof/02_bounds_checking.rst_
.. literalinclude:: ../examples/c/eof/02_bounds_checking.re
    :language: c
.. include:: /manual/eof/03_eof_rule.rst_
.. literalinclude:: ../examples/c/eof/03_eof_rule.re
    :language: c
.. include:: /manual/eof/04_generic_api.rst_
.. literalinclude:: ../examples/c/eof/05_generic_api_eof_rule.re
    :language: c

Buffer refilling
================
.. include:: /manual/fill/fill.rst_
.. include:: /manual/fill/01_fill.rst_
.. literalinclude:: ../examples/c/fill/01_fill.re
    :language: c
.. include:: /manual/fill/02_fill.rst_
.. literalinclude:: ../examples/c/fill/02_fill.re
    :language: c

Include files
=============
.. include:: /manual/includes/includes.rst_

Include file (definitions.h):

.. literalinclude:: ../examples/c/includes/definitions.h
    :language: c

Input file:

.. literalinclude:: ../examples/c/includes/include.re
    :language: c

Header files
============
.. include:: /manual/headers/headers.rst_

.. literalinclude:: ../examples/c/headers/header.re
    :language: c

The generated header file:

.. literalinclude:: ../examples/c/headers/src/lexer/lexer.h
    :language: c

Submatch extraction
===================
.. include:: /manual/submatch/submatch.rst_
.. include:: /manual/submatch/submatch_example_stags.rst_
.. literalinclude:: ../examples/c/submatch/01_stags.re
    :language: c
.. include:: /manual/submatch/submatch_example_posix.rst_
.. literalinclude:: ../examples/c/submatch/03_posix.re
    :language: c
.. include:: /manual/submatch/submatch_example_mtags.rst_
.. literalinclude:: ../examples/c/submatch/02_mtags.re
    :language: c

Storable state
==============
.. include:: /manual/state/state.rst_
.. literalinclude:: ../examples/c/state/push.re
    :language: c

Reusable blocks
===============
.. include:: /manual/reuse/reuse.rst_
.. literalinclude:: ../examples/c/reuse/reuse.re
    :language: c

Encoding support
================
.. include:: /manual/encodings/encodings.rst_

Start conditions
================
.. include:: /manual/conditions/conditions.rst_

Here is an example program that uses start conditions to parse integer numbers in binary, octal, decimal and hexadecimal format:

.. literalinclude:: ../examples/c/conditions/parse_u32_conditions.re
    :language: c

Skeleton programs
=================
.. include:: /manual/skeleton/skeleton.rst_
.. include:: /manual/skeleton/skeleton_example.rst

Visualization and debug
=======================
.. include:: /manual/dot/dot.rst_
.. include:: /manual/dot/example.rst

More examples
=============
.. include:: /examples/examples.rst
