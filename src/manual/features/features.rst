========
Features
========

.. include:: ../home.rst
.. include:: ../../contents.rst

Conditions
----------

You can preceed regular expressions with a list of condition names when
using the ``-c`` switch. In this case ``re2c`` generates scanner blocks for
each conditon. Where each of the generated blocks has its own
precondition. The precondition is given by the interface define
``YYGETCONDITON()`` and must be of type ``YYCONDTYPE``.

There are two special rule types. First, the rules of the condition ``<*>``
are merged to all conditions (note that they have lower priority than
other rules of that condition). And second the empty condition list
allows to provide a code block that does not have a scanner part.
Meaning it does not allow any regular expression. The condition value
referring to this special block is always the one with the enumeration
value 0. This way the code of this special rule can be used to
initialize a scanner. It is in no way necessary to have these rules: but
sometimes it is helpful to have a dedicated uninitialized condition
state.

Non empty rules allow to specify the new condition, which makes them
transition rules. Besides generating calls for the define
``YYSETCONDTITION`` no other special code is generated.

There is another kind of special rules that allow to prepend code to any
code block of all rules of a certain set of conditions or to all code
blocks to all rules. This can be helpful when some operation is common
among rules. For instance this can be used to store the length of the
scanned string. These special setup rules start with an exclamation mark
followed by either a list of conditions ``<! condition, ... >`` or a star
``<!*>``. When ``re2c`` generates the code for a rule whose state does not have a
setup rule and a star'd setup rule is present, than that code will be
used as setup code.

State
-----

When the ``-f`` flag is specified, ``re2c`` generates a scanner that can
store its current state, return to the caller, and later resume
operations exactly where it left off.

The default operation of ``re2c`` is a
"pull" model, where the scanner asks for extra input whenever it needs it. However, this mode of operation assumes that the scanner is the "owner"
the parsing loop, and that may not always be convenient.

Typically, if there is a preprocessor ahead of the scanner in the
stream, or for that matter any other procedural source of data, the
scanner cannot "ask" for more data unless both scanner and source
live in a separate threads.

The ``-f`` flag is useful for just this situation: it lets users design
scanners that work in a "push" model, i.e. where data is fed to the
scanner chunk by chunk. When the scanner runs out of data to consume, it
just stores its state, and return to the caller. When more input data is
fed to the scanner, it resumes operations exactly where it left off.

Changes needed compared to the "pull" model:

* User has to supply macros ``YYSETSTATE ()`` and ``YYGETSTATE (state)``.

* The ``-f`` option inhibits declaration of ``yych`` and ``yyaccept``. So the
  user has to declare these. Also the user has to save and restore these.
  In the example ``examples/push_model/push.re`` these are declared as
  fields of the (C++) class of which the scanner is a method, so they do
  not need to be saved/restored explicitly. For C they could e.g. be made
  macros that select fields from a structure passed in as parameter.
  Alternatively, they could be declared as local variables, saved with
  ``YYFILL (n)`` when it decides to return and restored at entry to the
  function. Also, it could be more efficient to save the state from
  ``YYFILL (n)`` because ``YYSETSTATE (state)`` is called unconditionally.
  ``YYFILL (n)`` however does not get ``state`` as parameter, so we would have
  to store state in a local variable by ``YYSETSTATE (state)``.

* Modify ``YYFILL (n)`` to return (from the function calling it) if more input is needed.

* Modify caller to recognise if more input is needed and respond appropriately.

* The generated code will contain a switch block that is used to
  restores the last state by jumping behind the corrspoding ``YYFILL (n)``
  call. This code is automatically generated in the epilog of the first ``/*!re2c */``
  block. It is possible to trigger generation of the ``YYGETSTATE ()``
  block earlier by placing a ``/*!getstate:re2c*/`` comment. This is especially useful when the scanner code should be
  wrapped inside a loop.

Please see ``examples/push_model/push.re`` for "push" model scanner. The
generated code can be tweaked using inplace configurations ``state:abort``
and ``state:nextlabel``.

Reuse
-----

Reuse mode is controlled by ``-r --reusable`` option.
Allows reuse of scanner definitions with ``/*!use:re2c */`` after ``/*!rules:re2c */``.
In this mode no ``/*!re2c */`` block and exactly one ``/*!rules:re2c */`` must be present.
The rules are being saved and used by every ``/*!use:re2c */`` block that follows.
These blocks can contain inplace configurations, especially ``re2c:flags:e``,
``re2c:flags:w``, ``re2c:flags:x``, ``re2c:flags:u`` and ``re2c:flags:8``.
That way it is possible to create the same scanner multiple times for
different character types, different input mechanisms or different output mechanisms.
The ``/*!use:re2c */`` blocks can also contain additional rules that will be appended
to the set of rules in ``/*!rules:re2c */``.

Encodings
---------

``re2c`` supports the following encodings: ASCII (default), EBCDIC (``-e``),
UCS-2 (``-w``), UTF-16 (``-x``), UTF-32 (``-u``) and UTF-8 (``-8``).
See also inplace configuration ``re2c:flags``.

The following concepts should be clarified when talking about encoding.
*Code point* is an abstract number, which represents single encoding
symbol. *Code unit* is the smallest unit of memory, which is used in the
encoded text (it corresponds to one character in the input stream). One
or more code units can be needed to represent a single code point,
depending on the encoding. In *fixed-length* encoding, each code point
is represented with equal number of code units. In *variable-length*
encoding, different code points can be represented with different number
of code units.

* ASCII is a fixed-length encoding. Its code space includes 0x100
  code points, from 0 to 0xFF. One code point is represented with exactly one
  1-byte code unit, which has the same value as the code point. Size of
  ``YYCTYPE`` must be 1 byte.

* EBCDIC is a fixed-length encoding. Its code space includes 0x100
  code points, from 0 to 0xFF. One code point is represented with exactly
  one 1-byte code unit, which has the same value as the code point. Size
  of ``YYCTYPE`` must be 1 byte.

* UCS-2 is a fixed-length encoding. Its code space includes 0x10000
  code points, from 0 to 0xFFFF. One code point is represented with
  exactly one 2-byte code unit, which has the same value as the code
  point. Size of ``YYCTYPE`` must be 2 bytes.

* UTF-16 is a variable-length encoding. Its code space includes all
  Unicode code points, from 0 to 0xD7FF and from 0xE000 to 0x10FFFF. One
  code point is represented with one or two 2-byte code units. Size of
  ``YYCTYPE`` must be 2 bytes.

* UTF-32 is a fixed-length encoding. Its code space includes all
  Unicode code points, from 0 to 0xD7FF and from 0xE000 to 0x10FFFF. One
  code point is represented with exactly one 4-byte code unit. Size of
  ``YYCTYPE`` must be 4 bytes.

* UTF-8 is a variable-length encoding. Its code space includes all
  Unicode code points, from 0 to 0xD7FF and from 0xE000 to 0x10FFFF. One
  code point is represented with sequence of one, two, three or four
  1-byte code units. Size of ``YYCTYPE`` must be 1 byte.

In Unicode, values from range 0xD800 to 0xDFFF (surrogates) are not
valid Unicode code points, any encoded sequence of code units, that
would map to Unicode code points in the range 0xD800-0xDFFF, is
ill-formed. The user can control how ``re2c`` treats such ill-formed
sequences with ``--encoding-policy <policy>`` flag.

For some encodings, there are code units, that never occur in valid
encoded stream (e.g. 0xFF byte in UTF-8). If the generated scanner must
check for invalid input, the only true way to do so is to use default
rule ``*``. Note, that full range rule ``[^]`` won't catch invalid code units when variable-length encoding is used
(``[^]`` means "all valid code points", while default rule ``*`` means "all possible code units").

Generic interface
-----------------

``re2c`` usually operates on input using pointer-like primitives
``YYCURSOR``, ``YYMARKER``, ``YYCTXMARKER`` and ``YYLIMIT``.

Generic input API (enabled with ``--input custom`` switch) allows to
customize input operations. In this mode, ``re2c`` will express all
operations on input in terms of the following primitives:

    +---------------------+-----------------------------------------------------+
    | ``YYPEEK ()``       | get current input character                         |
    +---------------------+-----------------------------------------------------+
    | ``YYSKIP ()``       | advance to the next character                       |
    +---------------------+-----------------------------------------------------+
    | ``YYBACKUP ()``     | backup current input position                       |
    +---------------------+-----------------------------------------------------+
    | ``YYBACKUPCTX ()``  | backup current input position for trailing context  |
    +---------------------+-----------------------------------------------------+
    | ``YYRESTORE ()``    | restore current input position                      |
    +---------------------+-----------------------------------------------------+
    | ``YYRESTORECTX ()`` | restore current input position for trailing context |
    +---------------------+-----------------------------------------------------+
    | ``YYLESSTHAN (n)``  | check if less than ``n`` input characters are left  |
    +---------------------+-----------------------------------------------------+

This `article <http://skvadrik.github.io/aleph_null/posts/re2c/2015-01-13-input_model.html>`_
has more details, and you can find some usage examples
`here <http://skvadrik.github.io/aleph_null/posts/re2c/2015-01-15-input_model_custom.html>`_.

