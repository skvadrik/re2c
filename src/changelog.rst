* 2015-02-23: 0.14
    - Added generic input API (#21 "Support to configure how re2c code interfaced with the symbol buffer?")
    - fixed #46 "re2c generates an infinite loop, depends on existence of previous parser"
    - fixed #47 "Dot output label escaped characters"

* 2014-08-22: 0.13.7.5

    - Fixed `Gentoo bug with PHP lexer <https://bugs.gentoo.org/show_bug.cgi?id=518904>`_

* 2014-07-29: 0.13.7.4

    - Enabled ``make docs`` only if configured with ``--enable-docs``
    - Disallowed to use yacc/byacc instead of bison to build parser
    - Removed non-portable sed feature in script that runs tests

* 2014-07-27: 0.13.7.3

    - Fixed CXX warning
    - Got rid of asciidoc build-time dependency

* 2014-07-27: 0.13.7.2

    - Included man page into dist, respect users CXXFLAGS.

* 2014-07-26: 0.13.7.1

    - Added missing files to tarball

* 2014-07-25: 0.13.7

    - Added UTF-8 support
    - Added UTF-16 support
    - Added default rule
    - Added option to control ill-formed Unicode

* 2013-07-04: 0.13.6

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
    - improve dot support: make char intervals (e.g. ``[A-Z]``) instead of one edge per char

* 2008-05-25: 0.13.5

    - Fixed #1952896 Segfault in ``re2c::Scanner::scan``.
    - Fixed #1952842 Regression.

* 2008-04-05: 0.13.4

    - Added transparent handling of ``#line`` directives in input files.
    - Added ``re2c:yyfill:check`` inplace configuration.
    - Added ``re2c:define:YYSETSTATE:naked`` inplace configuration.
    - Added ``re2c:flags:w`` and ``re2c:flags:u`` inplace configurations.
    - Added the ability to add rules in ``use:re2c`` blocks.
    - Changed ``-r`` flag to accept only ``rules:re2c`` and ``use:re2c`` blocks.

* 2008-03-14: 0.13.3

    - Added ``-r`` flag to allow reuse of scanner definitions.
    - Added ``-F`` flag to support flex syntax in rules.
    - Fixed SEGV in scanner that occurs with very large blocks.
    - Fixed issue with unused ``yybm``.
    - Partial support for flex syntax.
    - Changed to allow ``/*`` comments with ``-c`` switch.
    - Added flag ``-D/--emit-dot``.

* 2008-02-14: 0.13.2

    - Added flag ``--case-inverted``.
    - Added flag ``--case-insensitive``.
    - Added support for ``<!...>`` to enable rule setup.
    - Added support for ``=>`` style rules.
    - Added support for ``:=`` style rules.
    - Added support for ``:=>`` style rules.
    - Added ``re2c:cond:divider`` and ``re2c:cond:goto`` inplace configuration.
    - Fixed code generation to emit space after ``if``.

* 2007-08-24: 0.13.1

    - Added custom build rules for Visual Studio 2005 (``re2c.rules``). (William Swanson)
    - Fixed issue with some compilers.
    - Fixed #1776177 Build on AIX.
    - Fixed #1743180 ``fwrite`` with 0 length crashes on OS X.

* 2007-06-24: 0.13.0

    - Added ``-c`` and ``-t`` to generate scanners with (f)lex-like condition support.
    - Fixed issue with short form of switches and parameter if not first switch.
    - Fixed #1708378 segfault ``in actions.cc``.

* 2007-08-24: 0.12.3

    - Fixed issue with some compilers.
    - Fixed #1776177 Build on AIX.
    - Fixed #1743180 ``fwrite`` with 0 length crashes on OS X.

* 2007-06-26: 0.12.2

    - Fixed #1743180 ``fwrite`` with 0 length crashes on OS X.

* 2007-05-23: 0.12.1

    - Fixed #1711240 problem with ``"`` and ``7F`` on EBCDIC plattforms.

* 2007-05-01: 0.12.0

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

* 2007-04-01: 0.11.3

    - Added support for underscores in named definitions.
    - Added new option ``--no-generation-date``.
    - Fixed issue with long form of switches.

* 2007-03-01: 0.11.2

    - Added inplace configuration ``re2c:yyfill:parameter``.
    - Added inplace configuration ``re2c:yych:conversion``.
    - Fixed ``-u`` switch code generation.
    - Added ability to avoid defines and overwrite generated variable names.

* 2007-02-20: 0.11.1

    - Applied #1647875 Add ``const`` to ``yybm`` vector.

* 2007-01-01: 0.11.0

    - Added ``-u`` switch to support unicode.

* 2007-04-01: 0.10.8

    - Fixed issue with long form of switches.

* 2007-02-20: 0.10.7

    - Applied #1647875 Add ``const`` to ``yybm`` vector.

* 2006-08-05: 0.10.6

    - Fixed #1529351 Segv bug on unterminated code blocks.
    - Fixed #1528269 Invalid code generation.

* 2006-06-11: 0.10.5

    - Fixed long form of ``-1`` switch to ``--single-pass`` as noted in man page and help.
    - Added MSVC 2003 project files and renamed old 2002 ones.

* 2006-06-01: 0.10.4

    - Fix whitespace in generated code.

* 2006-05-14: 0.10.3

    - Fixed issue with ``-wb`` and ``-ws``.
    - Added ``-g`` switch to support gcc's computed goto's.
    - Changed to use nested ``if``'s instead of ``switch(yyaccept)`` in ``-s`` mode.

* 2006-05-01: 0.10.2

    - Changed to generate ``YYMARKER`` only when needed or in single pass mode.
    - Added ``-1`` switch to force single pass generation and make two pass the default.
    - Fixed ``-i`` switch.
    - Added configuration ``yyfill:enable`` to allow suppression of ``YYFILL()`` blocks.
    - Added tutorial like lessons to re2c.
    - Added ``/*!ignore:re2c */`` to support documenting of re2c source.
    - Fixed issue with multiline re2c comments (``/*!max:re2c ... */`` and alike).
    - Fixed generation of ``YYDEBUG()`` when using ``-d`` switch.
    - Added ``/*!getstate:re2c */`` which triggers generation of the ``YYGETSTATE()`` block.
    - Added configuration ``state:abort``.
    - Changed to not generate ``yyNext`` unless configuration ``state:nextlabel`` is used.
    - Changed to not generate ``yyaccept`` code unless needed.
    - Changed to use ``if`` instead of ``switch`` expression when ``yyaccpt`` has only one case.
    - Added docu, examples and tests to ``.src.zip`` package (0.10.1 zip was repackaged).
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
        + Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 14.00.50727.42 for 80x86 (Microsoft Visual C++ 2005)
        + Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 13.10.3077 for 80x86 (Mictosoft Visual C++ 2003)
        + Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 13.00.9466 for 80x86 (Microsoft Visual C++ 2002)
        + Intel(R) C++ Compiler for Intel(R) EM64T-based applications, Version 9.0 Build 20050430 Package ID: l_cc_p_9.0.021
        + CC: Sun C++ 5.8 2005/10/13 (``CXXFLAGS='-library=stlport4'``)
        + bison 2.1, 1.875d, 1.875b, 1.875

* 2006-02-28: 0.10.1

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
        + Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 14.00.50727.42 for 80x86 (Microsoft Visual C 2005)
        + Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 13.00.9466 for 80x86 (Microsoft Visual C 2002)
        + Intel(R) C++ Compiler for 32-bit applications, Version 9.0 Build 20051130Z Package ID: W_CC_C_9.0.028
        + CC: Sun C++ 5.8 2005/10/13 (``CXXFLAGS='-compat5 -library=stlport4'``)
        + bison 2.1, 1.875d, 1.875b, 1.875

* 2006-02-18: 0.10.0

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

* 2005-12-28: 0.9.12

    - Fixed bug #1390174 re2c cannot accept ``{0,}``.

* 2005-12-18: 0.9.11

    - Fixed #1313083 ``-e`` (EBCDIC cross compile) broken.
    - Fixed #1297658 underestimation of ``n`` in ``YYFILL(n)``.
    - Applied #1339483 Avoid rebuilds of re2c when running subtargets.
    - Implemented #1335305 symbol table reimplementation, just slightly modifed.

* 2005-09-04: 0.9.10

    - Add ``-i`` switch to avoid generating ``#line`` information.
    - Fixed bug #1251653 re2c generate some invalid ``#line`` on WIN32.

* 2005-07-21: 0.9.9

    - Implemented #1232777 negated char classes ``[^...]`` and the dot operator ``.``.
    - Added hexadecimal character definitions.
    - Added consistency check for octal character definitions.

* 2005-06-26: 0.9.8

    - Fixed code generation for ``-b`` switch.
    - Added Microsoft Visual C .NET build files.

* 2005-04-30: 0.9.7

    - Applied #1181535 storable state patch.
    - Added ``-d`` flag which outputs a debugable parser.
    - Fixed generation of ``#line`` directives (according to ISO-C99).
    - Fixed bug #1187785 Re2c fails to generate valid code.
    - Fixed bug #1187452 unused variable ``yyaccept``.

* 2005-04-14: 0.9.6

    - Fix build with gcc >= 3.4.

* 2005-04-08: 0.9.5

    - Added ``/*!max:re2c */`` which emits ``#define YYMAXFILL <max>``
      line. This allows to define buffers of the minimum required length.
      Occurence must follow ``/*re2c */`` and cannot preceed it.
    - Changed re2c to two pass generation to output warning free code.
    - Fixed bug #1163046 re2c hangs when processing valid re-file.
    - Fixed bug #1022799 re2c scanner has buffering bug.

* 2005-03-12: 0.9.4

    - Added ``--vernum`` support.
    - Fixed bug #1054496 incorrect code generated with ``-b`` option.
    - Fixed bug #1012748 re2c does not emit last line if ``\n`` missing.
    - Fixed bug #999104 ``--output=output`` option does not work as documented.
    - Fixed bug #999103 Invalid options prefixed with two dashes cause program crash.

* 2004-05-26: 0.9.3

    - Fixes one small possible bug in the generated output. ``ych`` instead of ``yych`` is output in certain circumstances.

* 2004-05-26: 0.9.2

    - Added ``-o`` option to specify the output file which also will set the ``#line`` directives to something useful.
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

* 2003-12-13: 0.9.1

    - Removed rcs comments in source files.

* 2003-12-09: re2c adopted
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
