#ifndef _RE2C_LIB_REGEX_
#define _RE2C_LIB_REGEX_

#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <limits.h>


// fwd
namespace re2c {
struct nfa_t;
struct dfa_t;
class RangeMgr;
} // namespace re2c

typedef ptrdiff_t regoff_t;

struct regmatch_t
{
    regoff_t rm_so;
    regoff_t rm_eo;
};

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

struct regex_t
{
    size_t re_nsub;
    re2c::RangeMgr *rmgr;
    const re2c::nfa_t *nfa;
    const re2c::dfa_t *dfa;
    regmatch_t *pmatch;
    regoff_t *regs;
    size_t *char2class;
    int flags;
    void *simctx;
};

static const int REG_NOMATCH = INT_MAX;

int regcomp(regex_t *preg, const char *pattern, int cflags);
size_t regerror(int errcode, const regex_t *preg, char *errbuf, size_t errbuf_size);
int regexec(const regex_t *preg, const char *string, size_t nmatch, regmatch_t pmatch[], int eflags);
void regfree(regex_t *preg);

#endif // _RE2C_LIB_REGEX_
