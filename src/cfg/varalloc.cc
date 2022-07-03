#include <algorithm>
#include <limits>

#include "src/cfg/cfg.h"
#include "src/dfa/dfa.h"
#include "src/dfa/tcmd.h"
#include "src/regexp/tag.h"
#include "src/util/check.h"

namespace re2c {

// We have a binary relation on the set of all tags and must construct set decomposition into
// subsets such that all tags in the same subset are equivalent. This problem is isomorphic to
// partitioning graph into cliques (aka finding the 'clique cover' of a graph). Finding the minimal
// clique cover in arbitrary graph is NP-complete. We build just some cover, not necessarily the
// minimal one. The algorithm takes quadratic time in the number of tags.

tagver_t cfg_t::variable_allocation(const cfg_t& cfg, const bool* interf, tagver_t* ver2new) {
    const size_t END = static_cast<size_t>(std::numeric_limits<tagver_t>::max());
    const size_t nver = static_cast<size_t>(cfg.dfa.maxtagver) + 1;

    size_t* next = new size_t[nver]; // list of class members
    size_t* repr = new size_t[nver]; // maps tag to class representative
    size_t rx, ry, x, y, z;

    std::fill(next, next + nver, END);
    std::fill(repr, repr + nver, END);

    // copy coalescing: for each command X = Y, try to merge X and Y
    const cfg_bb_t* b = cfg.bblocks, *e = b + cfg.nbbfall;
    for (; b < e; ++b) {
        for (const tcmd_t* p = b->cmd; p; p = p->next) {

            DCHECK(p->lhs >= 0 && p->rhs >= 0);
            x = static_cast<size_t>(p->lhs);
            y = static_cast<size_t>(p->rhs);

            if (y == TAGVER_ZERO || y == x) continue;

            rx = repr[x];
            ry = repr[y];

            if (rx != END) {
                if (ry != END) continue;
                for (z = rx; z != END; z = next[z]) {
                    if (interf[z * nver + y]) break;
                }
                if (z == END) {
                    repr[y] = rx;
                    next[y] = next[rx];
                    next[rx] = y;
                }
            } else if (ry != END) {
                for (z = ry; z != END; z = next[z]) {
                    if (interf[z * nver + x]) break;
                }
                if (z == END) {
                    repr[x] = ry;
                    next[x] = next[ry];
                    next[ry] = x;
                }
            } else if (!interf[x * nver + y]) {
                repr[x] = repr[y] = x;
                next[x] = y;
            }
        }
    }

    // try to merge equivalence classes left after copy coalescing
    for (rx = 0; rx < nver; ++rx) {
        if (rx != repr[rx]) continue;

        for (ry = rx + 1; ry < nver; ++ry) {
            if (ry != repr[ry]) continue;

            for (x = rx; x != END; x = next[x]) {
                for (y = ry; y != END; y = next[y]) {
                    if (interf[x * nver + y]) break;
                }
                if (y != END) break;
            }

            if (x == END) {
                for (y = ry;; y = next[y]) {
                    repr[y] = rx;
                    if (next[y] == END) {
                        next[y] = next[rx];
                        next[rx] = ry;
                        break;
                    }
                }
            }
        }
    }

    // push each remaining tag to any non-interfering class
    for (x = 0; x < nver; ++x) {
        if (repr[x] != END) continue;

        // try all existing classes
        for (rx = 0; rx < nver; ++rx) {
            if (rx != repr[rx]) continue;

            // check interference with class members
            for (y = rx; y != END; y = next[y]) {
                if (interf[x * nver + y]) break;
            }

            // no interference; add to class
            if (y == END) {
                repr[x] = rx;
                next[x] = next[rx];
                next[rx] = x;
                break;
            }
        }

        // make new equivalence class
        if (rx == nver) {
            repr[x] = x;
        }
    }

    tagver_t maxver = 0;
    rx = 0;

    // zero-th variable is artificial, skip if it's the only one in its class
    if (next[rx] == END) ++rx;

    for (; rx < nver; ++rx) {
        if (repr[rx] != rx) continue;

        ++maxver;
        for (x = rx; x != END; x = next[x]) {
            ver2new[x] = maxver;
        }
    }

    delete[] next;
    delete[] repr;

    return maxver;
}

} // namespace re2c

