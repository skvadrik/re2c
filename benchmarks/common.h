#ifndef _RE2C_BENCHMRKS_COMMON_
#define _RE2C_BENCHMRKS_COMMON_

#include <string>
#include <vector>

#include "src/util/c99_stdint.h"


static const uint64_t UNAVAIL = 0xFFFFffffFFFFffff;
static const int XREG_RE2 = 1 << 30;

enum engine_t {
    ENGINE_RE2C,
    ENGINE_RE2
};

struct benchmark_t {
    const char *name;
    engine_t engine;
    int flags;
};

struct Result
{
    const char *title;
    uint64_t ticks_gen;
    uint64_t ticks_run;
};

extern const benchmark_t benchmarks[];
extern const size_t nbenchmarks;

void bench(const char *regexp, const std::vector<std::string> &strings, uint32_t times,
    int mask, int need);

void load_strings(const char *fname, const char *delim,
    std::vector<std::string> &strings);

void show(const std::vector<Result> &results);

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
#define PACKAGE_ATOM2   PACKAGE_STR2 "-" PACKAGE_VER2 PACKAGE_REV

#endif // _RE2C_BENCHMRKS_COMMON_
