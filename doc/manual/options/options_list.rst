``-? -h --help``
    Show help message.

``-b --bit-vectors``
    Optimize conditional jumps using bit masks. Implies ``-s``.

``-c --conditions --start-conditions``
    Enable support of Flex-like "conditions": multiple interrelated lexers within one block.
    Option ``--start-conditions`` is a legacy alias; use ``--conditions`` instead.

``-d --debug-output``
    Emit ``YYDEBUG`` in the generated code.
    ``YYDEBUG`` should be defined by the user in the form of a void function with two parameters:
    ``state`` (lexer state or -1) and ``symbol`` (current input symbol of type ``YYCTYPE``).

``-D --emit-dot``
    Instead of normal output generate lexer graph in DOT format.
    The output can be converted to PNG with the help of Graphviz (something like ``dot -Tpng -odfa.png dfa.dot``).
    Note that large graphs may crash Graphviz.

``-e --ecb``
    Generate a lexer that reads input in EBCDIC encoding.
    ``re2c`` assumes that character range is 0 -- 0xFF an character size is 1 byte.

``-f --storable-state``
    Generate a lexer which can store its inner state.
    This is useful in push-model lexers which are stopped by an outer program when there is not enough input,
    and then resumed when more input becomes available.
    In this mode users should additionally define
    ``YYGETSTATE ()`` and ``YYSETSTATE (state)`` macros
    and variables ``yych``, ``yyaccept`` and the ``state`` as part of the lexer state.

``-F --flex-syntax``
    Partial support for Flex syntax:
    in this mode named definitions don't need the equal sign and the terminating semicolon,
    and when used they must be surrounded by curly braces.
    Names without curly braces are treated as double-quoted strings.

``-g --computed-gotos``
    Optimize conditional jumps using non-standard "computed goto" extension (must be supported by C/C++ compiler).
    ``re2c`` generates jump tables only in complex cases with a lot of conditional branches.
    Complexity threshold can be configured with ``cgoto:threshold`` configuration.
    This option implies ``-b``.

``-i --no-debug-info``
    Do not output ``#line`` information.
    This is useful when the generated code is tracked by some version control system.

``-o OUTPUT --output=OUTPUT``
    Specify the ``OUTPUT`` file.

``-r --reusable``
    Allows reuse of ``re2c`` rules with ``/*!rules:re2c */`` and ``/*!use:re2c */`` blocks.
    In this mode simple ``/*!re2c */`` blocks are not allowed
    and exactly one ``/*!rules:re2c */`` block must be present.
    The rules are saved and used by every ``/*!use:re2c */`` block that follows (which may add rules of their own).
    This option allows to reuse the same set of rules with different configurations.

``-s --nested-ifs``
    Use nested ``if`` statements instead of ``switch`` statements in conditional jumps.
    This usually results in more efficient code with non-optimizing C/C++ compilers.

``-t HEADER --type-header=HEADER``
    Generate a ``HEADER`` file that contains enum with condition names.
    Requires ``-c`` option.

``-T --tags``
    Enable submatch extraction with tags.

``-P --posix-captures``
    Enable submatch extraction with POSIX-style capturing groups.

``-u --unicode``
    Generate a lexer that reads input in UTF-32 encoding.
    ``re2c`` assumes that character range is 0 -- 0x10FFFF and character size is 4 bytes.
    Implies ``-s``.

``-v --version``
    Show version information.

``-V --vernum``
    Show version information in ``MMmmpp`` format (major, minor, patch).

``-w --wide-chars``
    Generate a lexer that reads input in UCS-2 encoding.
    ``re2c`` assumes that character range is 0 -- 0xFFFF and character size is 2 bytes.
    Implies ``-s``.

``-x --utf-16``
    Generate a lexer that reads input in UTF-16 encoding.
    ``re2c`` assumes that character range is 0 -- 0x10FFFF and character size is 2 bytes.
    Implies ``-s``.

``-8 --utf-8``
    Generate a lexer that reads input in UTF-8 encoding.
    ``re2c`` assumes that character range is 0 -- 0x10FFFF and character size is 1 byte.

``--case-insensitive``
    Treat single-quoted and double-quoted strings as case-insensitive.

``--case-inverted``
    Invert the meaning of single-quoted and double-quoted strings:
    treat single-quoted strings as case-sensitive and double-quoted strings as case-insensitive.

``--no-generation-date``
    Suppress date output in the generated file.

``--no-lookahead``
    Use TDFA(0) instead of TDFA(1).
    This option only has effect with ``--tags`` or ``--posix-captures`` options.

``--no-optimize-tags``
    Suppress optimization of tag variables (useful for debugging or benchmarking).

``--no-version``
    Suppress version output in the generated file.

``--encoding-policy POLICY``
    Define the way ``re2c`` treats Unicode surrogates.
    ``POLICY`` can be one of the following: ``fail`` (abort with an error when a surrogate is encountered),
    ``substitute`` (silently replace surrogates with the error code point 0xFFFD),
    ``ignore`` (default, treat surrogates as normal code points).
    The Unicode standard says that standalone surrogates are invalid,
    but real-world libraries and programs behave in different ways.

``--input INPUT``
    Specify ``re2c`` input API. ``INPUT`` can be either ``default`` or ``custom`` (enables the use of generic API).

``-S --skeleton``
    Ignore user-defined interface code and generate a self-contained "skeleton" program.
    Additionally, generate input files with strings derived from the regular grammar
    and compressed match results that are used to verify "skeleton" behavior on all inputs.
    This option is useful for finding bugs in optimizations and code generation.

``--empty-class POLICY``
    Define the way ``re2c`` treats empty character classes.
    ``POLICY`` can be one of the following: ``match-empty`` (match empty input: illogical, but default behavior for backwards compatibility reasons),
    ``match-none`` (fail to match on any input),
    ``error`` (compilation error).

``--dfa-minimization ALGORITHM``
    The internal algorithm used by re2c to minimize the DFA.
    ``ALGORITHM`` can be either ``moore`` (Moore algorithm, the default) or ``table`` (table filling algorithm).
    Both algorithms should produce the same DFA up to states relabeling;
    table filling is much slower and serves as a reference implementation.

``--eager-skip``
    Make the generated lexer advance the input position "eagerly":
    immediately after reading input symbol.
    By default this happens after transition to the next state.
    Implied by ``--no-lookahead``.

``--dump-nfa``
    Generate representation of NFA in DOT format and dump it on stderr.

``--dump-dfa-raw``
    Generate representation of DFA in DOT format under construction and dump it on stderr.

``--dump-dfa-det``
    Generate representation of DFA in DOT format immediately after determinization and dump it on stderr.

``--dump-dfa-tagopt``
    Generate representation of DFA in DOT format after tag optimizations and dump it on stderr.

``--dump-dfa-min``
    Generate representation of DFA in DOT format after minimization and dump it on stderr.

``--dump-adfa``
    Generate representation of DFA in DOT format after tunneling and dump it on stderr.

``-1 --single-pass``
    Deprecated. Does nothing (single pass is the default now).
