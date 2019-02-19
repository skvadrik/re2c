#include "lib/lex.h"
#include "lib/regex.h"
#include "lib/regex_impl.h"


using namespace re2c;
using namespace re2c::libre2c;

int regexec(const regex_t *preg, const char *string, size_t nmatch,
    regmatch_t pmatch[], int eflags)
{
    if (!(preg->flags & REG_NFA)) {
        return regexec_dfa(preg, string, nmatch, pmatch, eflags);
    }
    else if ((preg->flags & REG_LEFTMOST) && (preg->flags & REG_TRIE)) {
        return regexec_nfa_leftmost_trie(preg, string, nmatch, pmatch, eflags);
    }
    else if (preg->flags & REG_LEFTMOST) {
        return regexec_nfa_leftmost(preg, string, nmatch, pmatch, eflags);
    }
    else if (preg->flags & REG_TRIE) {
        return regexec_nfa_posix_trie(preg, string, nmatch, pmatch, eflags);
    }
    else {
        return regexec_nfa_posix(preg, string, nmatch, pmatch, eflags);
    }
}

namespace re2c {
namespace libre2c {

const int32_t history_t::ROOT = -1;

int finalize(const simctx_t &ctx, const char *string, size_t nmatch,
    regmatch_t pmatch[])
{
    if (ctx.rule == Rule::NONE) {
        return REG_NOMATCH;
    }

    regmatch_t *m = pmatch;
    m->rm_so = 0;
    m->rm_eo = ctx.marker - string - 1;

    const std::vector<Tag> &tags = ctx.nfa->tags;
    size_t todo = nmatch * 2;
    bool *done = ctx.done;
    memset(done, 0, ctx.nsub * sizeof(bool));

    for (int32_t i = ctx.hidx; todo > 0 && i != history_t::ROOT; ) {
        const history_t::node_t &n = ctx.hist.at(i);
        const Tag &tag = tags[n.info.idx];
        const size_t t = tag.ncap;
        if (!fictive(tag) && t < nmatch * 2 && !done[t]) {
            done[t] = true;
            --todo;
            const regoff_t off = n.info.neg ? -1 : static_cast<regoff_t>(n.step);
            m = &pmatch[t / 2 + 1];
            if (t % 2 == 0) {
                m->rm_so = off;
            }
            else {
                m->rm_eo = off;
            }
        }
        i = n.pred;
    }

    return 0;
}

simctx_t::simctx_t(const nfa_t *nfa, size_t re_nsub, int flags)
    : nfa(nfa)
    , nsub(2 * (re_nsub - 1))
    , flags(flags)
    , reach()
    , state()
    , hist(nfa->size)
    , hidx(history_t::ROOT)
    , step(0)
    , rule(Rule::NONE)
    , cursor(NULL)
    , marker(NULL)
    , offsets1(NULL)
    , offsets2(NULL)
    , offsets3(NULL)
    , done(NULL)
    , prectbl1(NULL)
    , prectbl2(NULL)
    , cache()
    , gor1_topsort()
    , gor1_linear()
    , gtop_heap_storage()
    , gtop_cmp()
    , gtop_heap(gtop_cmp, gtop_heap_storage)
{
    const size_t
        nstates = nfa->size,
        ncores = nfa->ncores;

    state.reserve(nstates);
    reach.reserve(nstates);

    done = new bool[nsub];

    if (!(flags & REG_TRIE)) {
        offsets1 = new regoff_t[nsub * ncores];
        offsets2 = new regoff_t[nsub * ncores];
        offsets3 = new regoff_t[nsub];
    }
    if (!(flags & REG_LEFTMOST) && !(flags & REG_TRIE)) {
        prectbl1 = new int32_t[ncores * ncores];
        prectbl2 = new int32_t[ncores * ncores];
    }

    if (flags & REG_GTOP) {
        gtop_heap_storage.reserve(nstates);
    }
    else {
        gor1_topsort.reserve(nstates);
        gor1_linear.reserve(nstates);
    }
}

simctx_t::~simctx_t()
{
    delete[] done;
    if (!(flags & REG_TRIE)) {
        delete[] offsets1;
        delete[] offsets2;
        delete[] offsets3;
    }
    if (!(flags & REG_LEFTMOST) && !(flags & REG_TRIE)) {
        delete[] prectbl1;
        delete[] prectbl2;
    }
}

void init(simctx_t &ctx, const char *string)
{
    ctx.reach.clear();
    ctx.state.clear();
    ctx.hist.nodes.clear();
    ctx.hidx = history_t::ROOT;
    ctx.step = 0;
    ctx.rule = Rule::NONE;
    ctx.cursor = ctx.marker = string;
    ctx.cache.clear();
    DASSERT(ctx.gor1_topsort.empty());
    DASSERT(ctx.gor1_linear.empty());
    DASSERT(ctx.gtop_heap.empty());
}

history_t::history_t(size_t nstates)
    : nodes()
{
    nodes.reserve(nstates);
}

} // namespace libre2c
} // namespace re2c
