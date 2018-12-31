#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <vector>

#include "src/ast/ast.h"
#include "src/nfa/nfa.h"
#include "src/re/re.h"
#include "src/re/tag.h"

namespace re2c {

static void calc_indegrees(nfa_state_t *);
static void calc_topord(nfa_state_t *, uint32_t &);


/*
 * note [counted repetition and iteration expansion]
 *
 * It is more convenient to express zero-or-more iterations in terms of
 * one-or-more iterations than vice versa, because the expansion 'r+ ::= r r*'
 * duplicates 'r', while 'r* = r+ | <empty>' allows to avoid duplication.
 *
 * Sometimes duplcation is unavoidable, like 'r{n}' for 'n' > 1 and 'r{n,m}'
 * for 'n' < 'm'. In such cases we duplicate 'r' together with all tags;
 * this may cause multiple (non-bottom) occurences of the same tag in the NFA.
 * Determinization must be careful to track multiple occurences of the same
 * tag while building epsilon-closure (this matters for POSIX disambiguation
 * strategy).
 *
 * We allow tags to apper only once in the original regular expression.
 * This is not strictly necessary (putting the same tag in non-overlapping
 * alternative branches may be handy), but it would allow to create very
 * confusing regexps and the disambiguation strategy would behave strangely.
 */

struct rtn_ctx_t
{
    const opt_t *opts;
    nfa_t &nfa;
    size_t nrule;
};

static nfa_state_t *re_to_nfa(rtn_ctx_t &ctx, const RE *re, nfa_state_t *t)
{
    nfa_t &nfa = ctx.nfa;
    const size_t nrule = ctx.nrule;
    nfa_state_t *s = NULL;

    switch (re->type) {
        case RE::NIL:
            s = t;
            break;
        case RE::SYM:
            s = &nfa.states[nfa.size++];
            s->make_ran(nrule, t, re->sym);
            break;
        case RE::ALT: {
            nfa_state_t
                *s1 = re_to_nfa(ctx, re->alt.re1, t),
                *s2 = re_to_nfa(ctx, re->alt.re2, t);
            s = &nfa.states[nfa.size++];
            s->make_alt(nrule, s1, s2);
            break;
        }
        case RE::CAT:
            s = re_to_nfa(ctx, re->cat.re2, t);
            s = re_to_nfa(ctx, re->cat.re1, s);
            break;
        case RE::ITER: {
            const uint32_t
                min = re->iter.min,
                max = re->iter.max;
            const RE *iter = re->iter.re;
            // see note [counted repetition and iteration expansion]
            if (max == AST::MANY) {
                nfa_state_t *q = &nfa.states[nfa.size++];
                s = re_to_nfa(ctx, iter, q);
                q->make_alt(nrule, s, t);
            } else {
                s = re_to_nfa(ctx, iter, t);
                for (uint32_t i = min; i < max; ++i) {
                    nfa_state_t *q = &nfa.states[nfa.size++];
                    if (ctx.opts->posix_captures) {
                        // POSIX: shorter alternative first to speed up GOR1
                        // by first exploring paths without optional empty repetitions
                        q->make_alt(nrule, t, s);
                    }
                    else {
                        // leftmost: must be greedy, longer alternative first
                        q->make_alt(nrule, s, t);
                    }
                    s = re_to_nfa(ctx, iter, q);
                }
            }
            for (uint32_t i = 1; i < min; ++i) {
                s = re_to_nfa(ctx, iter, s);
            }
            break;
        }
        case RE::TAG: {
            const Tag &tag = nfa.tags[re->tag.idx];
            if (fixed(tag) && !capture(tag)) {
                s = t;
            } else {
                s = &nfa.states[nfa.size++];
                s->make_tag(nrule, t, re->tag);
            }
            break;
        }
    }
    return s;
}

nfa_t::nfa_t(const RESpec &spec)
    : max_size(estimate_size(spec.res))
    , size(0)
    , states(new nfa_state_t[max_size])
    , charset(spec.charset)
    , rules(spec.rules)
    , tags(spec.tags)
    , root(NULL)
{
    const size_t nre = spec.res.size();

    if (nre == 0) return;

    for (size_t i = 0; i < nre; ++i) {
        rtn_ctx_t ctx = {spec.opts, *this, i};

        nfa_state_t *s = &states[size++];
        s->make_fin(i);
        s = re_to_nfa(ctx, spec.res[i], s);

        if (root) {
            nfa_state_t *t = &states[size++];
            t->make_alt(i, root, s);
            root = t;
        } else {
            root = s;
        }
    }

    if (spec.opts->posix_captures) {
        // needed for closure algorithms GOR1 and GTOP
        uint32_t topord = 0;
        calc_topord(root, topord);
        calc_indegrees(root);
    }
}

nfa_t::~nfa_t()
{
    delete[] states;
}

void calc_indegrees(nfa_state_t *n)
{
    ++n->indeg;
    if (n->indeg > 1) return;

    switch (n->type) {
        case nfa_state_t::NIL:
            calc_indegrees(n->nil.out);
            break;
        case nfa_state_t::ALT:
            calc_indegrees(n->alt.out1);
            calc_indegrees(n->alt.out2);
            break;
        case nfa_state_t::TAG:
            calc_indegrees(n->tag.out);
            break;
        case nfa_state_t::RAN:
            calc_indegrees(n->ran.out);
        case nfa_state_t::FIN:
            break;
    }
}

void calc_topord(nfa_state_t *n, uint32_t &topord)
{
    if (n->topord != 0) return;
    n->topord = ~0u; // temporary "visited" marker

    switch (n->type) {
        case nfa_state_t::NIL:
            calc_topord(n->nil.out, topord);
            break;
        case nfa_state_t::ALT:
            calc_topord(n->alt.out1, topord);
            calc_topord(n->alt.out2, topord);
            break;
        case nfa_state_t::TAG:
            calc_topord(n->tag.out, topord);
            break;
        case nfa_state_t::RAN:
            calc_topord(n->ran.out, topord);
        case nfa_state_t::FIN:
            break;
    }

    n->topord = topord++;
}

} // namespace re2c
