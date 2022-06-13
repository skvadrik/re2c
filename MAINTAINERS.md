If re2c is unmaintained for a long time and starts to bitrot, or if you have a
fork and need to make it as simple as possible, here is a list of things that
can be cut off rather safely vs. things that are essential.

## Things to remove

These are mostly experimental research projects that have never been used
outside of lab (to the best of author's knowledge, that is):

- Benchmarks: drop optional dependencies on re2, google-benchmark, Java (libre2c
  has JNI bindings); simplify the build system(s).

- libre2c: drop static/dynamic libraries support in the build system(s), e.g.
  Libtool; remove a few internal options and a bunch of explicit template
  instantiations in TDFA construction code that exist only for libre2c.

- One of the build systems: Autotools or CMake, whichever you like less. Someone
  will get unhappy in both cases (Windows is supported only by CMake, but distro
  maintainers may have decades old recipes based on Autotools).

## Things to remove only as a last resort

- Skeleton: it is really useful for testing and codegen validation, but re2c can
  live without it (and a few large tests can be dropped).

- Fuzzers: same here, they are really useful to find bugs and test hypotheses,
  but re2c can function without them.

## Things to keep

- Existing configurations / options / syntax: re2c must stay backwards
  compatible or it will become unusable. One exception is internal/debug options
  which may be removed with caution. For the rest, keep them as deprecated even
  if they do nothing.

- Language backends: they add little code complexity for a lot of value (and
  discipline in the codegen subsystem).

- Documentation (both on `master` branch and the website on `gh-pages` and
  `gh-pages-gen` branches). Without docs no one will know how to use re2c.

