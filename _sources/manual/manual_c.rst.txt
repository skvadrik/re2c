++++++++++++++++++++++++++++
User manual (C/C++)
++++++++++++++++++++++++++++


.. toctree::
    :hidden:

    basics/warnings/warnings

|

.. raw:: html

    <p style="color:gray";><i>Note: some examples are in C++ (but can be adapted to C).</i></p>

.. |re2c| replace:: re2c
.. |lang_name| replace:: C/C++
.. |nbsp| unicode:: 0xA0

Introduction
============
.. include:: /manual/intro.rst_

Here is an example of a small program that checks if a given string contains a
decimal number:

.. |run_01_basic| image:: ../_static/play.png
    :target: ../../playground?example=c/01_basic.re
    :class:  feed
    :width:  2em

|run_01_basic| |nbsp| `Run in playground <../../playground?example=c/01_basic.re>`__

.. literalinclude:: ../examples/c/01_basic.re
    :language: c

In the output |re2c| replaced the middle block with the generated code:

.. literalinclude:: ../examples/c/01_basic.c
    :language: c

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
.. include:: /manual/basics/api/api2_c.rst_
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
    :target: ../../playground?example=c/eof/01_sentinel.re
    :class:  feed
    :width:  2em

|run_eof_01| |nbsp| `Run in playground <../../playground?example=c/eof/01_sentinel.re>`__

.. literalinclude:: ../examples/c/eof/01_sentinel.re
    :language: c

.. include:: /manual/eof/03_eof_rule.rst_

.. |run_eof_03| image:: ../_static/play.png
    :target: ../../playground?example=c/eof/03_eof_rule.re
    :class:  feed
    :width:  2em

|run_eof_03| |nbsp| `Run in playground <../../playground?example=c/eof/03_eof_rule.re>`__

.. literalinclude:: ../examples/c/eof/03_eof_rule.re
    :language: c

.. include:: /manual/eof/02_bounds_checking.rst_

.. |run_eof_02| image:: ../_static/play.png
    :target: ../../playground?example=c/eof/02_bounds_checking.re
    :class:  feed
    :width:  2em

|run_eof_02| |nbsp| `Run in playground <../../playground?example=c/eof/02_bounds_checking.re>`__

.. literalinclude:: ../examples/c/eof/02_bounds_checking.re
    :language: c

.. include:: /manual/eof/04_fake_sentinel.rst_

.. |run_eof_04| image:: ../_static/play.png
    :target: ../../playground?example=c/eof/04_fake_sentinel.re
    :class:  feed
    :width:  2em

|run_eof_04| |nbsp| `Run in playground <../../playground?example=c/eof/04_fake_sentinel.re>`__

.. literalinclude:: ../examples/c/eof/04_fake_sentinel.re
    :language: c

Buffer refilling
================
.. include:: /manual/fill/fill.rst_
.. include:: /manual/fill/01_fill.rst_

.. |run_fill_01| image:: ../_static/play.png
    :target: ../../playground?example=c/fill/01_fill.re
    :class:  feed
    :width:  2em

|run_fill_01| |nbsp| `Run in playground <../../playground?example=c/fill/01_fill.re>`__

.. literalinclude:: ../examples/c/fill/01_fill.re
    :language: c

.. include:: /manual/fill/02_fill.rst_

.. |run_fill_02| image:: ../_static/play.png
    :target: ../../playground?example=c/fill/02_fill.re
    :class:  feed
    :width:  2em

|run_fill_02| |nbsp| `Run in playground <../../playground?example=c/fill/02_fill.re>`__

.. literalinclude:: ../examples/c/fill/02_fill.re
    :language: c

Features
========

Multiple blocks
---------------
.. include:: /manual/features/conditions/blocks.rst_

.. |run_cond_blocks| image:: ../_static/play.png
    :target: ../../playground?example=c/conditions/parse_u32_blocks.re
    :class:  feed
    :width:  2em

|run_cond_blocks| |nbsp| `Run in playground <../../playground?example=c/conditions/parse_u32_blocks.re>`__

.. literalinclude:: ../examples/c/conditions/parse_u32_blocks.re
    :language: c

Start conditions
----------------
.. include:: /manual/features/conditions/conditions.rst_

.. |run_cond_conds| image:: ../_static/play.png
    :target: ../../playground?example=c/conditions/parse_u32_conditions.re
    :class:  feed
    :width:  2em

|run_cond_conds| |nbsp| `Run in playground <../../playground?example=c/conditions/parse_u32_conditions.re>`__

.. literalinclude:: ../examples/c/conditions/parse_u32_conditions.re
    :language: c

Storable state
--------------
.. include:: /manual/features/state/state.rst_

.. |run_state_push| image:: ../_static/play.png
    :target: ../../playground?example=c/state/push.re
    :class:  feed
    :width:  2em

|run_state_push| |nbsp| `Run in playground <../../playground?example=c/state/push.re>`__

.. literalinclude:: ../examples/c/state/push.re
    :language: c

Reusable blocks
---------------
.. include:: /manual/features/reuse/reuse.rst_

Example of a ``!use`` directive:

.. |run_reuse_usedir| image:: ../_static/play.png
    :target: ../../playground?example=c/reuse/usedir.re
    :class:  feed
    :width:  2em

|run_reuse_usedir| |nbsp| `Run in playground <../../playground?example=c/reuse/usedir.re>`__

.. literalinclude:: ../examples/c/reuse/usedir.re
    :language: c

Example of a ``/*!use:re2c ... */`` block:

.. |run_reuse_reuse| image:: ../_static/play.png
    :target: ../../playground?example=c/reuse/reuse.re
    :class:  feed
    :width:  2em

|run_reuse_reuse| |nbsp| `Run in playground <../../playground?example=c/reuse/reuse.re>`__

.. literalinclude:: ../examples/c/reuse/reuse.re
    :language: c

Submatch extraction
-------------------
.. include:: /manual/features/submatch/submatch.rst_
.. include:: /manual/features/submatch/submatch_example_stags.rst_

.. |run_submatch_01| image:: ../_static/play.png
    :target: ../../playground?example=c/submatch/01_stags.re
    :class:  feed
    :width:  2em

|run_submatch_01| |nbsp| `Run in playground <../../playground?example=c/submatch/01_stags.re>`__

.. literalinclude:: ../examples/c/submatch/01_stags.re
    :language: c

.. include:: /manual/features/submatch/submatch_example_stags_fill.rst_

.. |run_submatch_01_fill| image:: ../_static/play.png
    :target: ../../playground?example=c/submatch/01_stags_fill.re
    :class:  feed
    :width:  2em

|run_submatch_01_fill| |nbsp| `Run in playground <../../playground?example=c/submatch/01_stags_fill.re>`__

.. literalinclude:: ../examples/c/submatch/01_stags_fill.re
    :language: c

.. include:: /manual/features/submatch/submatch_example_captures.rst_

.. |run_submatch_03| image:: ../_static/play.png
    :target: ../../playground?example=c/submatch/03_captures.re
    :class:  feed
    :width:  2em

|run_submatch_03| |nbsp| `Run in playground <../../playground?example=c/submatch/03_captures.re>`__

.. literalinclude:: ../examples/c/submatch/03_captures.re
    :language: c

.. include:: /manual/features/submatch/submatch_example_mtags.rst_

.. |run_submatch_02| image:: ../_static/play.png
    :target: ../../playground?example=c/submatch/02_mtags.re
    :class:  feed
    :width:  2em

|run_submatch_02| |nbsp| `Run in playground <../../playground?example=c/submatch/02_mtags.re>`__

.. literalinclude:: ../examples/c/submatch/02_mtags.re
    :language: c

Encoding support
----------------
.. include:: /manual/features/encodings/encodings.rst_

.. |run_encodings| image:: ../_static/play.png
    :target: ../../playground?example=c/encodings/unicode_identifier.re
    :class:  feed
    :width:  2em

|run_encodings| |nbsp| `Run in playground <../../playground?example=c/encodings/unicode_identifier.re>`__

.. literalinclude:: ../examples/c/encodings/unicode_identifier.re
    :language: c

Include files
-------------
.. include:: /manual/features/includes/includes.rst_

Include file 1 (definitions.h):

.. literalinclude:: ../examples/c/includes/definitions.h
    :language: c

Include file 2 (extra_rules.re.inc):

.. literalinclude:: ../examples/c/includes/extra_rules.re.inc

Input file:

.. |run_includes| image:: ../_static/play.png
    :target: ../../playground?example=c/includes/include.re
    :class:  feed
    :width:  2em

|run_includes| |nbsp| `Run in playground <../../playground?example=c/includes/include.re>`__

.. literalinclude:: ../examples/c/includes/include.re
    :language: c

Header files
------------
.. include:: /manual/features/headers/headers.rst_

.. |run_headers| image:: ../_static/play.png
    :target: ../../playground?example=c/headers/header.re
    :class:  feed
    :width:  2em

|run_headers| |nbsp| `Run in playground <../../playground?example=c/headers/header.re>`__

.. literalinclude:: ../examples/c/headers/header.re
    :language: c

The generated header file:

.. literalinclude:: ../examples/c/headers/lexer/state.h
    :language: c

Skeleton programs
-----------------
.. include:: /manual/features/skeleton/skeleton.rst_
.. include:: /manual/features/skeleton/skeleton_example.rst

Visualization and debug
-----------------------
.. include:: /manual/features/dot/dot.rst_
.. include:: /manual/features/dot/example.rst

.. include:: /examples/examples_c.rst
