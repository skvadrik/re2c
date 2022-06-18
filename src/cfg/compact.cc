#include <stddef.h>
#include <algorithm>
#include <vector>

#include "src/cfg/cfg.h"
#include "src/dfa/dfa.h"
#include "src/dfa/tcmd.h"
#include "src/regexp/tag.h"

namespace re2c {

tagver_t cfg_t::compact(const cfg_t& cfg, tagver_t* ver2new) {
    const std::vector<Tag>& tags = cfg.dfa.tags;
    const size_t
    nver = static_cast<size_t>(cfg.dfa.maxtagver) + 1,
    ntag = tags.size();
    const tagver_t* fins = cfg.dfa.finvers;
    bool* used = new bool[nver];

    std::fill(used, used + nver, false);
    for (size_t t = 0; t < ntag; ++t) {
        const tagver_t f = fins[t];
        used[f] = f != TAGVER_ZERO; // fixed tag or unreachable rule
    }
    for (size_t i = 0; i < cfg.nbbfall; ++i) {
        const cfg_bb_t& b = cfg.bblocks[i];
        for (const tcmd_t* p = b.cmd; p; p = p->next) {
            const tagver_t r = p->rhs;
            if (r != TAGVER_ZERO) {
                used[r] = true;
            }
            used[p->lhs] = true;
        }
    }

    tagver_t maxver = 0;
    for (size_t v = 0; v < nver; ++v) {
        ver2new[v] = used[v] ? ++maxver : TAGVER_ZERO;
    }

    delete[] used;
    return maxver;
}

} // namespace re2c

