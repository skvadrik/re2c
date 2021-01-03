bench_submatch_nfa_CXXFLAGS = $(AM_CXXFLAGS) -std=c++11 -O3 -I $(top_srcdir)
bench_submatch_nfa_LDFLAGS = $(LDFLAGS_RE2)
bench_submatch_nfa_LDADD = $(top_builddir)/libre2c.la

noinst_PROGRAMS = bench_submatch_nfa

bench_submatch_nfa_SOURCES = \
    bench.cc \
    $(top_srcdir)/benchmarks/common.cc \
    $(top_srcdir)/benchmarks/common.h

all-local: bench_submatch_nfa
