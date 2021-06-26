#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <vector>

#include "src/parse/ast.h"
#include "src/nfa/nfa.h"
#include "src/options/opt.h"
#include "src/regexp/re.h"
#include "src/regexp/tag.h"


namespace re2c {

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
                    if (ctx.opts->posix_semantics) {
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

// On-stack information for iterative DFS that computes NFA statistics.
struct DfsNfaStats {
    nfa_state_t *state; // current NFA state
    uint32_t     next;  // index of the next state to be visited
};

static uint32_t stats(nfa_state_t *root)
{
    std::vector<DfsNfaStats> stack;
    uint32_t topord = 0;
    uint32_t ncores = 0;

    DfsNfaStats i0 = {root, 0};
    stack.push_back(i0);

    while (!stack.empty()) {
        // Don't store references to stack as it may grow and get reallocated.
        nfa_state_t *state = stack.back().state;
        const uint32_t next = stack.back().next++;
        const size_t stack_size = stack.size();

        if (next == 0) {
            // Recursive enter: increase state in-degree.
            ++state->indeg;

            if (state->indeg > 1) {
                // In-degree was non-null => we have been here before, stop DFS.
                stack.pop_back();
                continue;
            }
        }

        switch (state->type) {
            case nfa_state_t::ALT:
                if (next == 0) {
                    DfsNfaStats i = {state->alt.out1, 0};
                    stack.push_back(i);
                } else if (next == 1) {
                    DfsNfaStats i = {state->alt.out2, 0};
                    stack.push_back(i);
                }
                break;
            case nfa_state_t::TAG:
                if (next == 0) {
                    DfsNfaStats i = {state->tag.out, 0};
                    stack.push_back(i);
                }
                break;
            case nfa_state_t::RAN:
                if (next == 0) {
                    ++ncores;
                    DfsNfaStats i = {state->tag.out, 0};
                    stack.push_back(i);
                }
                break;
            case nfa_state_t::FIN:
                ++ncores;
                break;
        }

        if (stack.size() == stack_size) {
            // No new states have been pushed on stack: all children have been
            // visited and this is the recursive return. Set topological index.
            state->topord = topord++;
            stack.pop_back();
        }
    }

    return ncores;
}

nfa_t::nfa_t(const RESpec &spec)
    : max_size(estimate_size(spec.res))
    , size(0)
    , states(new nfa_state_t[max_size])
    , charset(spec.charset)
    , rules(spec.rules)
    , tags(spec.tags)
    , root(NULL)
    , ncores(0)
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

    // In-degree and topological index are used by POSIX disambiguation;
    // the number of core states is used for both POSIX and leftmost.
    ncores = stats(root);
}

nfa_t::~nfa_t()
{
    delete[] states;
}

} // namespace re2c
