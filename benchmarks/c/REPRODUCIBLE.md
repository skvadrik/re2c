# Reproducible Vector Loop Benchmarks

These benchmarks compare scalar and vectorized lexers in the same process,
using the same lexer rules. They cover several input shapes without promising
a performance improvement on any particular compiler or machine.

## Data and Scope

The C prefix `vec-regime-` selects 23 regimes, each with `bounded-scalar` and
`bounded-vector` variants. The Go `BenchmarkLexString` benchmark has 29 regimes,
including the 21 synthetic regimes below, with `scalar` and `simd` variants.

| Regime | Definition |
|---|---|
| `fixedN` | Each corpus contains 4096 literals with bodies of exactly N bytes, for N in 0, 1, 2, 3, 4, 5, 6, 7, 8, 16, 24, 31, 32, 33, 64, 256. |
| `escapeK` | Each corpus contains 4096 bodies of 1024 bytes. K is 8, 32 or 64. Every group of K bytes ends with the two-byte escape `\n`, without changing the body length. |
| `stream` | The 4096 bodies have lengths `i % 66`, for i from 0 to 4095, and share one input buffer. |
| `end-buffer` | The literals are the same as in `stream`, but each is scanned with a separate input limit. |
| `csource` | C only: one copy of `benchmarks/_data/csource/small`, without repetition to reach a target size. |
| `headers` | C only: `src/util/containers.h` from the current revision, without repetition or host-dependent file collection. This corpus can change between revisions. |

Ordinary bytes in the synthetic corpora come from the same generator in C and
Go: a 32-bit unsigned state starts at 585, is updated with
`state = state * 1664525 + 1013904223`, and yields the letter
`'a' + (state >> 24) % 26`. The state is reset for each corpus. An escape
sequence consumes one update, like an ordinary byte. Lengths and escape
positions are periodic by construction, not randomly distributed.

The C lexer scans all tokens, including commas. Its byte count includes quotes,
bodies and commas, but excludes the sentinel and padding. The Go lexer scans
one literal per call and counts only the literal, including quotes. C and Go
throughput therefore represents different tasks. C/C++ source files are not
passed to the Go lexer, which recognizes only a string with JSON-style escapes.

In C, `end-buffer` uses the existing convention `YYLIMIT = end + YYMAXFILL`:
required padding remains visible, but no following literal is visible. The
allocation also includes at least 64 zero bytes after the input for the oracle;
this benchmark cannot detect reads into that extra space beyond `YYLIMIT`.
In Go, the input slice ends immediately after the closing quote. These regimes
are neither guard-page tests nor `YYFILL` refill benchmarks. The existing
`buffered-*` benchmarks are separate.

## Correctness Checks

Before timing, each C input is checked against the handwritten `lex_switch`
oracle: status, sum of lengths weighted by rule, and an ordered digest of
rule/length pairs. The digest uses the existing repository mechanism; it is
not a collision-free comparison of the full token stream. Every timed pass
checks its status and sum again. Missing, empty or NUL-containing corpus files
produce an error.

In Go, each call is checked against `referenceLexString` before timing, and
each timed pass is checked against the oracle's sum. `TestBenchmarkRegimes`
also checks repeatability, exact lengths, escape positions and reported byte
counts. Corpus preparation, file reading and initial checks are not timed.

## Building the C Benchmarks

Run these commands from the repository root. They require CMake, Ninja, GCC,
Clang and google/benchmark available through `pkg-config`. If the latter is
installed in a custom prefix, set `PKG_CONFIG_PATH` to its `lib/pkgconfig`
directory first. The vectorized build requires x86, and execution requires
AVX2. On a CPU without AVX2, the driver skips the `vec-*` benchmarks, including
their scalar variants; a skipped run does not validate them.

```sh
cmake -S . -B .build-repro -G Ninja \
    -DCMAKE_BUILD_TYPE=Release -DRE2C_BUILD_BENCHMARKS=ON \
    -DRE2C_BUILD_TESTS=OFF \
    -DRE2C_BENCH_SIMDJSON=OFF -DRE2C_BENCH_HYPERSCAN=OFF
cmake --build .build-repro \
    --target benchmarks/c/bench-gcc benchmarks/c/bench-clang -j2
```

These Ninja targets build the executables without generating the large `big`
corpus files used by the other benchmarks. The regimes above use repository
files directly, with the absolute source path embedded at compile time, so
the source tree must remain in place. The build uses `-O3 -g -std=c++11`, with
`-mavx2` for vectorized objects. This integration uses CMake, not Autotools.
Building regenerates the re2c benchmark sources and updates their copies in
`benchmarks/c/pregen`; check these changes when comparing generator revisions.

## Smoke Tests

One iteration exercises the checks but is not a performance measurement.
Run the two C commands sequentially.

```sh
.build-repro/benchmarks/c/bench-gcc --benchmark_filter='^vec-regime-' \
    --benchmark_min_time=1x --benchmark_repetitions=1 \
    --benchmark_out=.build-repro/gcc-smoke.json --benchmark_out_format=json
.build-repro/benchmarks/c/bench-clang --benchmark_filter='^vec-regime-' \
    --benchmark_min_time=1x --benchmark_repetitions=1 \
    --benchmark_out=.build-repro/clang-smoke.json --benchmark_out_format=json
```

google/benchmark can report a failed case without returning a nonzero exit
status. These checks require all 46 cases and no reported errors:

```sh
python3 -c 'import json, sys; runs = json.load(open(sys.argv[1]))["benchmarks"]; assert len(runs) == 46 and all(not r.get("error_occurred", False) for r in runs)' .build-repro/gcc-smoke.json
python3 -c 'import json, sys; runs = json.load(open(sys.argv[1]))["benchmarks"]; assert len(runs) == 46 and all(not r.get("error_occurred", False) for r in runs)' .build-repro/clang-smoke.json
```

For Go, run the following from the example module. These commands require
Go 1.27 with the SIMD experiment and an amd64 CPU with AVX2 support.

```sh
cd examples/go/simd/string_lexer
GOEXPERIMENT=simd GOMAXPROCS=1 \
    go test -run 'TestBenchmarkRegimes|TestParityFixed|TestScalarBaselineIsNotVectorized' -count=1
GOEXPERIMENT=simd GOMAXPROCS=1 go test -run '^$' \
    -bench 'BenchmarkLexString/regime=(fixed[0-9]+|escape[0-9]+|end-buffer|stream)$/impl=' \
    -benchtime=1x -count=1 -benchmem
```

This selection should report 42 cases unless skipped for lack of AVX2.
`string_lexer.go` is the generated file included in the tree. The module's
README gives the regeneration command; comparisons of generators must
regenerate this file with each generator being compared.

## Performance Limits

Vectorization is not always beneficial. One-byte strings in Go, short fixed
lengths with GCC, and closely spaced escapes can favor scalar code. Having a
whole vector available in the buffer says nothing about the length of the
next escape-free segment. Raising the length guard alone therefore does not
adapt the lexer to short segments.

The Go vector loop honors custom `code:yylessthan` definitions for the simple
and record APIs; the generic API is not vectorized. Depending on the Go
compiler's output, the vector length guard and setup can add overhead even
when the buffer boundary prevents vector processing. Comparisons should cover
short strings, end-of-buffer inputs, frequent escapes and long strings while
preserving custom bounds checks and AVX register cleanup. These benchmarks
do not establish a universally suitable entry threshold or reentry policy.

## Repeated Measurements

Use a quiet machine before replacing smoke tests with repeated measurements.
Record the revision, local changes, tool versions, commands, corpus hashes and
raw results. From the repository root:

```sh
sha256sum benchmarks/_data/csource/small src/util/containers.h
git rev-parse HEAD
git diff --stat
g++ --version
clang++ --version
go version
pkg-config --modversion benchmark
```

On Linux, set `CPU` to an available logical CPU and keep its SMT sibling idle.
Run these C commands sequentially from the repository root:

```sh
taskset -c "${CPU:?CPU must be set}" .build-repro/benchmarks/c/bench-gcc \
    --benchmark_filter='^vec-regime-' --benchmark_min_time=0.1s \
    --benchmark_repetitions=9 --benchmark_out=.build-repro/gcc.json \
    --benchmark_out_format=json
taskset -c "${CPU:?CPU must be set}" .build-repro/benchmarks/c/bench-clang \
    --benchmark_filter='^vec-regime-' --benchmark_min_time=0.1s \
    --benchmark_repetitions=9 --benchmark_out=.build-repro/clang.json \
    --benchmark_out_format=json
```

Run the Go command from `examples/go/simd/string_lexer`:

```sh
GOEXPERIMENT=simd GOMAXPROCS=1 \
    taskset -c "${CPU:?CPU must be set}" go test -run '^$' \
    -bench 'BenchmarkLexString/regime=(fixed[0-9]+|escape[0-9]+|end-buffer|stream)$/impl=' \
    -benchtime=100ms -count=9 -benchmem
```

These drivers do not collect grouped hardware counters, reject preempted
measurement intervals or verify that the SMT sibling is idle. Repetition and
CPU affinity alone do not remove scheduling, frequency or thermal effects.
Smoke tests establish functionality, not speedups; repeated results still
need to be interpreted in the context of the compiler and machine used.
