``-? -h --help``
    Show a short help screen:

``-b --bit-vectors``
    Implies ``-s``. Use bit vectors as well to try to 
    coax better code out of the compiler. Most useful for
    specifications with more than a few keywords (e.g., for most programming
    languages).

``-c --conditions``
    Used for (f)lex-like condition support.

``-d --debug-output``
    Creates a parser that dumps information about
    the current position and the state the parser is in. 
    This is useful for debugging parser issues and states. If you use this
    switch, you need to define a ``YYDEBUG`` macro, which will be called like a
    function with two parameters: ``void YYDEBUG (int state, char current)``.
    The first parameter receives the state or ``-1`` and the second parameter
    receives the input at the current cursor.

``-D --emit-dot``
    Emit Graphviz dot data, which can then be processed
    with e.g., ``dot -Tpng input.dot > output.png``. Please note that
    scanners with many states may crash dot.

``-e --ecb``
    Generate a parser that supports EBCDIC. The generated
    code can deal with any character up to 0xFF. In this mode, ``re2c`` assumes
    an input character size of 1 byte. This switch is incompatible with
    ``-w``, ``-x``, ``-u``, and ``-8``.

``-f --storable-state``
    Generate a scanner with support for storable state.

``-F --flex-syntax``
    Partial support for flex syntax. When this flag
    is active, named definitions must be surrounded by curly braces and
    can be defined without an equal sign and the terminating semicolon.
    Instead, names are treated as direct double quoted strings.

``-g --computed-gotos``
    Generate a scanner that utilizes GCC's
    computed-goto feature. That is, ``re2c`` generates jump tables whenever a
    decision is of certain complexity (e.g., a lot of if conditions would be
    otherwise necessary). This is only usable with compilers that support this feature.
    Note that this implies ``-b`` and that the complexity threshold can be configured 
    using the ``cgoto:threshold`` inplace configuration.

``-i --no-debug-info``
    Do not output ``#line`` information. This is
    useful when you want use a CMS tool with ``re2c``'s output. You might
    want to do this if you do not want to impose re2c as a build requirement
    for your source.

``-o OUTPUT --output=OUTPUT``
    Specify the ``OUTPUT`` file.

``-r --reusable``
    Allows reuse of scanner definitions with ``/*!use:re2c */`` after ``/*!rules:re2c */``.
    In this mode, no ``/*!re2c */`` block and exactly one ``/*!rules:re2c */`` must be present.
    The rules are saved and used by every ``/*!use:re2c */`` block that follows.
    These blocks can contain inplace configurations, especially ``re2c:flags:e``,
    ``re2c:flags:w``, ``re2c:flags:x``, ``re2c:flags:u``, and ``re2c:flags:8``.
    That way it is possible to create the same scanner multiple times for
    different character types, different input mechanisms, or different output mechanisms.
    The ``/*!use:re2c */`` blocks can also contain additional rules that will be appended
    to the set of rules in ``/*!rules:re2c */``.

``-s --nested-ifs``
    Generate nested ifs for some switches. Many
    compilers need this assist to generate better code.

``-t HEADER --type-header=HEADER``
    Create a ``HEADER`` file that
    contains types for the (f)lex-like condition support. This can only be
    activated when ``-c`` is in use.

``-T --tags``
    Enable submatch extraction with tags.
    This option is implied by ``--posix-captures``.

``-P --posix-captures``
    Enable submatch extraction with POSIX-style capturing groups.
    This option implies ``-T --tags``.

``-u --unicode``
    Generate a parser that supports UTF-32. The generated
    code can deal with any valid Unicode character up to 0x10FFFF. In this
    mode, ``re2c`` assumes an input character size of 4 bytes. This switch is
    incompatible with ``-e``, ``-w``, ``-x``, and ``-8``. This implies ``-s``.

``-v --version``
    Show version information.

``-V --vernum``
    Show the version as a number in the MMmmpp (Majorm, minor, patch) format.

``-w --wide-chars``
    Generate a parser that supports UCS-2. The
    generated code can deal with any valid Unicode character up to 0xFFFF.
    In this mode, ``re2c`` assumes an input character size of 2 bytes. This
    switch is incompatible with ``-e``, ``-x``, ``-u``, and ``-8``. This implies
    ``-s``.

``-x --utf-16``
    Generate a parser that supports UTF-16. The generated
    code can deal with any valid Unicode character up to 0x10FFFF. In this
    mode, ``re2c`` assumes an input character size of 2 bytes. This switch is
    incompatible with ``-e``, ``-w``, ``-u``, and ``-8``. This implies ``-s``.

``-8 --utf-8``
    Generate a parser that supports UTF-8. The generated
    code can deal with any valid Unicode character up to 0x10FFFF. In this
    mode, ``re2c`` assumes an input character size of 1 byte. This switch is
    incompatible with ``-e``, ``-w``, ``-x``, and ``-u``.

``--case-insensitive``
    Makes all strings case insensitive. This makes
    "-quoted expressions behave as '-quoted expressions.

``--case-inverted``
    Invert the meaning of single and double quoted
    strings. With this switch, single quotes are case sensitive and double
    quotes are case insensitive.

``--no-generation-date``
    Suppress date output in the generated file.

``--no-optimize-tags``
    Suppress tag optimization (mostly used for debugging).

``--no-version``
    Suppress version output in the generated file.

``--no-generation-date``
    Suppress version output in the generated file.

``--encoding-policy POLICY``
    Specify how ``re2c`` must treat Unicode
    surrogates. ``POLICY`` can be one of the following: ``fail`` (abort with
    an error when a surrogate is encountered), ``substitute`` (silently replace
    surrogates with the error code point 0xFFFD), ``ignore`` (treat surrogates as
    normal code points). By default, ``re2c`` ignores surrogates (for backward
    compatibility). The Unicode standard says that standalone surrogates are
    invalid code points, but different libraries and programs treat them
    differently.

``--input INPUT``
    Specify re2c's input API. ``INPUT`` can be either ``default`` or ``custom``.

``-S --skeleton``
    Instead of embedding re2c-generated code into C/C++
    source, generate a self-contained program for the same DFA. Most useful
    for correctness and performance testing.

``--empty-class POLICY``
    What to do if the user uses an empty character
    class. ``POLICY`` can be one of the following: ``match-empty`` (match empty
    input: pretty illogical, but this is the default for backwards
    compatibility reasons), ``match-none`` (fail to match on any input),
    ``error`` (compilation error). Note that there are various ways to
    construct an empty class, e.g., [], [^\\x00-\\xFF],
    [\\x00-\\xFF][\\x00-\\xFF].

``--dfa-minimization <table | moore>``
    The internal algorithm used by re2c to minimize the DFA (defaults to ``moore``).
    Both the table filling algorithm and the Moore algorithm should produce the same DFA (up to states relabeling).
    The table filling algorithm is much simpler and slower; it serves as a reference implementation.

``--eager-skip``
    This option controls when the generated lexer advances to the next input symbol
    (that is, increments YYCURSOR or invokes YYSKIP).
    By default this happens after transition to the next state,
    but ``--eager-skip`` option allows to override default behavior
    and advance input position immediately after reading input symbol.
    This option is implied by ``--no-lookahead``.

``--dump-nfa``
    Generate .dot representation of NFA and dump it on stderr.

``--dump-dfa-raw``
    Generate .dot representation of DFA under construction and dump it on stderr.

``--dump-dfa-det``
    Generate .dot representation of DFA immediately after determinization and dump it on stderr.

``--dump-dfa-tagopt``
    Generate .dot representation of DFA after tag optimizations and dump it on stderr.

``--dump-dfa-min``
    Generate .dot representation of DFA after minimization and dump it on stderr.

``--dump-adfa``
    Generate .dot representation of DFA after tunneling and dump it on stderr.

``-1 --single-pass``
    Deprecated. Does nothing (single pass is the default now).
