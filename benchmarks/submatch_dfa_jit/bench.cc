#include <assert.h>
#include <string.h>
#include <time.h>

#include "benchmarks/common.h"
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
    load_strings("../benchmarks/data/http", "\n\n", strings);
    regexp = MESSAGE_HEAD;
    bench(regexp, strings, 10000, 0, 0);
    regexp = MESSAGE_HEAD2;
    bench(regexp, strings, 10000, 0, 0);

    // uri
    load_strings("../benchmarks/data/uri", "\n", strings);
    regexp = URI;
    bench(regexp, strings, 10000, 0, 0);
    regexp = URI2;
    bench(regexp, strings, 10000, 0, 0);

    // ipv6
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
    regexp = IPV6;
    bench(regexp, strings, 100000, 0, 0);
    regexp = IPV62;
    bench(regexp, strings, 100000, 0, 0);

    strings.clear();
    strings.push_back("127.0.0.1");
    strings.push_back("192.168.1.200");
    strings.push_back("255.255.255.255");
    strings.push_back("8.8.8.8");
    strings.push_back("240.147.163.34");
    regexp = IPV4;
    bench(regexp, strings, 1000000, 0, 0);
    regexp = "([0-9]{1,3})[.]([0-9]{1,3})[.]([0-9]{1,3})[.]([0-9]{1,3})";
    bench(regexp, strings, 1000000, 0, 0);
    strings.clear();

    strings.push_back("Mon Jan 01 2019 00:24:00 GMT");
    strings.push_back("Tue Feb 02 2018 01:24:00 GMT");
    strings.push_back("Wed Mar 03 2017 02:24:00 GMT");
    strings.push_back("Thu Apr 04 2016 03:24:00 GMT");
    strings.push_back("Fri May 05 2015 04:24:00 GMT");
    strings.push_back("Sat Jun 06 2014 05:24:00 GMT");
    strings.push_back("Sun Jul 07 2013 06:24:00 GMT");
    regexp = "(Mon|Tue|Wed|Thu|Fri|Sat|Sun)"
        "[ ]+(Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep|Oct|Nov|Dec)"
        "[ ]+([0-9]{2})"
        "[ ]+([0-9]{4})"
        "[ ]+([0-9]{2}):([0-5][0-9]):[0-5][0-9](-[0-5][0-9])?(:[0-5][0-9])?"
        "[ ]+(([A-Z]{3})([+-]([0-5][0-9]):([0-5][0-9]))?)";
    bench(regexp, strings, 100000, 0, 0);
    regexp = "([a-zA-Z]+)[ ]+([a-zA-Z]+)[ ]+([0-9]+)[ ]+([0-9]+)[ ]+([0-9:-]+)[ ]+([A-Z0-9+-]+)";
    bench(regexp, strings, 100000, 0, 0);

    // atom
    load_strings("../benchmarks/data/atom", "\n", strings);
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

