#include <vector>

#include "lib/lex.h"
#include "lib/regex.h"
#include "lib/regex_impl.h"
#include "src/options/opt.h"
#include "src/options/warn.h"
#include "src/debug/debug.h"
#include "src/dfa/determinization.h"
#include "src/nfa/nfa.h"


namespace re2c {

namespace {

struct history_t
{
    struct node_t {
        uint32_t pred;
        uint32_t step;
        uint32_t tag;
        uint32_t neg;
    };

    std::vector<node_t> nodes;

    inline history_t(size_t nstates, size_t ntags);
    inline uint32_t push(uint32_t i, uint32_t step, tag_info_t info);
    FORBID_COPY(history_t);
};

struct conf_t
{
    nfa_state_t *state;
    uint32_t thist;
};

typedef std::vector<conf_t> confset_t;
typedef confset_t::iterator confiter_t;
typedef confset_t::const_iterator cconfiter_t;
typedef confset_t::const_reverse_iterator rcconfiter_t;

struct simctx_t
{
    const nfa_t *nfa;
    confset_t reach;
    confset_t state;
    history_t hist;
    uint32_t hidx;
    uint32_t step;
    size_t rule;
    const char *cursor;
    const char *marker;

    inline simctx_t(const regex_t *preg, const char *string);
    FORBID_COPY(simctx_t);
};

} // anonymous namespace

static void reach_on_symbol(simctx_t &, uint32_t);
static void closure_leftmost(simctx_t &);

int regexec_nfa_leftmost(const regex_t *preg, const char *string, size_t nmatch,
    regmatch_t pmatch[], int)
{
    simctx_t ctx(preg, string);
    const nfa_t *nfa = ctx.nfa;
    int result = REG_NOMATCH;

    const conf_t c0 = {nfa->root, HROOT};
    ctx.reach.push_back(c0);
    closure_leftmost(ctx);

    for (;;) {
        const uint32_t sym = static_cast<uint8_t>(*ctx.cursor++);
        if (ctx.state.empty() || sym == 0) break;
        reach_on_symbol(ctx, sym);
        ++ctx.step;
        closure_leftmost(ctx);
    }

    const confset_t &state = ctx.state;
    cconfiter_t b = state.begin(), e = state.end(), i;
    for (i = b; i != e; ++i) {
        i->state->clos = NOCLOS;
    }

    ctx.cursor = ctx.marker;

    if (ctx.rule != Rule::NONE) {
        result = 0;

        regmatch_t *m = pmatch;
        m->rm_so = 0;
        m->rm_eo = ctx.cursor - string - 1;

        size_t todo = nmatch * 2, ntags = nfa->tags.size();
        bool *done = new bool[ntags];
        memset(done, 0, ntags * sizeof(bool));

        for (size_t i = ctx.hidx; todo > 0 && i != HROOT; ) {
            const history_t::node_t &n = ctx.hist.nodes[i];
            const size_t t = n.tag;
            if (!done[t]) {
                done[t] = true;
                const Tag &tag = nfa->tags[t];
                if (!fictive(tag) && tag.ncap < nmatch * 2) {
                    --todo;
                    const regoff_t off = n.neg ? -1 : static_cast<regoff_t>(n.step);
                    m = &pmatch[tag.ncap / 2 + 1];
                    if (tag.ncap % 2 == 0) {
                        m->rm_so = off;
                    }
                    else {
                        m->rm_eo = off;
                    }
                }
            }
            i = n.pred;
        }

        delete[] done;
    }

    return result;
}

void reach_on_symbol(simctx_t &ctx, uint32_t sym)
{
    const confset_t &state = ctx.state;
    confset_t &reach = ctx.reach;

    // in reverse, so that future closure DFS has states in stack order
    rcconfiter_t b = state.rbegin(), e = state.rend(), i;
    DASSERT(reach.empty());

    for (i = b; i != e; ++i) {
        nfa_state_t *s = i->state;

        // cleanup from previous closure
        s->clos = NOCLOS;

        if (s->type == nfa_state_t::RAN) {
            for (const Range *r = s->ran.ran; r; r = r->next()) {
                if (r->lower() <= sym && sym < r->upper()) {
                    conf_t c = {s->ran.out, i->thist};
                    reach.push_back(c);
                    break;
                }
            }
        }
    }
}

void closure_leftmost(simctx_t &ctx)
{
    confset_t &state = ctx.state, &wl = ctx.reach;
    state.clear();
    for (; !wl.empty(); ) {

        conf_t x = wl.back();
        wl.pop_back();
        nfa_state_t *n = x.state;

        if (n->clos != NOCLOS) continue;

        n->clos = 0;
        state.push_back(x);

        switch (n->type) {
            case nfa_state_t::NIL:
                x.state = n->nil.out;
                wl.push_back(x);
                break;
            case nfa_state_t::ALT:
                x.state = n->alt.out2;
                wl.push_back(x);
                x.state = n->alt.out1;
                wl.push_back(x);
                break;
            case nfa_state_t::TAG:
                x.state = n->tag.out;
                x.thist = ctx.hist.push(x.thist, ctx.step, n->tag.info);
                wl.push_back(x);
                break;
            case nfa_state_t::RAN:
                break;
            case nfa_state_t::FIN:
                ctx.marker = ctx.cursor + 1;
                ctx.hidx = x.thist;
                ctx.rule = 0;
                break;
        }
    }
}

simctx_t::simctx_t(const regex_t *preg, const char *string)
    : nfa(preg->nfa)
    , reach()
    , state()
    , hist(nfa->size, nfa->tags.size())
    , hidx(HROOT)
    , step(0)
    , rule(Rule::NONE)
    , cursor(string)
    , marker(string)
{
    state.reserve(nfa->size);
    reach.reserve(nfa->size);
}

history_t::history_t(size_t nstates, size_t ntags)
    : nodes()
{
    nodes.reserve(ntags * nstates);
}

uint32_t history_t::push(uint32_t idx, uint32_t step, tag_info_t info)
{
    const node_t x = {idx, step, info.idx, info.neg};
    nodes.push_back(x);
    return static_cast<uint32_t>(nodes.size() - 1);
}

} // namespace re2c

