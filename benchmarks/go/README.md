# Go benchmarks for linear vectorization

Compare `re2c:vectorize:linear = 0` and `= 1` using Go's `testing.B` and the
shared generator in `benchmarks/_scripts/gen_linear.py`. C benchmarks for
`--vectorize-linear` live in `benchmarks/c` (`lin_00__http` and `lin-regime-*`).

## Workloads and correctness

`../_scripts/gen_linear.py` uses Python's `random.Random(586)` to produce 1024
known HTTP header names, 1024 unknown names and variable-length values in three
layouts (`isolated`, `names`, `values`), plus `sql_original` (4096 elements
mixing SQL keywords, identifiers, near misses, digits and punctuation).

`TestTokenTraces` and `TestUnpaddedTailEdges` validate complete `(kind, length)`
traces, exact byte consumption, unpadded tail bounds guards, and end of input
against the independent Python longest-match regular-expression oracle before
timing.

## Usage

From `benchmarks/go`:

```sh
make generate RE2GO=/path/to/re2go
make check
make smoke
```
