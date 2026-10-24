# AVX Cleanup Regression Test

The optional CMake target `check_vectorize_avx` generates C and Go lexers and
checks assembly control flow without executing AVX instructions. It requires
x86-64 Linux, Python 3, GCC, Clang and Go 1.27 or newer with the `simd` experiment.
Missing tools or unsupported assembly cause a failure, not a successful skip.

```sh
cmake -S . -B build-avx -DRE2C_BUILD_TESTS=ON
cmake --build build-avx --target check_vectorize_avx -j2
```

The target is separate from the portable `tests` target because its compiler
requirements are stronger. Release and Debug verification should explicitly
include it when these tools are available. The Go experiment is enabled by the
script for its child processes; the caller need not set `GOEXPERIMENT`.

To retain all generated sources and assembly, or isolate a backend:

```sh
python3 test/codegen/c/check_vectorize_avx.py build-avx/re2c --output-dir /tmp/re2c-avx
python3 test/codegen/c/check_vectorize_avx.py build-avx/re2c --language c
python3 test/codegen/c/check_vectorize_avx.py build-avx/re2c --language go
```

`--cc` selects a C compiler (repeatable); `--go` selects the Go executable.
`--syntax include/syntax/c` tests an external default C syntax instead of the
embedded one. The `fixed` benchmark override is always checked as well.
Go tests use the executable's embedded syntax unless a probe has a matching
`.inc` override, so rebuild the generator after regenerating the embedded Go syntax.
An override that replaces `code:vector_loop` is not a substitute for that
embedded template: the same probe is generated again without the override.

## Coverage and Limits

C is compiled with GCC and Clang at `-O0`, `-O1`, `-O2`, and `-Os`, with `-mavx2`
and normal jump-table generation enabled. Both the default and `vec_fixed.syntax`
templates use the same token-loop probe, including refill and token callbacks,
high bytes, singleton and multiple ranges, lookahead, and an all-byte class.
Outlined `.cold` blocks belong to the same graph. Conditional external branches
are checked as exits while their fallthrough is still followed. For an indirect
jump, all local code labels named in assembly table entries are conservative
successors; an unresolved indirect jump fails rather than being ignored.

Go probes are discovered from every `test/codegen/go/004_simd*.re` file, using
the matching `.inc` syntax override when present. They cover byte slices,
strings, unsigned cursors with refill, a custom length check, complement ranges
(`xrange`), and the all-byte class. An empty probe list fails. The complement-range
probe's `.inc` replaces `code:vector_loop` with a test template, so that probe is
also generated with the shipped Go template. The check fails if that shipped
variant is missing. Other overrides, such as a custom length check, leave the
shipped vector template in place. The script parses
the compiler's `go build -gcflags=-S` listing,
using numeric instruction addresses and Plan 9 Y-register operands. This avoids
depending on an object disassembler's support for experimental SIMD encodings.
Every function with Y-register instructions is discovered and checked, regardless
of its name, including additional lexers and compiler-generated functions.
The script reports the probe count and vector-function count for each probe.
Each probe must contain at least one vector-using function, except
`004_simd_all_bytes`: its empty complement only advances the cursor by whole
blocks and needs no Y registers. It is still generated and compiled, and any
Y-register functions it does contain are checked normally.
Calls and returns reached after touching a YMM register must have passed through
`VZEROUPPER` or `VZEROALL`. Bounds/index/slice panic calls and stack-growth restart
paths are treated as terminal exceptions, not ordinary returning user calls.
This does not prove buffer safety or panic-path cleanup; functional and boundary
tests remain necessary. Ordinary runtime calls, including string-to-byte-slice
conversion, are not exempt.

Each vector-using function also has a negative control: replacing every AVX
cleanup instruction with a no-op must produce a dirty exit. The shipped Go
template has one further mutant: its `archsimd.ClearAVXUpperBits()` emission is
removed, the complement-range probe is regenerated from that mutant, and the
check fails unless the resulting exits are dirty. Synthetic graphs
exercise cold branches, table dispatch, and conditional external branches even
when the installed compiler does not happen to emit those shapes.
Go discovery regressions include multiple functions separated by scalar code,
an extra vector function with a dirty exit, function-boundary isolation, and
rejection of empty vector coverage. The all-byte exception is checked both
without Y registers and with an added dirty vector function, so it cannot hide
additional functions from analysis.
