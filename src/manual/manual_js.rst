++++++++++++++++++++++++++++
User manual (JavaScript)
++++++++++++++++++++++++++++


.. toctree::
    :hidden:

    basics/warnings/warnings

|

.. raw:: html

    <p style="color:gray";><i></i></p>

.. |re2c| replace:: re2js
.. |lang_name| replace:: JavaScript

Introduction
============
.. include:: /manual/intro.rst_

Here is an example of a small program that checks if a given string contains a
decimal number:

.. literalinclude:: ../examples/js/01_basic.re
    :language: js

In the output |re2c| replaced the middle block with the generated code:

.. literalinclude:: ../examples/js/01_basic.js
    :language: js

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
.. include:: /manual/basics/api/api2_js.rst_
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
.. literalinclude:: ../examples/js/eof/01_sentinel.re
    :language: js
.. include:: /manual/eof/03_eof_rule.rst_
.. literalinclude:: ../examples/js/eof/03_eof_rule.re
    :language: js
.. include:: /manual/eof/02_bounds_checking.rst_
.. literalinclude:: ../examples/js/eof/02_bounds_checking.re
    :language: js
.. include:: /manual/eof/04_fake_sentinel.rst_
.. literalinclude:: ../examples/js/eof/04_fake_sentinel.re
    :language: js

Buffer refilling
================
.. include:: /manual/fill/fill.rst_
.. include:: /manual/fill/01_fill.rst_
.. literalinclude:: ../examples/js/fill/01_fill.re
    :language: js
.. include:: /manual/fill/02_fill.rst_
.. literalinclude:: ../examples/js/fill/02_fill.re
    :language: js

Features
========

Multiple blocks
---------------
.. include:: /manual/features/conditions/blocks.rst_
.. literalinclude:: ../examples/js/conditions/parse_u32_blocks.re
    :language: js

Start conditions
----------------
.. include:: /manual/features/conditions/conditions.rst_
.. literalinclude:: ../examples/js/conditions/parse_u32_conditions.re
    :language: js

Storable state
--------------
.. include:: /manual/features/state/state.rst_
.. literalinclude:: ../examples/js/state/push.re
    :language: js

Reusable blocks
---------------
.. include:: /manual/features/reuse/reuse.rst_

Example of a ``!use`` directive:

.. literalinclude:: ../examples/js/reuse/usedir.re
    :language: js

Example of a ``/*!use:re2c ... */`` block:

.. literalinclude:: ../examples/js/reuse/reuse.re
    :language: js

Submatch extraction
-------------------
.. include:: /manual/features/submatch/submatch.rst_
.. include:: /manual/features/submatch/submatch_example_stags.rst_
.. literalinclude:: ../examples/js/submatch/01_stags.re
    :language: js
.. include:: /manual/features/submatch/submatch_example_stags_fill.rst_
.. literalinclude:: ../examples/js/submatch/01_stags_fill.re
    :language: js
.. include:: /manual/features/submatch/submatch_example_captures.rst_
.. literalinclude:: ../examples/js/submatch/03_captures.re
    :language: js
.. include:: /manual/features/submatch/submatch_example_mtags.rst_
.. literalinclude:: ../examples/js/submatch/02_mtags.re
    :language: js

Encoding support
----------------
.. include:: /manual/features/encodings/encodings.rst_
.. literalinclude:: ../examples/js/encodings/unicode_identifier.re
    :language: js

Include files
-------------
.. include:: /manual/features/includes/includes.rst_

Include file 1 (definitions.js):

.. literalinclude:: ../examples/js/includes/definitions.js
    :language: js

Include file 2 (extra_rules.re.inc):

.. literalinclude:: ../examples/js/includes/extra_rules.re.inc

Input file:

.. literalinclude:: ../examples/js/includes/include.re
    :language: js

Header files
------------
.. include:: /manual/features/headers/headers.rst_

.. literalinclude:: ../examples/js/headers/header.re
    :language: js

The generated header file:

.. literalinclude:: ../examples/js/headers/lexer/state.js
    :language: js

Skeleton programs
-----------------
.. include:: /manual/features/skeleton/skeleton.rst_
.. include:: /manual/features/skeleton/skeleton_example.rst

Visualization and debug
-----------------------
.. include:: /manual/features/dot/dot.rst_
.. include:: /manual/features/dot/example.rst

.. include:: /examples/examples_js.rst
