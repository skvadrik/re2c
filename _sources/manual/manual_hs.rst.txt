++++++++++++++++++++++++++++
User manual (Haskell)
++++++++++++++++++++++++++++


.. toctree::
    :hidden:

    basics/warnings/warnings

|

.. raw:: html

    <p style="color:gray";><i></i></p>

.. |re2c| replace:: re2hs
.. |lang_name| replace:: Haskell
.. |nbsp| unicode:: 0xA0

Introduction
============
.. include:: /manual/intro.rst_

Here is an example of a small program that checks if a given string contains a
decimal number:

.. |run_01_basic| image:: ../_static/play.png
    :target: ../../playground?example=haskell/01_basic.re
    :class:  feed
    :width:  2em

|run_01_basic| |nbsp| `Run in playground <../../playground?example=haskell/01_basic.re>`__

.. literalinclude:: ../examples/haskell/01_basic.re
    :language: haskell

In the output |re2c| replaced the middle block with the generated code:

.. literalinclude:: ../examples/haskell/01_basic.hs
    :language: haskell

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
.. include:: /manual/basics/api/api2_haskell.rst_
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
    :target: ../../playground?example=haskell/eof/01_sentinel.re
    :class:  feed
    :width:  2em

|run_eof_01| |nbsp| `Run in playground <../../playground?example=haskell/eof/01_sentinel.re>`__

.. literalinclude:: ../examples/haskell/eof/01_sentinel.re
    :language: haskell

.. include:: /manual/eof/03_eof_rule.rst_

.. |run_eof_03| image:: ../_static/play.png
    :target: ../../playground?example=haskell/eof/03_eof_rule.re
    :class:  feed
    :width:  2em

|run_eof_03| |nbsp| `Run in playground <../../playground?example=haskell/eof/03_eof_rule.re>`__

.. literalinclude:: ../examples/haskell/eof/03_eof_rule.re
    :language: haskell

.. include:: /manual/eof/02_bounds_checking.rst_

.. |run_eof_02| image:: ../_static/play.png
    :target: ../../playground?example=haskell/eof/02_bounds_checking.re
    :class:  feed
    :width:  2em

|run_eof_02| |nbsp| `Run in playground <../../playground?example=haskell/eof/02_bounds_checking.re>`__

.. literalinclude:: ../examples/haskell/eof/02_bounds_checking.re
    :language: haskell

.. include:: /manual/eof/04_fake_sentinel.rst_

.. |run_eof_04| image:: ../_static/play.png
    :target: ../../playground?example=haskell/eof/04_fake_sentinel.re
    :class:  feed
    :width:  2em

|run_eof_04| |nbsp| `Run in playground <../../playground?example=haskell/eof/04_fake_sentinel.re>`__

.. literalinclude:: ../examples/haskell/eof/04_fake_sentinel.re
    :language: haskell

Buffer refilling
================
.. include:: /manual/fill/fill.rst_
.. include:: /manual/fill/01_fill.rst_

.. |run_fill_01| image:: ../_static/play.png
    :target: ../../playground?example=haskell/fill/01_fill.re
    :class:  feed
    :width:  2em

|run_fill_01| |nbsp| `Run in playground <../../playground?example=haskell/fill/01_fill.re>`__

.. literalinclude:: ../examples/haskell/fill/01_fill.re
    :language: haskell

.. include:: /manual/fill/02_fill.rst_

.. |run_fill_02| image:: ../_static/play.png
    :target: ../../playground?example=haskell/fill/02_fill.re
    :class:  feed
    :width:  2em

|run_fill_02| |nbsp| `Run in playground <../../playground?example=haskell/fill/02_fill.re>`__

.. literalinclude:: ../examples/haskell/fill/02_fill.re
    :language: haskell

Features
========

Multiple blocks
---------------
.. include:: /manual/features/conditions/blocks.rst_

.. |run_cond_blocks| image:: ../_static/play.png
    :target: ../../playground?example=haskell/conditions/parse_u32_blocks.re
    :class:  feed
    :width:  2em

|run_cond_blocks| |nbsp| `Run in playground <../../playground?example=haskell/conditions/parse_u32_blocks.re>`__

.. literalinclude:: ../examples/haskell/conditions/parse_u32_blocks.re
    :language: haskell

Start conditions
----------------
.. include:: /manual/features/conditions/conditions.rst_

.. |run_cond_conds| image:: ../_static/play.png
    :target: ../../playground?example=haskell/conditions/parse_u32_conditions.re
    :class:  feed
    :width:  2em

|run_cond_conds| |nbsp| `Run in playground <../../playground?example=haskell/conditions/parse_u32_conditions.re>`__

.. literalinclude:: ../examples/haskell/conditions/parse_u32_conditions.re
    :language: haskell

Storable state
--------------
.. include:: /manual/features/state/state.rst_

.. |run_state_push| image:: ../_static/play.png
    :target: ../../playground?example=haskell/state/push.re
    :class:  feed
    :width:  2em

|run_state_push| |nbsp| `Run in playground <../../playground?example=haskell/state/push.re>`__

.. literalinclude:: ../examples/haskell/state/push.re
    :language: haskell

Reusable blocks
---------------
.. include:: /manual/features/reuse/reuse.rst_

Example of a ``!use`` directive:

.. |run_reuse_usedir| image:: ../_static/play.png
    :target: ../../playground?example=haskell/reuse/usedir.re
    :class:  feed
    :width:  2em

|run_reuse_usedir| |nbsp| `Run in playground <../../playground?example=haskell/reuse/usedir.re>`__

.. literalinclude:: ../examples/haskell/reuse/usedir.re
    :language: haskell

Example of a ``/*!use:re2c ... */`` block:

.. |run_reuse_reuse| image:: ../_static/play.png
    :target: ../../playground?example=haskell/reuse/reuse.re
    :class:  feed
    :width:  2em

|run_reuse_reuse| |nbsp| `Run in playground <../../playground?example=haskell/reuse/reuse.re>`__

.. literalinclude:: ../examples/haskell/reuse/reuse.re
    :language: haskell

Submatch extraction
-------------------
.. include:: /manual/features/submatch/submatch.rst_
.. include:: /manual/features/submatch/submatch_example_stags.rst_

.. |run_submatch_01| image:: ../_static/play.png
    :target: ../../playground?example=haskell/submatch/01_stags.re
    :class:  feed
    :width:  2em

|run_submatch_01| |nbsp| `Run in playground <../../playground?example=haskell/submatch/01_stags.re>`__

.. literalinclude:: ../examples/haskell/submatch/01_stags.re
    :language: haskell

.. include:: /manual/features/submatch/submatch_example_stags_fill.rst_

.. |run_submatch_01_fill| image:: ../_static/play.png
    :target: ../../playground?example=haskell/submatch/01_stags_fill.re
    :class:  feed
    :width:  2em

|run_submatch_01_fill| |nbsp| `Run in playground <../../playground?example=haskell/submatch/01_stags_fill.re>`__

.. literalinclude:: ../examples/haskell/submatch/01_stags_fill.re
    :language: haskell

.. include:: /manual/features/submatch/submatch_example_captures.rst_

.. |run_submatch_03| image:: ../_static/play.png
    :target: ../../playground?example=haskell/submatch/03_captures.re
    :class:  feed
    :width:  2em

|run_submatch_03| |nbsp| `Run in playground <../../playground?example=haskell/submatch/03_captures.re>`__

.. literalinclude:: ../examples/haskell/submatch/03_captures.re
    :language: haskell

.. include:: /manual/features/submatch/submatch_example_mtags.rst_

.. |run_submatch_02| image:: ../_static/play.png
    :target: ../../playground?example=haskell/submatch/02_mtags.re
    :class:  feed
    :width:  2em

|run_submatch_02| |nbsp| `Run in playground <../../playground?example=haskell/submatch/02_mtags.re>`__

.. literalinclude:: ../examples/haskell/submatch/02_mtags.re
    :language: haskell

Encoding support
----------------
.. include:: /manual/features/encodings/encodings.rst_

.. |run_encodings| image:: ../_static/play.png
    :target: ../../playground?example=haskell/encodings/unicode_identifier.re
    :class:  feed
    :width:  2em

|run_encodings| |nbsp| `Run in playground <../../playground?example=haskell/encodings/unicode_identifier.re>`__

.. literalinclude:: ../examples/haskell/encodings/unicode_identifier.re
    :language: haskell

Include files
-------------
.. include:: /manual/features/includes/includes.rst_

Include file 1 (definitions.hs):

.. literalinclude:: ../examples/haskell/includes/definitions.hs
    :language: haskell

Include file 2 (extra_rules.re.inc):

.. literalinclude:: ../examples/haskell/includes/extra_rules.re.inc

Input file:

.. |run_includes| image:: ../_static/play.png
    :target: ../../playground?example=haskell/includes/include.re
    :class:  feed
    :width:  2em

|run_includes| |nbsp| `Run in playground <../../playground?example=haskell/includes/include.re>`__

.. literalinclude:: ../examples/haskell/includes/include.re
    :language: haskell

Header files
------------
.. include:: /manual/features/headers/headers.rst_

.. |run_headers| image:: ../_static/play.png
    :target: ../../playground?example=haskell/headers/header.re
    :class:  feed
    :width:  2em

|run_headers| |nbsp| `Run in playground <../../playground?example=haskell/headers/header.re>`__

.. literalinclude:: ../examples/haskell/headers/header.re
    :language: haskell

The generated header file:

.. literalinclude:: ../examples/haskell/headers/lexer/state.hs
    :language: haskell

Skeleton programs
-----------------
.. include:: /manual/features/skeleton/skeleton.rst_
.. include:: /manual/features/skeleton/skeleton_example.rst

Visualization and debug
-----------------------
.. include:: /manual/features/dot/dot.rst_
.. include:: /manual/features/dot/example.rst

.. include:: /examples/examples_haskell.rst
