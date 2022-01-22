++++++++++++++++++++++++++++
User manual (C)
++++++++++++++++++++++++++++


.. toctree::
    :hidden:

    warnings/warnings

|

.. raw:: html

    <p style="color:gray";><i>Note: examples are in C++ (but can be easily adapted to C).</i></p>

Introduction
============
.. include:: /manual/syntax/intro.rst_

Here is an example of a small program that checks if a given string contains a
decimal number:

.. literalinclude:: ../examples/c/01_basic.re
    :language: c

In the output everything between ``/*!re2c`` and ``*/`` has been replaced with
the generated code:

.. literalinclude:: ../examples/c/01_basic.c
    :language: c

Syntax
======

.. include:: /manual/syntax/syntax.rst_

Program interface
=================

.. include:: /manual/syntax/api1.rst_
.. include:: /manual/syntax/api2_c.rst_
.. include:: /manual/syntax/api3.rst_

Options
=======

Some of the options have corresponding `configurations`_,
others are global and cannot be changed after re2c starts reading the input file.
Debug options generally require building re2c in debug configuration.
Internal options are useful for experimenting with the algorithms used in re2c.

.. include:: /manual/options/options.rst_
.. include:: /manual/options/debug.rst_
.. include:: /manual/options/internal.rst_

Warnings
========

Warnings can be invividually enabled, disabled and turned into an error.

.. include:: /manual/warnings/warnings_general.rst_
.. include:: /manual/warnings/warnings_list.rst_

Blocks and directives
=====================
.. include:: /manual/directives/directives.rst_

API primitives
==============
.. include:: /manual/api/interface.rst_

Configurations
==============
.. include:: /manual/configurations/configurations.rst_

Regular expressions
===================
.. include:: /manual/regexps/regular_expressions.rst_

Handling the end of input
=========================
.. include:: /manual/eof/eof.rst_
.. include:: /manual/eof/01_sentinel.rst_
.. literalinclude:: ../examples/c/eof/01_sentinel.re
    :language: c
.. include:: /manual/eof/03_eof_rule.rst_
.. literalinclude:: ../examples/c/eof/03_eof_rule.re
    :language: c
.. include:: /manual/eof/02_bounds_checking.rst_
.. literalinclude:: ../examples/c/eof/02_bounds_checking.re
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

Multiple blocks
===============
.. include:: /manual/conditions/blocks.rst_
.. literalinclude:: ../examples/c/conditions/parse_u32_blocks.re
    :language: c

Start conditions
================
.. include:: /manual/conditions/conditions.rst_
.. literalinclude:: ../examples/c/conditions/parse_u32_conditions.re
    :language: c

Storable state
==============
.. include:: /manual/state/state.rst_
.. literalinclude:: ../examples/c/state/push.re
    :language: c

Reusable blocks
===============
.. include:: /manual/reuse/reuse.rst_

Example of a ``!use`` directive:

.. literalinclude:: ../examples/c/reuse/usedir.re
    :language: c

Example of a ``/*!use:re2c ... */`` block:

.. literalinclude:: ../examples/c/reuse/reuse.re
    :language: c

Submatch extraction
===================
.. include:: /manual/submatch/submatch.rst_
.. include:: /manual/submatch/submatch_example_stags.rst_
.. literalinclude:: ../examples/c/submatch/01_stags.re
    :language: c
.. include:: /manual/submatch/submatch_example_stags_fill.rst_
.. literalinclude:: ../examples/c/submatch/01_stags_fill.re
    :language: c
.. include:: /manual/submatch/submatch_example_posix.rst_
.. literalinclude:: ../examples/c/submatch/03_posix.re
    :language: c
.. include:: /manual/submatch/submatch_example_mtags.rst_
.. literalinclude:: ../examples/c/submatch/02_mtags.re
    :language: c

Encoding support
================
.. include:: /manual/encodings/encodings.rst_
.. literalinclude:: ../examples/c/encodings/unicode_identifier.re
    :language: c

Include files
=============
.. include:: /manual/includes/includes.rst_

Include file 1 (definitions.h):

.. literalinclude:: ../examples/c/includes/definitions.h
    :language: c

Include file 2 (extra_rules.re.inc):

.. literalinclude:: ../examples/c/includes/extra_rules.re.inc

Input file:

.. literalinclude:: ../examples/c/includes/include.re
    :language: c

Header files
============
.. include:: /manual/headers/headers.rst_

.. literalinclude:: ../examples/c/headers/header.re
    :language: c

The generated header file:

.. literalinclude:: ../examples/c/headers/lexer/state.h
    :language: c

Skeleton programs
=================
.. include:: /manual/skeleton/skeleton.rst_
.. include:: /manual/skeleton/skeleton_example.rst

Visualization and debug
=======================
.. include:: /manual/dot/dot.rst_
.. include:: /manual/dot/example.rst

.. include:: /examples/examples_c.rst
