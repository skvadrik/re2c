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

    static const size_t AAA_LEN = 1 << 13;
    char *aaa = new char[AAA_LEN + 1];
    memset(aaa, 'a', AAA_LEN);
    const char *aaa_strings[] = {aaa, NULL};

    const std::vector<bench_t> benches = {
        {"HTTP-RFC7230",   MESSAGE_HEAD,  http_strings, REG_BACKWARD},
        {"HTTP-simple",    MESSAGE_HEAD2, http_strings, 0},

        {"URI-RFC3986",    URI,           uri_strings,  0},
        {"URI-simple",     URI2,          uri_strings,  0},

        {"IPv6",           IPV6,          ipv6_strings, 0},
        {"IPv6-simple",    IPV62,         ipv6_strings, 0},
        {"IPv4",           IPV4,          ipv4_strings, 0},
        {"IPv4-simple",    IPV42,         ipv4_strings, 0},
        {"date",           DATE,          date_strings, 0},
        {"date-simple",    DATE2,         date_strings, 0},
        {"package",        PACKAGE_ATOM,  atom_strings, 0},
        {"package-simple", PACKAGE_ATOM2, atom_strings, 0},

        {NULL, "(a{2}|a{3}|a{5})*",       aaa_strings, 0},
        {NULL, "(a{7}|a{13}|a{19})*",     aaa_strings, 0},
        {NULL, "(a{29}|a{41}|a{53})*",    aaa_strings, 0},
        {NULL, "(a{67}|a{83}|a{103})*",   aaa_strings, 0},
        {NULL, "(a{127}|a{151}|a{179})*", aaa_strings, 0},
        {NULL, "(a{199}|a{239}|a{271})*", aaa_strings, 0},

        {NULL, "(((a){2})|((a){3})|((a){5}))*",       aaa_strings, 0},
        {NULL, "(((a){7})|((a){13})|((a){19}))*",     aaa_strings, 0},
        {NULL, "(((a){29})|((a){41})|((a){53}))*",    aaa_strings, 0},
        {NULL, "(((a){67})|((a){83})|((a){103}))*",   aaa_strings, 0},
        {NULL, "(((a){127})|((a){151})|((a){179}))*", aaa_strings, 0},
        {NULL, "(((a){199})|((a){239})|((a){271}))*", aaa_strings, 0},

        {NULL, "(a{0,16})*",    aaa_strings, 0},
        {NULL, "((a){0,16})*",  aaa_strings, 0},
        {NULL, "(a{0,64})*",    aaa_strings, 0},
        {NULL, "((a){0,64})*",  aaa_strings, 0},
        {NULL, "(a{0,256})*",   aaa_strings, 0},
        {NULL, "((a){0,256})*", aaa_strings, 0},

        // Pathological case for constant-memory POSIX algorithms that use naive
        // (worst-case cubic in the size of TNFA) algorithm for precedence matrix
        // computation. Cubic behaviour is caused by quadratic-time computation
        // of precedence matrix on each step (the number of core items in closure
        // approaches TNFA size), multiplied by the length of compared histores
        // (which also approaches TNFA size). Trie-based algorithms are not
        // affected, but they consume memory proportional to the length of input,
        // and so are also not practical.

        {NULL, "((a?){0,16})*",  aaa_strings, 0},
        {NULL, "((a*){0,16})*",  aaa_strings, 0},
        {NULL, "((a?){0,64})*",  aaa_strings, 0},
        {NULL, "((a*){0,64})*",  aaa_strings, 0},
        {NULL, "((a?){0,256})*", aaa_strings, 0},
        {NULL, "((a*){0,256})*", aaa_strings, 0},
    };

    const std::vector<alg_t> algs = {
        {"LG",        ENGINE_RE2C, REG_NFA | REG_LEFTMOST},
        {"lazy-LG",   ENGINE_RE2C, REG_NFA | REG_LEFTMOST | REG_TRIE},
        {"OS",        ENGINE_RE2C, REG_NFA | REG_GTOP},
        {"GTOP-OS",   ENGINE_RE2C, REG_NFA},
        {"simple-OS", ENGINE_RE2C, REG_NFA | REG_SLOWPREC},
        {"lazy-OS",   ENGINE_RE2C, REG_NFA | REG_TRIE},
        {"Kuklewicz", ENGINE_RE2C, REG_NFA | REG_KUKLEWICZ},
        {"Backward",  ENGINE_RE2C, REG_NFA | REG_BACKWARD},
#ifdef HAVE_RE2_RE2_H
        {"re2-LG",    ENGINE_RE2,  0},
#endif
    };

    benchmark::Initialize(&argc, argv);

    for (const bench_t &bench : benches) {
        for (const alg_t &alg : algs) {
            if (alg.flags & bench.not_flags) continue;

            const char *name = bench.name ? bench.name : bench.regexp;
            snprintf(title, MAX_TITLE, "%s_%s", name, alg.name);
            benchmark::RegisterBenchmark(title, bench_regexec_t(), alg, bench)
                ->Unit(benchmark::kMicrosecond);
        }
    }

    benchmark::RunSpecifiedBenchmarks();

    delete[] aaa;
}
