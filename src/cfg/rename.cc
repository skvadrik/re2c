#include <stddef.h>
#include <set>
#include <vector>

#include "src/cfg/cfg.h"
#include "src/dfa/dfa.h"
#include "src/dfa/tcmd.h"
#include "src/regexp/tag.h"

namespace re2c {

void cfg_t::renaming(cfg_t& cfg, const tagver_t* ver2new, tagver_t maxver) {
    tagver_t& oldmax = cfg.dfa.maxtagver;
    if (oldmax == maxver) return;
    oldmax = maxver;

    cfg_bb_t* b = cfg.bblocks, *be = b + cfg.nbbfall;
    for (; b < be; ++b) {
        for (tcmd_t* p, **pp = &b->cmd; (p = *pp);) {
            tagver_t& l = p->lhs, &r = p->rhs, h = p->history[0];

            l = ver2new[l];
            if (r != TAGVER_ZERO) {
                r = ver2new[r];
            }
            if (l == r && h == TAGVER_ZERO) {
                *pp = p->next;
            } else {
                pp = &p->next;
            }
        }
    }

    // final tag versions
    tagver_t* fins = cfg.dfa.finvers;
    const std::vector<Tag>& tags = cfg.dfa.tags;
    for (size_t t = 0; t < tags.size(); ++t) {
        tagver_t& f = fins[t];
        if (f != TAGVER_ZERO) { // fixed tag or unreachable rule
            f = ver2new[f];
        }
    }

    // versions of tags with history
    std::set<tagver_t> newmt, &oldmt = cfg.dfa.mtagvers;
    for (tagver_t v : oldmt) {
        newmt.insert(ver2new[v]);
    }
    oldmt.swap(newmt);
}

} // namespace re2c

