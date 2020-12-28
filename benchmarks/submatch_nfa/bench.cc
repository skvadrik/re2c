#include <string.h>

#include "config.h"
#include "benchmarks/common.h"
#include "lib/regex.h"


const benchmark_t benchmarks[] = {
    {"re2c-tnfa-leftmost",        ENGINE_RE2C, REG_NFA | REG_LEFTMOST},
    {"re2c-tnfa-leftmost-trie",   ENGINE_RE2C, REG_NFA | REG_LEFTMOST | REG_TRIE},
#ifdef HAVE_RE2_RE2_H
    {"re2",                       ENGINE_RE2,  0},
#endif
    {"re2c-tnfa-posix-gor1",      ENGINE_RE2C, REG_NFA | REG_GTOP},
    {"re2c-tnfa-posix-gtop",      ENGINE_RE2C, REG_NFA},
    {"re2c-tnfa-posix-gor1-slow", ENGINE_RE2C, REG_NFA | REG_SLOWPREC},
    {"re2c-tnfa-posix-gor1-trie", ENGINE_RE2C, REG_NFA | REG_TRIE},
    {"re2c-tnfa-posix-kukl-gor1", ENGINE_RE2C, REG_NFA | REG_KUKLEWICZ},
    {"re2c-tnfa-posix-back-gor1", ENGINE_RE2C, REG_NFA | REG_BACKWARD}
};

const size_t nbenchmarks = sizeof(benchmarks) / sizeof(benchmark_t);

int main()
{
    const char *regexp;
    std::vector<std::string> strings;
    static const size_t VERY_LONG = (1 << 14) + 1;
    static const size_t TIMES = 10;
    char *longstring = new char[VERY_LONG + 1];

    // http
    load_strings("../benchmarks/data/http", "\n\n", strings);
    regexp = MESSAGE_HEAD;
    bench(regexp, strings, 100, REG_BACKWARD | REG_STADFA, 0);
    regexp = MESSAGE_HEAD2;
    bench(regexp, strings, 100, REG_BACKWARD, 0);

    // uri
    load_strings("../benchmarks/data/uri", "\n", strings);
    regexp = URI;
    bench(regexp, strings, 100, REG_BACKWARD | REG_STADFA, 0);
    regexp = URI2;
    bench(regexp, strings, 100, 0, 0);

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
    bench(regexp, strings, 100, REG_BACKWARD, 0);
    regexp = IPV62;
    bench(regexp, strings, 100, 0, REG_NFA); // DFA is very large

    strings.clear();
    strings.push_back("127.0.0.1");
    strings.push_back("192.168.1.200");
    strings.push_back("255.255.255.255");
    strings.push_back("8.8.8.8");
    strings.push_back("240.147.163.34");
    regexp = IPV4;
    bench(regexp, strings, 10000, 0, 0);
    regexp = "([0-9]{1,3})[.]([0-9]{1,3})[.]([0-9]{1,3})[.]([0-9]{1,3})";
    bench(regexp, strings, 10000, 0, 0);

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
    bench(regexp, strings, 1000, 0, 0);
    regexp = "([a-zA-Z]+)[ ]+([a-zA-Z]+)[ ]+([0-9]+)[ ]+([0-9]+)[ ]+([0-9:-]+)[ ]+([A-Z0-9+-]+)";
    bench(regexp, strings, 1000, 0, 0);

    // atom
    load_strings("../benchmarks/data/atom", "\n", strings);
    regexp = PACKAGE_ATOM;
    bench(regexp, strings, 10, 0, 0);
    regexp = PACKAGE_ATOM2;
    bench(regexp, strings, 10, 0, 0);

    longstring[VERY_LONG] = 0;
    memset(longstring, 'a', VERY_LONG);
    longstring[VERY_LONG] = 0;
    strings.clear();
    strings.push_back(longstring);

    regexp = "(a{2}|a{3}|a{5})*";
    bench(regexp, strings, TIMES, 0, 0);
    regexp = "(a{7}|a{13}|a{19})*";
    bench(regexp, strings, TIMES, 0, 0);
    regexp = "(a{29}|a{41}|a{53})*";
    bench(regexp, strings, TIMES, 0, 0);
    regexp = "(a{67}|a{83}|a{103})*";
    bench(regexp, strings, TIMES, 0, 0);
    regexp = "(a{127}|a{151}|a{179})*";
    bench(regexp, strings, TIMES, 0, 0);
    regexp = "(a{199}|a{239}|a{271})*";
    bench(regexp, strings, TIMES, 0, 0);

    regexp = "(((a){2})|((a){3})|((a){5}))*";
    bench(regexp, strings, TIMES, 0, 0);
    regexp = "(((a){7})|((a){13})|((a){19}))*";
    bench(regexp, strings, TIMES, 0, 0);
    regexp = "(((a){29})|((a){41})|((a){53}))*";
    bench(regexp, strings, TIMES, 0, 0);
    regexp = "(((a){67})|((a){83})|((a){103}))*";
    bench(regexp, strings, TIMES, 0, 0);
    regexp = "(((a){127})|((a){151})|((a){179}))*";
    bench(regexp, strings, TIMES, 0, 0);
    regexp = "(((a){199})|((a){239})|((a){271}))*";
    bench(regexp, strings, TIMES, 0, 0);

    regexp = "(a{0,1})*";
    bench(regexp, strings, 1, 0, 0);
    regexp = "(a{0,256})*";
    bench(regexp, strings, 1, 0, 0);
    regexp = "(a{0,512})*";
    bench(regexp, strings, 1, 0, 0);

    regexp = "((a){0,1})*";
    bench(regexp, strings, 1, 0, 0);
    regexp = "((a){0,256})*";
    bench(regexp, strings, 1, 0, 0);
    regexp = "((a){0,512})*";
    bench(regexp, strings, 1, 0, 0);

    // Pathological case for constant-memory POSIX algorithms that use naive
    // (worst-case cubic in the size of TNFA) algorithm for precedence matrix
    // computation. Cubic behaviour is caused by quadratic-time computation
    // of precedence matrix on each step (the number of core items in closure
    // approaches TNFA size), multiplied by the length of compared histores
    // (which also approaches TNFA size). Trie-based algorithms are not
    // affected, but they consume memory proportional to the length of input,
    // and so are also not practical.

    regexp = "((a?){0,1})*";
    bench(regexp, strings, 1, 0, 0);
    regexp = "((a?){0,256})*";
    bench(regexp, strings, 1, 0, 0);
    regexp = "((a?){0,512})*";
    bench(regexp, strings, 1, 0, 0);

    regexp = "((a*){0,1})*";
    bench(regexp, strings, 1, 0, 0);
    regexp = "((a*){0,256})*";
    bench(regexp, strings, 1, 0, 0);
    regexp = "((a*){0,512})*";
    bench(regexp, strings, 1, 0, 0);

    delete[] longstring;
    return 0;
}

