#include <queue>
#include <stdio.h>

#include "lib/lex.h"
#include "lib/regex.h"
#include "lib/regex_impl.h"
#include "src/options/opt.h"
#include "src/options/warn.h"
#include "src/debug/debug.h"
#include "src/dfa/determinization.h"
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

static void reach_on_symbol(simctx_t &, uint32_t);
static void closure_posix(simctx_t &);
static void relax(simctx_t &, const conf_t &, worklist_t &);
static int32_t precedence(simctx_t &ctx, uint32_t xl, uint32_t yl, int32_t &rhox, int32_t &rhoy);
static int32_t precedence_(simctx_t &ctx, uint32_t xl, uint32_t yl, int32_t &rhox, int32_t &rhoy);
static uint32_t unwind(history_t &hist, tag_path_t &path, uint32_t hidx, uint32_t step);
static inline uint32_t get_step(const history_t &hist, uint32_t idx);
static inline uint32_t get_orig(const history_t &hist, uint32_t idx);

int regexec_nfa_posix(const regex_t *preg, const char *string, size_t nmatch,
    regmatch_t pmatch[], int)
{
    simctx_t ctx(preg, string);
    const nfa_t *nfa = ctx.nfa;
    confset_t &state = ctx.state;

    const conf_t c0 = {nfa->root, index(nfa, nfa->root), HROOT};
    ctx.reach.push_back(c0);
    closure_posix(ctx);

    for (;;) {
        const uint32_t sym = static_cast<uint8_t>(*ctx.cursor++);
        if (ctx.state.empty() || sym == 0) break;
        reach_on_symbol(ctx, sym);
        ++ctx.step;
        closure_posix(ctx);
    }

    confiter_t b = state.begin(), e = state.end(), i, j;
    for (i = b; i != e; ++i) {
        i->state->clos = NOCLOS;
        DASSERT(i->state->active == 0);
    }

    return finalize(ctx, string, nmatch, pmatch);
}

void reach_on_symbol(simctx_t &ctx, uint32_t sym)
{
    const nfa_t *nfa = ctx.nfa;
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
                    conf_t c = {s->ran.out, index(nfa, s), i->thist};
                    reach.push_back(c);
                    break;
                }
            }
        }
    }
}

void closure_posix(simctx_t &ctx)
{
    const confset_t &reach = ctx.reach;
    confset_t &state = ctx.state;

    worklist_t wl;
    state.clear();

    for (cconfiter_t c = reach.begin(); c != reach.end(); ++c) {
        relax(ctx, *c, wl);
    }

    for (; !wl.empty(); ) {
        nfa_state_t *q = wl.top();
        wl.pop();
        q->active = 0;
        conf_t x = state[q->clos];

        switch (q->type) {
            case nfa_state_t::NIL:
                x.state = q->nil.out;
                relax(ctx, x, wl);
                break;
            case nfa_state_t::ALT:
                x.state = q->alt.out1;
                relax(ctx, x, wl);
                x.state = q->alt.out2;
                relax(ctx, x, wl);
                break;
            case nfa_state_t::TAG:
                x.state = q->tag.out;
                x.thist = ctx.hist.push(x.thist, ctx.step, q->tag.info, x.origin);
                relax(ctx, x, wl);
                break;
            case nfa_state_t::FIN:
                ctx.marker = ctx.cursor + 1;
                ctx.hidx = x.thist;
                ctx.rule = 0;
                break;
            case nfa_state_t::RAN:
                break;
        }
    }
}

void relax(simctx_t &ctx, const conf_t &c, worklist_t &wl)
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
        wl.push(q);
    }
}

int32_t precedence(simctx_t &ctx, uint32_t idx1, uint32_t idx2
    , int32_t &prec1, int32_t &prec2)
{
    int32_t prec = 0;

    // use the same cache entry for (x, y) and (y, x)
    uint32_t k1 = idx1, k2 = idx2;
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

int32_t precedence_(simctx_t &ctx, uint32_t idx1, uint32_t idx2
    , int32_t &prec1, int32_t &prec2)
{
    if (idx1 == idx2) {
        prec1 = prec2 = MAX_RHO;
        return 0;
    }

    const std::vector<Tag> &tags = ctx.nfa->tags;
    history_t &hist = ctx.hist;
    tag_path_t &path1 = hist.path1, &path2 = hist.path2;

    int32_t prec = 0;

    const uint32_t orig1 = get_orig(hist, idx1);
    const uint32_t orig2 = get_orig(hist, idx2);

    const uint32_t step1 = get_step(hist, idx1);
    const uint32_t step2 = get_step(hist, idx2);
    const uint32_t step = std::max(step1, step2);

    const size_t oldsize1 = path1.size();
    const size_t oldsize2 = path2.size();

    // unwind histories one step back (paths may grow and be reallocated)
    idx1 = unwind(hist, path1, idx1, step);
    idx2 = unwind(hist, path2, idx2, step);

    const bool fork_frame = orig1 == orig2 && step1 == step2;

    if (!fork_frame) {
        // recurse into previous steps (via cache)
        prec = precedence(ctx, idx1, idx2, prec1, prec2);
    }

    tag_path_t::const_reverse_iterator
        s1 = path1.rbegin(),
        s2 = path2.rbegin(),
        e1 = path1.rend() - static_cast<ssize_t>(oldsize1),
        e2 = path2.rend() - static_cast<ssize_t>(oldsize2),
        i1 = s1, i2 = s2, j1, j2;

    // longest precedence
    if (fork_frame) {
        // find fork
        for (; i1 != e1 && i2 != e2 && *i1 == *i2; ++i1, ++i2);
        prec1 = prec2 = i1 > s1
            ? tags[(i1 - 1)->idx].height : MAX_RHO;
    }
    for (j1 = i1; j1 != e1; ++j1) {
        prec1 = std::min(prec1, tags[j1->idx].height);
    }
    for (j2 = i2; j2 != e2; ++j2) {
        prec2 = std::min(prec2, tags[j2->idx].height);
    }
    if (prec1 > prec2) { prec = -1; goto end; }
    if (prec1 < prec2) { prec =  1; goto end; }

    // leftmost precedence
    if (fork_frame) {
        // equal => not less
        if (i1 == e1 && i2 == e2) { prec = 0; goto end; }

        // shorter => less
        if (i1 == e1) { prec = -1; goto end; }
        if (i2 == e2) { prec =  1; goto end; }

        const uint32_t idx1 = i1->idx, idx2 = i2->idx;
        const bool neg1 = i1->neg, neg2 = i2->neg;

        // can't be both closing
        DASSERT(!(idx1 % 2 == 1 && idx2 % 2 == 1));

        // closing vs opening: closing wins
        if (idx1 % 2 == 1) { prec = -1; goto end; }
        if (idx2 % 2 == 1) { prec =  1; goto end; }

        // can't be both negative
        DASSERT(!(neg1 && neg2));

        // positive vs negative: positive wins
        if (neg1) { prec =  1; goto end; }
        if (neg2) { prec = -1; goto end; }

        DASSERT(false);
    }

end:
    path1.resize(oldsize1);
    path2.resize(oldsize2);
    return prec;
}

uint32_t get_step(const history_t &hist, uint32_t idx)
{
    return idx == HROOT ? 0 : hist.nodes[idx].step;
}

uint32_t get_orig(const history_t &hist, uint32_t idx)
{
    return idx == HROOT ? 0 : hist.nodes[idx].orig;
}

uint32_t unwind(history_t &hist, tag_path_t &path, uint32_t idx, uint32_t step)
{
    uint32_t new_idx = HROOT;
    for (uint32_t i = idx; i != HROOT; ) {
        const history_t::node_t &n = hist.nodes[i];
        if (n.step < step) {
            new_idx = i;
            break;
        }
        path.push_back(n.info);
        i = n.pred;
    }
    return new_idx;
}

} // namespace libre2c
} // namespace re2c

