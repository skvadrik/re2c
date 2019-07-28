.. toctree::
    :hidden:

A re2c program consists of a number of re2c blocks and
:ref:`directives <directives>` intermixed with normal C/C++ code. Each re2c
block consists of a sequence of named definitions,
:ref:`configurations <configurations>` and rules that contain
:ref:`regular expressions <regular-expressions>`. The generated lexer
communicates with the outer world by the means of
:ref:`user interface <user-interface>`.
Rules consist of a regular expression followed by a user-defined action
(semantic action): a block of C/C++ code that is executed in case of sucessful
match. Semantic action can be either an arbitrary block of code enclosed in
curly braces ``{`` and ``}``, or a block of code without curly braces preceded
with ``:=`` and ended with a newline that is not followed by a whitespace.
If multiple rules match, longest match takes precedence. If multiple rules match
the same string, the earlier rule takes priority. If ``-c --conditions`` option
is used, then rules have more complex form described in the section about
conditions.  There are two special kinds of rules:

- Default rule ``*`` which has the lowest priority reagrdless of its place in
  the source code, matches any code unit and consumes exactly one code unit.
  This rule should always be defined.

- EOF rule ``$`` which matches the end of input. This rule should be defined if
  the simplified EOF handling method is used.

Named definitions are of the form ``name = regexp ;`` where ``name`` is an
identifier that consists of letters, digits and underscores, and ``regexp`` is a
regular expression. With ``-F --flex-syntax`` option named definitions are also
of the form ``name regexp``. Each name should be defined before it is used.

.. include:: /manual/syntax/example.rst
