# Linear vectorization benchmarks

Compare `re2c:vectorize:linear = 0` and `= 1` using the same generator,
rules, actions and input bytes. Scanners are compiled as C11 with a C++
Google Benchmark driver, or run with Go's `testing.B`. No SIMD is required.
This standalone suite does not change the existing Automake benchmarks.

## Workloads and correctness

`generate.py` uses Python's `random.Random(586)` to produce 1024 known HTTP
header names, 1024 unknown names and variable-length values. Each population
uses the same sequence of names in three layouts:

| Case | Input |
| --- | --- |
| `isolated` | One name per buffer, including its colon. |
| `names` | All names concatenated in one buffer, without values. |
| `values` | Names with values and CRLF; two tokens per header line. |
| `sql_original` | 4096 elements mixing six keywords, identifiers, near misses, digits and punctuation. |

The SQL lexer retains `[a-zA-Z_][a-zA-Z0-9_]*`: keywords have no artificial
terminator, and `SELECTED` remains an identifier. Actions expose token kinds
and lengths, including spaces. This is a small lexer, not a SQL parser.
Unknown HTTP names start with `X-`; they do not model near misses.
Corpora are generated directly, not expanded by repeating a small file,
but are small and revisited on every iteration. Known names remain repetitive.

Both drivers use the same fixtures and validate complete (kind, length)
traces, exact byte consumption and end of input before timing. The Python
regular-expression oracle implements longest match and rule priority; it
shares the rule specification, not the generated implementation. Explicit
assertions check SQL prefixes and HTTP values. Empty inputs, prefixes,
extensions and malformed endings are correctness-only cases.

One iteration processes a whole corpus. Byte counts exclude the sentinel
and 64-byte zero padding; only `values` includes HTTP values. C also reports
token counts. Generation, allocation and trace validation are not timed.
Per-record initialization, per-token calls and an FNV-1a digest of kinds
and lengths are timed. The digest prevents unused results; it is neither
cryptographic nor an independent oracle.

## Build

Requirements: C/C++ compilers, CMake, Python 3, Go 1.24 or newer, and Google
Benchmark with its `benchmark.pc` file visible to `pkg-config`.
From the repository root:

```sh
cmake -S . -B benchmarks/vectorize-linear/build/re2c \
  -DCMAKE_BUILD_TYPE=Release -DRE2C_BUILD_TESTS=OFF \
  -DRE2C_BUILD_RE2GO=ON
cmake --build benchmarks/vectorize-linear/build/re2c --target re2c re2go -j2
```

This build uses the checked-in bootstrap files and does not regenerate them.
Run the remaining commands from `benchmarks/vectorize-linear`. If C and Go
generators with linear vectorization support are already available, skip the
CMake build and supply their paths to `make generate` instead:

```sh
export GOWORK=off
make generate RE2C="$PWD/build/re2c/re2c" RE2GO="$PWD/build/re2c/re2go"
make -j2
make check
```

Set `PKG_CONFIG_PATH` for a nonstandard Google Benchmark installation, or
override `BENCHMARK_CFLAGS` and `BENCHMARK_LIBS`. `RE2C` and `RE2GO` can select
other generator binaries. `CC` and `CXX` respect environment settings and can
also be set on the `make` command line. Use a separate `BUILD` when changing compilers or
flags, for example `make BUILD=build/clang CC=clang CXX=clang++ -j2`.
`generated/manifest.json` records generation commands and SHA-256 hashes of
generators, benchmark sources, fixtures and outputs. Preserve it together
with compiler versions, flags and logs. Build and generated files are ignored
by Git. `generated/codegen-checks.json` compares scalar and optimized sources
after normalizing only function names.

## Short checks

Run these sequentially, not alongside other performance tests:

```sh
./build/bench --benchmark_min_time=0.001s --benchmark_repetitions=2 \
  --benchmark_enable_random_interleaving=true \
  --benchmark_out=build/c-smoke.json --benchmark_out_format=json
go test -count=1 -bench . -benchtime=1x
make BUILD=build/asan CC=clang CXX=clang++ -j2 \
  CFLAGS='-O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer' \
  CXXFLAGS='-O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer'
./build/asan/bench --check
```

There are 56 C cases and 14 Go cases. C calibration can exceed the requested
millisecond; interleaving does not establish strict physical pairing. A single
Go iteration provides no statistical evidence. `make smoke` is another short
check, using one C repetition. These short checks are not publishable
performance measurements.

## Isolating refill effects

C compares `nofill` (checks disabled, padded resident input), `resident`
(checks enabled, no refill needed), and `refill64`/`refill4096` (the same
checked scanner with real compaction and copying from memory). Correctness
checks also use a 97-byte window. Tokens must fit in the window; this is not
a general-purpose file reader. Initial copying is timed only in refill modes.
Go provides resident-input controls, not a refill implementation.

Compare scalar and optimized variants within each mode first, then compare
`nofill` with `resident`, and `resident` with refill modes. Comparing layouts
separates per-name entry/sentinel work from value scanning. Without `YYFILL`,
linear-vectorization paths need their own limit guards; with it, preceding checks reserve
input, so disabling refill changes code shape as well as refill overhead.
Isolated known names can expose useful linear paths. In the SQL lexer, accepting
identifier prefixes stop chains, so linear vectorization leaves the scanner
unchanged. HTTP linear paths can be optimized even with `YYFILL`, but this does
not guarantee a C speedup: performance depends on the compiler, input
distribution and buffer handling.
