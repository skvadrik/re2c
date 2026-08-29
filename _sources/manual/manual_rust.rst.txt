++++++++++++++++++++++++++++
User manual (Rust)
++++++++++++++++++++++++++++


.. toctree::
    :hidden:

    basics/warnings/warnings

|

.. raw:: html

    <p style="color:gray";><i></i></p>

.. |re2c| replace:: re2rust
.. |lang_name| replace:: Rust
.. |nbsp| unicode:: 0xA0

Introduction
============
.. include:: /manual/intro.rst_

Here is an example of a small program that checks if a given string contains a
decimal number:

.. |run_01_basic| image:: ../_static/play.png
    :target: ../../playground?example=rust/01_basic.re
    :class:  feed
    :width:  2em

|run_01_basic| |nbsp| `Run in playground <../../playground?example=rust/01_basic.re>`__

.. literalinclude:: ../examples/rust/01_basic.re
    :language: rust

In the output |re2c| replaced the middle block with the generated code:

.. literalinclude:: ../examples/rust/01_basic.rs
    :language: rust

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

Actions
-------
.. include:: /manual/basics/actions.rst_

Directives
----------
.. include:: /manual/basics/directives.rst_

Program interface
-----------------
.. include:: /manual/basics/api/api1.rst_
.. include:: /manual/basics/api/api2_rust.rst_
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

.. |run_eof_01| image:: ../_static/play.png
    :target: ../../playground?example=rust/eof/01_sentinel.re
    :class:  feed
    :width:  2em

|run_eof_01| |nbsp| `Run in playground <../../playground?example=rust/eof/01_sentinel.re>`__

.. literalinclude:: ../examples/rust/eof/01_sentinel.re
    :language: rust

.. include:: /manual/eof/03_eof_rule.rst_

.. |run_eof_03| image:: ../_static/play.png
    :target: ../../playground?example=rust/eof/03_eof_rule.re
    :class:  feed
    :width:  2em

|run_eof_03| |nbsp| `Run in playground <../../playground?example=rust/eof/03_eof_rule.re>`__

.. literalinclude:: ../examples/rust/eof/03_eof_rule.re
    :language: rust

.. include:: /manual/eof/02_bounds_checking.rst_

.. |run_eof_02| image:: ../_static/play.png
    :target: ../../playground?example=rust/eof/02_bounds_checking.re
    :class:  feed
    :width:  2em

|run_eof_02| |nbsp| `Run in playground <../../playground?example=rust/eof/02_bounds_checking.re>`__

.. literalinclude:: ../examples/rust/eof/02_bounds_checking.re
    :language: rust

.. include:: /manual/eof/04_fake_sentinel.rst_

.. |run_eof_04| image:: ../_static/play.png
    :target: ../../playground?example=rust/eof/04_fake_sentinel.re
    :class:  feed
    :width:  2em

|run_eof_04| |nbsp| `Run in playground <../../playground?example=rust/eof/04_fake_sentinel.re>`__

.. literalinclude:: ../examples/rust/eof/04_fake_sentinel.re
    :language: rust

Buffer refilling
================
.. include:: /manual/fill/fill.rst_
.. include:: /manual/fill/01_fill.rst_

.. |run_fill_01| image:: ../_static/play.png
    :target: ../../playground?example=rust/fill/01_fill.re
    :class:  feed
    :width:  2em

|run_fill_01| |nbsp| `Run in playground <../../playground?example=rust/fill/01_fill.re>`__

.. literalinclude:: ../examples/rust/fill/01_fill.re
    :language: rust

.. include:: /manual/fill/02_fill.rst_

.. |run_fill_02| image:: ../_static/play.png
    :target: ../../playground?example=rust/fill/02_fill.re
    :class:  feed
    :width:  2em

|run_fill_02| |nbsp| `Run in playground <../../playground?example=rust/fill/02_fill.re>`__

.. literalinclude:: ../examples/rust/fill/02_fill.re
    :language: rust

Features
========

Multiple blocks
---------------
.. include:: /manual/features/conditions/blocks.rst_

.. |run_cond_blocks| image:: ../_static/play.png
    :target: ../../playground?example=rust/conditions/parse_u32_blocks.re
    :class:  feed
    :width:  2em

|run_cond_blocks| |nbsp| `Run in playground <../../playground?example=rust/conditions/parse_u32_blocks.re>`__

.. literalinclude:: ../examples/rust/conditions/parse_u32_blocks.re
    :language: rust

Start conditions
----------------
.. include:: /manual/features/conditions/conditions.rst_

.. |run_cond_conds| image:: ../_static/play.png
    :target: ../../playground?example=rust/conditions/parse_u32_conditions.re
    :class:  feed
    :width:  2em

|run_cond_conds| |nbsp| `Run in playground <../../playground?example=rust/conditions/parse_u32_conditions.re>`__

.. literalinclude:: ../examples/rust/conditions/parse_u32_conditions.re
    :language: rust

Storable state
--------------
.. include:: /manual/features/state/state.rst_

.. |run_state_push| image:: ../_static/play.png
    :target: ../../playground?example=rust/state/push.re
    :class:  feed
    :width:  2em

|run_state_push| |nbsp| `Run in playground <../../playground?example=rust/state/push.re>`__

.. literalinclude:: ../examples/rust/state/push.re
    :language: rust

Reusable blocks
---------------
.. include:: /manual/features/reuse/reuse.rst_

Example of a ``!use`` directive:

.. |run_reuse_usedir| image:: ../_static/play.png
    :target: ../../playground?example=rust/reuse/usedir.re
    :class:  feed
    :width:  2em

|run_reuse_usedir| |nbsp| `Run in playground <../../playground?example=rust/reuse/usedir.re>`__

.. literalinclude:: ../examples/rust/reuse/usedir.re
    :language: rust

Example of a ``/*!use:re2c ... */`` block:

.. |run_reuse_reuse| image:: ../_static/play.png
    :target: ../../playground?example=rust/reuse/reuse.re
    :class:  feed
    :width:  2em

|run_reuse_reuse| |nbsp| `Run in playground <../../playground?example=rust/reuse/reuse.re>`__

.. literalinclude:: ../examples/rust/reuse/reuse.re
    :language: rust

Submatch extraction
-------------------
.. include:: /manual/features/submatch/submatch.rst_
.. include:: /manual/features/submatch/submatch_example_stags.rst_

.. |run_submatch_01| image:: ../_static/play.png
    :target: ../../playground?example=rust/submatch/01_stags.re
    :class:  feed
    :width:  2em

|run_submatch_01| |nbsp| `Run in playground <../../playground?example=rust/submatch/01_stags.re>`__

.. literalinclude:: ../examples/rust/submatch/01_stags.re
    :language: rust

.. include:: /manual/features/submatch/submatch_example_stags_fill.rst_

.. |run_submatch_01_fill| image:: ../_static/play.png
    :target: ../../playground?example=rust/submatch/01_stags_fill.re
    :class:  feed
    :width:  2em

|run_submatch_01_fill| |nbsp| `Run in playground <../../playground?example=rust/submatch/01_stags_fill.re>`__

.. literalinclude:: ../examples/rust/submatch/01_stags_fill.re
    :language: rust

.. include:: /manual/features/submatch/submatch_example_captures.rst_

.. |run_submatch_03| image:: ../_static/play.png
    :target: ../../playground?example=rust/submatch/03_captures.re
    :class:  feed
    :width:  2em

|run_submatch_03| |nbsp| `Run in playground <../../playground?example=rust/submatch/03_captures.re>`__

.. literalinclude:: ../examples/rust/submatch/03_captures.re
    :language: rust

.. include:: /manual/features/submatch/submatch_example_mtags.rst_

.. |run_submatch_02| image:: ../_static/play.png
    :target: ../../playground?example=rust/submatch/02_mtags.re
    :class:  feed
    :width:  2em

|run_submatch_02| |nbsp| `Run in playground <../../playground?example=rust/submatch/02_mtags.re>`__

.. literalinclude:: ../examples/rust/submatch/02_mtags.re
    :language: rust

Encoding support
----------------
.. include:: /manual/features/encodings/encodings.rst_

.. |run_encodings| image:: ../_static/play.png
    :target: ../../playground?example=rust/encodings/unicode_identifier.re
    :class:  feed
    :width:  2em

|run_encodings| |nbsp| `Run in playground <../../playground?example=rust/encodings/unicode_identifier.re>`__

.. literalinclude:: ../examples/rust/encodings/unicode_identifier.re
    :language: rust

Include files
-------------
.. include:: /manual/features/includes/includes.rst_

Include file 1 (definitions.rs):

.. literalinclude:: ../examples/rust/includes/definitions.rs
    :language: rust

Include file 2 (extra_rules.re.inc):

.. literalinclude:: ../examples/rust/includes/extra_rules.re.inc

Input file:

.. |run_includes| image:: ../_static/play.png
    :target: ../../playground?example=rust/includes/include.re
    :class:  feed
    :width:  2em

|run_includes| |nbsp| `Run in playground <../../playground?example=rust/includes/include.re>`__

.. literalinclude:: ../examples/rust/includes/include.re
    :language: rust

Header files
------------
.. include:: /manual/features/headers/headers.rst_

.. |run_headers| image:: ../_static/play.png
    :target: ../../playground?example=rust/headers/header.re
    :class:  feed
    :width:  2em

|run_headers| |nbsp| `Run in playground <../../playground?example=rust/headers/header.re>`__

.. literalinclude:: ../examples/rust/headers/header.re
    :language: rust

The generated header file:

.. literalinclude:: ../examples/rust/headers/lexer/state.rs
    :language: rust

Skeleton programs
-----------------
.. include:: /manual/features/skeleton/skeleton.rst_
.. include:: /manual/features/skeleton/skeleton_example.rst

Visualization and debug
-----------------------
.. include:: /manual/features/dot/dot.rst_
.. include:: /manual/features/dot/example.rst

.. include:: /examples/examples_rust.rst
