++++++++++++++++++++++++++++
User manual (Rust)
++++++++++++++++++++++++++++


.. toctree::
    :hidden:

    warnings/warnings

|

.. raw:: html

    <p style="color:gray";><i>Note: This manual is for Rust, but it refers to re2c as the general program.</i></p>

Introduction
============
.. include:: /manual/syntax/intro.rst_

Here is an example of a small program that checks if a given string contains a
decimal number:

.. literalinclude:: ../examples/rust/01_basic.re
    :language: rust

In the output everything between ``/*!re2c`` and ``*/`` has been replaced with
the generated code:

.. literalinclude:: ../examples/rust/01_basic.rs
    :language: rust

Syntax
======

.. include:: /manual/syntax/syntax.rst_

Program interface
=================

.. include:: /manual/syntax/api1.rst_
.. include:: /manual/syntax/api2_rust.rst_
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
.. literalinclude:: ../examples/rust/eof/01_sentinel.re
    :language: rust
.. include:: /manual/eof/03_eof_rule.rst_
.. literalinclude:: ../examples/rust/eof/03_eof_rule.re
    :language: rust
.. include:: /manual/eof/02_bounds_checking.rst_
.. literalinclude:: ../examples/rust/eof/02_bounds_checking.re
    :language: rust
.. include:: /manual/eof/04_generic_api.rst_
.. literalinclude:: ../examples/rust/eof/05_generic_api_eof_rule.re
    :language: rust

Buffer refilling
================
.. include:: /manual/fill/fill.rst_
.. include:: /manual/fill/01_fill.rst_
.. literalinclude:: ../examples/rust/fill/01_fill.re
    :language: rust
.. include:: /manual/fill/02_fill.rst_
.. literalinclude:: ../examples/rust/fill/02_fill.re
    :language: rust

Multiple blocks
===============
.. include:: /manual/conditions/blocks.rst_
.. literalinclude:: ../examples/rust/conditions/parse_u32_blocks.re
    :language: rust

Start conditions
================
.. include:: /manual/conditions/conditions.rst_
.. literalinclude:: ../examples/rust/conditions/parse_u32_conditions.re
    :language: rust

Storable state
==============
.. include:: /manual/state/state.rst_
.. literalinclude:: ../examples/rust/state/push.re
    :language: rust

Reusable blocks
===============
.. include:: /manual/reuse/reuse.rst_

Example of a ``!use`` directive:

.. literalinclude:: ../examples/rust/reuse/usedir.re
    :language: rust

Example of a ``/*!use:re2c ... */`` block:

.. literalinclude:: ../examples/rust/reuse/reuse.re
    :language: rust

Submatch extraction
===================
.. include:: /manual/submatch/submatch.rst_
.. include:: /manual/submatch/submatch_example_stags.rst_
.. literalinclude:: ../examples/rust/submatch/01_stags.re
    :language: rust
.. include:: /manual/submatch/submatch_example_stags_fill.rst_
.. literalinclude:: ../examples/rust/submatch/01_stags_fill.re
    :language: rust
.. include:: /manual/submatch/submatch_example_posix.rst_
.. literalinclude:: ../examples/rust/submatch/03_posix.re
    :language: rust
.. include:: /manual/submatch/submatch_example_mtags.rst_
.. literalinclude:: ../examples/rust/submatch/02_mtags.re
    :language: rust

Encoding support
================
.. include:: /manual/encodings/encodings.rst_
.. literalinclude:: ../examples/rust/encodings/unicode_identifier.re
    :language: rust

Include files
=============
.. include:: /manual/includes/includes.rst_

Include file 1 (definitions.rs):

.. literalinclude:: ../examples/rust/includes/definitions.rs
    :language: rust

Include file 2 (extra_rules.re.inc):

.. literalinclude:: ../examples/rust/includes/extra_rules.re.inc

Input file:

.. literalinclude:: ../examples/rust/includes/include.re
    :language: rust

Header files
============
.. include:: /manual/headers/headers.rst_

.. literalinclude:: ../examples/rust/headers/header.re
    :language: rust

The generated header file:

.. literalinclude:: ../examples/rust/headers/lexer/state.rs
    :language: rust

Skeleton programs
=================
.. include:: /manual/skeleton/skeleton.rst_
.. include:: /manual/skeleton/skeleton_example.rst

Visualization and debug
=======================
.. include:: /manual/dot/dot.rst_
.. include:: /manual/dot/example.rst

.. include:: /examples/examples_rust.rst
