#ifndef _RE2C_LIB_REGEX_
#define _RE2C_LIB_REGEX_

#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <limits.h>


namespace re2c {
struct nfa_t;
struct dfa_t;
class RangeMgr;
} // namespace re2c

namespace re2c {
namespace libre2c {
struct rldfa_t;
struct regoff_trie_t;
} // namespace libre2c
} // namespace re2c

typedef ptrdiff_t regoff_t;

struct regmatch_t {
    regoff_t rm_so;
    regoff_t rm_eo;
};

struct subhistory_t {
    size_t size;
    regmatch_t *offs;
};

// T-string chars are 16 bits.
// This is aligned with Java implementation by Angelo Borsotti.
typedef uint16_t tchar_t;

struct tstring_t {
    size_t capacity;
    size_t length;
    tchar_t *string;
};

// Tags use the upper half of the t-string charater value range.
static const tchar_t TAG_BASE = 1 << (8 * sizeof(tchar_t) - 1);

// standard flags
static const int REG_EXTENDED  = 1u << 0;
static const int REG_ICASE     = 1u << 1;
static const int REG_NOSUB     = 1u << 2;
static const int REG_NEWLINE   = 1u << 3;
static const int REG_NOTBOL    = 1u << 4;
static const int REG_NOTEOL    = 1u << 5;
// extensions
static const int REG_NFA       = 1u << 6;
static const int REG_LEFTMOST  = 1u << 7;
static const int REG_TRIE      = 1u << 8;
static const int REG_GTOP      = 1u << 9;
static const int REG_SLOWPREC  = 1u << 10;
static const int REG_BACKWARD  = 1u << 11;
static const int REG_KUKLEWICZ = 1u << 12;
static const int REG_STADFA    = 1u << 13;
static const int REG_REGLESS   = 1u << 14;
static const int REG_SUBHIST   = 1u << 15;
static const int REG_TSTRING   = 1u << 16;

struct regex_t {
    size_t re_nsub;
    size_t re_ntag;
    re2c::RangeMgr *rmgr;
    const re2c::nfa_t *nfa;
    const re2c::dfa_t *dfa;
    const re2c::libre2c::rldfa_t *rldfa;
    void *simctx;
    size_t *char2class;
    int flags;
    union {
        regoff_t *regs;
        re2c::libre2c::regoff_trie_t *regtrie;
    };
    // Allow storing submatch results in RE (this is needed for Java bindings).
    union {
        regmatch_t *pmatch;
        subhistory_t *psubhist;
        mutable tstring_t tstring;
    };
};

static const int REG_NOMATCH = INT_MAX;

// standard functions
int regcomp(regex_t *preg, const char *pattern, int cflags);
size_t regerror(int errcode, const regex_t *preg, char *errbuf, size_t errbuf_size);
int regexec(const regex_t *preg, const char *string, size_t nmatch, regmatch_t pmatch[],
    int eflags);
void regfree(regex_t *preg);

// extensions
subhistory_t *regparse(const regex_t *preg, const char *string, size_t nmatch);
const tstring_t *regtstring(const regex_t *preg, const char *string);
void regfreesub(subhistory_t *history);

#endif // _RE2C_LIB_REGEX_
