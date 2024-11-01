++++++++++++++++++++++++++++
User manual (D)
++++++++++++++++++++++++++++


.. toctree::
    :hidden:

    basics/warnings/warnings

|

.. raw:: html

    <p style="color:gray";><i></i></p>

.. |re2c| replace:: re2d
.. |lang_name| replace:: D

Introduction
============
.. include:: /manual/intro.rst_

Here is an example of a small program that checks if a given string contains a
decimal number:

.. literalinclude:: ../examples/d/01_basic.re
    :language: d

In the output |re2c| replaced the middle block with the generated code:

.. literalinclude:: ../examples/d/01_basic.d
    :language: d

Basics
======
.. include:: /manual/basics/syntax.rst_

Blocks
------
.. include:: /manual/basics/blocks.rst_

Configurations
--------------
.. include:: /manual/basics/configurations.rst_

Regular expressions
-------------------
.. include:: /manual/basics/regular_expressions.rst_

Directives
----------
.. include:: /manual/basics/directives.rst_

Program interface
-----------------
.. include:: /manual/basics/api/api1.rst_
.. include:: /manual/basics/api/api2_d.rst_
.. include:: /manual/basics/api/api3.rst_

Options
-------

Some of the options have corresponding `configurations`_,
others are global and cannot be changed after re2c starts reading the input file.
Debug options generally require building re2c in debug configuration.
Internal options are useful for experimenting with the algorithms used in re2c.

.. include:: /manual/basics/options/options.rst_
.. include:: /manual/basics/options/debug.rst_
.. include:: /manual/basics/options/internal.rst_

Warnings
--------

See the :ref:`warnings page <detailed-warnings>` for detailed descriptions of individual warnings.

Warnings can be invividually enabled, disabled and turned into an error.

.. include:: /manual/basics/warnings/warnings_general.rst_
.. include:: /manual/basics/warnings/warnings_list.rst_

Syntax files
------------
.. include:: /manual/basics/syntax_files.rst_

Handling the end of input
=========================
.. include:: /manual/eof/eof.rst_
.. include:: /manual/eof/01_sentinel.rst_
.. literalinclude:: ../examples/d/eof/01_sentinel.re
    :language: d
.. include:: /manual/eof/03_eof_rule.rst_
.. literalinclude:: ../examples/d/eof/03_eof_rule.re
    :language: d
.. include:: /manual/eof/02_bounds_checking.rst_
.. literalinclude:: ../examples/d/eof/02_bounds_checking.re
    :language: d
.. include:: /manual/eof/04_fake_sentinel.rst_
.. literalinclude:: ../examples/d/eof/04_fake_sentinel.re
    :language: d

Buffer refilling
================
.. include:: /manual/fill/fill.rst_
.. include:: /manual/fill/01_fill.rst_
.. literalinclude:: ../examples/d/fill/01_fill.re
    :language: d
.. include:: /manual/fill/02_fill.rst_
.. literalinclude:: ../examples/d/fill/02_fill.re
    :language: d

Features
========

Multiple blocks
---------------
.. include:: /manual/features/conditions/blocks.rst_
.. literalinclude:: ../examples/d/conditions/parse_u32_blocks.re
    :language: d

Start conditions
----------------
.. include:: /manual/features/conditions/conditions.rst_
.. literalinclude:: ../examples/d/conditions/parse_u32_conditions.re
    :language: d

Storable state
--------------
.. include:: /manual/features/state/state.rst_
.. literalinclude:: ../examples/d/state/push.re
    :language: d

Reusable blocks
---------------
.. include:: /manual/features/reuse/reuse.rst_

Example of a ``!use`` directive:

.. literalinclude:: ../examples/d/reuse/usedir.re
    :language: d

Example of a ``/*!use:re2c ... */`` block:

.. literalinclude:: ../examples/d/reuse/reuse.re
    :language: d

Submatch extraction
-------------------
.. include:: /manual/features/submatch/submatch.rst_
.. include:: /manual/features/submatch/submatch_example_stags.rst_
.. literalinclude:: ../examples/d/submatch/01_stags.re
    :language: d
.. include:: /manual/features/submatch/submatch_example_stags_fill.rst_
.. literalinclude:: ../examples/d/submatch/01_stags_fill.re
    :language: d
.. include:: /manual/features/submatch/submatch_example_captures.rst_
.. literalinclude:: ../examples/d/submatch/03_captures.re
    :language: d
.. include:: /manual/features/submatch/submatch_example_mtags.rst_
.. literalinclude:: ../examples/d/submatch/02_mtags.re
    :language: d

Encoding support
----------------
.. include:: /manual/features/encodings/encodings.rst_
.. literalinclude:: ../examples/d/encodings/unicode_identifier.re
    :language: d

Include files
-------------
.. include:: /manual/features/includes/includes.rst_

Include file 1 (definitions.d):

.. literalinclude:: ../examples/d/includes/definitions.d
    :language: d

Include file 2 (extra_rules.re.inc):

.. literalinclude:: ../examples/d/includes/extra_rules.re.inc

Input file:

.. literalinclude:: ../examples/d/includes/include.re
    :language: d

Header files
------------
.. include:: /manual/features/headers/headers.rst_

.. literalinclude:: ../examples/d/headers/header.re
    :language: d

The generated header file:

.. literalinclude:: ../examples/d/headers/lexer/state.d
    :language: d

Skeleton programs
-----------------
.. include:: /manual/features/skeleton/skeleton.rst_
.. include:: /manual/features/skeleton/skeleton_example.rst

Visualization and debug
-----------------------
.. include:: /manual/features/dot/dot.rst_
.. include:: /manual/features/dot/example.rst

.. include:: /examples/examples_d.rst
