#include <queue>
#include <stdio.h>

#include "lib/lex.h"
#include "lib/regex.h"
#include "lib/regex_impl.h"
#include "src/options/opt.h"
#include "src/debug/debug.h"
#include "src/dfa/determinization.h"
#include "src/dfa/posix_precedence.h"
#include "src/nfa/nfa.h"


namespace re2c {
namespace libre2c {

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

static void make_step(pzctx_t &, uint32_t);
static void make_final_step(pzctx_t &);
static void closure_posix(pzctx_t &);
static int32_t precedence(pzctx_t &ctx, int32_t xl, int32_t yl, int32_t &rhox, int32_t &rhoy);
static int32_t precedence_(pzctx_t &ctx, int32_t xl, int32_t yl, int32_t &rhox, int32_t &rhoy);

// we *do* want this to be inlined
static inline void relax(pzctx_t &, const conf_t &);
static inline uint32_t get_step(const zhistory_t &hist, int32_t idx);
static inline uint32_t get_orig(const zhistory_t &hist, int32_t idx);

int regexec_nfa_posix_trie(const regex_t *preg, const char *string
    , size_t nmatch, regmatch_t pmatch[], int)
{
    pzctx_t &ctx = *static_cast<pzctx_t*>(preg->simctx);
    init(ctx, string);

    nfa_state_t *s0 = ctx.nfa.root;
    const conf_t c0(s0, s0->coreid, HROOT);
    ctx.reach.push_back(c0);
    closure_posix(ctx);
    for (;;) {
        const uint32_t sym = static_cast<uint8_t>(*ctx.cursor++);
        if (ctx.state.empty() || sym == 0) break;
        make_step(ctx, sym);
        closure_posix(ctx);
    }
    make_final_step(ctx);

    return finalize(ctx, string, nmatch, pmatch);
}

void make_step(pzctx_t &ctx, uint32_t sym)
{
    const confset_t &state = ctx.state;
    confset_t &reach = ctx.reach;
    cconfiter_t b = state.begin(), e = state.end(), i;

    reach.clear();
    for (i = b; i != e; ++i) {
        nfa_state_t *s = i->state;

        s->clos = NOCLOS;
        DASSERT(s->active == 0);

        if (s->type == nfa_state_t::RAN) {
            for (const Range *r = s->ran.ran; r; r = r->next()) {
                if (r->lower() <= sym && sym < r->upper()) {
                    const conf_t c(s->ran.out, s->coreid, i->thist);
                    reach.push_back(c);
                    break;
                }
            }
        }
        else if (s->type == nfa_state_t::FIN) {
            ctx.marker = ctx.cursor;
            ctx.hidx = i->thist;
            ctx.rule = 0;
        }
    }

    ++ctx.step;
}

void make_final_step(pzctx_t &ctx)
{
    for (confiter_t i = ctx.state.begin(), e = ctx.state.end(); i != e; ++i) {
        nfa_state_t *s = i->state;

        s->clos = NOCLOS;
        DASSERT(s->active == 0);

        if (s->type == nfa_state_t::FIN) {
            ctx.marker = ctx.cursor;
            ctx.hidx = i->thist;
            ctx.rule = 0;
        }
    }
}

void closure_posix(pzctx_t &ctx)
{
    const confset_t &reach = ctx.reach;
    confset_t &state = ctx.state;
    gtop_heap_t &heap = ctx.gtop_heap;

    state.clear();

    for (cconfiter_t c = reach.begin(); c != reach.end(); ++c) {
        relax(ctx, *c);
    }

    for (; !heap.empty(); ) {
        nfa_state_t *q = heap.top();
        heap.pop();
        q->active = 0;

        const conf_t &x = state[q->clos];
        const uint32_t o = x.origin;
        const int32_t h = x.thist;

        switch (q->type) {
            case nfa_state_t::NIL:
                relax(ctx, conf_t(q->nil.out, o, h));
                break;
            case nfa_state_t::ALT:
                relax(ctx, conf_t(q->alt.out1, o, h));
                relax(ctx, conf_t(q->alt.out2, o, h));
                break;
            case nfa_state_t::TAG:
                relax(ctx, conf_t(q->tag.out, o
                    , ctx.history.push(h, ctx.step, q->tag.info, o)));
                break;
            default:
                break;
        }
    }
}

void relax(pzctx_t &ctx, const conf_t &c)
{
    confset_t &state = ctx.state;
    nfa_state_t *q = c.state;
    const uint32_t idx = q->clos;
    int32_t h1, h2;

    // first time we see this state
    if (idx == NOCLOS) {
        q->clos = static_cast<uint32_t>(state.size());
        state.push_back(c);
    }

    // States of in-degree less than 2 are not joint points;
    // the fact that we are re-scanning this state means that we found
    // a better path to some previous state. Due to the right distributivity
    // of path comparison over path concatenation (X < Y => XZ < YZ) we
    // can just propagate the new path up to the next join point.
    else if (q->indeg < 2) {
        state[idx] = c;
    }

    // join point; compare the new path and the old path
    else if (precedence(ctx, c.thist, state[idx].thist, h1, h2) < 0) {
        state[idx] = c;
    }

    // the previous path was better, discard the new one
    else {
        q = NULL;
    }

    if (q != NULL && !q->active) {
        q->active = 1;
        ctx.gtop_heap.push(q);
    }
}

int32_t precedence(pzctx_t &ctx, int32_t idx1, int32_t idx2
    , int32_t &prec1, int32_t &prec2)
{
    int32_t prec = 0;

    // use the same cache entry for (x, y) and (y, x)
    uint32_t k1 = static_cast<uint32_t>(idx1), k2 = static_cast<uint32_t>(idx2);
    bool invert = k2 < k1;
    if (invert) std::swap(k1, k2);
    const uint64_t key = (static_cast<uint64_t>(k1) << 32) | k2;

    cache_t::const_iterator i = ctx.cache.find(key);
    if (i != ctx.cache.end()) {
        // use previously computed precedence values from cache
        const cache_entry_t &val = i->second;
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
        prec = precedence_(ctx, idx1, idx2, prec1, prec2);
        cache_entry_t val = {prec1, prec2, prec};
        if (invert) {
            std::swap(val.prec1, val.prec2);
            val.prec = -val.prec;
        }
        ctx.cache.insert(std::make_pair(key, val));
    }

    return prec;
}

int32_t precedence_(pzctx_t &ctx, int32_t idx1, int32_t idx2
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

    tag_info_t info1, info2;
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
        prec = precedence(ctx, i1, i2, p1, p2);
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
    if (fork_frame) {
        // equal => not less
        if (i1 == idx1 && i2 == idx2) return 0;

        // shorter => less
        if (i1 == idx1) return -1;
        if (i2 == idx2) return  1;

        const uint32_t tag1 = info1.idx, tag2 = info2.idx;
        const bool neg1 = info1.neg, neg2 = info2.neg;

        // can't be both closing
        DASSERT(!(tag1 % 2 == 1 && tag2 % 2 == 1));

        // closing vs opening: closing wins
        if (tag1 % 2 == 1) return -1;
        if (tag2 % 2 == 1) return  1;

        // can't be both negative
        DASSERT(!(neg1 && neg2));

        // positive vs negative: positive wins
        if (neg1) return  1;
        if (neg2) return -1;
    }
    else {
        return prec;
    }

    DASSERT(false); // unreachable
    return 0;
}

uint32_t get_step(const zhistory_t &hist, int32_t idx)
{
    return idx == HROOT ? 0 : hist.node(idx).step;
}

uint32_t get_orig(const zhistory_t &hist, int32_t idx)
{
    return idx == HROOT ? 0 : hist.node(idx).orig;
}

} // namespace libre2c
} // namespace re2c

