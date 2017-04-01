======
Syntax
======

.. toctree::
    :hidden:

Code for ``re2c`` consists of a set of `rules`_, `definitions`_ and
`configurations`_.

Rules
-----

Each rule consist of a `regular expression`_ accompanied with a block of C/C++ code
which is to be executed when the associated regular expression is
matched. You can either start the code with an opening curly brace or
the sequence ``:=``. If you use an opening curly brace, ``re2c`` will count brace depth
and stop looking for code automatically. Otherwise, curly braces are not
allowed and ``re2c`` stops looking for code at the first line that does
not begin with whitespace. If two or more rules overlap, the first rule
is preferred.

    ``regular-expression { C/C++ code }``

    ``regular-expression := C/C++ code``

There is one special rule: the default rule (``*``)

    ``* { C/C++ code }``

    ``* := C/C++ code``

Note that the default rule (``*``) differs from ``[^]``: the default rule has the lowest priority,
matches any code unit (either valid or invalid) and always consumes exactly one character.
``[^]``, on the other hand, matches any valid code point (not the same as a code unit) and can consume multiple
code units. In fact, when a variable-length encoding is used, ``*``
is the only possible way to match an invalid input character.

If ``-c`` is active, then each regular expression is preceded by a list
of comma-separated condition names. Besides the normal naming rules, there
are two special cases: ``<*>`` (these rules are merged to all conditions)
and ``<>`` (these rules cannot have an associated regular expression;
their code is merged to all actions). Non-empty rules may furthermore specify the new
condition. In that case, ``re2c`` will generate the necessary code to
change the condition automatically. Rules can use ``:=>`` as a shortcut
to automatically generate code that not only sets the
new condition state but also continues execution with the new state. A
shortcut rule should not be used in a loop where there is code between
the start of the loop and the ``re2c`` block unless ``re2c:cond:goto``
is changed to ``continue``. If some code is needed before all rules (though not before simple jumps),  you
can insert it with ``<!>`` pseudo-rules.

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
    condition labels. That is, the text to be prepended to condition labels
    in the generated output file.


``re2c:condenumprefix = yyc;``
    Allows to specify the prefix used for
    condition values. That is, the text to be prepended to condition enum
    values in the generated output file.

``re2c:cond:divider = "/* *********************************** */";``
    Allows to customize the divider for condition blocks. You can use ``@@``
    to put the name of the condition or customize the placeholder using
    ``re2c:cond:divider@cond``.

``re2c:cond:divider@cond = @@;``
    Specifies the placeholder that will be
    replaced with the condition name in ``re2c:cond:divider``.

``re2c:cond:goto = "goto @@;";``
    Allows to customize the condition goto statements used with ``:=>`` style rules. You can use ``@@``
    to put the name of the condition or customize the placeholder using
    ``re2c:cond:goto@cond``. You can also change this to ``continue;``, which
    would allow you to continue with the next loop cycle including any code
    between your loop start and your re2c block.

``re2c:cond:goto@cond = @@;``
    Specifies the placeholder that will be replaced with the condition label in ``re2c:cond:goto``.

``re2c:indent:top = 0;``
    Specifies the minimum amount of indentation to
    use. Requires a numeric value greater than or equal to zero.

``re2c:indent:string = "\t";``
    Specifies the string to use for indentation. Requires a string that should
    contain only whitespace unless you need something else for external tools. The easiest
    way to specify spaces is to enclose them in single or double quotes.
    If you do  not want any indentation at all, you can simply set this to "".

``re2c:yych:conversion = 0;``
    When this setting is non zero, ``re2c`` automatically generates
    conversion code whenever yych gets read. In this case the type must be
    defined using ``re2c:define:YYCTYPE``.

``re2c:yych:emit = 1;``
    The generation of *yych* can be suppressed by setting this to 0.

``re2c:yybm:hex = 0;``
    If set to zero, a decimal table will be used. Otherwise, a hexadecimal table will be generated.

``re2c:yyfill:enable = 1;``
    Set this to zero to suppress the generation of ``YYFILL (n)``. When using this, be sure to verify that the generated
    scanner does not read behind the end of your input, allowing such behavior might
    introduce several security issues to your program.

``re2c:yyfill:check = 1;``
    This can be set to 0 to suppress the generations of 
    ``YYCURSOR`` and ``YYLIMIT`` based precondition checks. This option is useful when
    ``YYLIMIT + YYMAXFILL`` is always accessible.

``re2c:define:YYFILL = "YYFILL";``
    Define a substitution for ``YYFILL``. Note that by default,
    ``re2c`` generates an argument in parentheses and a semicolon after
    ``YYFILL``. If you need to make ``YYFILL`` an arbitrary statement rather
    than a call, set ``re2c:define:YYFILL:naked`` to a non-zero value and use
    ``re2c:define:YYFILL@len`` to set a placeholder for the formal parameter inside of your ``YYFILL``
    body.

``re2c:define:YYFILL@len = "@@";``
    Any occurrence of this text
    inside of a ``YYFILL`` call will be replaced with the actual argument.

``re2c:yyfill:parameter = 1;``
    Controls the argument in the parentheses that follow ``YYFILL``. If zero, the argument is omitted. 
    If non-zero, the argument is generated unless ``re2c:define:YYFILL:naked`` is set to non-zero.

``re2c:define:YYFILL:naked = 0;``
    Controls the argument in the parentheses after ``YYFILL`` and 
    the following semicolon. If zero, both the argument and the semicolon are
    omitted. If non-zero, the argument is generated unless
    ``re2c:yyfill:parameter`` is set to zero; the semicolon is generated
    unconditionally.

``re2c:startlabel = 0;``
    If set to a non zero integer, then the start
    label of the next scanner block will be generated even if it isn't used by
    the scanner itself. Otherwise, the normal ``yy0``-like start label is only
    generated if needed. If set to a text value, then a label with that
    text will be generated regardless of whether the normal start label is
    used or not. This setting is reset to 0 after a start label has been generated.

``re2c:labelprefix = "yy";``
    Allows to change the prefix of numbered
    labels. The default is ``yy``. Can be set any string that is valid in
    a label name.

``re2c:state:abort = 0;``
    When not zero and the ``-f`` switch is active, then
    the ``YYGETSTATE`` block will contain a default case that aborts and a -1
    case will be used for initialization.

``re2c:state:nextlabel = 0;``
    Used when ``-f`` is active to control
    whether the ``YYGETSTATE`` block is followed by a ``yyNext:`` label line.
    Instead of using ``yyNext``, you can usually also use configuration
    ``startlabel`` to force a specific start label or default to ``yy0`` as
    a start label. Instead of using a dedicated label, it is often better to
    separate the ``YYGETSTATE`` code from the actual scanner code by placing a
    ``/*!getstate:re2c*/`` comment.

``re2c:cgoto:threshold = 9;``
    When ``-g`` is active, this value specifies
    the complexity threshold that triggers the generation of jump tables rather
    than nested ifs and decision bitfields. The threshold is compared
    against a calculated estimation of ifs needed where every used bitmap
    divides the threshold by 2.

``re2c:yych:conversion = 0;``
    When input uses signed characters and the
    ``-s`` or ``-b`` switches are in effect, re2c allows automatic conversion
    to the unsigned character type that is then necessary for its internal
    single character. When this setting is zero or an empty string, the
    conversion is disabled. If a non zero number is used, the conversion is taken
    from ``YYCTYPE``. If ``YYCTYPE`` is overridden by an inplace configuration setting, that setting is
    is used instead of a ``YYCTYPE`` cast. Otherwise, it will be ``(YYCTYPE)`` and changes to that
    configuration are no longer possible. When this setting is a string, it must contain the casting
    parentheses. Now assuming your input is a ``char *`` buffer and you are using the above mentioned switches, you can set
    ``YYCTYPE`` to ``unsigned char`` and this setting to either 1 or ``(unsigned char)``.

``re2c:define:YYCONDTYPE = "YYCONDTYPE";``
    Enumeration used for condition support with ``-c`` mode.

``re2c:define:YYCTXMARKER = "YYCTXMARKER";``
    Replaces the ``YYCTXMARKER`` placeholder with the specified identifier.

``re2c:define:YYCTYPE = "YYCTYPE";``
    Replaces the ``YYCTYPE`` placeholder with the specified type.

``re2c:define:YYCURSOR = "YYCURSOR";``
    Replaces the ``YYCURSOR`` placeholder with the specified identifier.

``re2c:define:YYDEBUG = "YYDEBUG";``
    Replaces the ``YYDEBUG`` placeholder with the specified identifier.

``re2c:define:YYGETCONDITION = "YYGETCONDITION";``
    Substitution for
    ``YYGETCONDITION``. Note that by default, ``re2c`` generates parentheses after
    ``YYGETCONDITION``. Set ``re2c:define:YYGETCONDITION:naked`` to non-zero to
    omit the parentheses.

``re2c:define:YYGETCONDITION:naked = 0;``
    Controls the parentheses after
    ``YYGETCONDITION``. If zero, the parentheses are omitted. If non-zero, the parentheses are
    generated.

``re2c:define:YYSETCONDITION = "YYSETCONDITION";``
    Substitution for
    ``YYSETCONDITION``. Note that by default, ``re2c`` generates an argument in
    parentheses followed by semicolon after ``YYSETCONDITION``. If you need to make
    ``YYSETCONDITION`` an arbitrary statement rather than a call, set
    ``re2c:define:YYSETCONDITION:naked`` to non-zero and use
    ``re2c:define:YYSETCONDITION@cond`` to denote the formal parameter inside of the
    ``YYSETCONDITION`` body.

``re2c:define:YYSETCONDITION@cond = "@@";``
    Any occurrence of this
    text inside of ``YYSETCONDITION`` will be replaced with the actual
    argument.

``re2c:define:YYSETCONDITION:naked = 0;``
    Controls the argument in parentheses
    and the semicolon after ``YYSETCONDITION``. If zero, both the argument and
    the semicolon are omitted. If non-zero, both the argument and the semicolon are
    generated.

``re2c:define:YYGETSTATE = "YYGETSTATE";``
    Substitution for
    ``YYGETSTATE``. Note that by default, ``re2c`` generates parentheses after
    ``YYGETSTATE``. Set ``re2c:define:YYGETSTATE:naked`` to non-zero to omit
    the parentheses.

``re2c:define:YYGETSTATE:naked = 0;``
    Controls the parentheses that follow
    ``YYGETSTATE``. If zero, the parentheses are omitted. If non-zero, they are
    generated.

``re2c:define:YYSETSTATE = "YYSETSTATE";``
    Substitution for
    ``YYSETSTATE``. Note that by default, ``re2c`` generates an argument in parentheses
    followed by a semicolon after ``YYSETSTATE``. If you need to make ``YYSETSTATE`` an
    arbitrary statement rather than a call, set
    ``re2c:define:YYSETSTATE:naked`` to non-zero and use
    ``re2c:define:YYSETSTATE@cond`` to denote formal parameter inside of
    your ``YYSETSTATE`` body.

``re2c:define:YYSETSTATE@state = "@@";``
    Any occurrence of this text
    inside of ``YYSETSTATE`` will be replaced with the actual argument.

``re2c:define:YYSETSTATE:naked = 0;``
    Controls the argument in parentheses and the
    semicolon after ``YYSETSTATE``. If zero, both argument and the semicolon are
    omitted. If non-zero, both the argument and the semicolon are generated.

``re2c:define:YYLIMIT = "YYLIMIT";``
    Replaces the ``YYLIMIT`` placeholder with the specified identifier.
    needed.

``re2c:define:YYMARKER = "YYMARKER";``
    Replaces the ``YYMARKER`` placeholder with the specified identifier.

``re2c:label:yyFillLabel = "yyFillLabel";``
    Overrides the name of the ``yyFillLabel`` label.

``re2c:label:yyNext = "yyNext";``
    Overrides the name of the ``yyNext`` label.

``re2c:variable:yyaccept = yyaccept;``
    Overrides the name of the ``yyaccept`` variable.

``re2c:variable:yybm = "yybm";``
    Overrides the name of the ``yybm`` variable.

``re2c:variable:yych = "yych";``
    Overrides the name of the ``yych`` variable.

``re2c:variable:yyctable = "yyctable";``
    When both ``-c`` and ``-g`` are active, ``re2c`` will use this variable to generate a static jump table
    for ``YYGETCONDITION``.

``re2c:variable:yystable = "yystable";``
    Deprecated.

``re2c:variable:yytarget = "yytarget";``
    Overrides the name of the ``yytarget`` variable.

Regular expressions
-------------------

``"foo"``
    literal string ``"foo"``. ANSI-C escape sequences can be used.

``'foo'``
    literal string ``"foo"`` (case insensitive for characters [a-zA-Z]). 
    ANSI-C escape sequences can be used.

``[xyz]``
    character class; in this case, the regular expression matches ``x``, ``y``, or ``z``.

``[abj-oZ]``
    character class with a range in it; matches ``a``, ``b``, any letter from ``j`` through ``o``, or ``Z``.

``[^class]``
    inverted character class.

``r \ s``
   match any ``r`` which isn't ``s``. ``r`` and ``s`` must be regular expressions
   which can be expressed as character classes.

``r*``
    zero or more occurrences of ``r``.

``r+``
    one or more occurrences of ``r``.

``r?``
    optional ``r``.

``(r)``
    ``r``; parentheses are used to override precedence.

``r s``
    ``r`` followed by ``s`` (concatenation).

``r | s``
    ``r`` or ``s`` (alternative).

``r`` / ``s``
    ``r`` but only if it is followed by ``s``. Note that ``s`` is not
    part of the matched text. This type of regular expression is called
    "trailing context". Trailing context can only be at the end of a rule
    and cannot be part of a named definition.

``r{n}``
    matches ``r`` exactly ``n`` times.

``r{n,}``
    matches ``r`` at least ``n`` times.

``r{n,m}``
    matches ``r`` at least ``n`` times, but not more than ``m`` times.

``.``
    match any character except newline.

``name``
    matches a named definition as specified by ``name`` only if ``-F`` is
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

The only portable "any" rule is the default rule, ``*``.

Interface
---------

The user must supply interface code either in the form of C/C++ code
(macros, functions, variables, etc.) or in the form of `configurations`_.
Which symbols must be defined and which are optional
depends on the particular use case.

``YYCONDTYPE``
    In ``-c`` mode, you can use ``-t`` to generate a file that
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
    ``char`` or ``unsigned char`` for ASCII, EBCDIC  or UTF-8, or *unsigned short*
    for UTF-16 or UCS-2, or ``unsigned int`` for UTF-32.

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
    provided. ``YYFILL (n)`` should adjust ``YYCURSOR``, ``YYLIMIT``, ``YYMARKER``,
    and ``YYCTXMARKER`` as needed. Note that for typical programming languages
    ``n`` will be the length of the longest keyword plus one. The user can
    place a comment of the form ``/*!max:re2c*/`` to insert ``YYMAXFILL`` definition that is set to the maximum
    length value.

``YYGETCONDITION ()``
    This define is used to get the condition prior to
    entering the scanner code when using the ``-c`` switch. The value must be
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
    the caller, all he has to do is store that unique identifier in a
    variable. Later, when the scanner is called again, it will call
    ``YYGETSTATE ()`` and resume execution right where it left off. The
    generated code will contain both ``YYSETSTATE (s)`` and ``YYGETSTATE`` even
    if ``YYFILL (n)`` is disabled.

