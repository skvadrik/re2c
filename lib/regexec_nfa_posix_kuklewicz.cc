#include <stdio.h>
#include <algorithm>
#include <utility>
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


/* note [POSIX orbit tags]
 *
 * POSIX disambiguation rules demand that earlier subexpressions match
 * the longest possible prefix of the input string (without violating the
 * whole match). To accommodate these rules, we resolve conflicts on orbit
 * tags by comparison of tag subhistories on conflicting NFA paths.
 *
 * If one subhistory is a proper prefix of another subhistory, it is less;
 * otherwise for the first pair of different offsets, if one offset is greater
 * than the other, then the corresponding subhistory is less.
 *
 * It is possible to pre-compare two NFA paths corresponding to the same
 * input string prefix and ending in the same NFA state; if paths are not
 * equal, the result of this comparison will hold for any common suffix.
 *
 * It is also possible to pre-compare NFA paths that correspond to the same
 * input prefix, but end in different NFA states. Such comparison is incorrect
 * unless subhistories start at the same offset; but if it is incorrect, we
 * will never use its result (tags with higher priority will also disagree).
 *
 * Therefore instead of keeping the whole history of offsets we calculate
 * the relative order of any pair of subhistories on each step.
 *
 * This part of the algorithm was invented by Christopher Kuklewicz.
 */

namespace re2c {

// specialization that doesn't sort initial closure like Okui-Suzuki
template<> void init_gor1<libre2c::ksimctx_t>(libre2c::ksimctx_t &ctx);

namespace libre2c {

static const int32_t DELIM = 0x7fffFFFF;

static void make_one_step(ksimctx_t &, uint32_t);
static void make_final_step(ksimctx_t &);
static void compute_orders(ksimctx_t &ctx);

// we *do* want these to be inlined
static inline void closure_posix(ksimctx_t &ctx);
static inline size_t boundary_tag(size_t tag);
static inline int32_t subhistory_list(const khistory_t &history, std::vector<int32_t> &path, hidx_t idx, size_t tag);
static inline void last_subhistory(const khistory_t &history, std::vector<tagver_t> &path, hidx_t idx, size_t tag);
static inline int32_t compare_last_subhistories(khistory_t &history, hidx_t x, hidx_t y, int32_t ox, int32_t oy, size_t t);

int regexec_nfa_posix_kuklewicz(const regex_t *preg, const char *string
    , size_t nmatch, regmatch_t pmatch[], int /* eflags */)
{
    ksimctx_t &ctx = *static_cast<ksimctx_t*>(preg->simctx);
    init(ctx, string);
    if (ctx.nfa.tags.size() > 0) {
        ctx.oldprectbl[0] = 0;
    }

    // root state can be non-core, so we pass zero as origin to avoid checks
    const conf_t c0(ctx.nfa.root, 0, HROOT);
    ctx.reach.push_back(c0);
    for (;;) {
        closure_posix(ctx);
        const uint32_t sym = static_cast<uint8_t>(*ctx.cursor++);
        if (ctx.state.empty() || sym == 0) break;
        make_one_step(ctx, sym);
    }
    make_final_step(ctx);

    if (ctx.rule == Rule::NONE) {
        return REG_NOMATCH;
    }

    const getoff_nfa_t fn = { ctx.offsets3 };
    tags_to_submatch(ctx.nfa.tags, nmatch, pmatch, ctx.marker - string - 1, fn);

    return 0;
}

void closure_posix(ksimctx_t &ctx)
{
    if (ctx.flags & REG_GTOP) {
        closure_posix_gtop(ctx);
    }
    else {
        closure_posix_gor1(ctx);
    }
}

void make_one_step(ksimctx_t &ctx, uint32_t sym)
{
    confset_t &state = ctx.state, &reach = ctx.reach;
    uint32_t j = 0;
    reach.clear();

    for (cconfiter_t i = state.begin(), e = state.end(); i != e; ++i) {
        nfa_state_t *s = i->state;

        s->clos = NOCLOS;
        s->arcidx = 0;
        DASSERT(s->status == GOR_NOPASS && s->active == 0);

        if (s->type == nfa_state_t::RAN) {
            for (const Range *r = s->ran.ran; r; r = r->next()) {
                if (r->lower() <= sym && sym < r->upper()) {
                    const conf_t c(s->ran.out, j, HROOT);
                    reach.push_back(c);
                    state[j] = *i;
                    update_offsets(ctx, *i, j);
                    ++j;
                    break;
                }
            }
        }
        else if (s->type == nfa_state_t::FIN) {
            update_offsets(ctx, *i, NONCORE);
        }
    }

    state.resize(j);
    std::swap(ctx.offsets1, ctx.offsets2);

    compute_orders(ctx);
    std::swap(ctx.newprectbl, ctx.oldprectbl);
    ctx.oldprecdim = j;

    ctx.history.init();
    ++ctx.step;
}

void make_final_step(ksimctx_t &ctx)
{
    for (cconfiter_t i = ctx.state.begin(), e = ctx.state.end(); i != e; ++i) {
        nfa_state_t *s = i->state;

        s->clos = NOCLOS;
        s->arcidx = 0;
        DASSERT(s->status == GOR_NOPASS && s->active == 0);

        if (s->type == nfa_state_t::FIN) {
            update_offsets(ctx, *i, NONCORE);
        }
    }
}

struct cmp_posix_t
{
    ksimctx_t &ctx;
    size_t tag;
    inline bool operator()(cconfiter_t x, cconfiter_t y) const
    {
        const int32_t
            ox = ctx.oldprectbl[tag * ctx.oldprecdim + x->origin],
            oy = ctx.oldprectbl[tag * ctx.oldprecdim + y->origin];
        // comparison result is inverted, because orders are used as offsets
        return compare_last_subhistories(ctx.history
            , x->thist, y->thist, ox, oy, tag) > 0;
    }
};

void compute_orders(ksimctx_t &ctx)
{
    const confset_t &state = ctx.state;
    const size_t ntags = ctx.nfa.tags.size();
    const size_t newdim = state.size();
    cconfiter_t b = state.begin(), e = state.end(), c;
    std::vector<cconfiter_t> &iters = ctx.stateiters;

    if (newdim == 0) return;

    iters.clear();
    iters.reserve(state.size());
    for (c = b; c != e; ++c) {
        iters.push_back(c);
    }

    for (size_t t = 1; t < ntags; t += 2) {
        cmp_posix_t cmp = {ctx, t};
        std::sort(iters.begin(), iters.end(), cmp);

        int32_t m = 0, *tbl = ctx.newprectbl + t * newdim;
        for (size_t i = 0; i < newdim; ++m) {
            *(tbl + (iters[i] - b)) = m;
            for (; ++i < newdim && cmp(iters[i - 1], iters[i]) == 0; ) {
                *(tbl + (iters[i] - b)) = m;
            }
        }
    }
}

int32_t compare_last_subhistories(khistory_t &history
    , hidx_t x, hidx_t y, int32_t ox, int32_t oy, size_t t)
{
    if (ox > oy) return -1;
    if (ox < oy) return 1;
    if (x == y) return 0;

    std::vector<int32_t> &p1 = history.path1, &p2 = history.path2;

    last_subhistory(history, p1, x, t);
    last_subhistory(history, p2, y, t);

    std::vector<int32_t>::const_reverse_iterator
        i1 = p1.rbegin(), e1 = p1.rend(),
        i2 = p2.rbegin(), e2 = p2.rend();
    for (;;) {
        if (i1 == e1 && i2 == e2) break;
        if (i1 == e1) return -1;
        if (i2 == e2) return 1;
        if (*i1 > *i2) return -1;
        if (*i1 < *i2) return 1;
        ++i1; ++i2;
    }

    return 0;
}

void last_subhistory(const khistory_t &history
    , std::vector<tagver_t> &path, hidx_t idx, size_t tag)
{
    path.clear();
    hidx_t i = idx;
    const size_t bound = boundary_tag(tag);
    for (; i != HROOT && history.node(i).info.idx >= bound; i = history.node(i).pred) {
        if (history.node(i).info.idx == tag) {
            path.push_back(history.node(i).info.neg ? -1 : 1);
        }
    }
}

template<typename ctx_t>
int32_t khistory_t::precedence(ctx_t &ctx
    , const typename ctx_t::conf_t &x, const typename ctx_t::conf_t &y
    , int32_t &/*prec1*/, int32_t &/*prec2*/)
{
    // History consists of multiple subhistories (each containing either a
    // single negative tag, or one or more positive tags (exactly one for
    // non-orbit subhistories). Because of the shortest-path algorithm earlier
    // subhistories do not necessarily coincide, so comparing only the last
    // pair of subhistories is not enough. See note [POSIX orbit tags].

    const size_t ntags = ctx.nfa.tags.size();
    for (size_t t = 1; t < ntags; t += 2) {
        const int32_t
            ox = ctx.oldprectbl[t * ctx.oldprecdim + x.origin],
            oy = ctx.oldprectbl[t * ctx.oldprecdim + y.origin];

        if (ox > oy) return -1;
        if (ox < oy) return 1;
        if (x.thist == y.thist) continue;

        std::vector<int32_t> &p1 = ctx.history.path1, &p2 = ctx.history.path2;
        int32_t n1, n2;
        (void)(n1 = subhistory_list(ctx.history, p1, x.thist, t));
        (void)(n2 = subhistory_list(ctx.history, p2, y.thist, t));
        DASSERT(n1 == n2);

        std::vector<int32_t>::const_reverse_iterator
            i1 = p1.rbegin(), e1 = p1.rend(),
            i2 = p2.rbegin(), e2 = p2.rend();
        for (;;) {
            if (i1 == e1 && i2 == e2) break;
            DASSERT(i1 != e1 && i2 != e2);
            const int32_t v1 = *i1++, v2 = *i2++;
            if (v1 == DELIM && v2 == DELIM) continue;
            if (v1 == DELIM) return -1;
            if (v2 == DELIM) return 1;
            if (v1 > v2) return -1;
            if (v1 < v2) return 1;
        }
    }
    return 0;
}

// returns all subhistories of the given tag as one sequence
// (individual subhistories are separated by delimiter)
int32_t subhistory_list(const khistory_t &history,
    std::vector<int32_t> &path, hidx_t idx, size_t tag)
{
    path.clear();
    int32_t nsub = 0;
    hidx_t i = idx;

    const size_t bound = boundary_tag(tag);
    path.push_back(DELIM);
    for (;;) {
        for (; i != HROOT && history.node(i).info.idx >= bound; i = history.node(i).pred) {
            if (history.node(i).info.idx == tag) {
                path.push_back(history.node(i).info.neg ? -1 : 1);
            }
        }
        if (i == HROOT) break;
        ++nsub;
        path.push_back(DELIM);
        for (; i != HROOT && history.node(i).info.idx != tag; i = history.node(i).pred);
    }

    return nsub;
}

size_t boundary_tag(size_t tag)
{
    // for start tags, return itself; for end tags, return start tag
    // (start tags have even numbers, end tags have odd numbers)
    return tag & ~1u;
}

} // namespace libre2c

template<> void init_gor1<libre2c::ksimctx_t>(libre2c::ksimctx_t &ctx)
{
    ctx.state.clear();
    libre2c::ksimctx_t::cconfiter_t c = ctx.reach.begin(), e = ctx.reach.end();
    for (; c != e; ++c) {
        relax_gor1(ctx, *c);
    }
}

} // namespace re2c

