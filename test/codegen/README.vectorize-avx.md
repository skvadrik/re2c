# AVX/SSE Register Hygiene Regression Test

The optional CMake target `check_vectorize_avx` generates C and Go lexers for
both `--vectorize-size 16` (SSE2 / XMM) and `--vectorize-size 32` (AVX2 / YMM)
and checks assembly control flow without executing AVX instructions. It requires
x86-64 Linux, Python 3, GCC, Clang and Go 1.27 or newer with the `simd`
experiment. Missing tools or unsupported assembly cause a failure, not a
successful skip.

```sh
cmake -S . -B build-avx -DRE2C_BUILD_TESTS=ON
cmake --build build-avx --target check_vectorize_avx -j2
```

To retain all generated sources and assembly, or isolate a backend:

```sh
python3 test/codegen/c/check_vectorize_avx.py build-avx/re2c --output-dir /tmp/re2c-avx
python3 test/codegen/c/check_vectorize_avx.py build-avx/re2c --language c
python3 test/codegen/c/check_vectorize_avx.py build-avx/re2c --language go
```

## Coverage

- **C (`--arch x86`)**: verifies that generated C contains no explicit
  `_mm256_zeroupper()` or `volatile` workaround; checks width 32 under GCC and
  Clang with `-O2 -mavx2` and `-O0/-O1 -mavx2 -mvzeroupper` across default,
  `--loop-switch`, `--eager-skip` and `--api generic`, and verifies that width
  16 (`-msse2`) touches zero YMM registers.
- **Go (`--arch x86`, `GOEXPERIMENT=simd`)**: discovers all
  `test/codegen/go/004_simd*.re` probes, verifies clean YMM exits for width 32,
  verifies that width 16 emits no `archsimd.ClearAVXUpperBits()` and touches
  zero YMM registers, and verifies via a `code:vec32_cleanup = "";` negative
  mutant that removing Go's YMM cleanup produces dirty exits.
