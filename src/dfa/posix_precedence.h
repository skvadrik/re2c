#ifndef _RE2C_DFA_POSIX_PRECEDENCE_
#define _RE2C_DFA_POSIX_PRECEDENCE_

#include "src/dfa/determinization.h"
#include "src/dfa/tag_history.h"
#include "src/options/opt.h"
#include "src/util/attribute.h"
#include "src/util/check.h"

namespace re2c {

// maximum 29-bit (we have 30 bits, but highest must be non-negative)
static constexpr int32_t MAX_RHO = 0x1fffFFFF;

template<typename ctx_t> static void compute_prectable_naive(ctx_t& ctx) RE2C_ATTR((used));
template<typename ctx_t> static void compute_prectable_complex(ctx_t& ctx) RE2C_ATTR((used));

// we *do* want this to be inlined
static inline int32_t leftprec(tag_info_t info1, tag_info_t info2, bool last1, bool last2);
static inline int32_t unpack_longest(int32_t packed);
static inline int32_t unpack_leftmost(int32_t packed);
static inline int32_t pack(int32_t longest, int32_t leftmost);

template<typename ctx_t>
int32_t phistory_t::precedence(ctx_t& ctx,
                               const typename ctx_t::conf_t& x,
                               const typename ctx_t::conf_t& y,
                               int32_t& prec1,
                               int32_t& prec2) {
    prec1 = prec2 = MAX_RHO;
    int32_t prec = 0;

    const int32_t idx1 = x.thist, idx2 = y.thist;
    const uint32_t orig1 = x.origin, orig2 = y.origin;

    if (idx1 == idx2 && orig1 == orig2) {
        return 0;
    }

    const std::vector<Tag>& tags = ctx.tags;
    typename ctx_t::history_t& hist = ctx.history;

    const bool fork_frame = orig1 == orig2;
    if (!fork_frame) {
        prec = unpack_leftmost(ctx.oldprectbl[orig1 * ctx.oldprecdim + orig2]);
        prec1 = unpack_longest(ctx.oldprectbl[orig1 * ctx.oldprecdim + orig2]);
        prec2 = unpack_longest(ctx.oldprectbl[orig2 * ctx.oldprecdim + orig1]);
    }

    tag_info_t info1 = NOINFO, info2 = NOINFO;
    int32_t i1 = idx1, i2 = idx2;
    for (; i1 != i2; ) {
        if (i1 > i2) {
            const typename ctx_t::history_t::node_t& n = hist.node(i1);
            info1 = n.info;
            prec1 = std::min(prec1, tags[info1.idx].height);
            i1 = n.pred;
        } else {
            const typename ctx_t::history_t::node_t& n = hist.node(i2);
            info2 = n.info;
            prec2 = std::min(prec2, tags[info2.idx].height);
            i2 = n.pred;
        }
        DINCCOUNT_CLLENGTH(ctx, 1);
    }
    if (i1 != HROOT) {
        DCHECK(fork_frame);
        const int32_t h = tags[hist.node(i1).info.idx].height;
        prec1 = std::min(prec1, h);
        prec2 = std::min(prec2, h);
    }
    DINCCOUNT_CLPREC(ctx);

    // longest precedence
    if (prec1 > prec2) return -1;
    if (prec1 < prec2) return  1;

    // leftmost precedence
    return !fork_frame ? prec : leftprec(info1, info2, i1 == idx1, i2 == idx2);
}

int32_t leftprec(tag_info_t info1, tag_info_t info2, bool last1, bool last2) {
    // equal => not less
    if (last1 && last2) return 0;

    // shorter => less
    if (last1) return -1;
    if (last2) return  1;

    const uint32_t tag1 = info1.idx, tag2 = info2.idx;
    const bool neg1 = info1.neg, neg2 = info2.neg;

    // can't be both negative
    DCHECK(!(neg1 && neg2));

    // positive vs negative: positive wins
    if (neg1) return  1;
    if (neg2) return -1;

    // can't be both closing
    DCHECK(!(tag1 % 2 == 1 && tag2 % 2 == 1));

    // closing vs opening: closing wins
    if (tag1 % 2 == 1) return -1;
    if (tag2 % 2 == 1) return  1;

    // positive vs positive: smaller wins (this case is only possible because multiple top-level
    // regexps don't have proper negative tags)
    if (tag1 < tag2) return -1;
    if (tag1 > tag2) return  1;

    UNREACHABLE();
}

template<typename ctx_t>
void compute_prectable(ctx_t& ctx) {
    switch (ctx.opts->posix_prectable) {
    case PosixPrectable::COMPLEX:
        compute_prectable_complex(ctx);
        break;
    case PosixPrectable::NAIVE:
        compute_prectable_naive(ctx);
        break;
    }
}

// Naive O(m^2*t) algorithm for computation of POSIX precedence table, where m is the number of
// states in TNFA and t is the number of tags. If t ~~ m, the complexity is O(n^3); one example that
// exhibits cubic behaviour is ((a?){1,N})*. In this example closure has O(m) states, and the
// compared histories have O(N) length.
template<typename ctx_t>
void compute_prectable_naive(ctx_t& ctx) {
    const typename ctx_t::confset_t& state = ctx.state;
    int32_t* newtbl = ctx.newprectbl;
    const size_t newdim = state.size();

    const int32_t p0 = pack(MAX_RHO, 0);

    for (uint32_t i = 0; i < newdim; ++i) {
        newtbl[i * newdim + i] = p0;
        for (uint32_t j = i + 1; j < newdim; ++j) {
            int32_t prec1, prec2;
            int32_t prec = ctx_t::history_t::precedence(ctx, state[i], state[j], prec1, prec2);
            newtbl[i * newdim + j] = pack(prec1, prec);
            newtbl[j * newdim + i] = pack(prec2, -prec);
        }
    }
}

// Complex O(m^2) algorithm for computation of POSIX precedence table, where m is the number of
// states in TNFA.
template<typename ctx_t>
void compute_prectable_complex(ctx_t& ctx) {
    const typename ctx_t::confset_t& state = ctx.state;
    const std::vector<Tag>& tags = ctx.tags;
    typename ctx_t::history_t& history = ctx.history;

    const prectable_t* oldtbl = ctx.oldprectbl;
    prectable_t* newtbl = ctx.newprectbl;
    const size_t olddim = ctx.oldprecdim, newdim = state.size();

    std::vector<uint32_t>& sortcores = ctx.sortcores;
    std::vector<uint32_t>& fcount = ctx.fincount;
    std::vector<int32_t>& stack = ctx.worklist;
    histleaf_t* level = ctx.histlevel, *li, *lj, *lk, *le = level;

    // Group core configurations by their history tree index, so that later while traversing the
    // tree we will know at once which configurations (if any) are bound to the given tree node. We
    // use counting sort, which requires additional memory, but is fast and conveniently creates an
    // array of boundaries in the sorted configuration array.
    uint32_t maxfin = 0;
    sortcores.resize(newdim);
    for (const typename ctx_t::conf_t& conf : state) {
        typename ctx_t::history_t::node_t& n = history.node(conf.thist);
        if (n.finidx >= USED) {
            n.finidx = maxfin++;
            fcount[n.finidx] = 0;

            // mark all nodes down to root as used (unless marked already)
            for (int32_t i = n.pred; i >= HROOT; ) {
                typename ctx_t::history_t::node_t& m = history.node(i);
                if (m.finidx <= USED) break;
                m.finidx = USED;
                i = m.pred;
            }
        }
        ++fcount[n.finidx];
    }
    fcount[maxfin] = 0;
    for (size_t i = 1; i <= maxfin; ++i) {
        fcount[i] += fcount[i - 1];
    }
    sortcores.resize(state.size());
    for (uint32_t i = static_cast<uint32_t>(newdim); i --> 0; ) {
        sortcores[--fcount[history.node(state[i].thist).finidx]] = i;
    }

    // Depth-first traversal of the history tree. During traversal we grow an array of items (one
    // item per core configuration). Items are added in tree nodes that have core configurations
    // associated with them. Each item represents one history. Items have immutable part (core ID,
    // origin) and mutable part (current minimal height, current tree index) that changes as we
    // return down the tree.
    stack.push_back(0);
    while (!stack.empty()) {
        const int32_t n = stack.back();
        typename ctx_t::history_t::node_t& node = history.node(n);
        const uint32_t fidx = node.finidx;

        if (fidx == NONFIN) {
            // aborted branch of search tree, don't waste time
            stack.pop_back();
            continue;
        }

        if (node.next != -1) {
            // start or continue visiting subtrees rooted at this node
            const typename ctx_t::history_t::arc_t& arc = history.arc(node.next);
            stack.push_back(arc.node);
            node.next = arc.next;
            continue;
        }

        // all subtrees visited, it's time to process this node
        const int32_t h = n == 0 ? MAX_RHO : tags[node.info.idx].height;
        li = level - 1;

        if (fidx < USED) {
            // this node has leaf configurations, add them to level
            for (uint32_t k = fcount[fidx], e = fcount[fidx + 1]; k < e; ++k) {
                const uint32_t j = sortcores[k];
                *level++ = {j, state[j].origin, HROOT, h};
            }

            // compute precedence for newly added configurations
            const int32_t p0 = pack(h, 0);
            for (lj = level - 1; lj > li; --lj) {
                for (lk = lj; lk > li; --lk) {
                    const uint32_t cj = lj->coreid, ck = lk->coreid;
                    const uint32_t oj = lj->origin, ok = lk->origin;
                    const bool fork = n != 0 || oj == ok;
                    if (fork) {
                        newtbl[cj * newdim + ck] = p0;
                        newtbl[ck * newdim + cj] = p0;
                    } else {
                        newtbl[cj * newdim + ck] = oldtbl[oj * olddim + ok];
                        newtbl[ck * newdim + cj] = oldtbl[ok * olddim + oj];
                    }
                }
            }
        }

        // Each subtree appended a sequence of items to level. We can find sequence boundaries by
        // looking at tree index of each item: it is equal to tree index of the corresponding
        // subtree (except for the leaf items added at this node; but we know where they start).

        // We must compute precedence for each pair of items from different sequences (including
        // leaf items added at this node), but not within sequence boundaries: those histories fork
        // higher up the subtree; their precedence has already been computed and must not be
        // touched.

        for (int32_t a = node.last; a != -1; ) {
            const typename ctx_t::history_t::arc_t& arc = history.arc(a);
            a = arc.prev;

            // for all the items of this subtree
            for (lk = li; li >= le && li->hidx == arc.node; --li) {

                // update height of each item coming from subtree
                li->height = std::min(li->height, h);

                // for all the level items to the right of this subtree
                for (lj = level - 1; lj > lk; --lj) {

                    const uint32_t ci = li->coreid, cj = lj->coreid;
                    const uint32_t oi = li->origin, oj = lj->origin;
                    const bool fork = n != 0 || oi == oj;
                    int32_t p1 = li->height, p2 = lj->height, p;

                    if (!fork) {
                        p1 = std::min(p1, unpack_longest(oldtbl[oi * olddim + oj]));
                        p2 = std::min(p2, unpack_longest(oldtbl[oj * olddim + oi]));
                    }

                    if (p1 > p2) {
                        p = -1;
                    } else if (p1 < p2) {
                        p = 1;
                    } else if (fork) {
                        const tag_info_t t1 = history.node(li->hidx).info;
                        const tag_info_t t2 = history.node(lj->hidx).info;
                        p = leftprec(t1, t2, t1 == NOINFO, t2 == NOINFO);
                    } else {
                        p = unpack_leftmost(oldtbl[oi * olddim + oj]);
                    }

                    newtbl[ci * newdim + cj] = pack(p1, p);
                    newtbl[cj * newdim + ci] = pack(p2, -p);
                }
            }
        }

        // Finally, downgrade tree index of all subtree items, making their origins
        // indistinguishable from each other for the previous level.
        for (lj = level - 1; lj > li; --lj) {
            lj->hidx = n;
        }

        stack.pop_back();
    }
}

int32_t unpack_longest(int32_t packed) {
    // take lower 30 bits and sign-extend
    return static_cast<int32_t>(static_cast<uint32_t>(packed) << 2u) >> 2u;
}

int32_t unpack_leftmost(int32_t packed) {
    // take higher 2 bits and sign-extend
    return packed >> 30u;
}

int32_t pack(int32_t longest, int32_t leftmost) {
    // avoid signed overflows by using unsigned arithmetics
    uint32_t u_longest = static_cast<uint32_t>(longest);
    uint32_t u_leftmost = static_cast<uint32_t>(leftmost);

    // leftmost: higher 2 bits, longest: lower 30 bits
    uint32_t u_packed = (u_longest & 0x3fffFFFF) | (u_leftmost << 30u);
    int32_t packed = static_cast<int32_t>(u_packed);

    DCHECK(unpack_longest(packed) == longest && unpack_leftmost(packed) == leftmost);

    return packed;
}

} // namespace re2c

#endif // _RE2C_DFA_POSIX_PRECEDENCE_
