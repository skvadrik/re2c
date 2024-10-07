How to build
============


Dependencies
------------

To build re2c from a release tarball one needs only a C++ compiler (supporting
at least C++11) and Python 3 for build-time scripts and for testing. Building on
Windows additionally requires either CMake or a Mingw build environment.

To develop re2c one also needs CMake or Autotools (both build systems are
maintained). Other dependencies include Bison (to rebuild parsers), Python 3
Docutils (to rebuild documentation) and Sphinx (to rebuild the website).
Benchmarks also use Google-benchmark, re2 and Java. A few helper scripts are
written in Haskell, but they are not essential for re2c development.

re2c is a self-hosting lexer generator, meaning that parts of its source code
are written in re2c (namely, all the source files that have a *.re* extension).
By default re2c builds from pre-generated bootstrap files. To build from source
*.re* files, it is necessary to reconfigure the build and provide a path to an
existing re2c binary that will be used for bootstrap (see the details below).


Build (Autotools)
-----------------

If you are building from a release tarball, the configure script is already
there. Otherwise it is necessary to generate it:
  ```
  $ autoreconf -i -W all
  ```
An in-tree build (objects are generated side by side with sources):
  ```
  $ ./configure && make && make install
  ```
An out-of-tree build (objects are generated in a separate directory):
  ```
  $ mkdir .build && cd .build && ../configure && make && make install
  ```

The configure script has many options (to see them all, run
`configure --help`). The options specific to re2c are the following:

  * `--enable-debug`
    Enable debug checks in the re2c source code. Also enables debug options.

  * `--enable-dlang`
    Build re2d (identical to `re2c --lang d`). This is on by default.

  * `--enable-golang`
    Build re2go (identical to `re2c --lang go`). This is on by default.

  * `--enable-haskell`
    Build re2hs (identical to `re2c --lang haskell`). This is on by default.

  * `--enable-java`
    Build re2java (identical to `re2c --lang java`). This is on by default.

  * `--enable-js`
    Build re2js (identical to `re2c --lang js`). This is on by default.

  * `--enable-ocaml`
    Build re2ocaml (identical to `re2c --lang ocaml`). This is on by default.

  * `--enable-python`
    Build re2py (identical to `re2c --lang python`). This is on by default.

  * `--enable-rust`
    Build re2rust (identical to `re2c --lang rust`). This is on by default.

  * `--enable-vlang`
    Build re2v (identical to `re2c --lang v`). This is on by default.

  * `--enable-zig`
    Build re2zig (identical to `re2c --lang zig`). This is on by default.

  * `--enable-lexers`
    Enable regeneration of lexers from *.re* files (as opposed to using
    pre-generated bootstrap files). This requires setting `RE2C_FOR_BUILD` to
    an existing re2c executable path.

  * `--enable-parsers`
    Enable regeneration of parsers from *.ypp* files with bison (as opposed to
    using pre-generated bootstrap files).

  * `--enable-syntax`
    Enable regeneration of default syntax files from the ones provided in
    include/ directory (as opposed to using pre-generated bootstrap files).

  * `--enable-docs`
    Enable regeneration of documentation (requires Python 3 Docutils).

  * `--enable-benchmarks`
    Build benchmarks (requires Google benchmarks library).

  * `--enable-benchmarks-regenerate`
    Regenerate C code for Ragel and Kleenex benchmarks (this will download and
    build Ragel and Kleenex). re2c benchmarks are always regenerated.

  * `--enable-libs`
    Build the experimental libre2c library that provides POSIX
    `regcomp`/`regexec`/`regfree` interface to re2c.


Cross-compile re2c for Windows (for some Mingw versions you might have to use
`-std=gnu++11` compiler option):
  ```
  $ ./configure --host i686-w64-ming32 \
      LDFLAGS="-static -static-libstdc++ -static-libgcc"
  ```

There is a bunch of build scripts for specialized builds with Asan, Ubsan,
GLIBCXX_DEBUG, etc. in the ``build`` subdirectory.


Build (CMake)
-------------

re2c includes CMake presets for Linux, MacOS, and Windows. Use `cmake
--list-presets` to see them.

* The `-fast` presets have minimal dependencies and build re2c using
  pre-generated manpages, lexers, and parsers.
* The `-full` presets have additional prerequisites (Docutils, Bison, and a
  pre-existing re2c binary) and re-generate the manpages, lexers, and parsers.

If you just want to build re2c, use the `-release-ootree-fast` preset. The
other presets are primarily of interest to developers.

For example, to build the `windows-msvc-release-ootree-fast` preset:

* CD to the root of the re2c folder (the folder containing this README).
* Configure: `cmake --preset=windows-msvc-release-ootree-fast`
* Build: `cmake --build --preset=windows-msvc-release-ootree-fast`
* The binary will be in the `.build/<preset-name>` folder.

CMake supports different build modes, which can be further customized with
individual options. By default re2c builds with `-O2 -g` and does not set any
particular mode to allow the user complete freedom in overriding the build
options. To enable a build mode at configure phase, use
`-DCMAKE_BUILD_TYPE=<mode>` option (this works with single-config generators,
such as Makefiles or Ninja). At build phase use `--config <mode>` option.
The following modes are supported:

  * `Release`
    This is an optimized `-O3 -DNDEBUG` build without debug symbols, asserts
    and debug checks.

  * `Debug`
    This is a non-optimized `-g -DRE2C_DEBUG` build with debug symbols, asserts,
    and debug checks.

  * `RelWithDebInfo`
    This is an optimized `-O2 -g -DNDEBUG` build with debug symbols, but
    without asserts and debug checks.

  * `MinSizeRel`
    This is an optimized for size `-Os -DNDEBUG` build without debug symbols,
    asserts and debug checks.

  * `Asan`
    This is a non-optimized `-g -fsanitize=address` build that instruments the
    code with Address Sanitizer to check for memory errors.

  * `Ubsan`
    This is a non-optimized `-g -fsanitize=undefined` build that instruments
    the code with Undefined Behavior Sanitizer to check for undefined behavior
    errors.

A simple build (objects are generated in a separate build directory):
  ```
  $ mkdir .build && cd .build && cmake .. && cmake --build .
  ```

CMake supports a lot of configuration options. Here is the list of options
specific to re2c:

  * `-DRE2C_BUILD_RE2D=yes`
    Build re2d executable (an alias to `re2c --lang d`). Enabled by default.

  * `-DRE2C_BUILD_RE2GO=yes`
    Build re2go executable (an alias to `re2c --lang go`). Enabled by default.

  * `-DRE2C_BUILD_RE2HS=yes`
    Build re2hs executable (an alias to `re2c --lang haskell`). Enabled by
    default.

  * `-DRE2C_BUILD_RE2JAVA=yes`
    Build re2java executable (an alias to `re2c --lang java`). Enabled by
    default.

  * `-DRE2C_BUILD_RE2JS=yes`
    Build re2js executable (an alias to `re2c --lang js`). Enabled by default.

  * `-DRE2C_BUILD_RE2OCAML=yes`
    Build re2ocaml executable (an alias to `re2c --lang ocaml`). Enabled by
    default.

  * `-DRE2C_BUILD_RE2PY=yes`
    Build re2py executable (an alias to `re2c --lang python`). Enabled by
    default.

  * `-DRE2C_BUILD_RE2RUST=yes`
    Build re2rust executable (an alias to `re2c --lang rust`). Enabled by
    default.

  * `-DRE2C_BUILD_RE2V=yes`
    Build re2v executable (an alias to `re2c --lang v`). Enabled by default.

  * `-DRE2C_BUILD_RE2ZIG=yes`
    Build re2zig executable (an alias to `re2c --lang zig`). Enabled by default.

  * `-DRE2C_REBUILD_LEXERS=yes`
    Enable regeneration of lexers from *.re* files (as opposed to using
    pre-generated bootstrap files). This requires setting `-DRE2C_FOR_BUILD` to
    an existing re2c executable path.

  * `-DRE2C_REBUILD_PARSERS=yes`
    Enable regeneration of parsers from *.ypp* files with bison (as opposed to
    using pre-generated bootstrap files).

  * `-DRE2C_REBUILD_SYNTAX=yes`
    Enable regeneration of default syntax files from the ones provided in
    include/ directory (as opposed to using pre-generated bootstrap files).

  * `-DRE2C_REBUILD_DOCS=yes`
    Enable regeneration of documentation (requires Python 3 Docutils).

  * `-DRE2C_BUILD_BENCHMARKS=yes`
    Build benchmarks (requires Google benchmarks library).

  * `-DRE2C_REGEN_BENCHMARKS=yes`
    Regenerate C code for Ragel and Kleenex benchmarks (this will download and
    build Ragel and Kleenex). re2c benchmarks are always regenerated.

  * `-DRE2C_BUILD_LIBS=yes`
    Build the experimental libre2c library that provides POSIX
    `regcomp`/`regexec`/`regfree` interface to re2c.


Cross-compile re2c for Windows using Mingw:
  ```
  $ cmake . -DCMAKE_TOOLCHAIN_FILE=cmake/Toolchain-cross-mingw32-linux.cmake \
      -DCMAKE_EXE_LINKER_FLAGS="-static -static-libstdc++ -static-libgcc" \
      -DBUILD_SHARED_LIBS=no
  ```

There is a bunch of build scripts for specialized builds with Asan, Ubsan,
GLIBCXX_DEBUG, etc. in the ``build`` subdirectory.


Test
----

re2c has a main test suite and a number of unit tests. Run them all:
  ```
  $ make check
  ```
Run only the main test suite and watch the progress dumped on stdout:
  ```
  $ python3 run_tests.py -j<N>
  ```
Run the main test suite with `--skeleton` re2c option:
  ```
  $ python3 run_tests.py --skeleton
  ```
Run the test suite under Valgrind (takes some time and memory):
  ```
  $ python3 run_tests.py --valgrind
  ```
Test Mingw builds with Wine:
  ```
  $ make wtests
  ```
Check the distribution (works with Autotools):
  ```
  $ make distcheck
  ```

re2c provides a helper script `build/__alltest.sh` that builds and tests various
re2c build flavours with Asan, Ubsan, GLIBCXX_DEBUG, etc. There is a couple of
fuzz-testing Haskell scripts in the *fuzz* subdirectory; they are based on the
QuickCheck library and can be easily modified to fuzz-test various aspects of
re2c by comparing current re2c version against older versions or against other
regular expression libraries.
