#include "lib/lex.h"
#include "lib/regex.h"
#include "lib/regex_impl.h"


using namespace re2c;
using namespace re2c::libre2c;

int regexec(const regex_t *preg, const char *string, size_t nmatch,
    regmatch_t pmatch[], int eflags)
{
    if (preg->flags & REG_NFA) {
        if (preg->flags & REG_LEFTMOST) {
            return regexec_nfa_leftmost(preg, string, nmatch, pmatch, eflags);
        }
        else {
            return regexec_nfa_posix(preg, string, nmatch, pmatch, eflags);
        }
    }
    else {
        return regexec_dfa(preg, string, nmatch, pmatch, eflags);
    }
}

namespace re2c {
namespace libre2c {

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
    size_t todo = nmatch * 2, ntags = tags.size();
    bool *done = new bool[ntags];
    memset(done, 0, ntags * sizeof(bool));

    for (size_t i = ctx.hidx; todo > 0 && i != HROOT; ) {
        const history_t::node_t &n = ctx.hist.nodes[i];
        const size_t t = n.info.idx;
        if (!done[t]) {
            done[t] = true;
            const Tag &tag = tags[t];
            if (!fictive(tag) && tag.ncap < nmatch * 2) {
                --todo;
                const regoff_t off = n.info.neg ? -1 : static_cast<regoff_t>(n.step);
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
    return 0;
}

simctx_t::simctx_t(const regex_t *preg, const char *string)
    : nfa(preg->nfa)
    , reach()
    , state()
    , prec(preg->prec_buf1)
    , prec_next(preg->prec_buf2)
    , hist(nfa->size, nfa->tags.size())
    , hidx(HROOT)
    , step(0)
    , rule(Rule::NONE)
    , cursor(string)
    , marker(string)
    , cache()
{
    state.reserve(nfa->size);
    reach.reserve(nfa->size);
}

history_t::history_t(size_t nstates, size_t ntags)
    : nodes()
    , path1()
    , path2()
{
    nodes.reserve(ntags * nstates);
    path1.reserve(ntags);
    path2.reserve(ntags);
}

} // namespace libre2c
} // namespace re2c
