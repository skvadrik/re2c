#include "src/util/c99_stdint.h"
#include <algorithm>
#include <memory>
#include <set>
#include <string>
#include <valarray>
#include <vector>

#include "src/options/opt.h"
#include "src/debug/debug.h"
#include "src/dfa/dfa.h"
#include "src/dfa/determinization.h"
#include "src/dfa/tcmd.h"
#include "src/msg/warn.h"
#include "src/nfa/nfa.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"
#include "src/util/range.h"


namespace re2c {

template<typename ctx_t> static void determinization(ctx_t &ctx);
template<typename ctx_t> static void clear_caches(ctx_t &ctx);
template<typename ctx_t> static void reach_on_symbol(ctx_t &ctx, uint32_t sym);
template<typename ctx_t> static uint32_t init_tag_versions(ctx_t &ctx);
template<typename ctx_t> static void warn_nondeterministic_tags(const ctx_t &ctx);
static nfa_state_t *transition(nfa_state_t *, uint32_t);

const uint32_t dfa_t::NIL = ~0u;

dfa_t::dfa_t(const nfa_t &nfa, const opt_t *opts, const std::string &cond
    , Msg &msg)
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
    if (opts->posix_semantics) {
        pdetctx_t ctx(opts, msg, cond, nfa, *this);
        determinization(ctx);
    }
    else {
        ldetctx_t ctx(opts, msg, cond, nfa, *this);
        determinization(ctx);
    }
}

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

template<typename ctx_t>
void determinization(ctx_t &ctx)
{
    const uint32_t INITIAL_TAGS = init_tag_versions(ctx);

    // initial state
    const clos_t c0(ctx.nfa.root, 0, INITIAL_TAGS, HROOT, HROOT);
    ctx.reach.push_back(c0);
    tagged_epsilon_closure(ctx);
    find_state(ctx);

    // iterate while new kernels are added: for each alphabet symbol,
    // build tagged epsilon-closure of all reachable NFA states,
    // then find identical or mappable DFA state or add a new one
    for (uint32_t i = 0; i < ctx.dc_kernels.size(); ++i) {
        ctx.dc_origin = i;
        clear_caches(ctx);

        for (uint32_t c = 0; c < ctx.dfa.nchars; ++c) {
            reach_on_symbol(ctx, c);
            tagged_epsilon_closure(ctx);
            find_state(ctx);
        }
    }

    warn_nondeterministic_tags(ctx);
}

template<typename ctx_t>
void clear_caches(ctx_t &ctx)
{
    ctx.dc_newvers.clear();

    const size_t ntags = ctx.nfa.tags.size();
    for (size_t t = 0; t < ntags; ++t) {
        ctx.dc_hc_caches[t].clear();
    }
}

template<typename ctx_t>
void reach_on_symbol(ctx_t &ctx, uint32_t sym)
{
    ctx.dc_symbol = sym;
    const uint32_t symbol = ctx.dfa.charset[sym];

    const kernel_t *kernel = ctx.dc_kernels[ctx.dc_origin];
    ctx.oldprectbl = kernel->prectbl;
    ctx.oldprecdim = kernel->size;

    closure_t &reach = ctx.reach;
    reach.clear();

    // Add configurations in reverse order: leftmost greedy closure uses
    // the resulting array as stack, and POSIX closure doesn't care (GOR1
    // pre-sorts configurations, and GTOP uses priority queue).
    for (uint32_t i = static_cast<uint32_t>(kernel->size); i --> 0; ) {
        nfa_state_t *s = transition(kernel->state[i], symbol);
        if (s) {
            const uint32_t v = ctx.dc_opts->stadfa ? 0 : kernel->tvers[i];
            const clos_t c(s, i, v, kernel->thist[i], HROOT);
            reach.push_back(c);
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

template<typename ctx_t>
uint32_t init_tag_versions(ctx_t &ctx)
{
    dfa_t &dfa = ctx.dfa;
    const size_t ntags = dfa.tags.size();

    // all-zero tag configuration must have static number zero
    ctx.dc_tagvertbl.insert_const(TAGVER_ZERO);
    DASSERT(ZERO_TAGS == ctx.dc_tagvertbl.insert_const(TAGVER_ZERO));

    // initial tag versions: [1 .. N]
    const tcid_t INITIAL_TAGS = ctx.dc_tagvertbl.insert_succ(1);

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
template<typename ctx_t>
void warn_nondeterministic_tags(const ctx_t &ctx)
{
    if (ctx.dc_opts->posix_syntax
        || ctx.dc_opts->stadfa) return;

    Warn &warn = ctx.dc_msg.warn;
    const kernels_t &kernels = ctx.dc_kernels;
    const std::vector<Tag> &tags = ctx.dfa.tags;
    const std::valarray<Rule> &rules = ctx.dfa.rules;

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
                warn.nondeterministic_tags(rule.code->loc
                    , ctx.dc_condname, tags[t].name, m);
            }
        }
    }
}

template<typename history_t>
determ_context_t<history_t>::determ_context_t(const opt_t *opts, Msg &msg
    , const std::string &condname, const nfa_t &nfa, dfa_t &dfa)
    : dc_opts(opts)
    , dc_msg(msg)
    , dc_condname(condname)
    , nfa(nfa)
    , dfa(dfa)
    , dc_allocator()
    , dc_origin(dfa_t::NIL)
    , dc_target(dfa_t::NIL)
    , dc_symbol(0)
    , dc_actions(NULL)
    , dc_tagvertbl(nfa.tags.size())
    , history()
    , dc_kernels()
    , dc_buffers()
    , dc_hc_caches()
    , dc_newvers(newver_cmp_t<history_t>(history, dc_hc_caches))
    , dc_path1()
    , dc_path2()
    , dc_path3()
    , dc_tagcount()
    , stadfa_actions(NULL)
    , stadfa_tagvers()
    , reach()
    , state()
    , gor1_topsort()
    , gor1_linear()
    , gtop_buffer()
    , gtop_cmp()
    , gtop_heap(gtop_cmp, gtop_buffer)
    , newprectbl(NULL)
    , oldprectbl(NULL)
    , oldprecdim(0)
    , histlevel(NULL)
    , sortcores()
    , fincount()
    , worklist()
    , dump_dfa_tree(*this)
    , dc_dump(opts)
    , dc_clstats()
{
    const size_t nstates = nfa.size;
    const size_t ncores = nfa.ncores;
    const size_t ntags = nfa.tags.size();

    reach.reserve(nstates);
    state.reserve(nstates);

    dc_hc_caches.resize(ntags);
    dc_path1.reserve(ntags);
    dc_path2.reserve(ntags);
    dc_path3.reserve(ntags);
    dc_tagcount.resize(ntags);

    if (opts->posix_semantics) {
        newprectbl = new prectable_t[ncores * ncores];
        histlevel = new histleaf_t[ncores];
        sortcores.reserve(ncores);
        fincount.resize(ncores + 1);
        worklist.reserve(nstates);
    }

    if (opts->posix_closure == POSIX_CLOSURE_GTOP) {
        gtop_buffer.reserve(nstates);
    }
    else {
        gor1_topsort.reserve(nstates);
        gor1_linear.reserve(nstates);
    }
}

template<typename history_t>
determ_context_t<history_t>::~determ_context_t()
{
    delete[] newprectbl;
    delete[] histlevel;
}

} // namespace re2c

