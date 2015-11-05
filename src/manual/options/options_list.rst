``-? -h --help``
    Invoke a short help.

``-b --bit-vectors``
    Implies ``-s``. Use bit vectors as well in the
    attempt to coax better code out of the compiler. Most useful for
    specifications with more than a few keywords (e.g. for most programming
    languages).

``-c --conditions``
    Used to support (f)lex-like condition support.

``-d --debug-output``
    Creates a parser that dumps information about
    the current position and in which state the parser is while parsing the
    input. This is useful to debug parser issues and states. If you use this
    switch you need to define a macro ``YYDEBUG`` that is called like a
    function with two parameters: ``void YYDEBUG (int state, char current)``.
    The first parameter receives the state or ``-1`` and the second parameter
    receives the input at the current cursor.

``-D --emit-dot``
    Emit Graphviz dot data. It can then be processed
    with e.g. ``dot -Tpng input.dot > output.png``. Please note that
    scanners with many states may crash dot.

``-e --ecb``
    Generate a parser that supports EBCDIC. The generated
    code can deal with any character up to 0xFF. In this mode ``re2c`` assumes
    that input character size is 1 byte. This switch is incompatible with
    ``-w``, ``-x``, ``-u`` and ``-8``.

``-f --storable-state``
    Generate a scanner with support for storable state.

``-F --flex-syntax``
    Partial support for flex syntax. When this flag
    is active then named definitions must be surrounded by curly braces and
    can be defined without an equal sign and the terminating semi colon.
    Instead names are treated as direct double quoted strings.

``-g --computed-gotos``
    Generate a scanner that utilizes GCC's
    computed goto feature. That is ``re2c`` generates jump tables whenever a
    decision is of a certain complexity (e.g. a lot of if conditions are
    otherwise necessary). This is only useable with GCC and produces output
    that cannot be compiled with any other compiler. Note that this implies
    ``-b`` and that the complexity threshold can be configured using the
    inplace configuration ``cgoto:threshold``.

``-i --no-debug-info``
    Do not output ``#line`` information. This is
    usefull when you want use a CMS tool with the ``re2c`` output which you
    might want if you do not require your users to have ``re2c`` themselves
    when building from your source.

``-o OUTPUT --output=OUTPUT``
    Specify the ``OUTPUT`` file.

``-r --reusable``
    Allows reuse of scanner definitions with ``/*!use:re2c */`` after ``/*!rules:re2c */``.
    In this mode no ``/*!re2c */`` block and exactly one ``/*!rules:re2c */`` must be present.
    The rules are being saved and used by every ``/*!use:re2c */`` block that follows.
    These blocks can contain inplace configurations, especially ``re2c:flags:e``,
    ``re2c:flags:w``, ``re2c:flags:x``, ``re2c:flags:u`` and ``re2c:flags:8``.
    That way it is possible to create the same scanner multiple times for
    different character types, different input mechanisms or different output mechanisms.
    The ``/*!use:re2c */`` blocks can also contain additional rules that will be appended
    to the set of rules in ``/*!rules:re2c */``.

``-s --nested-ifs``
    Generate nested ifs for some switches. Many
    compilers need this assist to generate better code.

``-t HEADER --type-header=HEADER``
    Create a ``HEADER`` file that
    contains types for the (f)lex-like condition support. This can only be
    activated when ``-c`` is in use.

``-u --unicode``
    Generate a parser that supports UTF-32. The generated
    code can deal with any valid Unicode character up to 0x10FFFF. In this
    mode ``re2c`` assumes that input character size is 4 bytes. This switch is
    incompatible with ``-e``, ``-w``, ``-x`` and ``-8``. This implies ``-s``.

``-v --version``
    Show version information.

``-V --vernum``
    Show the version as a number XXYYZZ.

``-w --wide-chars``
    Generate a parser that supports UCS-2. The
    generated code can deal with any valid Unicode character up to 0xFFFF.
    In this mode ``re2c`` assumes that input character size is 2 bytes. This
    switch is incompatible with ``-e``, ``-x``, ``-u`` and ``-8``. This implies
    ``-s``.

``-x --utf-16``
    Generate a parser that supports UTF-16. The generated
    code can deal with any valid Unicode character up to 0x10FFFF. In this
    mode ``re2c`` assumes that input character size is 2 bytes. This switch is
    incompatible with ``-e``, ``-w``, ``-u`` and ``-8``. This implies ``-s``.

``-8 --utf-8``
    Generate a parser that supports UTF-8. The generated
    code can deal with any valid Unicode character up to 0x10FFFF. In this
    mode ``re2c`` assumes that input character size is 1 byte. This switch is
    incompatible with ``-e``, ``-w``, ``-x`` and ``-u``.

``--case-insensitive``
    All strings are case insensitive, so all
    "-expressions are treated in the same way '-expressions are.

``--case-inverted``
    Invert the meaning of single and double quoted
    strings. With this switch single quotes are case sensitive and double
    quotes are case insensitive.

``--no-generation-date``
    Suppress date output in the generated output so
    that it only shows the ``re2c`` version.

``--encoding-policy POLICY``
    Specify how ``re2c`` must treat Unicode
    surrogates. ``POLICY`` can be one of the following: ``fail`` (abort with
    error when surrogate encountered), ``substitute`` (silently substitute
    surrogate with error code point 0xFFFD), ``ignore`` (treat surrogates as
    normal code points). By default ``re2c`` ignores surrogates (for backward
    compatibility). Unicode standard says that standalone surrogates are
    invalid code points, but different libraries and programs treat them
    differently.

``--input INPUT``
    Specify re2c input API. ``INPUT`` can be one of the
    following: ``default``, ``custom``.

``-S --skeleton``
    Instead of embedding re2c-generated code into C/C++
    source, generate a self-contained program for the same DFA. Most useful
    for correctness and performance testing.

``--empty-class POLICY``
    What to do if user inputs empty character
    class. ``POLICY`` can be one of the following: ``match-empty`` (match empty
    input: pretty illogical, but this is the default for backwards
    compatibility reason), ``match-none`` (fail to match on any input),
    ``error`` (compilation error). Note that there are various ways to
    construct empty class, e.g: [], [^\\x00-\\xFF],
    [\\x00-\\xFF][\\x00-\\xFF].

``-1 --single-pass``
    Deprecated and does nothing (single pass is by default now).
