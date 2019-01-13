#ifndef _RE2C_LIB_REGEX_IMPL_
#define _RE2C_LIB_REGEX_IMPL_

#include <stddef.h>

#include "libre2c_posix/regex.h"
#include "src/util/c99_stdint.h"

// fwd
namespace re2c {

struct nfa_t;
struct dfa_t;
struct RangeMgr;

} // namespace re2c

struct regex_t
{
    re2c::RangeMgr *rmgr;
    const re2c::nfa_t *nfa;
    const re2c::dfa_t *dfa;
    size_t char2class[256];
};

#endif // _RE2C_LIB_REGEX_IMPL_
