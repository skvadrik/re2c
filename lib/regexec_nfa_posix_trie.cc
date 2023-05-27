#include <stddef.h>
#include <algorithm>
#include <vector>

#include "lib/regex.h"
#include "lib/regex_impl.h"
#include "src/dfa/closure_posix.h"
#include "src/dfa/tag_history.h"
#include "src/nfa/nfa.h"
#include "src/util/check.h"
#include "src/util/range.h"

namespace re2c {

// Specialization that doesn't sort initial closure like Okui-Suzuki (there is no cheap way to sort
// it in the lazy-disambiguation algorithm).
template<> void init_gor1<libre2c::pzsimctx_t>(libre2c::pzsimctx_t& ctx);

namespace libre2c {

// note [lazy computation and caching of precedence]
//
// Eagerly computing precedence values on each step for each pair of closure states is a waste of
// time: most of these values are not needed, because regexp may be unambigous, or the given input
// string may be unambigous, or even if there is ambiguity, it may take only a few comparisons to
// resolve. All the rest is wasted effort.
//
// We can avoid it by delaying precedence computation until necessary, and then unwinding all the
// steps backwards, computing precedence for each step and caching the computed values (so that the
// same pair of histories is not compared twice). It is still the same incremental comparison as
// with precedence matrices: we compare step by step, going from the fork frame to the join frame.
// The result of comparison on each step is folded to a triple of numbers and recorded in cache. It
// is important that we do record each step, not just the final step, because the next pair of
// ambiguous histories may unwind to the same pair of prefixes that was compared before.
//
// For all this to work, it is necessary that we are able to store all history until the end,
// because at any step we might need to unwind an arbitrary number of steps back. We also need to
// address individual subhistories efficiently in order to use them as keys in the cache. All this
// is achieved by storing history in the form of a trie and addressing individual histories by
// indices in that trie. We also use trie to compute the final tag values (instead of storing tags
// in registers at each step).

static void make_step(pzsimctx_t&, uint32_t);
static void make_final_step(pzsimctx_t&);
template<typename ctx_t> static int32_t zprecedence1(
        ctx_t& ctx, hidx_t idx1, hidx_t idx2, int32_t& prec1, int32_t& prec2);
template<typename ctx_t> static int32_t zprecedence2(
        ctx_t& ctx, hidx_t idx1, hidx_t idx2, int32_t& prec1, int32_t& prec2);

// we *do* want this to be inlined
static inline uint32_t get_step(const zhistory_t& hist, int32_t idx);
static inline uint32_t get_orig(const zhistory_t& hist, int32_t idx);
static inline void closure_posix(pzsimctx_t& ctx);

int regexec_nfa_posix_trie(
        const regex_t* preg, const char* string, size_t nmatch, regmatch_t pmatch[], int) {
    pzsimctx_t& ctx = *static_cast<pzsimctx_t*>(preg->simctx);
    init(ctx, string);

    const conf_t c0(ctx.nfa.root, 0, HROOT);
    ctx.reach.push_back(c0);
    for (;;) {
        closure_posix(ctx);
        const uint32_t sym = static_cast<uint8_t>(*ctx.cursor++);
        if (ctx.state.empty() || sym == 0) break;
        make_step(ctx, sym);
    }
    make_final_step(ctx);

    ctx.history.cache.clear();
    return finalize(ctx, string, nmatch, pmatch);
}

void closure_posix(pzsimctx_t& ctx) {
    closure_posix_gor1(ctx);
}

void make_step(pzsimctx_t& ctx, uint32_t sym) {
    const confset_t& state = ctx.state;
    confset_t& reach = ctx.reach;
    cconfiter_t b = state.begin(), e = state.end(), i;

    reach.clear();
    uint32_t j = 0;
    for (i = b; i != e; ++i) {
        TnfaState* s = i->state;

        s->clos = NOCLOS;
        s->arcidx = 0;
        DCHECK(s->status == GOR_NOPASS && s->active == 0);

        if (s->kind == TnfaState::Kind::RAN) {
            for (const Range* r = s->ran; r; r = r->next()) {
                if (r->lower() <= sym && sym < r->upper()) {
                    const conf_t c(s->out1, j++, i->thist);
                    reach.push_back(c);
                    break;
                }
            }
        } else if (s->kind == TnfaState::Kind::FIN) {
            ctx.marker = ctx.cursor;
            ctx.hidx = i->thist;
            ctx.rule = 0;
        }
    }

    ++ctx.step;
}

void make_final_step(pzsimctx_t& ctx) {
    for (confiter_t i = ctx.state.begin(), e = ctx.state.end(); i != e; ++i) {
        TnfaState* s = i->state;

        s->clos = NOCLOS;
        s->arcidx = 0;
        DCHECK(s->status == GOR_NOPASS && s->active == 0);

        if (s->kind == TnfaState::Kind::FIN) {
            ctx.marker = ctx.cursor;
            ctx.hidx = i->thist;
            ctx.rule = 0;
        }
    }
}

template<typename ctx_t>
int32_t zhistory_t::precedence(ctx_t& ctx,
                               const typename ctx_t::conf_t& x,
                               const typename ctx_t::conf_t& y,
                               int32_t& prec1,
                               int32_t& prec2) {
    return zprecedence1(ctx, x.thist, y.thist, prec1, prec2);
}

// see note [lazy computation and caching of precedence]
template<typename ctx_t>
int32_t zprecedence1(ctx_t& ctx, hidx_t idx1, hidx_t idx2, int32_t& prec1, int32_t& prec2) {
    zhistory_t::cache_t& cache = ctx.history.cache;
    int32_t prec = 0;

    // use the same cache entry for (x, y) and (y, x)
    uint32_t k1 = static_cast<uint32_t>(idx1), k2 = static_cast<uint32_t>(idx2);
    bool invert = k2 < k1;
    if (invert) std::swap(k1, k2);
    const uint64_t key = (static_cast<uint64_t>(k1) << 32) | k2;

    zhistory_t::cache_t::const_iterator i = cache.find(key);
    if (i != cache.end()) {
        // use previously computed precedence values from cache
        const zhistory_t::cache_entry_t& val = i->second;
        prec1 = val.prec1;
        prec2 = val.prec2;
        prec = val.prec;
        if (invert) {
            std::swap(prec1, prec2);
            prec = -prec;
        }
    } else {
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
int32_t zprecedence2(ctx_t& ctx, hidx_t idx1, hidx_t idx2, int32_t& prec1, int32_t& prec2) {
    if (idx1 == idx2) {
        prec1 = prec2 = MAX_RHO;
        return 0;
    }

    const std::vector<Tag>& tags = ctx.nfa.tags;
    zhistory_t& hist = ctx.history;

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
            const zhistory_t::node_t& n = hist.node(i1);
            info1 = n.info;
            prec1 = std::min(prec1, tags[info1.idx].height);
            i1 = n.pred;
            s1 = get_step(hist, i1);
        } else {
            const zhistory_t::node_t& n = hist.node(i2);
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
    } else if (i1 != HROOT) {
        const int32_t h = tags[hist.node(i1).info.idx].height;
        prec1 = std::min(prec1, h);
        prec2 = std::min(prec2, h);
    }

    // longest precedence
    if (prec1 > prec2) return -1;
    if (prec1 < prec2) return  1;

    // leftmost precedence
    return !fork_frame ? prec : leftprec(info1, info2, i1 == idx1, i2 == idx2);
}

uint32_t get_step(const zhistory_t& hist, int32_t idx) {
    return idx == HROOT ? 0 : hist.node(idx).step;
}

uint32_t get_orig(const zhistory_t& hist, int32_t idx) {
    return idx == HROOT ? 0 : hist.node(idx).orig;
}

} // namespace libre2c

template<> void init_gor1<libre2c::pzsimctx_t>(libre2c::pzsimctx_t& ctx) {
    ctx.state.clear();
    libre2c::pzsimctx_t::cconfiter_t c = ctx.reach.begin(), e = ctx.reach.end();
    for (; c != e; ++c) {
        relax_gor1(ctx, *c);
    }
}

} // namespace re2c
