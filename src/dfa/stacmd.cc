#include <string.h>

#include "src/dfa/stacmd.h"


namespace re2c {

static inline void swap(stacmd_t &x, stacmd_t &y)
{
    std::swap(x.kind, y.kind);
    std::swap(x.tag, y.tag);
    std::swap(x.lhs, y.lhs);
    std::swap(x.rhs, y.rhs);
    std::swap(x.hist, y.hist);
}

static inline bool less(const stacmd_t &x, const stacmd_t &y)
{
    if (x.kind < y.kind) return true;
    if (x.kind > y.kind) return false;
    if (x.tag < y.tag) return true;
    if (x.tag > y.tag) return false;
    if (x.lhs < y.lhs) return true;
    if (x.lhs > y.lhs) return false;
    if (x.rhs < y.rhs) return true;
    if (x.rhs > y.rhs) return false;
    if (x.hist < y.hist) return true;
    if (x.hist > y.hist) return false;
    return false;
}

void sort_stacmd(stacmd_t *cmd)
{
    for (stacmd_t *p = cmd; p; p = p->next) {
        for (stacmd_t *q = p->next; q; q = q->next) {
            if (less(*q, *p)) {
                swap(*p, *q);
            }
        }
    }
}

} // namespace re2c
