Changelog
=========

----
2.1x
----

2.1.1 (2021-03-27)
~~~~~~~~~~~~~~~~~~

- Added missing CMakeLists.txt to release tarballs
  (`#346 <https://github.com/skvadrik/re2c/issues/346>`_).

2.1 (2021-03-26)
~~~~~~~~~~~~~~~~

- Added GitHub Actions CI for Linux, macOS and Windows and fixed numerous build
  issues on those platforms (thanks to
  `Serghei Iakovlev <https://github.com/sergeyklay>`_).

- Added benchmarks for submatch extraction in lexer generators (ragel vs.
  kleenex vs. re2c with TDFA(0), TDFA(1) or sta-DFA algorithms).

  + New Autotools (configure) options: ``--enable-benchmarks``,
    ``--enable-benchmarks-regenerate``

  + New CMake options: ``-DRE2C_BUILD_BENCHMARKS``, ``-DRE2C_REGEN_BENCHMARKS``

  + New `json2pgfplot.py
    <https://github.com/skvadrik/re2c/blob/master/benchmarks/json2pgfplot.py>`_
    script that converts benchmark results in JSON to a PDF with bar charts

- Added option ``--depfile <filename>`` to generate build dependency files
  (allows to track ``/*!include:re2c*/`` dependencies in the build system).

- Added option ``--fixed-tags <none | all | toplevel>`` and improved fixed-tag
  optimization to work with nested tags.

- Added lzip to the distribution tarballs.

- Added registerless-TDFA algorithm in the experimental libre2c library.

- Explicitly disallowed invalid configuration when ``-f``, ``--storable-state``
  option is used, but ``YYFILL`` is disabled
  (`#306 <https://github.com/skvadrik/re2c/issues/306>`_).

- Fixed bug in UTF-8 decode for 4-bytes rune
  (`#307 <https://github.com/skvadrik/re2c/pull/307>`_, thanks to
  `Satoshi Yasushima <https://github.com/s-yasu>`_).

- Fixed bugs in rare cases of the end-of-input rule ``$`` usage
  (`277f0295 <https://github.com/skvadrik/re2c/commit/277f0295fc77a2dad3b9838e45f787319b54a25f>`_,
  `68611a57 <https://github.com/skvadrik/re2c/commit/68611a57a9683c05801255b35ba6217b91391dd8>`_
  and `a9d582f9 <https://github.com/skvadrik/re2c/commit/a9d582f9d2a6d123aa55f3b8b73076aae7cb5616>`_).

- Optimized ``--skeleton`` generation time.

- Renamed internal option ``--dfa`` to ``--nested-negative-tags``.

- Updated documentation for end of input handling and submatch extraction.

----
2.0x
----

2.0.3 (2020-08-22)
~~~~~~~~~~~~~~~~~~

- Fix issues when building re2c as a CMake subproject
  (`#302 <https://github.com/skvadrik/re2c/pull/302>`_:
  Using CMake add_subdirectory fails)

- Final corrections in the SIMPA article "RE2C: A lexer generator based on
  lookahead-TDFA", https://doi.org/10.1016/j.simpa.2020.100027

2.0.2 (2020-08-08)
~~~~~~~~~~~~~~~~~~

- Enable re2go building by default.

- Package CMake files into release tarball.

2.0.1 (2020-07-29)
~~~~~~~~~~~~~~~~~~

- Updated version for CMake build system (forgotten in release 2.0).

- Added a short article about re2c for the Software Impacts journal.

2.0 (2020-07-20)
~~~~~~~~~~~~~~~~

- Added new code generation backend for Go and a new ``re2go`` program
  (`#272 <https://github.com/skvadrik/re2c/issues/272>`_: Go support).
  Added option ``--lang <c | go>``.

- Added CMake build system as an alternative to Autotools
  (`#275 <https://github.com/skvadrik/re2c/pull/275>`_:
  Add a CMake build system (thanks to ligfx),
  `#244 <https://github.com/skvadrik/re2c/issues/244>`_: Switching to CMake).

- Changes in generic API:

  + Removed primitives ``YYSTAGPD`` and ``YYMTAGPD``.
  + Added primitives ``YYSHIFT``, ``YYSHIFTSTAG``, ``YYSHIFTMTAG``
    that allow to express fixed tags in terms of generic API.
  + Added configurations ``re2c:api:style`` and ``re2c:api:sigil``.
  + Added named placeholders in interpolated configuration strings.

- Changes in reuse mode (``-r, --reuse`` option):

  + Do not reset API-related configurations in each `use:re2c` block
    (`#291 <https://github.com/skvadrik/re2c/issues/291>`_:
    Defines in rules block are not propagated to use blocks).
  + Use block-local options instead of last block options.
  + Do not accumulate options from rules/reuse blocks in whole-program options.
  + Generate non-overlapping YYFILL labels for reuse blocks.
  + Generate start label for each reuse block in storable state mode.

- Changes in start-conditions mode (``-c, --start-conditions`` option):

  + Allow to use normal (non-conditional) blocks in `-c` mode
    (`#263 <https://github.com/skvadrik/re2c/issues/263>`_:
    allow mixing conditional and non-conditional blocks with -c,
    `#296 <https://github.com/skvadrik/re2c/issues/296>`_:
    Conditions required for all lexers when using '-c' option).
  + Generate condition switch in every re2c block
    (`#295 <https://github.com/skvadrik/re2c/issues/295>`_:
    Condition switch generated for only one lexer per file).

- Changes in the generated labels:

  + Use ``yyeof`` label prefix instead of ``yyeofrule``.
  + Use ``yyfill`` label prefix instead of ``yyFillLabel``.
  + Decouple start label and initial label (affects label numbering).

- Removed undocumented configuration ``re2c:flags:o``, ``re2c:flags:output``.

- Changes in ``re2c:flags:t``, ``re2c:flags:type-header`` configuration:
  filename is now relative to the output file directory.

- Added option ``--case-ranges`` and configuration ``re2c:flags:case-ranges``.

- Extended fixed tags optimization for the case of fixed-counter repetition.

- Fixed bugs related to EOF rule:

  + `#276 <https://github.com/skvadrik/re2c/issues/276>`_:
    Example 01_fill.re in docs is broken
  + `#280 <https://github.com/skvadrik/re2c/issues/280>`_:
    EOF rules with multiple blocks
  + `#284 <https://github.com/skvadrik/re2c/issues/284>`_:
    mismatched YYBACKUP and YYRESTORE
    (Add missing fallback states with EOF rule)

- Fixed miscellaneous bugs:

  + `#286 <https://github.com/skvadrik/re2c/issues/286>`_:
    Incorrect submatch values with fixed-length trailing context.
  + `#297 <https://github.com/skvadrik/re2c/issues/297>`_:
    configure error on ubuntu 18.04 / cmake 3.10

- Changed bootstrap process (require explicit configuration flags and a path to
  re2c executable to regenerate the lexers).

- Added internal options ``--posix-prectable <naive | complex>``.

- Added debug option ``--dump-dfa-tree``.

- Major revision of the paper "Efficient POSIX submatch extraction on NFA".

----
1.3x
----

1.3 (2019-12-14)
~~~~~~~~~~~~~~~~

- Added option: ``--stadfa``.

- Added warning: ``-Wsentinel-in-midrule``.

- Added generic API primitives:

  + ``YYSTAGPD``
  + ``YYMTAGPD``

- Added configurations:

  + ``re2c:sentinel = 0;``
  + ``re2c:define:YYSTAGPD = "YYSTAGPD";``
  + ``re2c:define:YYMTAGPD = "YYMTAGPD";``

- Worked on reproducible builds
  (`#258 <https://github.com/skvadrik/re2c/pull/258>`_:
  Make the build reproducible).

----
1.2x
----

1.2.1 (2019-08-11)
~~~~~~~~~~~~~~~~~~

- Fixed bug `#253 <https://github.com/skvadrik/re2c/issues/253>`_:
  re2c should install unicode_categories.re somewhere.

- Fixed bug `#254 <https://github.com/skvadrik/re2c/issues/254>`_:
  Turn off re2c:eof = 0.

1.2 (2019-08-02)
~~~~~~~~~~~~~~~~

- Added EOF rule ``$`` and configuration ``re2c:eof``.

- Added ``/*!include:re2c ... */`` directive and ``-I`` option.

- Added ``/*!header:re2c:on*/`` and ``/*!header:re2c:off*/`` directives.

- Added ``--input-encoding <ascii | utf8>`` option.

  + `#237 <https://github.com/skvadrik/re2c/issues/237>`_:
    Handle non-ASCII encoded characters in regular expressions
  + `#250 <https://github.com/skvadrik/re2c/issues/250>`_
    UTF8 enoding

- Added include file with a list of definitions for Unicode character classes.

  + `#235 <https://github.com/skvadrik/re2c/issues/235>`_:
    Unicode character classes

- Added ``--location-format <gnu | msvc>`` option.

  + `#195 <https://github.com/skvadrik/re2c/issues/195>`_:
    Please consider using Gnu format for error messages

- Added ``--verbose`` option that prints "success" message if re2c exits
  without errors.

- Added configurations for options:

  + ``-o --output`` (specify output file)
  + ``-t --type-header`` (specify header file)

- Removed configurations for internal/debug options.

- Extended ``-r`` option: allow to mix multiple ``/*!rules:re2c*/``,
  ``/*!use:re2c*/`` and ``/*!re2c*/`` blocks.

  + `#55 <https://github.com/skvadrik/re2c/issues/55>`_:
    allow standard re2c blocks in reuse mode

- Fixed ``-F --flex-support`` option: parsing and operator precedence.

  + `#229 <https://github.com/skvadrik/re2c/issues/229>`_:
    re2c option -F (flex syntax) broken
  + `#242 <https://github.com/skvadrik/re2c/issues/242>`_:
    Operator precedence with --flex-syntax is broken

- Changed difference operator ``/`` to apply before encoding expansion of
  operands.

  + `#236 <https://github.com/skvadrik/re2c/issues/236>`_:
    Support range difference with variable-length encodings

- Changed output generation of output file to be atomic.

  + `#245 <https://github.com/skvadrik/re2c/issues/245>`_:
    re2c output is not atomic

- Authored research paper "Efficient POSIX Submatch Extraction on NFA"
  together with Dr Angelo Borsotti.

- Added experimental libre2c library (``--enable-libs`` configure option) with
  the following algorithms:

  + TDFA with leftmost-greedy disambiguation
  + TDFA with POSIX disambiguation (Okui-Suzuki algorithm)
  + TNFA with leftmost-greedy disambiguation
  + TNFA with POSIX disambiguation (Okui-Suzuki algorithm)
  + TNFA with lazy POSIX disambiguation (Okui-Suzuki algorithm)
  + TNFA with POSIX disambiguation (Kuklewicz algorithm)
  + TNFA with POSIX disambiguation (Cox algorithm)

- Added debug subsystem (``--enable-debug`` configure option) and new debug
  options:

  + ``-dump-cfg`` (dump control flow graph of tag variables)
  + ``-dump-interf`` (dump interference table of tag variables)
  + ``-dump-closure-stats`` (dump epsilon-closure statistics)

- Added internal options:

  + ``--posix-closure <gor1 | gtop>`` (switch between shortest-path algorithms
    used for the construction of POSIX closure)

- Fixed a number of crashes found by American Fuzzy Lop fuzzer:

  + `#226 <https://github.com/skvadrik/re2c/issues/226>`_,
    `#227 <https://github.com/skvadrik/re2c/issues/227>`_,
    `#228 <https://github.com/skvadrik/re2c/issues/228>`_,
    `#231 <https://github.com/skvadrik/re2c/issues/231>`_,
    `#232 <https://github.com/skvadrik/re2c/issues/232>`_,
    `#233 <https://github.com/skvadrik/re2c/issues/233>`_,
    `#234 <https://github.com/skvadrik/re2c/issues/234>`_,
    `#238 <https://github.com/skvadrik/re2c/issues/238>`_

- Fixed handling of newlines:

  + correctly parse multi-character newlines CR LF in ``#line`` directives
  + consistently convert all newlines in the generated file to Unix-style LF

- Changed default tarball format from .gz to .xz.

  + `#221 <https://github.com/skvadrik/re2c/issues/221>`_:
    big source tarball

- Fixed a number of other bugs and resolved issues:

  + `#2 <https://github.com/skvadrik/re2c/issues/2>`_: abort
  + `#6 <https://github.com/skvadrik/re2c/issues/6>`_: segfault
  + `#10 <https://github.com/skvadrik/re2c/issues/10>`_:
    lessons/002_upn_calculator/calc_002 doesn't produce a useful example program
  + `#44 <https://github.com/skvadrik/re2c/issues/44>`_:
    Access violation when translating the attached file
  + `#49 <https://github.com/skvadrik/re2c/issues/49>`_:
    wildcard state \000 rules makes lexer behave weard
  + `#98 <https://github.com/skvadrik/re2c/issues/98>`_:
    Transparent handling of #line directives in input files
  + `#104 <https://github.com/skvadrik/re2c/issues/104>`_:
    Improve const-correctness
  + `#105 <https://github.com/skvadrik/re2c/issues/105>`_:
    Conversion of pointer parameters into references
  + `#114 <https://github.com/skvadrik/re2c/issues/114>`_:
    Possibility of fixing bug 2535084
  + `#120 <https://github.com/skvadrik/re2c/issues/120>`_:
    condition consisting of default rule only is ignored
  + `#167 <https://github.com/skvadrik/re2c/issues/167>`_:
    Add word boundary support
  + `#168 <https://github.com/skvadrik/re2c/issues/168>`_:
    Wikipedia's article on re2c
  + `#180 <https://github.com/skvadrik/re2c/issues/180>`_:
    Comment syntax?
  + `#182 <https://github.com/skvadrik/re2c/issues/182>`_:
    yych being set by YYPEEK () and then not used
  + `#196 <https://github.com/skvadrik/re2c/issues/196>`_:
    Implicit type conversion warnings
  + `#198 <https://github.com/skvadrik/re2c/issues/198>`_:
    no match for ‘operator!=’ in ‘i != std::vector<_Tp, _Alloc>::rend() [with _Tp = re2c::bitmap_t, _Alloc = std::allocator<re2c::bitmap_t>]()’
  + `#210 <https://github.com/skvadrik/re2c/issues/210>`_:
    How to build re2c in windows?
  + `#215 <https://github.com/skvadrik/re2c/issues/215>`_:
    A memory read overrun issue in s_to_n32_unsafe.cc
  + `#220 <https://github.com/skvadrik/re2c/issues/220>`_:
    src/dfa/dfa.h: simplify constructor to avoid g++-3.4 bug
  + `#223 <https://github.com/skvadrik/re2c/issues/223>`_:
    Fix typo
  + `#224 <https://github.com/skvadrik/re2c/issues/224>`_:
    src/dfa/closure_posix.cc: pack() tweaks
  + `#225 <https://github.com/skvadrik/re2c/issues/225>`_:
    Documentation link is broken in libre2c/README
  + `#230 <https://github.com/skvadrik/re2c/issues/230>`_:
    Changes for upcoming Travis' infra migration
  + `#239 <https://github.com/skvadrik/re2c/issues/239>`_:
    Push model example has wrong re2c invocation, breaks guide
  + `#241 <https://github.com/skvadrik/re2c/issues/241>`_:
    Guidance on how to use re2c for full-duplex command & response protocol
  + `#243 <https://github.com/skvadrik/re2c/issues/243>`_:
    A code generated for period (.) requires 4 bytes
  + `#246 <https://github.com/skvadrik/re2c/issues/246>`_:
    Please add a license to this repo
  + `#247 <https://github.com/skvadrik/re2c/issues/247>`_:
    Build failure on current Cygwin, probably caused by force-fed c++98 mode
  + `#248 <https://github.com/skvadrik/re2c/issues/248>`_:
    distcheck still looks for README
  + `#251 <https://github.com/skvadrik/re2c/issues/251>`_:
    Including what you use is find, but not without inclusion guards

- Updated documentation and website.


----
1.1x
----

1.1.1 (2018-08-30)
~~~~~~~~~~~~~~~~~~

- Fixed bug `#211 <https://github.com/skvadrik/re2c/issues/211>`_:
  re2c ``-V`` throws ``std::out_of_range`` (version to vernum conversion).

1.1 (2018-08-27)
~~~~~~~~~~~~~~~~

- Replaced Kuklewicz POSIX disambiguation algorithm with Okui algorithm.
- Optimized GOR1 algorithm (computation of tagged epsilon-closure).
- Added option ``--conditions`` (an alias for ``-c --start-conditions``).
- Fixed bug `#201 <https://github.com/skvadrik/re2c/issues/201>`_:
  Bugs with option: ``re2c:flags:no-debug-info``.
- Reworked first part of TDFA paper.

----
1.0x
----

1.0.3 (2017-11-08)
~~~~~~~~~~~~~~~~~~

- Fixed bug `#198 <https://github.com/skvadrik/re2c/issues/198>`_:
  build error on MacOS with GCC-4.2.1

1.0.2 (2017-08-26)
~~~~~~~~~~~~~~~~~~

- Fixed bug `#194 <https://github.com/skvadrik/re2c/issues/194>`_:
  Build with ``--enable-docs``
- Updated documentation.

1.0.1 (2017-08-11)
~~~~~~~~~~~~~~~~~~

- Fixed bug `#193 <https://github.com/skvadrik/re2c/issues/193>`_:
  1.0 build failure on macOS: error: calling a private constructor of class
  're2c::Rule'

- Added paper "Tagged Deterministic Finite Automata with Lookahead" to the
  distribution files.

1.0 (2017-08-11)
~~~~~~~~~~~~~~~~

- Added options:

  + ``-P --posix-captures`` (POSIX-compliant capturing groups)
  + ``-T --tags`` (standalone tags with leftmost greedy disambiguation)
  + ``--no-lookahead``
  + ``--no-optimize-tags``
  + ``--eager-skip``
  + ``--dump-nfa``
  + ``--dump-dfa-raw``
  + ``--dump-dfa-det``
  + ``--dump-dfa-tagopt``
  + ``--dump-dfa-min``
  + ``--dump-adfa``

- Added new syntax:

  + ``@<stag>``
  + ``#<mtag>``

- Added new directives:

  + ``/*!stags:re2c ... */``
  + ``/*!mtags:re2c ... */``
  + ``/*!maxnmatch:re2c ... */``

- Added new API:

  + ``YYSTAGN (t)``
  + ``YYSTAGP (t)``
  + ``YYMTAGN (t)``
  + ``YYMTAGP (t)``
  + ``YYRESTORETAG (t)``
  + ``YYMAXNMATCH``
  + ``yynmatch``
  + ``yypmatch``

- Added inplace confgurations:

  + ``re2c:define:YYSTAGN``
  + ``re2c:define:YYSTAGP``
  + ``re2c:define:YYMTAGN``
  + ``re2c:define:YYMTAGP``
  + ``re2c:define:YYRESTORETAG``
  + ``re2c:flags:8`` or ``re2c:flags:utf-8````
  + ``re2c:flags:b`` or ``re2c:flags:bit-vectors``
  + ``re2c:flags:case-insensitive``
  + ``re2c:flags:case-inverted``
  + ``re2c:flags:d`` or ``re2c:flags:debug-output``
  + ``re2c:flags:dfa-minimization``
  + ``re2c:flags:eager-skip``
  + ``re2c:flags:e`` or ``re2c:flags:ecb``
  + ``re2c:flags:empty-class``
  + ``re2c:flags:encoding-policy``
  + ``re2c:flags:g`` or ``re2c:flags:computed-gotos``
  + ``re2c:flags:i`` or ``re2c:flags:no-debug-info``
  + ``re2c:flags:input``
  + ``re2c:flags:lookahead``
  + ``re2c:flags:optimize-tags``
  + ``re2c:flags:P`` or ``re2c:flags:posix-captures``
  + ``re2c:flags:s`` or ``re2c:flags:nested-ifs``
  + ``re2c:flags:T`` or ``re2c:flags:tags``
  + ``re2c:flags:u`` or ``re2c:flags:unicode``
  + ``re2c:flags:w`` or ``re2c:flags:wide-chars``
  + ``re2c:flags:x`` or ``re2c:flags:utf-16``
  + ``re2c:tags:expression``
  + ``re2c:tags:prefix``

- Added warning ``-Wnondeterministic-tags``.

- Added fuzz-testing scripts

- Added paper "Tagged Deterministic Finite Automata with Lookahead".

- Fixed bugs:

  + `#121 <https://github.com/skvadrik/re2c/issues/121>`_:
    trailing contexts are fundamentally broken
  + `#135 <https://github.com/skvadrik/re2c/issues/135>`_:
    In installation ``make check`` give syntax error
  + `#137 <https://github.com/skvadrik/re2c/issues/137>`_:
    run_tests.sh fail when running configure script with absolute path
  + `#138 <https://github.com/skvadrik/re2c/issues/138>`_:
    website improvement
  + `#141 <https://github.com/skvadrik/re2c/issues/141>`_:
    Tests under Windows
  + `#142 <https://github.com/skvadrik/re2c/issues/142>`_:
    segvault with null terminated input
  + `#145 <https://github.com/skvadrik/re2c/issues/145>`_:
    Values for enum YYCONDTYPE are not generated when default rules with conditions are used
  + `#147 <https://github.com/skvadrik/re2c/issues/147>`_:
    Please add symbol name to "can't find symbol" error message
  + `#152 <https://github.com/skvadrik/re2c/issues/152>`_:
    Line number in #line directive after enum YYCONDTYPE is 0-based
  + `#156 <https://github.com/skvadrik/re2c/issues/156>`_:
    Build with Visual Studio 14 2015: symbol name conflict
  + `#158 <https://github.com/skvadrik/re2c/issues/158>`_:
    Inconsistent forward declaration of struct/class vs definition
  + `#160 <https://github.com/skvadrik/re2c/issues/160>`_:
    Open text files with "wb" causes issues on Windows
  + `#162 <https://github.com/skvadrik/re2c/issues/162>`_:
    Reading files with "rb" causes issues in Windows
  + `#165 <https://github.com/skvadrik/re2c/issues/165>`_:
    Trailing context consumed if initial expression matches it
  + `#176 <https://github.com/skvadrik/re2c/issues/176>`_:
    re2c help message is too wide for most terminals
  + `#184 <https://github.com/skvadrik/re2c/issues/184>`_:
    Small documentation issue
  + `#186 <https://github.com/skvadrik/re2c/issues/186>`_:
    Difference operator sometimes doesn't work with utf-8

- Merged pull requests:

  + `#131 <https://github.com/skvadrik/re2c/issues/131>`_:
    Use bash-specific ``[[`` builtin
  + `#136 <https://github.com/skvadrik/re2c/issues/136>`_:
    Added basic support for travis-ci.org integration
  + `#171 <https://github.com/skvadrik/re2c/issues/171>`_:
    Typo fix
  + `#172 <https://github.com/skvadrik/re2c/issues/172>`_:
    Grammar fixes in the docs
  + `#173 <https://github.com/skvadrik/re2c/issues/173>`_:
    Grammar fixes in the manpage
  + `#174 <https://github.com/skvadrik/re2c/issues/174>`_:
    more documentation fixes
  + `#175 <https://github.com/skvadrik/re2c/issues/175>`_:
    more manpage fixes
  + `#177 <https://github.com/skvadrik/re2c/issues/177>`_:
    sync --help output w/ manpage
  + `#178 <https://github.com/skvadrik/re2c/issues/178>`_:
    Moves rts used in the manpage to master
  + `#179 <https://github.com/skvadrik/re2c/issues/179>`_:
    compose manpage out of rsts from gh-pages-gen
  + `#189 <https://github.com/skvadrik/re2c/issues/189>`_:
    Typo fix and small grammatical change
  + `#191 <https://github.com/skvadrik/re2c/issues/191>`_:
    Makefile.am: create target directory before writing into it


-----
0.16x
-----

0.16 (2016-01-21)
~~~~~~~~~~~~~~~~~

- Fixed bug `#127 <https://github.com/skvadrik/re2c/issues/127>`_:
  code generation error with wide chars and bitmaps (omitted ``goto`` statement)
- Added DFA minimization and option ``--dfa-minimization <table | moore>``
- Fixed bug `#128 <https://github.com/skvadrik/re2c/issues/128>`_:
  very slow DFA construction (resulting in a very large DFA)
- Fixed bug `#132 <https://github.com/skvadrik/re2c/issues/132>`_:
  test failure on big endian archs with 0.15.3


-----
0.15x
-----

0.15.3 (2015-12-02)
~~~~~~~~~~~~~~~~~~~

- Fixed bugs and applied patches:

  + `#122 <https://github.com/skvadrik/re2c/issues/122>`_:
    clang does not compile re2c 0.15.x
  + `#124 <https://github.com/skvadrik/re2c/issues/124>`_:
    Get rid of UINT32_MAX and friends
  + `#125 <https://github.com/skvadrik/re2c/issues/125>`_:
    [OS X] git reports changes not staged for commit in newly cloned repository

- Added option ``--no-version`` that allows to omit version information.
- Reduced memory and time consumed with ``-Wundefined-control-flow``.
- Improved coverage of input data generated with ``-S --skeleton``.


0.15.2 (2015-11-23)
~~~~~~~~~~~~~~~~~~~

- Fixed build system: lexer depends on bison-generated header
  (Gentoo bug: https://bugs.gentoo.org/show_bug.cgi?id=566620)


0.15.1 (2015-11-22)
~~~~~~~~~~~~~~~~~~~

- Fixed test failures caused by locale-sensitive 'sort'.


0.15 (2015-11-22)
~~~~~~~~~~~~~~~~~

- Updated website http://re2c.org:

  + added examples
  + updated docs
  + added news
  + added web feed (Atom 1.0)

- Added options:

  + ``-S, --skeleton``
  + ``--empty-class <match-empty | match-none | error>``

- Added warnings:

  + ``-W``
  + ``-Werror``
  + ``-W<warning>``
  + ``-Wno-<warning>``
  + ``-Werror-<warning>``
  + ``-Wno-error-<warning>``

- Added specific warnings:

  + ``-Wundefined-control-flow``
  + ``-Wunreachable-rules``
  + ``-Wcondition-order``
  + ``-Wuseless-escape``
  + ``-Wempty-character-class``
  + ``-Wswapped-range``
  + ``-Wmatch-empty-string``

- Fixed options:

  + ``--`` (interpret remaining arguments as non-options)

- Deprecated options:

  + ``-1 --single-pass`` (single pass is the default now)

- Reduced size of the generated ``.dot`` files.

- Fixed bugs:

  + `#27 <https://github.com/skvadrik/re2c/issues/27>`_:
    re2c crashes reading files containing ``%{ %}`` (patch by Rui)
  + `#51 <https://github.com/skvadrik/re2c/issues/51>`_:
    default rule doesn't work in reuse mode
  + `#52 <https://github.com/skvadrik/re2c/issues/52>`_:
    eliminate multiple passes
  + `#59 <https://github.com/skvadrik/re2c/issues/59>`_:
    bogus ``yyaccept`` in ``-c`` mode
  + `#60 <https://github.com/skvadrik/re2c/issues/60>`_:
    redundant use of ``YYMARKER``
  + `#61 <https://github.com/skvadrik/re2c/issues/61>`_:
    empty character class ``[]`` matches empty string
  + `#115 <https://github.com/skvadrik/re2c/issues/115>`_:
    flex-style named definitions cause ambiguity in re2c grammar
  + `#119 <https://github.com/skvadrik/re2c/issues/119>`_:
    ``-f`` with ``-b``/``-g`` generates incorrect dispatch on fill labels
  + `#116 <https://github.com/skvadrik/re2c/issues/116>`_:
    empty string with non-empty trailing context consumes code units

- Added test options:

  + ``-j``, ``-j <N>`` (run tests in ``N`` threads, defaults to the number of CPUs)
  + ``--wine`` (test windows builds using ``wine``)
  + ``--skeleton`` (generate skeleton programs, compile and execute them)
  + ``--keep-tmp-files`` (don't delete intermediate files for successful tests)

- Updated build system:

  + support out of source builds
  + support ```make distcheck```
  + added ```make bootstrap``` (rebuild re2c after building with precompiled
    ``.re`` files)
  + added ```make tests``` (run tests with ``-j``)
  + added ```make vtests``` (run tests with ``--valgrind -j``)
  + added ```make wtests``` (run tests with ``--wine -j 1``)
  + added Autoconf tests for ``CXXFLAGS``. By default try the following options:
    ``-W -Wall -Wextra -Weffc++ -pedantic -Wformat=2 -Wredundant-decls
    -Wsuggest-attribute=format -Wconversion -Wsign-conversion -O2 -Weverything``),
    respect user-defined ``CXXFLAGS``
  + support Mingw builds: ```configure -host i686-w64-mingw32```
  + structured source files
  + removed old MSVC files

- Moved development to github (https://github.com/skvadrik/re2c),
  keep a mirror on sourceforge.


-----
0.14x
-----

0.14.3 (2015-05-20)
~~~~~~~~~~~~~~~~~~~

- applied patch `#27 <https://github.com/skvadrik/re2c/issues/27>`_:
  re2c crashes reading files containing %{ %}
- dropped distfiles for MSVC (they are broken anyway)

0.14.2 (2015-03-25)
~~~~~~~~~~~~~~~~~~~

- fixed `#57 <https://github.com/skvadrik/re2c/issues/57>`_:
  Wrong result only if another rule is present

0.14.1 (2015-02-27)
~~~~~~~~~~~~~~~~~~~

- fixed `#55 <https://github.com/skvadrik/re2c/issues/55>`_:
  re2c-0.14: re2c -V outputs null byte

0.14 (2015-02-23)
~~~~~~~~~~~~~~~~~

- Added generic input API

  + `#21 <https://github.com/skvadrik/re2c/issues/21>`_:
    Support to configure how re2c code interfaced with the symbol buffer?"

- fixed `#46 <https://github.com/skvadrik/re2c/issues/46>`_:
  re2c generates an infinite loop, depends on existence of previous parser
- fixed `#47 <https://github.com/skvadrik/re2c/issues/47>`_:
  Dot output label escaped characters


-----
0.13x
-----

0.13.7.5 (2014-08-22)
~~~~~~~~~~~~~~~~~~~~~

- Fixed `Gentoo bug with PHP lexer <https://bugs.gentoo.org/show_bug.cgi?id=518904>`_

0.13.7.4 (2014-07-29)
~~~~~~~~~~~~~~~~~~~~~

- Enabled ``make docs`` only if configured with ``--enable-docs``
- Disallowed to use yacc/byacc instead of bison to build parser
- Removed non-portable sed feature in script that runs tests

0.13.7.3 (2014-07-27)
~~~~~~~~~~~~~~~~~~~~~

- Fixed CXX warning
- Got rid of asciidoc build-time dependency

0.13.7.2 (2014-07-27)
~~~~~~~~~~~~~~~~~~~~~

- Included man page into dist, respect users CXXFLAGS.

0.13.7.1 (2014-07-26)
~~~~~~~~~~~~~~~~~~~~~

- Added missing files to tarball

0.13.7 (2014-07-25)
~~~~~~~~~~~~~~~~~~~

- Added UTF-8 support
- Added UTF-16 support
- Added default rule
- Added option to control ill-formed Unicode

0.13.6 (2013-07-04)
~~~~~~~~~~~~~~~~~~~

- Fixed #2535084 uint problem with Sun C 5.8
- #3308400: allow Yacc-style ``%{`` code brackets ``}%``
- #2506253: allow C++ ``//`` comments
- Fixed inplace configuration in ``-e`` mode.
- Applied #2482572 Typos in error messages.
- Applied #2482561 Error in manual section on ``-r`` mode.
- Fixed #2478216 Wrong ``start_label`` in ``-c`` mode.
- Fixed #2186718 Unescaped backslash in file name of ``#line`` directive.
- Fixed #2102138 Duplicate case labels on EBCDIC.
- Fixed #2088583 Compile problem on AIX.
- Fixed #2038610 Ebcdic problem.
- improve dot support: make char intervals (e.g. ``[A-Z]``) instead of one edge
  per char

0.13.5 (2008-05-25)
~~~~~~~~~~~~~~~~~~~

- Fixed #1952896 Segfault in ``re2c::Scanner::scan``.
- Fixed #1952842 Regression.

0.13.4 (2008-04-05)
~~~~~~~~~~~~~~~~~~~

- Added transparent handling of ``#line`` directives in input files.
- Added ``re2c:yyfill:check`` inplace configuration.
- Added ``re2c:define:YYSETSTATE:naked`` inplace configuration.
- Added ``re2c:flags:w`` and ``re2c:flags:u`` inplace configurations.
- Added the ability to add rules in ``use:re2c`` blocks.
- Changed ``-r`` flag to accept only ``rules:re2c`` and ``use:re2c`` blocks.

0.13.3 (2008-03-14)
~~~~~~~~~~~~~~~~~~~

- Added ``-r`` flag to allow reuse of scanner definitions.
- Added ``-F`` flag to support flex syntax in rules.
- Fixed SEGV in scanner that occurs with very large blocks.
- Fixed issue with unused ``yybm``.
- Partial support for flex syntax.
- Changed to allow ``/*`` comments with ``-c`` switch.
- Added flag ``-D/--emit-dot``.

0.13.2 (2008-02-14)
~~~~~~~~~~~~~~~~~~~

- Added flag ``--case-inverted``.
- Added flag ``--case-insensitive``.
- Added support for ``<!...>`` to enable rule setup.
- Added support for ``=>`` style rules.
- Added support for ``:=`` style rules.
- Added support for ``:=>`` style rules.
- Added ``re2c:cond:divider`` and ``re2c:cond:goto`` inplace configuration.
- Fixed code generation to emit space after ``if``.

0.13.1 (2007-08-24)
~~~~~~~~~~~~~~~~~~~

- Added custom build rules for Visual Studio 2005 (``re2c.rules``).
  (William Swanson)
- Fixed issue with some compilers.
- Fixed #1776177 Build on AIX.
- Fixed #1743180 ``fwrite`` with 0 length crashes on OS X.

0.13.0 (2007-06-24)
~~~~~~~~~~~~~~~~~~~

- Added ``-c`` and ``-t`` to generate scanners with (f)lex-like condition
  support.
- Fixed issue with short form of switches and parameter if not first switch.
- Fixed #1708378 segfault ``in actions.cc``.


-----
0.12x
-----

0.12.3 (2007-08-24)
~~~~~~~~~~~~~~~~~~~

- Fixed issue with some compilers.
- Fixed #1776177 Build on AIX.
- Fixed #1743180 ``fwrite`` with 0 length crashes on OS X.

0.12.2 (2007-06-26)
~~~~~~~~~~~~~~~~~~~

- Fixed #1743180 ``fwrite`` with 0 length crashes on OS X.

0.12.1 (2007-05-23)
~~~~~~~~~~~~~~~~~~~

- Fixed #1711240 problem with ``"`` and ``7F`` on EBCDIC plattforms.

0.12.0 (2007-05-01)
~~~~~~~~~~~~~~~~~~~

- Re-release of 0.11.3 as new stable branch.
- Fixed issue with short form of switches and parameter if not first switch.
- Fixed #1708378 segfault in ``actions.cc``.
- re2c 0.12.0 has been tested with the following compilers:

  + gcc version 4.1.2 (Gentoo 4.1.2)
  + gcc version 4.1.2 20070302 (prerelease) (4.1.2-1mdv2007.1)
  + gcc version 4.1.2 20061115 (prerelease) (Debian 4.1.1-21)
  + gcc version 4.1.1 20070105 (Red Hat 4.1.1-51)
  + gcc version 4.1.0 (SUSE Linux 10)
  + gcc version 4.0.3 (4.0.3-0.20060215.2mdk for Mandriva Linux release 2006.1)
  + gcc version 4.0.2 20050901 (prerelease) (SUSE Linux) (32 + 64 bit)
  + MacPPC, gcc version 4.0.1 (Apple Computer, Inc. build 5367)
  + MacIntel, gcc version 4.0.1 (Apple Computer, Inc. build 5250)
  + gcc version 3.4.4 [FreeBSD] 20050518 (32 + 64 bit)
  + gcc version 3.4.4 (cygming special) (gdc 0.12, using dmd 0.125)
  + gcc version 3.4.2 [FreeBSD]
  + gcc version 3.3.5 20050117 (prerelease) (SUSE Linux)
  + gcc version 3.3.3 (PPC, 32 + 64 bit)
  + Microsoft (R) C/C++ Optimizing Compiler Version 14.00.50727.762 for x64 (64 bit)
  + Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 14.00.50727.42 for 80x86 (Microsoft Visual C++ 2005)
  + Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 13.10.3077 for 80x86 (Mictosoft Visual C++ 2003)
  + Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 13.00.9466 for 80x86 (Microsoft Visual C++ 2002)
  + Intel(R) C++ Compiler for 32-bit applications, Version 9.1 Build 20070322Z Package ID: W_CC_C_9.1.037
  + Intel(R) C++ Compiler for Intel(R) EM64T-based applications, Version 9.1 (64 bit)
  + icpcbin (ICC) 9.1 20070215
  + CC: Sun C++ 5.8 2005/10/13 (``CXXFLAGS='-library=stlport4'``)
  + MIPSpro Compilers: Version 7.4.4m (32 + 64 bit)
  + aCC: HP C/aC++ B3910B A.06.15 [Mar 28 2007] (HP-UX IA64)


-----
0.11x
-----

0.11.3 (2007-04-01)
~~~~~~~~~~~~~~~~~~~

- Added support for underscores in named definitions.
- Added new option ``--no-generation-date``.
- Fixed issue with long form of switches.

0.11.2 (2007-03-01)
~~~~~~~~~~~~~~~~~~~

- Added inplace configuration ``re2c:yyfill:parameter``.
- Added inplace configuration ``re2c:yych:conversion``.
- Fixed ``-u`` switch code generation.
- Added ability to avoid defines and overwrite generated variable names.

0.11.1 (2007-02-20)
~~~~~~~~~~~~~~~~~~~

- Applied #1647875 Add ``const`` to ``yybm`` vector.

0.11.0 (2007-01-01)
~~~~~~~~~~~~~~~~~~~

- Added ``-u`` switch to support unicode.


-----
0.10x
-----

0.10.8 (2007-04-01)
~~~~~~~~~~~~~~~~~~~

- Fixed issue with long form of switches.

0.10.7 (2007-02-20)
~~~~~~~~~~~~~~~~~~~

- Applied #1647875 Add ``const`` to ``yybm`` vector.

0.10.6 (2006-08-05)
~~~~~~~~~~~~~~~~~~~

- Fixed #1529351 Segv bug on unterminated code blocks.
- Fixed #1528269 Invalid code generation.

0.10.5 (2006-06-11)
~~~~~~~~~~~~~~~~~~~

- Fixed long form of ``-1`` switch to ``--single-pass`` as noted in man page
  and help.
- Added MSVC 2003 project files and renamed old 2002 ones.

0.10.4 (2006-06-01)
~~~~~~~~~~~~~~~~~~~

- Fix whitespace in generated code.

0.10.3 (2006-05-14)
~~~~~~~~~~~~~~~~~~~

- Fixed issue with ``-wb`` and ``-ws``.
- Added ``-g`` switch to support gcc's computed goto's.
- Changed to use nested ``if``'s instead of ``switch(yyaccept)`` in ``-s`` mode.

0.10.2 (2006-05-01)
~~~~~~~~~~~~~~~~~~~

- Changed to generate ``YYMARKER`` only when needed or in single pass mode.
- Added ``-1`` switch to force single pass generation and make two pass the
  default.
- Fixed ``-i`` switch.
- Added configuration ``yyfill:enable`` to allow suppression of ``YYFILL()``
  blocks.
- Added tutorial like lessons to re2c.
- Added ``/*!ignore:re2c */`` to support documenting of re2c source.
- Fixed issue with multiline re2c comments (``/*!max:re2c ... */`` and alike).
- Fixed generation of ``YYDEBUG()`` when using ``-d`` switch.
- Added ``/*!getstate:re2c */`` which triggers generation of the
  ``YYGETSTATE()`` block.
- Added configuration ``state:abort``.
- Changed to not generate ``yyNext`` unless configuration ``state:nextlabel`` is
  used.
- Changed to not generate ``yyaccept`` code unless needed.
- Changed to use ``if`` instead of ``switch`` expression when ``yyaccpt`` has
  only one case.
- Added docu, examples and tests to ``.src.zip`` package (0.10.1 zip was
  repackaged).
- Fixed #1479044 incorrect code generated when using ``-b``.
- Fixed #1472770 re2c creates an infinite loop.
- Fixed #1454253 Piece of code saving a backtracking point not generated.
- Fixed #1463639 Missing forward declaration.
- Implemented #1187127 savable state support for multiple re2c blocks.
- re2c 0.10.2 has been tested with the following compilers:

  + gcc (GCC) 4.1.0 (Gentoo 4.1.0)
  + gcc version 4.0.3 (4.0.3-0.20060215.2mdk for Mandriva Linux release 2006.1)
  + gcc version 4.0.2 20050901 (prerelease) (SUSE Linux)
  + gcc (GCC) 3.4.5 (Gentoo 3.4.5, ssp-3.4.5-1.0, pie-8.7.9)
  + gcc version 3.4.4 [FreeBSD] 20050518
  + gcc version 3.4.4 (cygming special) (gdc 0.12, using dmd 0.125)
  + gcc version 3.4.2 20041017 (Red Hat 3.4.2-6.fc3)
  + gcc-Version 3.3.5 (Debian 1:3.3.5-13)
  + gcc-Version 3.3.0 (mips-sgi-irix6.5/3.3.0/specs)
  + MIPSpro Compilers: Version 7.4.4m
  + Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 14.00.50727.42 for
    80x86 (Microsoft Visual C++ 2005)
  + Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 13.10.3077 for 80x86
    (Mictosoft Visual C++ 2003)
  + Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 13.00.9466 for 80x86
    (Microsoft Visual C++ 2002)
  + Intel(R) C++ Compiler for Intel(R) EM64T-based applications, Version 9.0
    Build 20050430 Package ID: l_cc_p_9.0.021
  + CC: Sun C++ 5.8 2005/10/13 (``CXXFLAGS='-library=stlport4'``)
  + bison 2.1, 1.875d, 1.875b, 1.875

0.10.1 (2006-02-28)
~~~~~~~~~~~~~~~~~~~

- Added support for Solaris and native SUN compiler.
- Applied #1438160 expose ``YYCTXMARKER``.
- re2c 0.10.1 has been tested with the following compilers:

  + gcc version 4.0.3 (4.0.3-0.20060215.2mdk for Mandriva Linux release 2006.1)
  + gcc version 4.0.2 (4.0.2-1mdk for Mandriva Linux release 2006.1)
  + gcc version 4.0.2 20050901 (prerelease) (SUSE Linux)
  + gcc version 3.4.4 (cygming special) (gdc 0.12, using dmd 0.125)
  + gcc-Version 3.3.5 (Debian 1:3.3.5-13)
  + gcc-Version 3.3.0 (mips-sgi-irix6.5/3.3.0/specs)
  + MIPSpro Compilers: Version 7.4.4m
  + Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 14.00.50727.42 for
    80x86 (Microsoft Visual C 2005)
  + Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 13.00.9466 for 80x86
    (Microsoft Visual C 2002)
  + Intel(R) C++ Compiler for 32-bit applications, Version 9.0 Build 20051130Z
    Package ID: W_CC_C_9.0.028
  + CC: Sun C++ 5.8 2005/10/13 (``CXXFLAGS='-compat5 -library=stlport4'``)
  + bison 2.1, 1.875d, 1.875b, 1.875

0.10.0 (2006-02-18)
~~~~~~~~~~~~~~~~~~~

- Added make target ``zip`` to create windows source packages as zip files.
- Added ``re2c:startlabel`` configuration.
- Fixed code generation to not generate unreachable code for initial state.
- Added support for c/c++ compatible ``\u`` and ``\U`` unicode notation.
- Added ability to control indendation.
- Made scanner error out in case an ambiguous ``/*`` is found.
- Fixed indendation of generated code.
- Added support for DOS line endings.
- Added experimental unicode support.
- Added ``config_w32.h`` to build out of the box on windows (using msvc 2002+).
- Added Microsoft Visual C .NET 2005 build files.
- Applied #1411087 variable length trailing context.
- Applied #1408326 do not generate ``goto`` next state.
- Applied #1408282 ``CharSet`` initialization fix.
- Applied #1408278 ``readsome`` with MSVC.
- Applied #1307467 Unicode patch for 0.9.7.


----
0.9x
----

0.9.12 (2005-12-28)
~~~~~~~~~~~~~~~~~~~

- Fixed bug #1390174 re2c cannot accept ``{0,}``.

0.9.11 (2005-12-18)
~~~~~~~~~~~~~~~~~~~

- Fixed #1313083 ``-e`` (EBCDIC cross compile) broken.
- Fixed #1297658 underestimation of ``n`` in ``YYFILL(n)``.
- Applied #1339483 Avoid rebuilds of re2c when running subtargets.
- Implemented #1335305 symbol table reimplementation, just slightly modifed.

0.9.10 (2005-09-04)
~~~~~~~~~~~~~~~~~~~

- Add ``-i`` switch to avoid generating ``#line`` information.
- Fixed bug #1251653 re2c generate some invalid ``#line`` on WIN32.

0.9.9 (2005-07-21)
~~~~~~~~~~~~~~~~~~~

- Implemented #1232777 negated char classes ``[^...]`` and the dot operator ``.``.
- Added hexadecimal character definitions.
- Added consistency check for octal character definitions.

0.9.8 (2005-06-26)
~~~~~~~~~~~~~~~~~~~

- Fixed code generation for ``-b`` switch.
- Added Microsoft Visual C .NET build files.

0.9.7 (2005-04-30)
~~~~~~~~~~~~~~~~~~~

- Applied #1181535 storable state patch.
- Added ``-d`` flag which outputs a debugable parser.
- Fixed generation of ``#line`` directives (according to ISO-C99).
- Fixed bug #1187785 Re2c fails to generate valid code.
- Fixed bug #1187452 unused variable ``yyaccept``.

0.9.6 (2005-04-14)
~~~~~~~~~~~~~~~~~~~

- Fix build with gcc >= 3.4.

0.9.5 (2005-04-08)
~~~~~~~~~~~~~~~~~~~

- Added ``/*!max:re2c */`` which emits ``#define YYMAXFILL <max>``
  line. This allows to define buffers of the minimum required length.
  Occurence must follow ``/*re2c */`` and cannot preceed it.
- Changed re2c to two pass generation to output warning free code.
- Fixed bug #1163046 re2c hangs when processing valid re-file.
- Fixed bug #1022799 re2c scanner has buffering bug.

0.9.4 (2005-03-12)
~~~~~~~~~~~~~~~~~~~

- Added ``--vernum`` support.
- Fixed bug #1054496 incorrect code generated with ``-b`` option.
- Fixed bug #1012748 re2c does not emit last line if ``\n`` missing.
- Fixed bug #999104 ``--output=output`` option does not work as documented.
- Fixed bug #999103 Invalid options prefixed with two dashes cause program
  crash.

0.9.3 (2004-05-26)
~~~~~~~~~~~~~~~~~~~

- Fixes one small possible bug in the generated output. ``ych`` instead of
  ``yych`` is output in certain circumstances.

0.9.2 (2004-05-26)
~~~~~~~~~~~~~~~~~~~

- Added ``-o`` option to specify the output file which also will set the
  ``#line`` directives to something useful.
- Print version to ``cout`` instead of ``cerr``.
- Added ``-h`` and ``--`` style options.
- Moved development to http://sourceforge.net/projects/re2c
- Fixed bug #960144 minor cosmetic problem.
- Fixed bug #953181 cannot compile with.
- Fixed bug #939277 Windows support.
- Fixed bug #914462 automake build patch
- Fixed bug #891940 braced quantifiers: ``{\d+(,|,\d+)?}`` style.
- Fixed bug #869298 Add case insensitive string literals.
- Fixed bug #869297 Input buffer overrun.

0.9.1 (2003-12-13)
~~~~~~~~~~~~~~~~~~~

- Removed rcs comments in source files.

-------------------------
re2c adopted (2003-12-09)
-------------------------

- Version 0.9.1 README::

    Originally written by Peter Bumbulis (peter@csg.uwaterloo.ca)
    Currently maintained by Brian Young (bayoung@acm.org)

    The re2c distribution can be found at:
    http://www.tildeslash.org/re2c/index.html

    The source distribution is available from:
    http://www.tildeslash.org/re2c/re2c-0.9.1.tar.gz

    This distribution is a cleaned up version of the 0.5 release
    maintained by me (Brian Young). Several bugs were fixed as well
    as code cleanup for warning free compilation. It has been
    developed and tested with egcs 1.0.2 and gcc 2.7.2.3 on Linux x86.
    Peter Bumbulis' original release can be found at:
    ftp://csg.uwaterloo.ca/pub/peter/re2c.0.5.tar.gz

    re2c is a great tool for writing fast and flexible lexers.
    It has served many people well for many years and it deserves
    to be maintained more actively. re2c is on the order of 2-3
    times faster than a flex based scanner, and its input model
    is much more flexible.

    Patches and requests for features will be entertained. Areas
    of particular interest to me are porting (a Solaris and an NT
    version will be forthcoming) and wide character support. Note
    that the code is already quite portable and should be buildable
    on any platform with minor makefile changes.

- Version 0.5 Peter's original ANNOUNCE and README::

    re2c is a tool for generating C-based recognizers from regular
    expressions. re2c-based scanners are efficient: for programming
    languages, given similar specifications, an re2c-based scanner
    is typically almost twice as fast as a flex-based scanner with
    little or no increase in size (possibly a decrease on cisc
    architectures). Indeed, re2c-based scanners are quite competitive
    with hand-crafted ones.

    Unlike flex, re2c does not generate complete scanners: the user
    must supply some interface code. While this code is not bulky
    (about 50-100 lines for a flex-like scanner; see the man page
    and examples in the distribution) careful coding is required for
    efficiency (and correctness). One advantage of this arrangement
    is that the generated code is not tied to any particular input
    model. For example, re2c generated code can be used to scan
    data from a null-byte terminated buffer as illustrated below.

    Given the following source:

        #define NULL        ((char*) 0)
        char *scan(char *p) {
        char *q;
        #define YYCTYPE     char
        #define YYCURSOR    p
        #define YYLIMIT     p
        #define YYMARKER    q
        #define YYFILL(n)
        /*!re2c
            [0-9]+      {return YYCURSOR;}
            [\000-\377] {return NULL;}
        */
        }

    re2c will generate:

        /* Generated by re2c on Sat Apr 16 11:40:58 1994 */
        #line 1 "simple.re"
        #define NULL        ((char*) 0)
        char *scan(char *p) {
        char *q;
        #define YYCTYPE     char
        #define YYCURSOR    p
        #define YYLIMIT     p
        #define YYMARKER    q
        #define YYFILL(n)
        {
                YYCTYPE yych;
                unsigned int yyaccept;
                goto yy0;
        yy1:    ++YYCURSOR;
        yy0:
                if((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
                yych = *YYCURSOR;
                if(yych <= '/') goto yy4;
                if(yych >= ':') goto yy4;
        yy2:    yych = *++YYCURSOR;
                goto yy7;
        yy3:
        #line 10
                {return YYCURSOR;}
        yy4:    yych = *++YYCURSOR;
        yy5:
        #line 11
                {return NULL;}
        yy6:    ++YYCURSOR;
                if(YYLIMIT == YYCURSOR) YYFILL(1);
                yych = *YYCURSOR;
        yy7:    if(yych <= '/') goto yy3;
                if(yych <= '9') goto yy6;
                goto yy3;
        }
        #line 12

        }

    Note that most compilers will perform dead-code elimination to
    remove all YYCURSOR, YYLIMIT comparisions.

    re2c was developed for a particular project (constructing a fast
    REXX scanner of all things!) and so while it has some rough edges,
    it should be quite usable. More information about re2c can be
    found in the (admittedly skimpy) man page; the algorithms and
    heuristics used are described in an upcoming LOPLAS article
    (included in the distribution). Probably the best way to find out
    more about re2c is to try the supplied examples. re2c is written in
    C++, and is currently being developed under Linux using gcc 2.5.8.

    Peter
