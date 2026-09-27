# SIMD string lexer benchmark

`string_lexer.re` defines one set of rules for a double-quoted string literal
with JSON-like escapes and instantiates it twice:

- `LexStringSIMD` with `re2c:vectorize:loops = 1` (vector fast-forward loop
  on the reflexive `[^"\\\x00\n\r]+` state),
- `LexStringScalar` with `re2c:vectorize:loops = 0` (same rules, same DFA,
  no vector loop).

`string_lexer.go` is generated; do not edit it. To regenerate it with a
re2go binary built from this tree (the flags are the ones used by the test
suite, see the first line of `string_lexer.re`):

    re2go -W string_lexer.re -o string_lexer.go -i --api simple --vectorize-loops \
        --no-version --no-generation-date

## Requirements

- Go 1.27 with `GOEXPERIMENT=simd` (the `simd/archsimd` package is
  experimental; without the experiment all files are excluded by their build
  constraint and `go test` fails with "build constraints exclude all Go files").
- amd64 with AVX2 (the generated code uses 32-byte vectors, which
  `simd/archsimd` only provides on amd64; tests and benchmarks are skipped at
  run time if AVX2 is missing).
- The file that contains the lexer must import both `simd/archsimd` and
  `math/bits`: the default `code:vector_loop` template uses
  `bits.TrailingZeros32` to advance the cursor to the first byte that leaves
  the loop.

## Tests

    GOEXPERIMENT=simd go test

This checks that both generated lexers agree with a hand-written reference
implementation on fixed cases, on every special byte at every position of
strings up to 140 bytes long, and on 200000 random strings; each input is
checked as is and followed by padding, so that short strings also go through
the vector loop. `FuzzParity` can be run for longer with
`GOEXPERIMENT=simd go test -fuzz FuzzParity`.
`TestScalarBaselineIsNotVectorized` checks in the generated code that only
`LexStringSIMD` contains a vector loop.

## Benchmark

The additional `fixedN`, `escapeK`, `stream` and `end-buffer` regimes are described
in [the reproduction guide](../../../../benchmarks/c/REPRODUCIBLE.md), including
short commands, exact corpus definitions and oracle checks. The size and regime
table below describe the original eight regimes only.

    GOEXPERIMENT=simd go test -run '^$' -bench . -benchmem -count 5 | tee bench.txt

Optionally pin the process to one core (e.g. `taskset -c 2`) and compare the
two implementations with [benchstat](https://pkg.go.dev/golang.org/x/perf/cmd/benchstat):

    benchstat -col /impl bench.txt

Each regime is a corpus of about 1 MiB of string literals stored back to back
in one buffer (except `huge`, which is a single 900 KB string, the input used
for the initial measurement). Throughput is in bytes of string literals.

| regime           | strings                                                     | slicing  |
|------------------|-------------------------------------------------------------|----------|
| `short-isolated` | 0..30 bytes, identifiers                                    | isolated |
| `short-inbuf`    | same corpus                                                 | in buffer|
| `medium`         | 32..256 bytes of text, no escapes                           | in buffer|
| `long`           | 4096 bytes of text, no escapes                              | in buffer|
| `huge`           | one 900000-byte string, no escapes                          | in buffer|
| `escapes`        | 64..256 bytes of text, an escape every ~7 bytes             | in buffer|
| `mix-isolated`   | JSON-like mix: 60% keys (2..16 bytes), 25% values (16..120 bytes, rare escapes), 10% prose (200..1000 bytes), 5% blobs (1..4 KiB) | isolated |
| `mix-inbuf`      | same corpus                                                 | in buffer|

With "isolated" slicing, each string is passed to the lexer as a slice of its
own. With "in buffer" slicing, each string is lexed from its start to the end
of the whole buffer, as a lexer working on a larger input would do. The
distinction matters because the vector loop is guarded by the number of bytes
left in the buffer (at least 33), not by the length of the string.
