#include <benchmark/benchmark.h>
#include <string.h>

#include "benchmarks/common/common.h"
#include "benchmarks/common/strings_atom.h"
#include "benchmarks/common/strings_date.h"
#include "benchmarks/common/strings_http.h"
#include "benchmarks/common/strings_ipv4.h"
#include "benchmarks/common/strings_ipv6.h"
#include "benchmarks/common/strings_uri.h"
#include "lib/regex.h"


int main(int argc, char** argv)
{
    static const size_t MAX_TITLE = 1024;
    char title[MAX_TITLE];

    static const size_t AAA_LEN = 1 << 14;
    char *aaa = new char[AAA_LEN + 1];
    memset(aaa, 'a', AAA_LEN);
    const char *aaa_strings[] = {aaa, NULL};

    const std::vector<bench_t> benches {
        {"http-rfc7230",   MESSAGE_HEAD,  http_strings, 0},
        {"http-simple",    MESSAGE_HEAD2, http_strings, 0},
        {"uri-rfc3986",    URI,           uri_strings,  0},
        {"uri-simple",     URI2,          uri_strings,  0},
        {"ipv6",           IPV6,          ipv6_strings, 0},
        {"ipv6-simple",    IPV62,         ipv6_strings, 0},
        {"ipv4",           IPV4,          ipv4_strings, 0},
        {"ipv4-simple",    IPV42,         ipv4_strings, 0},
        {"date",           DATE,          date_strings, 0},
        {"date-simple",    DATE2,         date_strings, 0},
        {"package",        PACKAGE_ATOM,  atom_strings, 0},
        {"package-simple", PACKAGE_ATOM2, atom_strings, 0},

        {NULL, "(a)*a{1}",    aaa_strings, 0},
        {NULL, "(a)*a{10}",   aaa_strings, 0},
        {NULL, "(a)*a{100}",  aaa_strings, 0},
        {NULL, "(a)*a{1000}", aaa_strings, 0},
    };

    const std::vector<alg_t> algs {
        {"regs-last-offset",   ENGINE_RE2C, 0},
        {"noregs-last-offset", ENGINE_RE2C, REG_REGLESS},
        {"regs-all-offsets",   ENGINE_RE2C, REG_SUBHIST},
        {"noregs-all-offsets", ENGINE_RE2C, REG_SUBHIST | REG_REGLESS},
    };

    benchmark::Initialize(&argc, argv);

    for (const bench_t &bench : benches) {
        for (const alg_t &alg : algs) {
            if (alg.flags & bench.not_flags) continue;

            const char *name = bench.name ? bench.name : bench.regexp;
            snprintf(title, MAX_TITLE, "%s-regcomp_%s", name, alg.name);
            benchmark::RegisterBenchmark(title, bench_regcomp_t(), alg, bench)
                ->Unit(benchmark::kMicrosecond);
        }
        for (const alg_t &alg : algs) {
            if (alg.flags & bench.not_flags) continue;

            const char *name = bench.name ? bench.name : bench.regexp;
            snprintf(title, MAX_TITLE, "%s-regexec_%s", name, alg.name);
            benchmark::RegisterBenchmark(title, bench_regexec_t(), alg, bench)
                ->Unit(benchmark::kMicrosecond);
        }
    }

    benchmark::RunSpecifiedBenchmarks();

    delete[] aaa;
}
