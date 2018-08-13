#include <assert.h>
#include "src/util/c99_stdint.h"
#include <string.h>
#include <algorithm>
#include <limits>
#include <set>
#include <string>
#include <valarray>
#include <vector>

#include "src/conf/opt.h"
#include "src/conf/warn.h"
#include "src/dfa/dfa.h"
#include "src/dfa/determinization.h"
#include "src/dfa/dump.h"
#include "src/dfa/tcmd.h"
#include "src/nfa/nfa.h"
#include "src/re/rule.h"
#include "src/re/tag.h"
#include "src/util/range.h"


namespace re2c
{

static void reach_on_symbol(determ_context_t &);
static nfa_state_t *transition(nfa_state_t *, uint32_t);
static uint32_t init_tag_versions(determ_context_t &);
static void warn_nondeterministic_tags(const determ_context_t &);


const uint32_t dfa_t::NIL = ~0u;


dfa_t::dfa_t(const nfa_t &nfa, const opt_t *opts, const std::string &cond, Warn &warn)
    : states()
    , nchars(nfa.charset.size() - 1) // (n + 1) bounds for n ranges
    , charset(nfa.charset)
    , rules(nfa.rules)
    , tags(nfa.tags)
    , mtagvers(*new std::set<tagver_t>)
    , finvers(NULL)
    , tcpool(*new tcpool_t)
    , maxtagver(0)
    , tcmd0(NULL)
    , tcid0(TCID0)
{
    determ_context_t ctx(opts, warn, cond, nfa, *this);

    const uint32_t INITIAL_TAGS = init_tag_versions(ctx);

    // initial state
    const clos_t c0 = {nfa.root, 0, INITIAL_TAGS, HROOT, HROOT};
    ctx.dc_reached.push_back(c0);
    tagged_epsilon_closure(ctx);
    find_state(ctx);

    // iterate while new kernels are added: for each alphabet symbol,
    // build tagged epsilon-closure of all reachable NFA states,
    // then find identical or mappable DFA state or add a new one
    for (uint32_t i = 0; i < ctx.dc_kernels.size(); ++i) {

        ctx.dc_origin = i;
        ctx.dc_newvers.clear();

        for (uint32_t c = 0; c < nchars; ++c) {
            ctx.dc_symbol = c;

            reach_on_symbol(ctx);
            tagged_epsilon_closure(ctx);
            find_state(ctx);
        }
    }

    warn_nondeterministic_tags(ctx);
}


void reach_on_symbol(determ_context_t &ctx)
{
    const kernel_t *kernel = ctx.dc_kernels[ctx.dc_origin];
    closure_t &reached = ctx.dc_reached;
    const uint32_t symbol = ctx.dc_dfa.charset[ctx.dc_symbol];

    reached.clear();
    for (uint32_t i = 0; i < kernel->size; ++i) {
        nfa_state_t *s = transition(kernel->state[i], symbol);
        if (s) {
            clos_t c = {s, i, kernel->tvers[i], kernel->tlook[i], HROOT};
            reached.push_back(c);
        }
    }
}


nfa_state_t *transition(nfa_state_t *state, uint32_t symbol)
{
    if (state->type != nfa_state_t::RAN) {
        return NULL;
    }
    for (const Range *r = state->ran.ran; r; r = r->next()) {
        if ((r->lower() <= symbol) && (symbol < r->upper())) {
            return state->ran.out;
        }
    }
    return NULL;
}


uint32_t init_tag_versions(determ_context_t &ctx)
{
    dfa_t &dfa = ctx.dc_dfa;
    const size_t ntags = dfa.tags.size();

    // all-zero tag configuration must have static number zero
    assert(ZERO_TAGS == ctx.dc_tagvertbl.insert_const(TAGVER_ZERO));

    // initial tag versions: [1 .. N]
    const uint32_t INITIAL_TAGS = ctx.dc_tagvertbl.insert_succ(1);

    // other versions: [ .. -(N + 1)] and [N + 1 .. ]
    dfa.maxtagver = static_cast<tagver_t>(ntags);

    // final/fallback versions will be assigned on the go
    dfa.finvers = new tagver_t[ntags];
    for (size_t i = 0; i < ntags; ++i) {
        dfa.finvers[i] = fixed(dfa.tags[i]) ? TAGVER_ZERO : ++dfa.maxtagver;
    }

    // mark tags with history (initial and final)
    for (size_t i = 0; i < ntags; ++i) {
        if (history(dfa.tags[i])) {
            tagver_t v = static_cast<tagver_t>(i) + 1, f = dfa.finvers[i];
            if (f != TAGVER_ZERO) {
                dfa.mtagvers.insert(f);
            }
            dfa.mtagvers.insert(v);
        }
    }

    return INITIAL_TAGS;
}


// For each tag, find maximal number of parallel versions of this tag
// used in each kernel (degree of non-determinism) and warn about tags with
// maximum degree two or more.
// WARNING: this function assumes that kernel items are grouped by rule
void warn_nondeterministic_tags(const determ_context_t &ctx)
{
    if (ctx.dc_opts->posix_captures) return;

    Warn &warn = ctx.dc_warn;
    const kernels_t &kernels = ctx.dc_kernels;
    const std::vector<Tag> &tags = ctx.dc_dfa.tags;
    const std::valarray<Rule> &rules = ctx.dc_dfa.rules;

    const size_t
        ntag = tags.size(),
        nkrn = kernels.size(),
        nrule = rules.size();
    std::vector<size_t> maxv(ntag, 0);
    std::set<tagver_t> uniq;

    for (uint32_t i = 0; i < nkrn; ++i) {
        const kernel_t *k = kernels[i];
        nfa_state_t **s = k->state;
        const size_t n = k->size;
        const uint32_t *v = k->tvers;

        for (size_t u = 0; u < n;) {
            const size_t r = s[u]->rule;
            const Rule &rule = rules[r];

            const size_t l = u;
            for (; ++u < n && s[u]->rule == r;);
            for (size_t t = rule.ltag; t < rule.htag; ++t) {
                uniq.clear();
                for (size_t m = l; m < u; ++m) {
                    uniq.insert(ctx.dc_tagvertbl[v[m]][t]);
                }
                maxv[t] = std::max(maxv[t], uniq.size());
            }
        }
    }

    for (uint32_t r = 0; r < nrule; ++r) {
        const Rule &rule = rules[r];
        for (size_t t = rule.ltag; t < rule.htag; ++t) {
            const size_t m = maxv[t];
            if (m > 1) {
                const uint32_t line = rule.code->fline;
                warn.nondeterministic_tags(line, ctx.dc_condname, tags[t].name, m);
            }
        }
    }
}


determ_context_t::determ_context_t(const opt_t *opts, Warn &warn
    , const std::string &condname, const nfa_t &nfa, dfa_t &dfa)
    : dc_opts(opts)
    , dc_warn(warn)
    , dc_condname(condname)
    , dc_nfa(nfa)
    , dc_dfa(dfa)
    , dc_allocator()
    , dc_origin(dfa_t::NIL)
    , dc_target(dfa_t::NIL)
    , dc_symbol(0)
    , dc_actions(NULL)
    , dc_reached()
    , dc_closure()
    , dc_prectbl(NULL)
    , dc_tagvertbl(nfa.tags.size())
    , dc_taghistory()
    , dc_kernels()
    , dc_buffers(dc_allocator)
    , dc_newvers(newver_cmp_t(dc_taghistory))
    , dc_stack_topsort()
    , dc_stack_linear()
    , dc_stack_dfs()
    , dc_dump(opts)
{}


dfa_t::~dfa_t()
{
    std::vector<dfa_state_t*>::iterator
        i = states.begin(),
        e = states.end();
    for (; i != e; ++i)
    {
        delete *i;
    }
}


bool newver_cmp_t::operator()(const newver_t &x, const newver_t &y) const
{
    if (x.tag < y.tag) return true;
    if (x.tag > y.tag) return false;

    if (x.base < y.base) return true;
    if (x.base > y.base) return false;

    return history.compare_reversed(x.history, y.history, x.tag) < 0;
}

} // namespace re2c

