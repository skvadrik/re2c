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
        {"http-rfc7230",   MESSAGE_HEAD,  http_strings},
        {"http-simple",    MESSAGE_HEAD2, http_strings},
        {"uri-rfc3986",    URI,           uri_strings},
        {"uri-simple",     URI2,          uri_strings},
        {"ipv6",           IPV6,          ipv6_strings},
        {"ipv4",           IPV4,          ipv4_strings},
        {"date",           DATE,          date_strings},
        {"package",        PACKAGE_ATOM,  atom_strings},

        {NULL, "(a)*a{10}",   aaa_strings},
        {NULL, "(a)*a{100}",  aaa_strings},
        {NULL, "(a)*a{1000}", aaa_strings},
    };

    const std::vector<alg_t> algs {
        {"last-offset",           ENGINE_RE2C, 0},
        {"multipass-last-offset", ENGINE_RE2C, REG_MULTIPASS},
        {"all-offsets",           ENGINE_RE2C, REG_SUBHIST},
        {"multipass-all-offsets", ENGINE_RE2C, REG_SUBHIST | REG_MULTIPASS},
    };

    benchmark::Initialize(&argc, argv);

    for (const bench_t &bench : benches) {
        for (const alg_t &alg : algs) {
            const char *name = bench.name ? bench.name : bench.regexp;
            snprintf(title, MAX_TITLE, "%s-regcomp_%s", name, alg.name);
            benchmark::RegisterBenchmark(title, bench_regcomp_t(), alg, bench)
                ->Unit(benchmark::kMicrosecond);
        }
        for (const alg_t &alg : algs) {
            const char *name = bench.name ? bench.name : bench.regexp;
            snprintf(title, MAX_TITLE, "%s-regexec_%s", name, alg.name);
            benchmark::RegisterBenchmark(title, bench_regexec_t(), alg, bench)
                ->Unit(benchmark::kMicrosecond);
        }
    }

    benchmark::RunSpecifiedBenchmarks();

    delete[] aaa;
}
