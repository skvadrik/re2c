#ifndef _RE2C_DFA_STACMD_
#define _RE2C_DFA_STACMD_

#include <stddef.h>
#include "src/util/c99_stdint.h"

#include "src/dfa/tag_history.h"


namespace re2c {

struct stacmd_t
{
    enum kind_t {STORE, ACCEPT, TRANSFER};

    stacmd_t *next;
    size_t tag;
    kind_t kind;
    int32_t lhs;
    int32_t rhs;
    hidx_t hist;
};

template <typename allocator_t>
stacmd_t *make_stacmd(allocator_t &alc, stacmd_t::kind_t kind, stacmd_t *next,
    size_t tag, int32_t lhs, int32_t rhs, hidx_t hist)
{
    stacmd_t *p = alc.template alloct<stacmd_t>(1);
    p->next = next;
    p->tag = tag;
    p->kind = kind;
    p->lhs = lhs;
    p->rhs = rhs;
    p->hist = hist;
    return p;
}

void sort_stacmd(stacmd_t *cmd);

} // namespace re2c

#endif // _RE2C_DFA_STACMD_
