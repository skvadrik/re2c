/*
 * This is not a real benchmark, just some very early attempt at comparing
 * various libre2c algorithms and re2.
 */

#include "config.h"
#include "src/util/c99_stdint.h"
#include "lib/regex.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <vector>
#include <string>

#ifdef HAVE_RE2_RE2_H
#include "re2/re2.h"
#endif


struct Result
{
    const char *title;
    uint64_t ticks;
};

static const uint64_t UNAVAIL = 0xFFFFffffFFFFffff;
static const int XREG_RE2 = 1 << 30;

static inline void show(const std::vector<Result> &results)
{
    const size_t n = results.size();
    assert(n > 0);

    const uint64_t ticks0 = results[0].ticks;

    for (size_t i = 0; i < n; ++i) {
        const Result &r = results[i];
        if (r.ticks == UNAVAIL) {
            fprintf(stderr, "%30s:%10s%10s\n", r.title, "-", "-");
        }
        else {
            fprintf(stderr, "%30s:%10.2lf%10.3lfs\n", r.title
                , double(r.ticks) / double(ticks0)
                , double(r.ticks) / CLOCKS_PER_SEC);
        }
    }
}

static Result bench_re2c(const char *regexp, std::vector<std::string> &strings
    , size_t ntimes, int flags, int mask, int need, const char *prefix)
{
    Result x;
    x.title = prefix;

    if ((flags & mask)
        || (need != 0 && !(flags & need))) {
        x.ticks = UNAVAIL;
        return x;
    }

    regex_t re;
    int err;
    clock_t /*t1 = 0, t2 = 0,*/ t3 = 0, t4 = 0;

    //t1 = clock();
    err = regcomp(&re, regexp, flags);
    //t2 = clock();
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

    x.ticks = uint64_t(t4 - t3);
    return x;
}

#ifdef HAVE_RE2_RE2_H
static Result bench_re2(const char *regexp, std::vector<std::string> &strings
    , size_t ntimes, int mask, const char *prefix)
{
    Result x;
    x.title = prefix;

    if (mask & XREG_RE2) {
        x.ticks = UNAVAIL;
        return x;
    }

    RE2 *re2;
    clock_t /*t1 = 0, t2 = 0,*/ t3 = 0, t4 = 0;
    bool ok = true;

    //t1 = clock();
    re2 = new RE2(regexp, RE2::POSIX);
    //t2 = clock();
    if (!re2->ok()) {
        fprintf(stderr, "*** %s compile failed\n", prefix);
        exit(1);
    }

    const int argc = re2->NumberOfCapturingGroups();
    RE2::Arg *args = new RE2::Arg[argc];
    RE2::Arg **argps = new RE2::Arg*[argc];
    std::string *results = new std::string[argc];
    for (int i = 0; i < argc; ++i) {
        args[i] = &results[i];
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

    delete[] results;
    delete[] argps;
    delete[] args;
    delete re2;

    x.ticks = uint64_t(t4 - t3);
    return x;
}
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

static void bench(const char *r, std::vector<std::string> &ss, uint32_t n
    , int mask, int need)
{
    assert(!ss.empty());
    const char *s0 = ss[0].c_str();

    fprintf(stderr, "\nr: %.*s..., s: %.*s..., n: %u, %u chars, %u groups\n"
        , 30, r, 30, s0, n, (uint32_t)strlen(r), (uint32_t)groupcnt(r));

    std::vector<Result> rs;

    rs.push_back(bench_re2c(r, ss, n, REG_NFA | REG_LEFTMOST,             mask, need, "re2c-tnfa-leftmost"));
    rs.push_back(bench_re2c(r, ss, n, REG_NFA | REG_TRIE | REG_LEFTMOST,  mask, need, "re2c-tnfa-leftmost-trie"));
#ifdef HAVE_RE2_RE2_H
    rs.push_back(bench_re2(r, ss, n, mask, "re2"));
#endif
    rs.push_back(bench_re2c(r, ss, n, REG_NFA,                            mask, need, "re2c-tnfa-posix-gor1"));
    rs.push_back(bench_re2c(r, ss, n, REG_NFA | REG_GTOP,                 mask, need, "re2c-tnfa-posix-gtop"));
    rs.push_back(bench_re2c(r, ss, n, REG_NFA | REG_SLOWPREC,             mask, need, "re2c-tnfa-posix-gor1-slow"));
    rs.push_back(bench_re2c(r, ss, n, REG_NFA | REG_TRIE,                 mask, need, "re2c-tnfa-posix-gor1-trie"));
    rs.push_back(bench_re2c(r, ss, n, REG_NFA | REG_KUKLEWICZ,            mask, need, "re2c-tnfa-posix-kukl-gor1"));
    rs.push_back(bench_re2c(r, ss, n, REG_NFA | REG_BACKWARD,             mask, need, "re2c-tnfa-posix-back-gor1"));
    //rs.push_back(bench_re2c(r, ss, n, REG_STADFA,                         mask, need, "re2c-tdfa-stadfa"));
    //rs.push_back(bench_re2c(r, ss, n, 0,                                  mask, need, "re2c-tdfa"));
    //rs.push_back(bench_re2c(r, ss, n, REG_NFA | REG_TRIE | REG_GTOP,      mask, need, "re2c-tnfa-posix-gtop-trie"));
    //rs.push_back(bench_re2c(r, ss, n, REG_NFA | REG_KUKLEWICZ | REG_GTOP, mask, need, "re2c-tnfa-posix-kukl-gtop"));
    //rs.push_back(bench_re2c(r, ss, n, REG_NFA | REG_BACKWARD | REG_GTOP,  mask, need, "re2c-tnfa-posix-back-gtop"));

    show(rs);
}

static void load_strings(const char *fname, const char *delim
    , std::vector<std::string> &strings)
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

// RFC URI and HTTP
#define CRLF           "[\\n]"
#define OCT            "([0-9]|[1-9][0-9]|[1][0-9]{2}|[2][0-4][0-9]|[2][5][0-5])"
#define IPV4           "(" OCT "[.]" OCT "[.]" OCT "[.]" OCT ")"
#define H16            "[0-9a-fA-F]{1,4}"
#define LS32           "(" H16 ":" H16 "|" IPV4 ")"
#define IPV6                   "((" H16 ":){6}" LS32 \
    "|"                       "::(" H16 ":){5}" LS32 \
    "|("                H16 ")?::(" H16 ":){4}" LS32 \
    "|((" H16 ":){0,1}" H16 ")?::(" H16 ":){3}" LS32 \
    "|((" H16 ":){0,2}" H16 ")?::(" H16 ":){2}" LS32 \
    "|((" H16 ":){0,3}" H16 ")?::"  H16 ":"     LS32 \
    "|((" H16 ":){0,4}" H16 ")?::"              LS32 \
    "|((" H16 ":){0,5}" H16 ")?::"              H16 \
    "|((" H16 ":){0,6}" H16 ")?::)"
#define IPVFUTURE      "(v[0-9a-fA-F]+[.][-0-9a-zA-Z._~!$&'()*+,;=:]+)"
#define IPLITERAL      "([[](" IPV6 "|" IPVFUTURE ")[\\]])"
#define REGNAME        "(([-0-9a-zA-Z._~!$&'()*+,;=]|%[0-9a-fA-F]{2})*)"
#define HOST           "(" IPLITERAL "|" IPV4 "|" REGNAME ")"
#define PORT           "(:[0-9]*)?"
#define USERINFO       "(([-a-zA-Z0-9._~!$&'()*+,;=:]|%[0-9a-fA-F]{2})*@)?"
#define SCHEME         "([a-zA-Z][a-zA-Z0-9+.-]*):"
#define QUERY          "([?]([-a-zA-Z0-9._~!$&'()*+,;=:@/?]|%[0-9a-fA-F]{2})*)?"
#define FRAGMENT       "([#]([-a-zA-Z0-9._~!$&'()*+,;=:@/?]|%[0-9a-fA-F]{2})*)?"
#define PCHAR          "([-0-9a-zA-Z._~!$&'()*+,;=:@]|%[0-9a-fA-F]{2})"
#define PATH_ABEMPTY   "(/" PCHAR "*)*"
#define PATH_ABSOLUTE  "/(" PCHAR "+(/" PCHAR "*)*)?"
#define PATH_ROOTLESS  PCHAR "+(/" PCHAR "*)*"
#define PATH_EMPTY     "([/]?)"
#define AUTHORITY      "(" USERINFO HOST PORT ")"
#define HIER_PART      "(//" AUTHORITY PATH_ABEMPTY "|" PATH_ABSOLUTE "|" PATH_ROOTLESS "|" PATH_EMPTY ")"
#define URI            SCHEME HIER_PART QUERY FRAGMENT
#define ABSOLUTE_URI   SCHEME HIER_PART QUERY
#define ORIGIN_FROM    PATH_ABEMPTY QUERY
#define REQUEST_TARGET "(" AUTHORITY "|" ABSOLUTE_URI "|" ORIGIN_FROM "|([*]))"
#define METHOD         "([-!#$%&'*+.^_`|~0-9a-zA-Z]+)"
#define HTTP_VERSION   "(HTTP/[0-9][.][0-9])"
#define STATUS_CODE    "([0-9]{3})"
#define REASON_PHRASE  "([ \\t \\x1f-\\x7e\\x80-\\xff]*)"
#define REQUEST_LINE   METHOD "[ ]" REQUEST_TARGET "[ ]" HTTP_VERSION CRLF
#define STATUS_LINE    HTTP_VERSION "[ ]" STATUS_CODE "[ ]" REASON_PHRASE CRLF
#define FIELD_NAME     "([-!#$%&'*+.^_`|~0-9a-zA-Z]+)"
#define FIELD_VCHAR    "[\\x1f-\\x7e\\x80-\\xff]"
#define FIELD_CONTENT  "(" FIELD_VCHAR "([ \\t]+" FIELD_VCHAR")?)"
#define FIELD_VALUE    "(" FIELD_CONTENT "|" CRLF "[ \\t]+)*"
#define HEADER_FIELD   "(" FIELD_NAME ":[ \\t]*" FIELD_VALUE "[ \\t]*)"
#define MESSAGE_HEAD   "(" REQUEST_LINE "|" STATUS_LINE ")" "(" HEADER_FIELD CRLF ")*"

// simplified URI and HTTP
#define CHAR2           "[-._~%!$&'()*+,;=a-zA-Z0-9]"
#define SCHEME2         "([-+.a-zA-Z0-9]+):"
#define USERINFO2       "((" CHAR2 "|[:])+@)?"
#define HOST2           "((" CHAR2 "|[:[\\]])+)"
#define PORT2           "(:[0-9]*)?"
#define AUTHORITY2      USERINFO2 HOST2 PORT2
#define PATH2          "((" CHAR2 "|[:@/])*)"
#define QUERY2          "([?](" CHAR2 "|[:@?/])*)?"
#define FRAGMENT2       "([#](" CHAR2 "|[:@?/])*)?"
#define URI2            SCHEME2 "(//" AUTHORITY2 ")?" PATH2 QUERY2 FRAGMENT2
#define ABSOLUTE_URI2   SCHEME2 "(//" AUTHORITY2 PORT2 ")?" PATH2 QUERY2
#define ORIGIN_FROM2    "/" PATH2 QUERY2
#define REQUEST_TARGET2 "(" AUTHORITY2 "|" ABSOLUTE_URI2 "|" ORIGIN_FROM2 "|[*])"
#define HTTP_VERSION2   "(HTTP/[0-9][.][0-9])"
#define METHOD2         "([-._~%!$&'*+#^`|a-zA-Z0-9]+)"
#define REQUEST_LINE2   "(" METHOD2 "[ ]" REQUEST_TARGET2 "[ ]" HTTP_VERSION2 CRLF ")"
#define STATUS_LINE2    "(" HTTP_VERSION2 "[ ]([0-9]{3})[ ]([\\t \\x1f-\\x7e\\x80-\\xff]*)" CRLF ")"
#define HEADER_FIELD2   "([-._~%!$&'*+#^`|a-zA-Z0-9]+:[\\x1f-\\x7e\\x80-\\xff \\t\\n]*)"
#define MESSAGE_HEAD2   "(" REQUEST_LINE2 "|" STATUS_LINE2 ")" "(" HEADER_FIELD2 CRLF ")*"

// simplified IPv6
#define IPV62 "(((" H16 ":){0,7}" H16 ")?(::)?((" H16 ":){0,7}" H16 ")?)"

// Gentoo package atom
#define PACKAGE_STR    "([a-zA-Z0-9_+-]+)"
#define PACKAGE_NUM     "([0-9]+)"
#define PACKAGE_VER     "(" PACKAGE_NUM "([.]" PACKAGE_NUM ")*)"
#define PACKAGE_SFX1    "([a-z])?"
#define PACKAGE_SFX2    "((alpha|beta|pre|rc|p)" PACKAGE_NUM "?)"
#define PACKAGE_REV     "(-r" PACKAGE_NUM ")?"
#define PACKAGE_ATOM    PACKAGE_STR "/" PACKAGE_STR "-" PACKAGE_VER PACKAGE_SFX1 "(_" PACKAGE_SFX2 ")*" PACKAGE_REV

// simplified Gentoo package atom
#define PACKAGE_STR2    "([a-zA-Z0-9_/+-]+)"
#define PACKAGE_VER2    "([0-9.a-z_]+)"
#define PACKAGE_REV2    "(-r[0-9]+)?"
#define PACKAGE_ATOM2   PACKAGE_STR2 "-" PACKAGE_VER2 PACKAGE_REV

int main()
{
    const char *regexp;
    std::vector<std::string> strings;
    static const size_t VERY_LONG = (1 << 14) + 1;
    static const size_t TIMES = 10;
    char *longstring = new char[VERY_LONG + 1];

    // http
    load_strings("../lib/bench.data_http", "\n\n", strings);
    regexp = MESSAGE_HEAD;
    bench(regexp, strings, 100, REG_BACKWARD | REG_STADFA, 0);
    regexp = MESSAGE_HEAD2;
    bench(regexp, strings, 100, REG_BACKWARD, 0);

    // uri
    load_strings("../lib/bench.data_uri", "\n", strings);
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
    load_strings("../lib/bench.data_atom", "\n", strings);
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

