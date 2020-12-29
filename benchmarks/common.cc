#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <vector>
#include <string>

#include "benchmarks/common.h"
#include "lib/regex.h"

#ifdef HAVE_RE2_RE2_H
#include "re2/re2.h"
#endif


static void bench_re2c(std::vector<Result> &results, const char *regexp,
    const std::vector<std::string> &strings, size_t ntimes,
    int flags, int mask, int need, const char *prefix)
{
    Result x = {prefix, UNAVAIL, UNAVAIL};
    if ((flags & mask) || (need != 0 && !(flags & need))) return;

    regex_t re;
    int err;
    clock_t t1 = 0, t2 = 0, t3 = 0, t4 = 0;

    t1 = clock();
    err = regcomp(&re, regexp, flags);
    t2 = clock();
    if (err) {
        fprintf(stderr, "*** %s compile failed\n", prefix);
        exit(1);
    }

    const size_t nmatch = re.re_nsub;
    regmatch_t *pmatch = new regmatch_t[nmatch];

    // first time is warmup
    for (size_t k = 0; k < 2; ++k) {
        t3 = clock();
        err = 0;
        for (size_t j = 0; j < strings.size(); ++j) {
            for (size_t i = 0; i < ntimes; ++i) {
                err |= regexec(&re, strings[j].c_str(), nmatch, pmatch, 0);
            }
        }
        t4 = clock();
    }
    if (err) {
        fprintf(stderr, "*** %s run failed\n", prefix);
        exit(1);
    }

    delete[] pmatch;
    regfree(&re);

    x.ticks_gen = uint64_t(t2 - t1);
    x.ticks_run = uint64_t(t4 - t3);

    results.push_back(x);
}

#ifdef HAVE_RE2_RE2_H
static void bench_re2(std::vector<Result> &results, const char *regexp,
    const std::vector<std::string> &strings, size_t ntimes, int mask, const char *prefix)
{
    Result x = {prefix, UNAVAIL, UNAVAIL};
    if (mask & XREG_RE2) return;

    RE2 *re2;
    clock_t t1 = 0, t2 = 0, t3 = 0, t4 = 0;
    bool ok = true;

    t1 = clock();
    re2 = new RE2(regexp, RE2::POSIX);
    t2 = clock();
    if (!re2->ok()) {
        fprintf(stderr, "*** %s compile failed\n", prefix);
        exit(1);
    }

    const int argc = re2->NumberOfCapturingGroups();
    RE2::Arg *args = new RE2::Arg[argc];
    RE2::Arg **argps = new RE2::Arg*[argc];
    std::string *submatch = new std::string[argc];
    for (int i = 0; i < argc; ++i) {
        args[i] = &submatch[i];
        argps[i] = &args[i];
    }

    // first time is warmup
    for (size_t k = 0; k < 2; ++k) {
        t3 = clock();
        for (size_t j = 0; j < strings.size(); ++j) {
            for (size_t i = 0; i < ntimes; ++i) {
                ok = ok && RE2::FullMatchN(strings[j].c_str(), *re2, argps, argc);
            }
        }
        t4 = clock();
    }
    if (!ok) {
        fprintf(stderr, "*** %s run failed\n", prefix);
        exit(1);
    }

    delete[] submatch;
    delete[] argps;
    delete[] args;
    delete re2;

    x.ticks_gen = uint64_t(t2 - t1);
    x.ticks_run = uint64_t(t4 - t3);

    results.push_back(x);
}
#else
static void bench_re2(std::vector<Result>, const char *,
    const std::vector<std::string> &, size_t, int, const char *) {}
#endif

static size_t groupcnt(const char *regexp)
{
    regex_t re;
    int err = regcomp(&re, regexp, REG_NFA);
    if (err) {
        fprintf(stderr,
            "*** cannot find the number of capturing groups for RE %s\n",
            regexp);
        exit(1);
    }
    return re.re_nsub;
}

void bench(const char *regexp, const std::vector<std::string> &strings, uint32_t times,
    int mask, int need)
{
    assert(!strings.empty());
    const char *s0 = strings[0].c_str();

    fprintf(stderr, "\nr: %.*s..., s: %.*s..., n: %u, %u chars, %u groups\n",
        30, regexp, 30, s0, times, (uint32_t)strlen(regexp), (uint32_t)groupcnt(regexp));

    std::vector<Result> rs;
    rs.reserve(nbenchmarks);

    for (size_t i = 0; i < nbenchmarks; ++i) {
        const benchmark_t &b = benchmarks[i];
        switch (b.engine) {
        case ENGINE_RE2C:
            bench_re2c(rs, regexp, strings, times, b.flags, mask, need, b.name);
            break;
        case ENGINE_RE2:
            bench_re2(rs, regexp, strings, times, mask, b.name);
            break;
        }
    }

    show(rs);
}

static void load_strings(std::vector<std::string> &strings,
    const char *fname, const char *delim)
{
    FILE *f = fopen(fname, "r");
    if (!f) {
        fprintf(stderr, "cannot open file %s\n", fname);
        exit(1);
    }

    fseek(f, 0, SEEK_END);
    const size_t flen = static_cast<size_t>(ftell(f));
    fseek(f, 0, SEEK_SET);

    char *fbuf = new char[flen];
    if (flen != fread(fbuf, 1, flen, f)) {
        fprintf(stderr, "cannot read file %s\n", fname);
        exit(1);
    }

    strings.clear();
    const size_t dlen = strlen(delim);
    for (char *p1 = fbuf, *p2 = fbuf, *p3 = fbuf + flen; p2 < p3; ) {
        for (p1 = p2; p2 + dlen <= p3; ++p2) {
            if (memcmp(p2, delim, dlen) == 0) {
                p2 += dlen;
                break;
            }
        }
        strings.push_back(std::string(p1, static_cast<size_t>(p2 - p1 - 1)));
    }

    delete[] fbuf;
    fclose(f);
}

void load_strings_http(std::vector<std::string> &strings)
{
    load_strings(strings, "../benchmarks/data/http", "\n\n");
}

void load_strings_uri(std::vector<std::string> &strings)
{
    load_strings(strings, "../benchmarks/data/uri", "\n");
}

void load_strings_atom(std::vector<std::string> &strings)
{
    load_strings(strings, "../benchmarks/data/atom", "\n");
}

void load_strings_date(std::vector<std::string> &strings)
{
    strings.clear();
    strings.push_back("Mon Jan 01 2019 00:24:00 GMT");
    strings.push_back("Tue Feb 02 2018 01:24:00 GMT");
    strings.push_back("Wed Mar 03 2017 02:24:00 GMT");
    strings.push_back("Thu Apr 04 2016 03:24:00 GMT");
    strings.push_back("Fri May 05 2015 04:24:00 GMT");
    strings.push_back("Sat Jun 06 2014 05:24:00 GMT");
    strings.push_back("Sun Jul 07 2013 06:24:00 GMT");
}

void load_strings_ipv6(std::vector<std::string> &strings)
{
    strings.clear();
    strings.push_back("fee2:586:10aa:fd03:37f:76ee:bed7:880");
    strings.push_back("::fee2:586:fd03:37f:76ee:bed7:880");
    strings.push_back("fee2::586:fd03:37f:76ee:bed7:880");
    strings.push_back("fee2:586::fd03:37f:76ee:bed7:880");
    strings.push_back("fee2:586:fd03::37f:76ee:bed7:880");
    strings.push_back("fee2:586:fd03:37f::76ee:bed7:880");
    strings.push_back("fee2:586:fd03:37f:76ee::bed7:880");
    strings.push_back("fee2:586:fd03:37f:76ee:bed7::880");
    strings.push_back("fee2:586:fd03:37f:76ee:bed7:880::");
    strings.push_back("::586:fd03:37f:76ee:bed7:880");
    strings.push_back("fee2::fd03:37f:76ee:bed7:880");
    strings.push_back("fee2:fd03::37f:76ee:bed7:880");
    strings.push_back("fee2:fd03:37f::76ee:bed7:880");
    strings.push_back("fee2:fd03:37f:76ee::bed7:880");
    strings.push_back("fee2:fd03:37f:76ee:bed7::880");
    strings.push_back("fee2:fd03:37f:76ee:bed7:880::");
    strings.push_back("::fd03:37f:76ee:bed7:880");
    strings.push_back("fd03::37f:76ee:bed7:880");
    strings.push_back("fd03:37f::76ee:bed7:880");
    strings.push_back("fd03:37f:76ee::bed7:880");
    strings.push_back("fd03:37f:76ee:bed7::880");
    strings.push_back("fd03:fd03:37f:76ee:bed7::");
    strings.push_back("::37f:76ee:bed7:880");
    strings.push_back("fd03::76ee:bed7:880");
    strings.push_back("fd03:37f::bed7:880");
    strings.push_back("fd03:37f:76ee::880");
    strings.push_back("fd03:37f:76ee:bed7::");
    strings.push_back("::76ee:bed7:880");
    strings.push_back("fd03::bed7:880");
    strings.push_back("fd03:37f::880");
    strings.push_back("fd03:37f:76ee::");
    strings.push_back("::bed7:880");
    strings.push_back("fd03::880");
    strings.push_back("fd03:37f::");
    strings.push_back("::bed7");
    strings.push_back("fd03::");
    strings.push_back("::");
}

void load_strings_ipv4(std::vector<std::string> &strings)
{
    strings.clear();
    strings.push_back("127.0.0.1");
    strings.push_back("192.168.1.200");
    strings.push_back("255.255.255.255");
    strings.push_back("8.8.8.8");
    strings.push_back("240.147.163.34");
}
