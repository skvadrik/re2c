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
- Added individual warnings:
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
    + ``-1 --single-pass`` (single pass is by default now)
- Reduced size of the generated ``.dot`` files.
- Fixed bugs:
    + #27 re2c crashes reading files containing ``%{ %}`` (patch by Rui)
    + #51 default rule doesn't work in reuse mode
    + #52 eliminate multiple passes
    + #59 bogus ``yyaccept`` in ``-c`` mode
    + #60 redundant use of ``YYMARKER``
    + #61 empty character class ``[]`` matches empty string
    + #115 flex-style named definitions cause ambiguity in re2c grammar
    + #119 ``-f`` with ``-b``/``-g`` generates incorrect dispatch on fill labels
    + #116 empty string with non-empty trailing context consumes code units
- Added test options:
    + ``-j``, ``-j <N>`` (run tests in ``N`` threads, defaults to the number of CPUs)
    + ``--wine`` (test windows builds using ``wine``)
    + ``--skeleton`` (generate skeleton programs, compile and execute them)
    + ``--keep-tmp-files`` (don't delete intermediate files for successful tests)
- Updated build system:
    + support out of source builds
    + support ```make distcheck```
    + added ```make bootstrap``` (rebuild re2c after building with precomplied ``.re`` files)
    + added ```make tests``` (run tests with ``-j``)
    + added ```make vtests``` (run tests with ``--valgrind -j``)
    + added ```make wtests``` (run tests with ``--wine -j 1``)
    + added Autoconf tests for ``CXXFLAGS``. By default try the following options:
      ``-W -Wall -Wextra -Weffc++ -pedantic -Wformat=2 -Wredundant-decls -Wsuggest-attribute=format -Wconversion -Wsign-conversion -O2 -Weverything``),
      respect user-defined ``CXXFLAGS``
    + support Mingw builds: ```configure -host i686-w64-mingw32```
    + structured source files
    + removed old MSVC files
- Moved development to github (https://github.com/skvadrik/re2c), keep a mirror on sourceforge.

