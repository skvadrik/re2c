#include <string.h>

#include "benchmarks/common/common.h"
#include "lib/regex.h"

#ifdef HAVE_RE2_RE2_H
#include "re2/re2.h"
#endif


static void add_counters(benchmark::State &state, const alg_t &,
    const bench_t &bench, int captures)
{
    size_t bytes = 0;
    for (const char **s = bench.strings; *s; ++s) {
        bytes += strlen(*s);
    }

    state.counters["captures"] = double(captures);
    state.counters["regsize"] = double(strlen(bench.regexp));
}

void bench_regcomp_re2c(benchmark::State& state, const alg_t &alg, const bench_t &bench)
{
    int err = 0;
    size_t nmatch = 0;

    for (auto _ : state) {
        regex_t re;
        err = regcomp(&re, bench.regexp, alg.flags);
        nmatch = re.re_nsub;
        regfree(&re);
    }
    if (err) {
        state.SkipWithError("regcomp failed");
    }

    add_counters(state, alg, bench, int(nmatch) - 1);
}

void bench_regexec_re2c(benchmark::State& state, const alg_t &alg, const bench_t &bench)
{
    regex_t re;
    int err = regcomp(&re, bench.regexp, alg.flags);
    if (err) {
        state.SkipWithError("regcomp failed");
    }

    const bool with_hist = alg.flags & REG_SUBHIST;
    const size_t nmatch = re.re_nsub;
    regmatch_t *pmatch = with_hist ? NULL : new regmatch_t[nmatch];

    // Do not move condition inside of the loop to avoid overhead.
    if (with_hist) {
        for (auto _ : state) {
            for (const char **strings = bench.strings; *strings; ++strings) {
                subhistory_t *h = regparse(&re, *strings, nmatch);
                err |= h ? 0 : 1;
                regfreesub(h);
            }
        }
    } else {
        for (auto _ : state) {
            for (const char **strings = bench.strings; *strings; ++strings) {
                err |= regexec(&re, *strings, nmatch, pmatch, 0);
            }
        }
    }
    if (err) {
        state.SkipWithError("regexec failed");
    }

    add_counters(state, alg, bench, int(nmatch) - 1);

    delete[] pmatch;
    regfree(&re);
}

#ifdef HAVE_RE2_RE2_H
void bench_regcomp_re2(benchmark::State &state, const alg_t &alg, const bench_t &bench)
{
    bool ok = true;
    int argc = 0;

    for (auto _ : state) {
        RE2 re(bench.regexp, RE2::POSIX);
        ok = re.ok();
        argc = re.NumberOfCapturingGroups();
    }
    if (!ok) {
        state.SkipWithError("regcomp failed");
    }

    add_counters(state, alg, bench, argc);
}

void bench_regexec_re2(benchmark::State &state, const alg_t &alg, const bench_t &bench)
{
    RE2 re(bench.regexp, RE2::POSIX);
    if (!re.ok()) {
        state.SkipWithError("regcomp failed");
    }

    const int argc = re.NumberOfCapturingGroups();
    RE2::Arg *args = new RE2::Arg[argc];
    RE2::Arg **argps = new RE2::Arg*[argc];
    std::string *submatch = new std::string[argc];
    for (int i = 0; i < argc; ++i) {
        args[i] = &submatch[i];
        argps[i] = &args[i];
    }

    bool ok = true;
    for (auto _ : state) {
        for (const char **strings = bench.strings; *strings; ++strings) {
            ok = ok && RE2::FullMatchN(*strings, re, argps, argc);
        }
    }
    if (!ok) {
        state.SkipWithError("regexec failed");
    }

    add_counters(state, alg, bench, argc);

    delete[] submatch;
    delete[] argps;
    delete[] args;
}
#else
void bench_regcomp_re2(benchmark::State &, const alg_t &, const bench_t &) {}
void bench_regexec_re2(benchmark::State &, const alg_t &, const bench_t &) {}
#endif

void bench_regcomp_t::operator()(benchmark::State &state, const alg_t &alg,
    const bench_t &bench) const {
    alg.engine == ENGINE_RE2C
        ? bench_regcomp_re2c(state, alg, bench)
        : bench_regcomp_re2(state, alg, bench);
}

void bench_regexec_t::operator()(benchmark::State &state, const alg_t &alg,
    const bench_t &bench) const {
    alg.engine == ENGINE_RE2C
        ? bench_regexec_re2c(state, alg, bench)
        : bench_regexec_re2(state, alg, bench);
}
