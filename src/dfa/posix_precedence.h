#ifndef _RE2C_DFA_POSIX_PRECEDENCE_
#define _RE2C_DFA_POSIX_PRECEDENCE_

#include "src/dfa/tag_history.h"
#include "src/debug/debug.h"


namespace re2c {

/* note [lazy computation and caching of precedence]
 *
 * Eagerly computing precedence values on each step for each pair of closure
 * states is a waste of time: most of these values are not needed, because
 * RE may be unambigous, or the given input string may be unambigous, or even
 * if there is ambiguity, it may take only a few comparisons to resolve. All
 * the rest is wasted effort.
 *
 * We can avoid it by delaying precedence computation until necessary, and
 * then unwinding all the steps backwards, computing precedence for each step
 * and caching the computed values (so that the same pair of histories is not
 * compared twice). It is still the same incremental comparison as with
 * precedence matrices: we compare step by step, going from the fork frame to
 * the join frame. The result of comparison on each step is folded to a triple
 * of numbers and recorded in cache. It is important that we do record each
 * step, not just the final step, because the next pair of ambiguous histories
 * may unwind to the same pair of prefixes that was compared before.
 *
 * For all this to work, it is necessary that we are able to store all history
 * until the end, because at any step we might need to unwind an arbitrary
 * number of steps back. We also need to address individual subhistories
 * efficiently in order to use them as keys in the cache. All this is achieved
 * by storing history in the form of a trie and addressing individual
 * histories by indices in that trie. We also use trie to compute the final
 * tag values (instead of storing tags in registers at each step).
 */

// maximum 29-bit (we have 30 bits, but highest must be non-negative)
static const int32_t MAX_RHO = 0x1fffFFFF;

template<typename ctx_t> static int32_t zprecedence1(ctx_t &ctx
    , hidx_t idx1, hidx_t idx2, int32_t &prec1, int32_t &prec2);
template<typename ctx_t> static int32_t zprecedence2(ctx_t &ctx
    , hidx_t idx1, hidx_t idx2, int32_t &prec1, int32_t &prec2);

// we *do* want this to be inlined
static inline int32_t leftprec(tag_info_t info1, tag_info_t info2, bool last1, bool last2);
static inline int32_t unpack_longest(int32_t packed);
static inline int32_t unpack_leftmost(int32_t packed);
static inline int32_t pack(int32_t longest, int32_t leftmost);
static inline uint32_t get_step(const zhistory_t &hist, int32_t idx);
static inline uint32_t get_orig(const zhistory_t &hist, int32_t idx);

template<typename ctx_t>
int32_t phistory_t::precedence(ctx_t &ctx
    , const typename ctx_t::conf_t &x, const typename ctx_t::conf_t &y
    , int32_t &prec1, int32_t &prec2)
{
    prec1 = prec2 = MAX_RHO;
    int32_t prec = 0;

    const int32_t idx1 = x.thist, idx2 = y.thist;
    const uint32_t orig1 = x.origin, orig2 = y.origin;

    if (idx1 == idx2 && orig1 == orig2) {
        return 0;
    }

    const std::vector<Tag> &tags = ctx.nfa.tags;
    typename ctx_t::history_t &hist = ctx.history;

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
            const typename ctx_t::history_t::node_t &n = hist.node(i1);
            info1 = n.info;
            prec1 = std::min(prec1, tags[info1.idx].height);
            i1 = n.pred;
        }
        else {
            const typename ctx_t::history_t::node_t &n = hist.node(i2);
            info2 = n.info;
            prec2 = std::min(prec2, tags[info2.idx].height);
            i2 = n.pred;
        }
        DINCCOUNT_CLLENGTH(ctx, 1);
    }
    if (i1 != HROOT) {
        DASSERT(fork_frame);
        const int32_t h = tags[hist.node(i1).info.idx].height;
        prec1 = std::min(prec1, h);
        prec2 = std::min(prec2, h);
    }
    DINCCOUNT_CLPREC(ctx);

    // longest precedence
    if (prec1 > prec2) return -1;
    if (prec1 < prec2) return  1;

    // leftmost precedence
    return !fork_frame ? prec
        : leftprec(info1, info2, i1 == idx1, i2 == idx2);
}

int32_t leftprec(tag_info_t info1, tag_info_t info2, bool last1, bool last2)
{
    // equal => not less
    if (last1 && last2) return 0;

    // shorter => less
    if (last1) return -1;
    if (last2) return  1;

    const uint32_t tag1 = info1.idx, tag2 = info2.idx;
    const bool neg1 = info1.neg, neg2 = info2.neg;

    // can't be both negative
    DASSERT(!(neg1 && neg2));

    // positive vs negative: positive wins
    if (neg1) return  1;
    if (neg2) return -1;

    // can't be both closing
    DASSERT(!(tag1 % 2 == 1 && tag2 % 2 == 1));

    // closing vs opening: closing wins
    if (tag1 % 2 == 1) return -1;
    if (tag2 % 2 == 1) return  1;

    // positive vs positive: smaller wins
    // (this case is only possible because multiple
    // top-level RE don't have proper negative tags)
    if (tag1 < tag2) return -1;
    if (tag1 > tag2) return  1;

    DASSERT(false);
    return 0;
}

template<typename ctx_t>
void compute_prectable(ctx_t &ctx)
{
    const typename ctx_t::confset_t &state = ctx.state;
    const std::vector<Tag> &tags = ctx.nfa.tags;
    typename ctx_t::history_t &history = ctx.history;

    const prectable_t *oldtbl = ctx.oldprectbl;
    prectable_t *newtbl = ctx.newprectbl;
    const size_t olddim = ctx.oldprecdim, newdim = state.size();

    std::vector<uint32_t> &sortcores = ctx.sortcores;
    std::vector<uint32_t> &fcount = ctx.fincount;
    std::vector<int32_t> &stack = ctx.worklist;
    histleaf_t *level = ctx.histlevel, *li, *lj, *lk, *le = level;

    // Group core configurations by their history tree index, so that later
    // while traversing the tree we will know at once which configurations
    // (if any) are bound to the given tree node. We use counting sort, which
    // requires additional memory, but is fast and conveniently creates an
    // array of boundaries in the sorted configuration array.
    uint32_t maxfin = 0;
    sortcores.resize(newdim);
    for (typename ctx_t::cconfiter_t c = state.begin(), e = state.end(); c != e; ++c) {
        typename ctx_t::history_t::node_t &n = history.node(c->thist);
        if (n.finidx >= USED) {
            n.finidx = maxfin++;
            fcount[n.finidx] = 0;

            // mark all nodes down to root as used (unless marked already)
            for (int32_t i = n.pred; i >= HROOT; ) {
                typename ctx_t::history_t::node_t &m = history.node(i);
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

    // Depth-first traversal of the history tree. During traversal we grow
    // an array of items (one item per core configuration). Items are added
    // in tree nodes that have core configurations associated with them.
    // Each item represents one history. Items have immutable part (core ID,
    // origin) and mutable part (current minimal height, current tree index)
    // that changes as we return down the tree.
    stack.push_back(0);
    while (!stack.empty()) {
        const int32_t n = stack.back();
        typename ctx_t::history_t::node_t &node = history.node(n);
        const uint32_t fidx = node.finidx;

        if (fidx == NONFIN) {
            // aborted branch of search tree, don't waste time
            stack.pop_back();
            continue;
        }

        if (node.next != -1) {
            // start or continue visiting subtrees rooted at this node
            const typename ctx_t::history_t::arc_t &arc = history.arc(node.next);
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
                const histleaf_t l = {j, state[j].origin, HROOT, h};
                *level++ = l;
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
                    }
                    else {
                        newtbl[cj * newdim + ck] = oldtbl[oj * olddim + ok];
                        newtbl[ck * newdim + cj] = oldtbl[ok * olddim + oj];
                    }
                }
            }
        }

        // Each subtree appended a sequence of items to level. We can find
        // sequence boundaries by looking at tree index of each item: it is
        // equal to tree index of the corresponding subtree (except for the
        // leaf items added at this node; but we know where they start).

        // We must compute precedence for each pair of items from different
        // sequences (including leaf items added at this node), but not within
        // sequence boundaries: those histories fork higher up the subtree;
        // their precedence has already been computed and must not be touched.

        for (int32_t a = node.last; a != -1; ) {
            const typename ctx_t::history_t::arc_t &arc = history.arc(a);
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
                    }
                    else if (p1 < p2) {
                        p = 1;
                    }
                    else if (fork) {
                        const tag_info_t t1 = history.node(li->hidx).info;
                        const tag_info_t t2 = history.node(lj->hidx).info;
                        p = leftprec(t1, t2, t1 == NOINFO, t2 == NOINFO);
                    }
                    else {
                        p = unpack_leftmost(oldtbl[oi * olddim + oj]);
                    }

                    newtbl[ci * newdim + cj] = pack(p1, p);
                    newtbl[cj * newdim + ci] = pack(p2, -p);
                }
            }
        }

        // finally, downgrade tree index of all subtree items, making their
        // origins indistinguishable from each other for the previous level
        for (lj = level - 1; lj > li; --lj) {
            lj->hidx = n;
        }

        stack.pop_back();
    }
}

template<typename ctx_t>
int32_t zhistory_t::precedence(ctx_t &ctx
    , const typename ctx_t::conf_t &x, const typename ctx_t::conf_t &y
    , int32_t &prec1, int32_t &prec2)
{
    return zprecedence1(ctx, x.thist, y.thist, prec1, prec2);
}

// see note [lazy computation and caching of precedence]
template<typename ctx_t>
int32_t zprecedence1(ctx_t &ctx, hidx_t idx1, hidx_t idx2
    , int32_t &prec1, int32_t &prec2)
{
    zhistory_t::cache_t &cache = ctx.history.cache;
    int32_t prec = 0;

    // use the same cache entry for (x, y) and (y, x)
    uint32_t k1 = static_cast<uint32_t>(idx1), k2 = static_cast<uint32_t>(idx2);
    bool invert = k2 < k1;
    if (invert) std::swap(k1, k2);
    const uint64_t key = (static_cast<uint64_t>(k1) << 32) | k2;

    zhistory_t::cache_t::const_iterator i = cache.find(key);
    if (i != cache.end()) {
        // use previously computed precedence values from cache
        const zhistory_t::cache_entry_t &val = i->second;
        prec1 = val.prec1;
        prec2 = val.prec2;
        prec = val.prec;
        if (invert) {
            std::swap(prec1, prec2);
            prec = -prec;
        }
    }
    else {
        // compute precedence values and put them into cache
        prec = zprecedence2(ctx, idx1, idx2, prec1, prec2);
        zhistory_t::cache_entry_t val = {prec1, prec2, prec};
        if (invert) {
            std::swap(val.prec1, val.prec2);
            val.prec = -val.prec;
        }
        cache.insert(std::make_pair(key, val));
    }

    return prec;
}

// see note [lazy computation and caching of precedence]
template<typename ctx_t>
int32_t zprecedence2(ctx_t &ctx, hidx_t idx1, hidx_t idx2
    , int32_t &prec1, int32_t &prec2)
{
    if (idx1 == idx2) {
        prec1 = prec2 = MAX_RHO;
        return 0;
    }

    const std::vector<Tag> &tags = ctx.nfa.tags;
    zhistory_t &hist = ctx.history;

    int32_t prec = 0;
    prec1 = prec2 = MAX_RHO;

    int32_t i1 = idx1, i2 = idx2;

    const uint32_t o1 = get_orig(hist, idx1), o2 = get_orig(hist, idx2);

    uint32_t s1 = get_step(hist, i1), s2 = get_step(hist, i2);
    const uint32_t s = std::max(s1, s2);

    const bool fork_frame = o1 == o2 && s1 == s2;

    tag_info_t info1 = NOINFO, info2 = NOINFO;
    for (; i1 != i2 && (s1 >= s || s2 >= s);) {
        if (s1 >= s && (i1 > i2 || s2 < s)) {
            const zhistory_t::node_t &n = hist.node(i1);
            info1 = n.info;
            prec1 = std::min(prec1, tags[info1.idx].height);
            i1 = n.pred;
            s1 = get_step(hist, i1);
        }
        else {
            const zhistory_t::node_t &n = hist.node(i2);
            info2 = n.info;
            prec2 = std::min(prec2, tags[info2.idx].height);
            i2 = n.pred;
            s2 = get_step(hist, i2);
        }
    }
    if (!fork_frame) {
        // recurse into previous steps (via cache)
        int32_t p1, p2;
        prec = zprecedence1(ctx, i1, i2, p1, p2);
        prec1 = std::min(prec1, p1);
        prec2 = std::min(prec2, p2);
    }
    else if (i1 != HROOT) {
        const int32_t h = tags[hist.node(i1).info.idx].height;
        prec1 = std::min(prec1, h);
        prec2 = std::min(prec2, h);
    }

    // longest precedence
    if (prec1 > prec2) return -1;
    if (prec1 < prec2) return  1;

    // leftmost precedence
    return !fork_frame ? prec
        : leftprec(info1, info2, i1 == idx1, i2 == idx2);
}

int32_t unpack_longest(int32_t packed)
{
    // take lower 30 bits and sign-extend
    return static_cast<int32_t>(static_cast<uint32_t>(packed) << 2u) >> 2u;
}

int32_t unpack_leftmost(int32_t packed)
{
    // take higher 2 bits and sign-extend
    return packed >> 30u;
}

int32_t pack(int32_t longest, int32_t leftmost)
{
    // avoid signed overflows by using unsigned arithmetics
    uint32_t u_longest = static_cast<uint32_t>(longest);
    uint32_t u_leftmost = static_cast<uint32_t>(leftmost);

    // leftmost: higher 2 bits, longest: lower 30 bits
    uint32_t u_packed = (u_longest & 0x3fffFFFF) | (u_leftmost << 30u);
    int32_t packed = static_cast<int32_t>(u_packed);

    DASSERT(unpack_longest(packed) == longest
        && unpack_leftmost(packed) == leftmost);

    return packed;
}

uint32_t get_step(const zhistory_t &hist, int32_t idx)
{
    return idx == HROOT ? 0 : hist.node(idx).step;
}

uint32_t get_orig(const zhistory_t &hist, int32_t idx)
{
    return idx == HROOT ? 0 : hist.node(idx).orig;
}

} // namespace re2c

#endif // _RE2C_DFA_POSIX_PRECEDENCE_
