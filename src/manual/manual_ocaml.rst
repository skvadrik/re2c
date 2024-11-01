++++++++++++++++++++++++++++
User manual (OCaml)
++++++++++++++++++++++++++++


.. toctree::
    :hidden:

    basics/warnings/warnings

|

.. raw:: html

    <p style="color:gray";><i></i></p>

.. |re2c| replace:: re2ocaml
.. |lang_name| replace:: OCaml

Introduction
============
.. include:: /manual/intro.rst_

Here is an example of a small program that checks if a given string contains a
decimal number:

.. literalinclude:: ../examples/ocaml/01_basic.re
    :language: ocaml

In the output |re2c| replaced the middle block with the generated code:

.. literalinclude:: ../examples/ocaml/01_basic.ml
    :language: ocaml

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
.. include:: /manual/basics/api/api2_ocaml.rst_
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
.. literalinclude:: ../examples/ocaml/eof/01_sentinel.re
    :language: ocaml
.. include:: /manual/eof/03_eof_rule.rst_
.. literalinclude:: ../examples/ocaml/eof/03_eof_rule.re
    :language: ocaml
.. include:: /manual/eof/02_bounds_checking.rst_
.. literalinclude:: ../examples/ocaml/eof/02_bounds_checking.re
    :language: ocaml
.. include:: /manual/eof/04_fake_sentinel.rst_
.. literalinclude:: ../examples/ocaml/eof/04_fake_sentinel.re
    :language: ocaml

Buffer refilling
================
.. include:: /manual/fill/fill.rst_
.. include:: /manual/fill/01_fill.rst_
.. literalinclude:: ../examples/ocaml/fill/01_fill.re
    :language: ocaml
.. include:: /manual/fill/02_fill.rst_
.. literalinclude:: ../examples/ocaml/fill/02_fill.re
    :language: ocaml

Features
========

Multiple blocks
---------------
.. include:: /manual/features/conditions/blocks.rst_
.. literalinclude:: ../examples/ocaml/conditions/parse_u32_blocks.re
    :language: ocaml

Start conditions
----------------
.. include:: /manual/features/conditions/conditions.rst_
.. literalinclude:: ../examples/ocaml/conditions/parse_u32_conditions.re
    :language: ocaml

Storable state
--------------
.. include:: /manual/features/state/state.rst_
.. literalinclude:: ../examples/ocaml/state/push.re
    :language: ocaml

Reusable blocks
---------------
.. include:: /manual/features/reuse/reuse.rst_

Example of a ``!use`` directive:

.. literalinclude:: ../examples/ocaml/reuse/usedir.re
    :language: ocaml

Example of a ``/*!use:re2c ... */`` block:

.. literalinclude:: ../examples/ocaml/reuse/reuse.re
    :language: ocaml

Submatch extraction
-------------------
.. include:: /manual/features/submatch/submatch.rst_
.. include:: /manual/features/submatch/submatch_example_stags.rst_
.. literalinclude:: ../examples/ocaml/submatch/01_stags.re
    :language: ocaml
.. include:: /manual/features/submatch/submatch_example_stags_fill.rst_
.. literalinclude:: ../examples/ocaml/submatch/01_stags_fill.re
    :language: ocaml
.. include:: /manual/features/submatch/submatch_example_captures.rst_
.. literalinclude:: ../examples/ocaml/submatch/03_captures.re
    :language: ocaml
.. include:: /manual/features/submatch/submatch_example_mtags.rst_
.. literalinclude:: ../examples/ocaml/submatch/02_mtags.re
    :language: ocaml

Encoding support
----------------
.. include:: /manual/features/encodings/encodings.rst_
.. literalinclude:: ../examples/ocaml/encodings/unicode_identifier.re
    :language: ocaml

Include files
-------------
.. include:: /manual/features/includes/includes.rst_

Include file 1 (definitions.ml):

.. literalinclude:: ../examples/ocaml/includes/definitions.ml
    :language: ocaml

Include file 2 (extra_rules.re.inc):

.. literalinclude:: ../examples/ocaml/includes/extra_rules.re.inc

Input file:

.. literalinclude:: ../examples/ocaml/includes/include.re
    :language: ocaml

Header files
------------
.. include:: /manual/features/headers/headers.rst_

.. literalinclude:: ../examples/ocaml/headers/header.re
    :language: ocaml

The generated header file:

.. literalinclude:: ../examples/ocaml/headers/lexer/state.ml
    :language: ocaml

Skeleton programs
-----------------
.. include:: /manual/features/skeleton/skeleton.rst_
.. include:: /manual/features/skeleton/skeleton_example.rst

Visualization and debug
-----------------------
.. include:: /manual/features/dot/dot.rst_
.. include:: /manual/features/dot/example.rst

.. include:: /examples/examples_ocaml.rst
