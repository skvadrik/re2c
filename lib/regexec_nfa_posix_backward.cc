#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>

#include "lib/regex.h"
#include "lib/regex_impl.h"
#include "src/debug/debug.h"
#include "src/dfa/closure_posix.h"
#include "src/dfa/tag_history.h"
#include "src/nfa/nfa.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"
#include "src/util/range.h"


namespace re2c {
namespace libre2c {

/*
 * This is a quick-and-dirty implementation of backward matching algorithm
 * suggested by Cox. The algorithm is incorrect, but it is surprisingly
 * close to correct, and we keep it around for research purposes (in case
 * we need to confirm its incorrectness in the light of some future findings).
 *
 * The algorithm attempts to find POSIX longest match by going from right
 * to left and maximizing the length of the latest iteration of each
 * capturing group, similar to the way Laurikari algorithm minimizez or
 * maximizes the most recent value of each tag.
 *
 * The algorithm also has to remember the match on the last iteration, so
 * it has to carry around twice as much data for offssets. Offsets are
 * bound to configurations: for each configuration, there is a "scratch"
 * offset pair, an "accepted" offset pair and also a "backup" offset pair
 * that is used only during closure initialization. And double all that,
 * as we keep offsets of both last and most recent iterations. All this
 * means a lot of copying, so unsurprisingly the algorithm is very slow
 * if RE has many submatch groups. Some copying can be reduced, but not all:
 * SSSP does not (in general) proceed in stack order, therefore the
 * previous scanned configuration might not be related at all to the next.
 * GOR1's topsort phase is DFS though, so it can be made to use a single
 * scratch buffer for offsets (that is updated on DFS recursive enter and
 * restored on DFS recursive return).
 *
 * The algorithm is incorrect because it sometimes compares ambiguous
 * paths too late, when the difference between them has been overwritten
 * with more recent offsets. This may happen when two conditions are met:
 *
 * (1) the most recent iteration of both paths matches the same substring,
 *     so that the offsets on this iteration are equal
 *
 * (2) paths are compared for the first time *after* the offsets have been
 *     updated and have become indistinguishable
 *
 * The algorithm would work if such paths had a join point somewhere
 * before the problematic iteration, and were properly disambiguated at that
 * point. The algorithm may fail to do so in two cases:
 *
 * (A) With bounded repetition, each repetition duplicated in is a separate
 *     automaton, and paths may not meet until the final join point (because
 *     at each step they end in different subautomata). This depends on how
 *     we unroll bounded repetition. An example of this is (aaaa|aaa|a){3,4}
 *     and paths X = (aaaa)(aaaa)(a)(a) and Y = (aaaa)(aaa)(aaa), provided
 *     that we unroll bounded repetition by making the last iteration
 *     optional and the first three non-optional (the normal way we unroll
 *     it). Note that the paths have different number of iterations (4 and 3)
 *     which is why they don't meet until the very end.
 *
 * (B) Even if there is a join point, due to a particular order of closure
 *     traversal paths may need to be compared *after* the join point (at
 *     the time when offsets are already overwritten with new ones, making
 *     the paths indistinguishable). This may happen if the order of closure
 *     traversal is not topological (for example, when we go in depth-first
 *     order, start from some unfortunate initial state and propagate the
 *     wrong path to other states, then start from another initial state and
 *     need to propagate improvement to all those states).
 *
 */

static void make_one_step_simple(psimctx_t &, uint32_t);
static void make_one_step(psimctx_t &, uint32_t);
static void make_final_step(psimctx_t &);
static void update_final_offsets(psimctx_t &ctx, const conf_t &c);
static void closure_simple(psimctx_t &ctx);
static void relax_gtop(psimctx_t &ctx, const psimctx_t::conf_t &c);
static void closure_posix_gtop(psimctx_t &ctx);
static bool scan(psimctx_t &ctx, nfa_state_t *q, bool all);
static bool relax_gor1(psimctx_t &ctx, const psimctx_t::conf_t &c);
static void closure_posix_gor1(psimctx_t &ctx);
static inline void closure_posix(psimctx_t &ctx);
static inline uint32_t index(const nfa_state_t *s, const nfa_t &nfa);
static void copy_offs(psimctx_t &ctx, const nfa_state_t *y, const nfa_state_t *x, tag_info_t info);
static inline void accept_offsets(psimctx_t &ctx, const nfa_state_t *s);

// debug
static int D = 0;
static void prtoff(psimctx_t &ctx, uint32_t x, bool newer);
static inline void prtoff4(psimctx_t &ctx, uint32_t x);
static inline void prtoff5(psimctx_t &ctx, uint32_t x);

static regoff_t *offsets4 = NULL;
static regoff_t *offsets5 = NULL;
static regoff_t *offsets6 = NULL;

int regexec_nfa_posix_backward(const regex_t *preg, const char *string
    , size_t nmatch, regmatch_t pmatch[], int /* eflags */)
{
    psimctx_t &ctx = *static_cast<psimctx_t*>(preg->simctx);
    init(ctx, string);

    // 1st pass, forward: find longest match on a simple NFA

    ctx.reach.push_back(conf_t(ctx.nfa0->root, 0, 0));
    for (;;) {
        closure_simple(ctx);
        const uint32_t sym = static_cast<uint8_t>(*ctx.cursor++);
        if (ctx.state.empty() || sym == 0) break;
        make_one_step_simple(ctx, sym);
    }

    for (cconfiter_t i = ctx.state.begin(), e = ctx.state.end(); i != e; ++i) {
        nfa_state_t *s = i->state;
        s->clos = NOCLOS;
        if (s->type == nfa_state_t::FIN) {
            ctx.marker = ctx.cursor;
            ctx.rule = 0;
        }
    }

    if (ctx.rule == Rule::NONE) {
        return REG_NOMATCH;
    }

    // 2nd pass, backward: find submatches

    const uint32_t len = static_cast<uint32_t>(ctx.marker - string) - 1;
    init(ctx, string);
    ctx.step = len;
    ctx.cursor = ctx.marker = string + len;

    const std::vector<Tag> &tags = ctx.nfa.tags;
    const size_t sz = tags.size() * ctx.nfa.size * 2;
    offsets4 = new regoff_t[sz];
    offsets5 = new regoff_t[sz];
    offsets6 = new regoff_t[sz];

    std::fill(offsets4, offsets4 + sz, -2);
    std::fill(offsets5, offsets5 + sz, -2);

    ctx.reach.push_back(conf_t(ctx.nfa.root, 0, 0));
    for (;;) {
        closure_posix(ctx);
        if (ctx.state.empty() || ctx.cursor == string) break;
        const uint32_t sym = static_cast<uint8_t>(*--ctx.cursor);
        make_one_step(ctx, sym);
        --ctx.step;
    }
    make_final_step(ctx);

    delete[] offsets6;
    delete[] offsets5;
    delete[] offsets4;

    if (ctx.rule == Rule::NONE) {
        return REG_NOMATCH;
    }

    const getoff_nfa_t fn = { ctx.offsets3 };
    tags_to_submatch(tags, nmatch, pmatch, static_cast<regoff_t>(len), fn);

    return 0;
}

static uint32_t index(const nfa_state_t *s, const nfa_t &nfa)
{
    return static_cast<uint32_t>(s - nfa.states);
}

void closure_simple(psimctx_t &ctx)
{
    psimctx_t::confset_t &state = ctx.state, &stack = ctx.reach;
    state.clear();

    for (; !stack.empty(); ) {
        const psimctx_t::conf_t x = stack.back();
        stack.pop_back();
        nfa_state_t *n = x.state;

        if (n->clos != NOCLOS) continue;

        n->clos = static_cast<uint32_t>(state.size());
        state.push_back(x);

        switch (n->type) {
            case nfa_state_t::NIL:
                stack.push_back(psimctx_t::conf_t(x, n->nil.out));
                break;
            case nfa_state_t::ALT:
                stack.push_back(psimctx_t::conf_t(x, n->alt.out2));
                stack.push_back(psimctx_t::conf_t(x, n->alt.out1));
                break;
            case nfa_state_t::TAG:
                stack.push_back(psimctx_t::conf_t(x, n->tag.out, 0));
                break;
            case nfa_state_t::RAN:
            case nfa_state_t::FIN:
                break;
        }
    }
}

void make_one_step_simple(psimctx_t &ctx, uint32_t sym)
{
    const confset_t &state = ctx.state;
    confset_t &reach = ctx.reach;
    DASSERT(reach.empty());

    for (rcconfiter_t i = state.rbegin(), e = state.rend(); i != e; ++i) {
        nfa_state_t *s = i->state;
        s->clos = NOCLOS;

        if (s->type == nfa_state_t::RAN) {
            for (const Range *r = s->ran.ran; r; r = r->next()) {
                if (r->lower() <= sym && sym < r->upper()) {
                    conf_t c(s->ran.out, 0, 0);
                    reach.push_back(c);
                    break;
                }
            }
        }
        else if (s->type == nfa_state_t::FIN) {
            ctx.marker = ctx.cursor;
            ctx.rule = 0;
        }
    }

    ++ctx.step;
}

void closure_posix(psimctx_t &ctx)
{
    if (ctx.flags & REG_GTOP) {
        closure_posix_gtop(ctx);
    }
    else {
        closure_posix_gor1(ctx);
    }
}

static int32_t precedence(psimctx_t &ctx, const conf_t &x, const conf_t &y)
{
    DASSERT(x.state == y.state); (void)y;
    const uint32_t idx = index(x.state, ctx.nfa);

    const size_t ntags = ctx.nfa.tags.size();
    const regoff_t *ox = offsets5 + ntags * idx * 2;
    const regoff_t *oy = offsets4 + ntags * idx * 2;

    prtoff5(ctx, idx);
    prtoff4(ctx, idx);
    if (D) fprintf(stderr, "prec %u: ", idx);

    for (size_t t = 0; t < ctx.nfa.tags.size(); t += 2) {
        const regoff_t offx = ox[2 * (t + 1)];
        const regoff_t offy = oy[2 * (t + 1)];
        if (offx != offy) {
            int cmp;
            if (offx == -2) {
                cmp = -1;
            }
            if (offy == -2) {
                cmp = 1;
            }
            else {
                cmp = offx > offy ? -1 : 1;
            }
            if (D) fprintf(stderr, "%d\n", cmp);
            return cmp;
        }
    }
    if (D) fprintf(stderr, "0\n");
    return 0;
}

void closure_posix_gor1(psimctx_t &ctx)
{
    psimctx_t::confset_t &state = ctx.state, &reach = ctx.reach;
    std::vector<nfa_state_t*>
        &topsort = ctx.gor1_topsort,
        &linear = ctx.gor1_linear;
    const size_t ntags = ctx.nfa.tags.size();

    state.clear();
    memcpy(offsets6, offsets4, ctx.nfa.size * ntags * sizeof(regoff_t) * 2);

    // Reverse order happens to result in less test errors, but both orders
    // do not yield a correct algorithm (paths are still compared after
    // their join point sometimes).
    for (psimctx_t::rcconfiter_t c = reach.rbegin(); c != reach.rend(); ++c) {
        regoff_t       *ox = offsets5 + ntags * index(c->state, ctx.nfa) * 2;
        const regoff_t *oy = offsets6 + ntags * c->origin * 2;
        memcpy(ox, oy, ntags * sizeof(regoff_t) * 2);

        if (D) fprintf(stderr, "restoring offsets %u to %u\n"
            , c->origin, index(c->state, ctx.nfa));

        relax_gor1(ctx, *c);
    }

    for (; !topsort.empty(); ) {

        // 1st pass: depth-first postorder traversal of admissible subgraph
        for (; !topsort.empty(); ) {
            nfa_state_t *q = topsort.back();
            if (q->status == GOR_LINEAR) {
                topsort.pop_back();
            }
            else {
                q->status = GOR_TOPSORT;
                if (!scan(ctx, q, false)) {
                    q->status = GOR_LINEAR;
                    topsort.pop_back();
                    linear.push_back(q);
                }
            }
        }

        // 2nd pass: linear scan of topologically ordered states
        for (; !linear.empty(); ) {
            nfa_state_t *q = linear.back();
            linear.pop_back();
            if (q->active) {
                q->active = 0;
                q->arcidx = 0;
                scan(ctx, q, true);
            }
            q->status = GOR_NOPASS;
        }
    }
}

bool scan(psimctx_t &ctx, nfa_state_t *q, bool all)
{
    bool any = false;

    typedef psimctx_t::conf_t conf_t;
    const conf_t x = ctx.state[q->clos];

    switch (q->type) {
        case nfa_state_t::NIL:
            if (q->arcidx == 0) {
                copy_offs(ctx, q, q->nil.out, NOINFO);
                any |= relax_gor1(ctx, conf_t(x, q->nil.out));
                ++q->arcidx;
            }
            break;
        case nfa_state_t::ALT:
            if (q->arcidx == 0) {
                copy_offs(ctx, q, q->alt.out1, NOINFO);
                any |= relax_gor1(ctx, conf_t(x, q->alt.out1));
                ++q->arcidx;
            }
            if (q->arcidx == 1 && (!any || all)) {
                copy_offs(ctx, q, q->alt.out2, NOINFO);
                any |= relax_gor1(ctx, conf_t(x, q->alt.out2));
                ++q->arcidx;
            }
            break;
        case nfa_state_t::TAG:
            if (q->arcidx == 0) {
                copy_offs(ctx, q, q->tag.out, q->tag.info);
                any |= relax_gor1(ctx, conf_t(x, q->tag.out, 0));
                ++q->arcidx;
            }
            break;
        case nfa_state_t::RAN:
        case nfa_state_t::FIN:
            break;
    }

    return any;
}

bool relax_gor1(psimctx_t &ctx, const psimctx_t::conf_t &x)
{
    psimctx_t::confset_t &state = ctx.state;
    nfa_state_t *q = x.state;
    const uint32_t idx = q->clos;

    if (q->status == GOR_TOPSORT) {
        return false;
    }

    if (idx == NOCLOS) {
        q->clos = static_cast<uint32_t>(state.size());
        state.push_back(x);
        accept_offsets(ctx, q);
    }
    else if (q->indeg < 2 || precedence(ctx, x, state[idx]) < 0) {
        state[idx] = x;
        accept_offsets(ctx, q);
    }
    else {
        return false;
    }

    if (q->status == GOR_NOPASS) {
        ctx.gor1_topsort.push_back(q);
        q->arcidx = 0;
        return true;
    }
    else {
        q->active = 1;
        return false;
    }
}

void closure_posix_gtop(psimctx_t &ctx)
{
    const psimctx_t::confset_t &reach = ctx.reach;
    psimctx_t::confset_t &state = ctx.state;
    gtop_heap_t &heap = ctx.gtop_heap;
    const size_t ntags = ctx.nfa.tags.size();

    state.clear();
    memcpy(offsets6, offsets4, ctx.nfa.size * ntags * sizeof(regoff_t) * 2);
    for (psimctx_t::cconfiter_t c = reach.begin(); c != reach.end(); ++c) {
        regoff_t       *ox = offsets5 + ntags * index(c->state, ctx.nfa) * 2;
        const regoff_t *oy = offsets6 + ntags * c->origin * 2;
        memcpy(ox, oy, ntags * sizeof(regoff_t) * 2);

        if (D) fprintf(stderr, "restoring offsets %u to %u\n"
            , c->origin, index(c->state, ctx.nfa));

        relax_gtop(ctx, *c);
        prtoff4(ctx, index(c->state, ctx.nfa));
    }

    for (; !heap.empty(); ) {
        nfa_state_t *q = heap.top();
        heap.pop();
        q->active = 0;

        if (D) fprintf(stderr, "> %u ", index(q, ctx.nfa));
        prtoff4(ctx, index(q, ctx.nfa));

        typedef psimctx_t::conf_t conf_t;
        const conf_t x = ctx.state[q->clos];

        switch (q->type) {
            case nfa_state_t::NIL:
                copy_offs(ctx, q, q->nil.out, NOINFO);
                relax_gtop(ctx, conf_t(x, q->nil.out));
                break;
            case nfa_state_t::ALT:
                copy_offs(ctx, q, q->alt.out1, NOINFO);
                relax_gtop(ctx, conf_t(x, q->alt.out1));
                copy_offs(ctx, q, q->alt.out2, NOINFO);
                relax_gtop(ctx, conf_t(x, q->alt.out2));
                break;
            case nfa_state_t::TAG:
                copy_offs(ctx, q, q->tag.out, q->tag.info);
                relax_gtop(ctx, conf_t(x, q->tag.out, 0));
                break;
            case nfa_state_t::RAN:
            case nfa_state_t::FIN:
                break;
        }
    }
}

void relax_gtop(psimctx_t &ctx, const psimctx_t::conf_t &c)
{
    psimctx_t::confset_t &state = ctx.state;
    nfa_state_t *q = c.state;
    const uint32_t idx = q->clos;

    if (idx == NOCLOS) {
        q->clos = static_cast<uint32_t>(state.size());
        state.push_back(c);
        accept_offsets(ctx, q);
    }
    else if (q->indeg < 2 || precedence(ctx, c, state[idx]) < 0) {
        state[idx] = c;
        accept_offsets(ctx, q);
    }
    else {
        return;
    }

    if (!q->active) {
        q->active = 1;
        ctx.gtop_heap.push(q);
    }
}

void make_one_step(psimctx_t &ctx, uint32_t sym)
{
    confset_t &state = ctx.state, &reach = ctx.reach;
    reach.clear();

    if (D) fprintf(stderr, "\n--- step %u (sym %c)\n", ctx.step, sym);

    for (cconfiter_t i = state.begin(), e = state.end(); i != e; ++i) {
        nfa_state_t *s = i->state;

        s->clos = NOCLOS;
        s->arcidx = 0;
        DASSERT(s->status == GOR_NOPASS && s->active == 0);

        if (s->type == nfa_state_t::RAN) {
            for (const Range *r = s->ran.ran; r; r = r->next()) {
                if (r->lower() <= sym && sym < r->upper()) {
                    const conf_t c(s->ran.out, index(s, ctx.nfa), HROOT);
                    reach.push_back(c);
                    break;
                }
            }
        }
        else if (s->type == nfa_state_t::FIN) {
            update_final_offsets(ctx, *i);
        }
    }
}

void make_final_step(psimctx_t &ctx)
{
    for (cconfiter_t i = ctx.state.begin(), e = ctx.state.end(); i != e; ++i) {
        nfa_state_t *s = i->state;

        s->clos = NOCLOS;
        s->arcidx = 0;
        DASSERT(s->status == GOR_NOPASS && s->active == 0);

        if (s->type == nfa_state_t::FIN) {
            update_final_offsets(ctx, *i);
        }
    }
}

void update_final_offsets(psimctx_t &ctx, const conf_t &c)
{
    nfa_state_t *s = c.state;
    DASSERT(s->type == nfa_state_t::FIN);

    const std::vector<Tag> &tags = ctx.nfa.tags;
    const size_t ntags = tags.size();

    ctx.marker = ctx.cursor;
    ctx.rule = 0;

    regoff_t       *of = ctx.offsets3;
    const regoff_t *ox = offsets4 + ntags * index(s, ctx.nfa) * 2;

    if (D) fprintf(stderr, "finally: ");
    prtoff4(ctx, index(s, ctx.nfa));

    for (size_t t = 0; t < ntags; t += 2) {
        of[t]     = ox[2 * t       + 1];
        of[t + 1] = ox[2 * (t + 1) + 1];
    }
}

static void copy_offs(psimctx_t &ctx, const nfa_state_t *y, const nfa_state_t *x
    , tag_info_t info)
{
    const std::vector<Tag> &tags = ctx.nfa.tags;
    const size_t ntags = tags.size();
    const uint32_t
        xidx = index(x, ctx.nfa),
        yidx = index(y, ctx.nfa);

    if (D) fprintf(stderr, "copying offsets %u to %u ", yidx, xidx);
    prtoff4(ctx, yidx);

    regoff_t       *ox = offsets5 + ntags * xidx * 2;
    const regoff_t *oy = offsets4 + ntags * yidx * 2;
    memcpy(ox, oy, ntags * sizeof(regoff_t) * 2);

    if (!(info == NOINFO)) {
        const uint32_t t = info.idx;

        // update active tag, and set final tag if it's not set already
        ox[2 * t] = info.neg ? -1 : static_cast<regoff_t>(ctx.step);
        if (ox[2 * t + 1] == -2) {
            ox[2 * t + 1] = ox[2 * t];
        }

        // update nested negative tags (if any)
        if (info.neg) {
            const Tag &tag = tags[t];
            for (size_t l = tag.lnest; l < tag.hnest; ++l) {
                ox[2 * l] = -1;
                if (ox[2 * l + 1] == -2) {
                    ox[2 * l + 1] = -1;
                }
            }
        }

        if (D) fprintf(stderr, "setting offset %u[%u] to %ld\n"
            , xidx, t, (long)ox[2 * t]);
    }
}

void accept_offsets(psimctx_t &ctx, const nfa_state_t *s)
{
    const uint32_t idx = index(s, ctx.nfa);
    const size_t ntags = ctx.nfa.tags.size();

    const regoff_t *ox = offsets5 + ntags * idx * 2;
    regoff_t       *oy = offsets4 + ntags * idx * 2;
    memcpy(oy, ox, ntags * sizeof(regoff_t) * 2);

    if (D) fprintf(stderr, "setting offsets %u to ", idx);
    prtoff4(ctx, idx);
}

static void prtoff(psimctx_t &ctx, uint32_t x, bool newer)
{
    if (!D) return;

    const size_t ntags = ctx.nfa.tags.size();
    const regoff_t *ox = (newer ? offsets5 : offsets4) + ntags * x * 2;
    for (size_t t = 0; t < ntags; t += 2) {
        fprintf(stderr, "(%ld,%ld)(%ld,%ld)"
            , (long)ox[2 * t],     (long)ox[2 * (t + 1)]
            , (long)ox[2 * t + 1], (long)ox[2 * (t + 1) + 1]);
    }
    fprintf(stderr, "\n");
}

static void prtoff4(psimctx_t &ctx, uint32_t x)
{
    if (D) fprintf(stderr, "off4: ");
    prtoff(ctx, x, false);
}

static void prtoff5(psimctx_t &ctx, uint32_t x)
{
    if (D) fprintf(stderr, "off5: ");
    prtoff(ctx, x, true);
}

} // namespace libre2c
} // namespace re2c

