#include <assert.h>
#include <string.h>
#include <time.h>

#include "benchmarks/common/common.h"
#include "benchmarks/common/strings_atom.h"
#include "benchmarks/common/strings_date.h"
#include "benchmarks/common/strings_http.h"
#include "benchmarks/common/strings_ipv4.h"
#include "benchmarks/common/strings_ipv6.h"
#include "benchmarks/common/strings_uri.h"
#include "lib/regex.h"


const benchmark_t benchmarks[] = {
    {"re2c-tdfa-posix",           ENGINE_RE2C, 0},
    {"re2c-tdfa-leftmost",        ENGINE_RE2C, REG_LEFTMOST},
    //{"re2c-stadfa",               ENGINE_RE2C, REG_STADFA},
};

const size_t nbenchmarks = sizeof(benchmarks) / sizeof(benchmark_t);

void show(const std::vector<Result> &results)
{
    const size_t n = results.size();
    assert(n > 0);

    const uint64_t ticks0_gen = results[0].ticks_gen;
    const uint64_t ticks0_run = results[0].ticks_run;

    fprintf(stderr, "%30s %13s%13s%13s%12s\n", "", "gen", "run", "gen+run", "gen+run %");
    for (size_t i = 0; i < n; ++i) {
        const Result &r = results[i];
        if (r.ticks_gen == UNAVAIL || r.ticks_run == UNAVAIL) {
            assert(r.ticks_gen == UNAVAIL && r.ticks_run == UNAVAIL);
            fprintf(stderr, "%30s:%13s%13s%13s%12s\n", r.title, "-", "-", "-", "-");
        } else {
            fprintf(stderr, "%30s:%12.3lfs%12.3lfs%12.3lfs%12.2lf\n", r.title,
                double(r.ticks_gen) / CLOCKS_PER_SEC,
                double(r.ticks_run) / CLOCKS_PER_SEC,
                double(r.ticks_gen + r.ticks_run) / CLOCKS_PER_SEC,
                double(r.ticks_gen + r.ticks_run) / double(ticks0_gen + ticks0_run));
        }
    }
}

int main()
{
    const char *regexp;
    std::vector<std::string> strings;
    static const size_t VERY_LONG = (1 << 14) + 1;
    char *longstring = new char[VERY_LONG + 1];

    // http
    LOAD_STRINGS(strings, http);
    regexp = MESSAGE_HEAD;
    bench(regexp, strings, 10000, 0, 0);
    regexp = MESSAGE_HEAD2;
    bench(regexp, strings, 10000, 0, 0);

    // uri
    LOAD_STRINGS(strings, uri);
    regexp = URI;
    bench(regexp, strings, 10000, 0, 0);
    regexp = URI2;
    bench(regexp, strings, 10000, 0, 0);

    // ipv6
    LOAD_STRINGS(strings, ipv6);
    regexp = IPV6;
    bench(regexp, strings, 100000, 0, 0);
    regexp = IPV62;
    bench(regexp, strings, 100000, 0, 0);

    // ipv4
    LOAD_STRINGS(strings, ipv4);
    regexp = IPV4;
    bench(regexp, strings, 1000000, 0, 0);
    regexp = IPV42;
    bench(regexp, strings, 1000000, 0, 0);

    // date
    LOAD_STRINGS(strings, date);
    regexp = DATE;
    bench(regexp, strings, 100000, 0, 0);
    regexp = DATE2;
    bench(regexp, strings, 100000, 0, 0);

    // atom
    LOAD_STRINGS(strings, atom);
    regexp = PACKAGE_ATOM;
    bench(regexp, strings, 10000, 0, 0);
    regexp = PACKAGE_ATOM2;
    bench(regexp, strings, 10000, 0, 0);

    longstring[VERY_LONG] = 0;
    memset(longstring, 'a', VERY_LONG);
    longstring[VERY_LONG] = 0;
    strings.clear();
    strings.push_back(longstring);

    //regexp = "((((a){2})|((a){3})|((a){5}))*)a{1000}";
    regexp = "((a{2}|a{3}|a{5})*)a{1000}";
    bench(regexp, strings, 100, 0, 0);

    //regexp = "(((a)|(aa))*)a{1000}";
    regexp = "((a|aa)*)a{1000}";
    bench(regexp, strings, 100, 0, 0);

    //regexp = "(((a)?)*)a{1000}";
    regexp = "((a?)*)a{1000}";
    bench(regexp, strings, 100, 0, 0);

    delete[] longstring;
    return 0;
}

