======
Syntax
======

.. toctree::
    :hidden:

Code for ``re2c`` consists of a set of `rules`_, `definitions`_ and
`configurations`_.

Rules
-----

Rules consist of a `regular expressions`_ along with a block of C/C++ code
that is to be executed when the associated regular expression is
matched. You can either start the code with an opening curly brace or
the sequence ``:=``. When the code with a curly brace then ``re2c`` counts the brace depth
and stops looking for code automatically. Otherwise curly braces are not
allowed and ``re2c`` stops looking for code at the first line that does
not begin with whitespace. If two or more rules overlap, the first rule
is preferred.

    ``regular-expression { C/C++ code }``

    ``regular-expression := C/C++ code``

There is one special rule: default rule ``*``

    ``* { C/C++ code }``

    ``* := C/C++ code``

Note that default rule ``*`` differs from ``[^]``: default rule has the lowest priority,
matches any code unit (either valid or invalid) and always consumes one character;
while ``[^]`` matches any valid code point (not code unit) and can consume multiple
code units. In fact, when variable-length encoding is used, ``*``
is the only possible way to match invalid input character.

If ``-c`` is active then each regular expression is preceeded by a list
of comma separated condition names. Besides normal naming rules there
are two special cases: ``<*>`` (such rules are merged to all conditions)
and ``<>`` (such the rule cannot have an associated regular expression,
its code is merged to all actions). Non empty rules may further more specify the new
condition. In that case ``re2c`` will generate the necessary code to
change the condition automatically. Rules can use ``:=>`` as a shortcut
to automatically generate code that not only sets the
new condition state but also continues execution with the new state. A
shortcut rule should not be used in a loop where there is code between
the start of the loop and the ``re2c`` block unless ``re2c:cond:goto``
is changed to ``continue``. If code is necessary before all rules (though not simple jumps) you
can doso by using ``<!>`` pseudo-rules.

    ``<condition-list> regular-expression { C/C++ code }``

    ``<condition-list> regular-expression := C/C++ code``

    ``<condition-list> * { C/C++ code }``

    ``<condition-list> * := C/C++ code``

    ``<condition-list> regular-expression => condition { C/C++ code }``

    ``<condition-list> regular-expression => condition := C/C++ code``

    ``<condition-list> * => condition { C/C++ code }``

    ``<condition-list> * => condition := C/C++ code``

    ``<condition-list> regular-expression :=> condition``


    ``<*> regular-expression { C/C++ code }``

    ``<*> regular-expression := C/C++ code``

    ``<*> * { C/C++ code }``

    ``<*> * := C/C++ code``

    ``<*> regular-expression => condition { C/C++ code }``

    ``<*> regular-expression => condition := C/C++ code``

    ``<*> * => condition { C/C++ code }``

    ``<*> * => condition := C/C++ code``

    ``<*> regular-expression :=> condition``


    ``<> { C/C++ code }``

    ``<> := C/C++ code``

    ``<> => condition { C/C++ code }``

    ``<> => condition := C/C++ code``

    ``<> :=> condition``

    ``<> :=> condition``


    ``<! condition-list> { C/C++ code }``

    ``<! condition-list> := C/C++ code``

    ``<!> { C/C++ code }``

    ``<!> := C/C++ code``

Definitions
-----------

Named definitions are of the form:

    ``name = regular-expression;``

If ``-F`` is active, then named definitions are also of the form:

    ``name { regular-expression }``

Configurations
--------------

``re2c:condprefix = yyc;``
    Allows to specify the prefix used for
    condition labels. That is this text is prepended to any condition label
    in the generated output file.

``re2c:condenumprefix = yyc;``
    Allows to specify the prefix used for
    condition values. That is this text is prepended to any condition enum
    value in the generated output file.

``re2c:cond:divider = "/* *********************************** */";``
    Allows to customize the devider for condition blocks. You can use ``@@``
    to put the name of the condition or customize the placeholder using
    ``re2c:cond:divider@cond``.

``re2c:cond:divider@cond = @@;``
    Specifies the placeholder that will be
    replaced with the condition name in ``re2c:cond:divider``.

``re2c:cond:goto = "goto @@;";``
    Allows to customize the condition goto statements used with ``:=>`` style rules. You can use ``@@``
    to put the name of the condition or ustomize the placeholder using
    ``re2c:cond:goto@cond``. You can also change this to ``continue;``, which
    would allow you to continue with the next loop cycle including any code
    between loop start and re2c block.

``re2c:cond:goto@cond = @@;``
    Spcifies the placeholder that will be replaced with the condition label in ``re2c:cond:goto``.

``re2c:indent:top = 0;``
    Specifies the minimum number of indendation to
    use. Requires a numeric value greater than or equal zero.

``re2c:indent:string = "\t";``
    Specifies the string to use for indendation. Requires a string that should
    contain only whitespace unless you need this for external tools. The easiest
    way to specify spaces is to enclude them in single or double quotes.
    If you do  not want any indendation at all you can simply set this to "".

``re2c:yych:conversion = 0;``
    When this setting is non zero, then ``re2c`` automatically generates
    conversion code whenever yych gets read. In this case the type must be
    defined using ``re2c:define:YYCTYPE``.

``re2c:yych:emit = 1;``
    Generation of *yych* can be suppressed by setting this to 0.

``re2c:yybm:hex = 0;``
    If set to zero then a decimal table is being used else a hexadecimal table will be generated.

``re2c:yyfill:enable = 1;``
    Set this to zero to suppress generation of ``YYFILL (n)``. When using this be sure to verify that the generated
    scanner does not read behind input. Allowing this behavior might
    introduce sever security issues to you programs.

``re2c:yyfill:check = 1;``
    This can be set 0 to suppress output of the
    pre condition using ``YYCURSOR`` and ``YYLIMIT`` which becomes usefull when
    ``YYLIMIT + YYMAXFILL`` is always accessible.

``re2c:define:YYFILL = "YYFILL";``
    Substitution for ``YYFILL``. Note
    that by default ``re2c`` generates argument in braces and semicolon after
    ``YYFILL``. If you need to make ``YYFILL`` an arbitrary statement rather
    than a call, set ``re2c:define:YYFILL:naked`` to non-zero and use
    ``re2c:define:YYFILL@len`` to denote formal parameter inside of ``YYFILL``
    body.

``re2c:define:YYFILL@len = "@@";``
    Any occurence of this text
    inside of ``YYFILL`` will be replaced with the actual argument.

``re2c:yyfill:parameter = 1;``
    Controls argument in braces after
    ``YYFILL``. If zero, agrument is omitted. If non-zero, argument is
    generated unless ``re2c:define:YYFILL:naked`` is set to non-zero.

``re2c:define:YYFILL:naked = 0;``
    Controls argument in braces and
    semicolon after ``YYFILL``. If zero, both agrument and semicolon are
    omitted. If non-zero, argument is generated unless
    ``re2c:yyfill:parameter`` is set to zero and semicolon is generated
    unconditionally.

``re2c:startlabel = 0;``
    If set to a non zero integer then the start
    label of the next scanner blocks will be generated even if not used by
    the scanner itself. Otherwise the normal ``yy0`` like start label is only
    being generated if needed. If set to a text value then a label with that
    text will be generated regardless of whether the normal start label is
    being used or not. This setting is being reset to 0 after a start
    label has been generated.

``re2c:labelprefix = "yy";``
    Allows to change the prefix of numbered
    labels. The default is ``yy`` and can be set any string that is a valid
    label.

``re2c:state:abort = 0;``
    When not zero and switch ``-f`` is active then
    the ``YYGETSTATE`` block will contain a default case that aborts and a -1
    case is used for initialization.

``re2c:state:nextlabel = 0;``
    Used when ``-f`` is active to control
    whether the ``YYGETSTATE`` block is followed by a ``yyNext:`` label line.
    Instead of using ``yyNext`` you can usually also use configuration
    ``startlabel`` to force a specific start label or default to ``yy0`` as
    start label. Instead of using a dedicated label it is often better to
    separate the ``YYGETSTATE`` code from the actual scanner code by placing a
    ``/*!getstate:re2c*/`` comment.

``re2c:cgoto:threshold = 9;``
    When ``-g`` is active this value specifies
    the complexity threshold that triggers generation of jump tables rather
    than using nested if's and decision bitfields. The threshold is compared
    against a calculated estimation of if-s needed where every used bitmap
    divides the threshold by 2.

``re2c:yych:conversion = 0;``
    When the input uses signed characters and
    ``-s`` or ``-b`` switches are in effect re2c allows to automatically convert
    to the unsigned character type that is then necessary for its internal
    single character. When this setting is zero or an empty string the
    conversion is disabled. Using a non zero number the conversion is taken
    from ``YYCTYPE``. If that is given by an inplace configuration that value
    is being used. Otherwise it will be ``(YYCTYPE)`` and changes to that
    configuration are no longer possible. When this setting is a string the
    braces must be specified. Now assuming your input is a ``char *``
    buffer and you are using above mentioned switches you can set
    ``YYCTYPE`` to ``unsigned char`` and this setting to either 1 or ``(unsigned char)``.

``re2c:define:YYCONDTYPE = "YYCONDTYPE";``
    Enumeration used for condition support with ``-c`` mode.

``re2c:define:YYCTXMARKER = "YYCTXMARKER";``
    Allows to overwrite the
    define ``YYCTXMARKER`` and thus avoiding it by setting the value to the
    actual code needed.

``re2c:define:YYCTYPE = "YYCTYPE";``
    Allows to overwrite the define
    ``YYCTYPE`` and thus avoiding it by setting the value to the actual code
    needed.

``re2c:define:YYCURSOR = "YYCURSOR";``
    Allows to overwrite the define
    ``YYCURSOR`` and thus avoiding it by setting the value to the actual code
    needed.

``re2c:define:YYDEBUG = "YYDEBUG";``
    Allows to overwrite the define
    ``YYDEBUG`` and thus avoiding it by setting the value to the actual code
    needed.

``re2c:define:YYGETCONDITION = "YYGETCONDITION";``
    Substitution for
    ``YYGETCONDITION``. Note that by default ``re2c`` generates braces after
    ``YYGETCONDITION``. Set ``re2c:define:YYGETCONDITION:naked`` to non-zero to
    omit braces.

``re2c:define:YYGETCONDITION:naked = 0;``
    Controls braces after
    ``YYGETCONDITION``. If zero, braces are omitted. If non-zero, braces are
    generated.

``re2c:define:YYSETCONDITION = "YYSETCONDITION";``
    Substitution for
    ``YYSETCONDITION``. Note that by default ``re2c`` generates argument in
    braces and semicolon after ``YYSETCONDITION``. If you need to make
    ``YYSETCONDITION`` an arbitrary statement rather than a call, set
    ``re2c:define:YYSETCONDITION:naked`` to non-zero and use
    ``re2c:define:YYSETCONDITION@cond`` to denote formal parameter inside of
    ``YYSETCONDITION`` body.

``re2c:define:YYSETCONDITION@cond = "@@";``
    Any occurence of this
    text inside of ``YYSETCONDITION`` will be replaced with the actual
    argument.

``re2c:define:YYSETCONDITION:naked = 0;``
    Controls argument in braces
    and semicolon after ``YYSETCONDITION``. If zero, both agrument and
    semicolon are omitted. If non-zero, both argument and semicolon are
    generated.

``re2c:define:YYGETSTATE = "YYGETSTATE";``
    Substitution for
    ``YYGETSTATE``. Note that by default ``re2c`` generates braces after
    ``YYGETSTATE``. Set ``re2c:define:YYGETSTATE:naked`` to non-zero to omit
    braces.

``re2c:define:YYGETSTATE:naked = 0;``
    Controls braces after
    ``YYGETSTATE``. If zero, braces are omitted. If non-zero, braces are
    generated.

``re2c:define:YYSETSTATE = "YYSETSTATE";``
    Substitution for
    ``YYSETSTATE``. Note that by default ``re2c`` generates argument in braces
    and semicolon after ``YYSETSTATE``. If you need to make ``YYSETSTATE`` an
    arbitrary statement rather than a call, set
    ``re2c:define:YYSETSTATE:naked`` to non-zero and use
    ``re2c:define:YYSETSTATE@cond`` to denote formal parameter inside of
    ``YYSETSTATE`` body.

``re2c:define:YYSETSTATE@state = "@@";``
    Any occurence of this text
    inside of ``YYSETSTATE`` will be replaced with the actual argument.

``re2c:define:YYSETSTATE:naked = 0;``
    Controls argument in braces and
    semicolon after ``YYSETSTATE``. If zero, both agrument and semicolon are
    omitted. If non-zero, both argument and semicolon are generated.

``re2c:define:YYLIMIT = "YYLIMIT";``
    Allows to overwrite the define
    ``YYLIMIT`` and thus avoiding it by setting the value to the actual code
    needed.

``re2c:define:YYMARKER = "YYMARKER";``
    Allows to overwrite the define
    ``YYMARKER`` and thus avoiding it by setting the value to the actual code
    needed.

``re2c:label:yyFillLabel = "yyFillLabel";``
    Allows to overwrite the name of the label ``yyFillLabel``.

``re2c:label:yyNext = "yyNext";``
    Allows to overwrite the name of the label ``yyNext``.

``re2c:variable:yyaccept = yyaccept;``
    Allows to overwrite the name of the variable ``yyaccept``.

``re2c:variable:yybm = "yybm";``
    Allows to overwrite the name of the variable ``yybm``.

``re2c:variable:yych = "yych";``
    Allows to overwrite the name of the variable ``yych``.

``re2c:variable:yyctable = "yyctable";``
    When both ``-c`` and ``-g`` are active then ``re2c`` uses this variable to generate a static jump table
    for ``YYGETCONDITION``.

``re2c:variable:yystable = "yystable";``
    Deprecated.

``re2c:variable:yytarget = "yytarget";``
    Allows to overwrite the name of the variable ``yytarget``.

Regular expressions
-------------------

``"foo"``
    literal string ``"foo"``. ANSI-C escape sequences can be used.

``'foo'``
    literal string ``"foo"`` (characters [a-zA-Z] treated
    case-insensitive). ANSI-C escape sequences can be used.

``[xyz]``
    character class; in this case, regular expression matches either ``x``, ``y``, or ``z``.

``[abj-oZ]``
    character class with a range in it; matches ``a``, ``b``, any letter from ``j`` through ``o`` or ``Z``.

``[^class]``
    inverted character class.

``r \ s``
   match any ``r`` which isn't ``s``. ``r`` and ``s`` must be regular expressions
   which can be expressed as character classes.

``r*``
    zero or more occurences of ``r``.

``r+``
    one or more occurences of ``r``.

``r?``
    optional ``r``.

``(r)``
    ``r``; parentheses are used to override precedence.

``r s``
    ``r`` followed by ``s`` (concatenation).

``r | s``
    either ``r`` or ``s`` (alternative).

``r`` / ``s``
    ``r`` but only if it is followed by ``s``. Note that ``s`` is not
    part of the matched text. This type of regular expression is called
    "trailing context". Trailing context can only be the end of a rule
    and not part of a named definition.

``r{n}``
    matches ``r`` exactly ``n`` times.

``r{n,}``
    matches ``r`` at least ``n`` times.

``r{n,m}``
    matches ``r`` at least ``n`` times, but not more than ``m`` times.

``.``
    match any character except newline.

``name``
    matches named definition as specified by ``name`` only if ``-F`` is
    off. If ``-F`` is active then this behaves like it was enclosed in double
    quotes and matches the string "name".

Character classes and string literals may contain octal or hexadecimal
character definitions and the following set of escape sequences:
``\a``, ``\b``, ``\f``, ``\n``, ``\r``, ``\t``, ``\v``, ``\\``. An octal character is defined by a backslash
followed by its three octal digits (e.g. ``\377``).
Hexadecimal characters from 0 to 0xFF are defined by backslash, a lower
cased ``x`` and two hexadecimal digits (e.g. ``\x12``). Hexadecimal characters from 0x100 to 0xFFFF are defined by backslash, a lower cased
``\u`` or an upper cased ``\X`` and four hexadecimal digits (e.g. ``\u1234``).
Hexadecimal characters from 0x10000 to 0xFFFFffff are defined by backslash, an upper cased ``\U``
and eight hexadecimal digits (e.g. ``\U12345678``).

The only portable "any" rule is the default rule ``*``.

Interface
---------

The user must supply interface code either in the form of C/C++ code
(macros, functions, variables, etc.) or in the form of `configurations`_.
Which symbols must be defined and which are optional
depends on a particular use case.

``YYCONDTYPE``
    In ``-c`` mode you can use ``-t`` to generate a file that
    contains the enumeration used as conditions. Each of the values refers
    to a condition of a rule set.

``YYCTXMARKER``
    l-value of type ``YYCTYPE *``.
    The generated code saves trailing context backtracking information in
    ``YYCTXMARKER``. The user only needs to define this macro if a scanner
    specification uses trailing context in one or more of its regular
    expressions.

``YYCTYPE``
    Type used to hold an input symbol (code unit). Usually
    ``char`` or ``unsigned char`` for ASCII, EBCDIC and UTF-8, *unsigned short*
    for UTF-16 or UCS-2 and ``unsigned int`` for UTF-32.

``YYCURSOR``
    l-value of type ``YYCTYPE *`` that points to the current input symbol. The generated code advances
    ``YYCURSOR`` as symbols are matched. On entry, ``YYCURSOR`` is assumed to
    point to the first character of the current token. On exit, ``YYCURSOR``
    will point to the first character of the following token.

``YYDEBUG (state, current)``
    This is only needed if the ``-d`` flag was
    specified. It allows to easily debug the generated parser by calling a
    user defined function for every state. The function should have the
    following signature: ``void YYDEBUG (int state, char current)``. The first
    parameter receives the state or -1 and the second parameter receives the
    input at the current cursor.

``YYFILL (n)``
    The generated code "calls"" ``YYFILL (n)`` when the
    buffer needs (re)filling: at least ``n`` additional characters should be
    provided. ``YYFILL (n)`` should adjust ``YYCURSOR``, ``YYLIMIT``, ``YYMARKER``
    and ``YYCTXMARKER`` as needed. Note that for typical programming languages
    ``n`` will be the length of the longest keyword plus one. The user can
    place a comment of the form ``/*!max:re2c*/`` to insert ``YYMAXFILL`` definition that is set to the maximum
    length value.

``YYGETCONDITION ()``
    This define is used to get the condition prior to
    entering the scanner code when using ``-c`` switch. The value must be
    initialized with a value from the enumeration ``YYCONDTYPE`` type.

``YYGETSTATE ()``
    The user only needs to define this macro if the ``-f``
    flag was specified. In that case, the generated code "calls"
    ``YYGETSTATE ()`` at the very beginning of the scanner in order to obtain
    the saved state. ``YYGETSTATE ()`` must return a signed integer. The value
    must be either -1, indicating that the scanner is entered for the first
    time, or a value previously saved by ``YYSETSTATE (s)``. In the second
    case, the scanner will resume operations right after where the last
    ``YYFILL (n)`` was called.

``YYLIMIT``
    Expression of type ``YYCTYPE *`` that marks the end of the buffer ``YYLIMIT[-1]``
    is the last character in the buffer). The generated code repeatedly
    compares ``YYCURSOR`` to ``YYLIMIT`` to determine when the buffer needs
    (re)filling.

``YYMARKER``
    l-value of type ``YYCTYPE *``.
    The generated code saves backtracking information in ``YYMARKER``. Some
    easy scanners might not use this.

``YYMAXFILL``
    This will be automatically defined by ``/*!max:re2c*/`` blocks as explained above.

``YYSETCONDITION (c)``
    This define is used to set the condition in
    transition rules. This is only being used when ``-c`` is active and
    transition rules are being used.

``YYSETSTATE (s)``
    The user only needs to define this macro if the ``-f``
    flag was specified. In that case, the generated code "calls"
    ``YYSETSTATE`` just before calling ``YYFILL (n)``. The parameter to
    ``YYSETSTATE`` is a signed integer that uniquely identifies the specific
    instance of ``YYFILL (n)`` that is about to be called. Should the user
    wish to save the state of the scanner and have ``YYFILL (n)`` return to
    the caller, all he has to do is store that unique identifer in a
    variable. Later, when the scannered is called again, it will call
    ``YYGETSTATE ()`` and resume execution right where it left off. The
    generated code will contain both ``YYSETSTATE (s)`` and ``YYGETSTATE`` even
    if ``YYFILL (n)`` is being disabled.

