#ifndef _RE2C_LIB_REGEX_
#define _RE2C_LIB_REGEX_

#include <stddef.h>
#include <stdint.h>
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

// regmatch_t stores an offset pair representing a capturing group.
// No match is represented with (-1,-1).
struct regmatch_t {
    regoff_t rm_so;
    regoff_t rm_eo;
};

// subhistory_t stores subhistory of a capturing group: an array of offset pairs
// corresponding to all positions in the input string where this capturing group
// has matched. The length of the array depends on how many times the group has
// matched, which depends on the RE and the input string.
struct subhistory_t {
    size_t size;
    regmatch_t *offs;
};

// T-string chars are 16 bits.
// This is aligned with the Java implementation by Angelo Borsotti.
typedef uint16_t tchar_t;

// A t-string is a flattened representation a parse tree where characters of the
// input string are interleaved with tags. Input characters occupy the lower
// byte of the 16-bit value, leaving the higher byte as zero. Tags are stored as
// numeric values shifted to the upper half of the 16-bit range.
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
static const int REG_AUTOTAGS  = 1u << 17;

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

// The regparse() function returns parse results as an array of nmatch size,
// where each element is an array of offset pairs for the corresponding
// capturing group. If a group has matched repeatedly at different parts of the
// input string, then its array will contain multiple offset pairs; otherwise, a
// single pair. This differs from the standard POSIX API, where only the last
// offset pair for each group is returned.
//
// regparse() can be used if REG_SUBHIST flag has been passed to regcomp().
//
// The allocation of memory for the parse results is done by the library (the
// user cannot know how much memory will be needed). The ownership of parse
// results is transferred to the user, who is expected to deallocate memory
// allocated by regparse() with regfreesub().
subhistory_t *regparse(const regex_t *preg, const char *string, size_t nmatch);

// regfreesub() deallocates memory allocated with regparse(). It must be called
// every time after regparse() is called.
void regfreesub(subhistory_t *history);

// The regtstring() function constructs a t-string.
//
// It can be used if REG_TSTRING flag has been passed to regcomp().
//
// The goal of this function is to construct parse results in the cheapest
// possible way. There is no standard representation of a parse tree, and any
// nontrivial representation incurs significant overhead on construction (the
// algorithm spends more time constructing parse results than doing the actual
// parsing). The t-string representation requires very little effort to
// construct, provided that the t-string fragments corresponding to the tagged
// paths in the epsilon-closure are prepared in advance at regcomp() time. The
// fragments are stored as arrays of tags, so that they can be easily copied to
// the resulting t-string. Importantly, this does not require unwinding of tag
// history stored in a trie form, which is rather slow.
//
// T-string allocation is done on the library side, and the t-string is stored
// in the regexp structure. The user gets an immutable view of it and is not
// expected to free memory after calling regtstring(). Moreover, the library
// reuses the same memory on each regtstring() call and reallocates it only if
// the new t-string does not fit into the old memory area. So each call to
// regtstring() invalidates the previous results returned from it.
//
// The regtstring() function is primarily intended for benchmarking the speed
// of a parsing algorithm.
const tstring_t *regtstring(const regex_t *preg, const char *string);


#endif // _RE2C_LIB_REGEX_
