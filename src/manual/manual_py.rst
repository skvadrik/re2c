++++++++++++++++++++++++++++
User manual (Python)
++++++++++++++++++++++++++++


.. toctree::
    :hidden:

    basics/warnings/warnings

|

.. raw:: html

    <p style="color:gray";><i></i></p>

.. |re2c| replace:: re2py
.. |lang_name| replace:: Python

Introduction
============
.. include:: /manual/intro.rst_

Here is an example of a small program that checks if a given string contains a
decimal number:

.. literalinclude:: ../examples/python/01_basic.re
    :language: python

In the output |re2c| replaced the middle block with the generated code:

.. literalinclude:: ../examples/python/01_basic.py
    :language: python

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
.. include:: /manual/basics/api/api2_python.rst_
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
.. literalinclude:: ../examples/python/eof/01_sentinel.re
    :language: python
.. include:: /manual/eof/03_eof_rule.rst_
.. literalinclude:: ../examples/python/eof/03_eof_rule.re
    :language: python
.. include:: /manual/eof/02_bounds_checking.rst_
.. literalinclude:: ../examples/python/eof/02_bounds_checking.re
    :language: python
.. include:: /manual/eof/04_fake_sentinel.rst_
.. literalinclude:: ../examples/python/eof/04_fake_sentinel.re
    :language: python

Buffer refilling
================
.. include:: /manual/fill/fill.rst_
.. include:: /manual/fill/01_fill.rst_
.. literalinclude:: ../examples/python/fill/01_fill.re
    :language: python
.. include:: /manual/fill/02_fill.rst_
.. literalinclude:: ../examples/python/fill/02_fill.re
    :language: python

Features
========

Multiple blocks
---------------
.. include:: /manual/features/conditions/blocks.rst_
.. literalinclude:: ../examples/python/conditions/parse_u32_blocks.re
    :language: python

Start conditions
----------------
.. include:: /manual/features/conditions/conditions.rst_
.. literalinclude:: ../examples/python/conditions/parse_u32_conditions.re
    :language: python

Storable state
--------------
.. include:: /manual/features/state/state.rst_
.. literalinclude:: ../examples/python/state/push.re
    :language: python

Reusable blocks
---------------
.. include:: /manual/features/reuse/reuse.rst_

Example of a ``!use`` directive:

.. literalinclude:: ../examples/python/reuse/usedir.re
    :language: python

Example of a ``/*!use:re2c ... */`` block:

.. literalinclude:: ../examples/python/reuse/reuse.re
    :language: python

Submatch extraction
-------------------
.. include:: /manual/features/submatch/submatch.rst_
.. include:: /manual/features/submatch/submatch_example_stags.rst_
.. literalinclude:: ../examples/python/submatch/01_stags.re
    :language: python
.. include:: /manual/features/submatch/submatch_example_stags_fill.rst_
.. literalinclude:: ../examples/python/submatch/01_stags_fill.re
    :language: python
.. include:: /manual/features/submatch/submatch_example_captures.rst_
.. literalinclude:: ../examples/python/submatch/03_captures.re
    :language: python
.. include:: /manual/features/submatch/submatch_example_mtags.rst_
.. literalinclude:: ../examples/python/submatch/02_mtags.re
    :language: python

Encoding support
----------------
.. include:: /manual/features/encodings/encodings.rst_
.. literalinclude:: ../examples/python/encodings/unicode_identifier.re
    :language: python

Include files
-------------
.. include:: /manual/features/includes/includes.rst_

Include file 1 (definitions.py):

.. literalinclude:: ../examples/python/includes/definitions.py
    :language: python

Include file 2 (extra_rules.re.inc):

.. literalinclude:: ../examples/python/includes/extra_rules.re.inc

Input file:

.. literalinclude:: ../examples/python/includes/include.re
    :language: python

Header files
------------
.. include:: /manual/features/headers/headers.rst_

.. literalinclude:: ../examples/python/headers/header.re
    :language: python

The generated header file:

.. literalinclude:: ../examples/python/headers/lexer/state.py
    :language: python

Skeleton programs
-----------------
.. include:: /manual/features/skeleton/skeleton.rst_
.. include:: /manual/features/skeleton/skeleton_example.rst

Visualization and debug
-----------------------
.. include:: /manual/features/dot/dot.rst_
.. include:: /manual/features/dot/example.rst

.. include:: /examples/examples_python.rst
