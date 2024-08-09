#include <algorithm>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "src/options/opt.h"
#include "src/dfa/dfa.h"
#include "src/dfa/determinization.h"
#include "src/dfa/tcmd.h"
#include "src/msg/warn.h"
#include "src/nfa/nfa.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"
#include "src/util/check.h"
#include "src/util/range.h"

namespace re2c {

template<typename ctx_t> static Ret determinization(ctx_t& ctx) NODISCARD;
template<typename ctx_t> static void clear_caches(ctx_t& ctx);
template<typename ctx_t> static void warn_nondeterministic_tags(const ctx_t& ctx);

Tdfa::Tdfa(DfaAllocator& dfa_alc, size_t charset_bounds, size_t def_rule, size_t eof_rule)
    : dfa_alc(dfa_alc),
      ir_alc(),
      charset(),
      rules(),
      tags(),
      states(),
      nchars(charset_bounds - 1), // (n + 1) bounds for n ranges
      mtagvers(),
      finvers(nullptr),
      tcpool(dfa_alc),
      maxtagver(0),
      def_rule(def_rule),
      eof_rule(eof_rule) {}

Ret determinization(Tnfa&& nfa, Tdfa& dfa, const opt_t* opts, Msg& msg, const std::string& cond) {
    if (opts->captures_posix) {
        pdetctx_t ctx(std::move(nfa), dfa, opts, msg, cond);
        return determinization(ctx);
    } else {
        ldetctx_t ctx(std::move(nfa), dfa, opts, msg, cond);
        return determinization(ctx);
    }
}

Tdfa::~Tdfa() {
    for (TdfaState* s : states) {
        delete s;
    }
}

template<typename ctx_t>
Ret determinization(ctx_t& ctx) {
    const uint32_t INITIAL_TAGS = init_tag_versions(ctx);

    // initial state
    const clos_t c0(ctx.nfa_root, 0, INITIAL_TAGS, HROOT, HROOT);
    ctx.reach.push_back(c0);
    tagged_epsilon_closure(ctx);
    find_state(ctx);

    // Iterate while new kernels are added: for each alphabet symbol, build tagged epsilon-closure
    // of all reachable TNFA states, then find identical or mappable TDFA state or add a new one.
    for (uint32_t i = 0; i < ctx.kernels.size(); ++i) {
        ctx.origin = i;
        clear_caches(ctx);

        for (uint32_t c = 0; c < ctx.dfa.nchars; ++c) {
            reach_on_symbol(ctx, c);
            tagged_epsilon_closure(ctx);
            find_state(ctx);

            // Abort if TDFA grows too fast (either in the number of states, or in the total size of
            // all state kernels which may have many TNFA substates).
            if (ctx.kernels.size() > MAX_DFA_STATES) {
                RET_FAIL(error("DFA has too many states"));
            } else if (ctx.kernels_total > MAX_DFA_SIZE) {
                RET_FAIL(error("DFA is too large"));
            }
        }
    }

    warn_nondeterministic_tags(ctx);

    // Move ownership of common data from determinization context to TDFA.
    ctx.dfa.ir_alc = std::move(ctx.ir_alc);
    ctx.dfa.charset = std::move(ctx.charset);
    ctx.dfa.rules = std::move(ctx.rules);
    ctx.dfa.tags = std::move(ctx.tags);
    return Ret::OK;
}

template<typename ctx_t>
void clear_caches(ctx_t& ctx) {
    ctx.newvers.clear();

    const size_t ntags = ctx.tags.size();
    for (size_t t = 0; t < ntags; ++t) {
        ctx.hc_caches[t].clear();
    }
}

template<typename ctx_t>
void reach_on_symbol(ctx_t& ctx, uint32_t sym) {
    ctx.symbol = sym;
    const uint32_t symbol = ctx.charset[sym];

    const kernel_t* kernel = ctx.kernels[ctx.origin];
    ctx.oldprectbl = kernel->prectbl;
    ctx.oldprecdim = kernel->size;

    closure_t& reach = ctx.reach;
    reach.clear();

    // Add configurations in reverse order: leftmost greedy closure uses the resulting array as a
    // stack, and POSIX closure doesn't care (GOR1 pre-sorts configurations).
    for (uint32_t i = static_cast<uint32_t>(kernel->size); i --> 0; ) {
        TnfaState* s = transition(kernel->state[i], symbol);
        if (s) {
            const clos_t c(s, i, kernel->tvers[i], kernel->thist[i], HROOT);
            reach.push_back(c);
        }
    }
}

TnfaState* transition(TnfaState* state, uint32_t symbol) {
    if (state->kind != TnfaState::Kind::RAN) {
        return nullptr;
    }
    for (const Range* r = state->ran; r; r = r->next()) {
        if ((r->lower() <= symbol) && (symbol < r->upper())) {
            return state->out1;
        }
    }
    return nullptr;
}

template<typename ctx_t>
uint32_t init_tag_versions(ctx_t& ctx) {
    Tdfa& dfa = ctx.dfa;
    const size_t ntags = ctx.tags.size();

    // all-zero tag configuration must have static number zero
    ctx.tagvertbl.insert_const(TAGVER_ZERO);
    DCHECK(ZERO_TAGS == ctx.tagvertbl.insert_const(TAGVER_ZERO));

    // initial tag versions: [1 .. N]
    const tcid_t INITIAL_TAGS = ctx.tagvertbl.insert_succ(1);

    // other versions: [ .. -(N + 1)] and [N + 1 .. ]
    dfa.maxtagver = static_cast<tagver_t>(ntags);

    // final/fallback versions will be assigned on the go
    dfa.finvers = ctx.dfa.dfa_alc.template alloct<tagver_t>(ntags);
    for (size_t i = 0; i < ntags; ++i) {
        dfa.finvers[i] = fixed(ctx.tags[i]) ? TAGVER_ZERO : ++dfa.maxtagver;
    }

    // mark tags with history (initial and final)
    for (size_t i = 0; i < ntags; ++i) {
        if (history(ctx.tags[i])) {
            tagver_t v = static_cast<tagver_t>(i) + 1, f = dfa.finvers[i];
            if (f != TAGVER_ZERO) {
                dfa.mtagvers.insert(f);
            }
            dfa.mtagvers.insert(v);
        }
    }

    return INITIAL_TAGS;
}

// For each tag, find maximal number of parallel versions of this tag used in each kernel (the
// degree of non-determinism) and warn about tags with maximum degree two or more.
// WARNING: This function assumes that kernel items are grouped by rule.
template<typename ctx_t>
void warn_nondeterministic_tags(const ctx_t& ctx) {
    if (ctx.opts->captures) return;

    Warn& warn = ctx.msg.warn;
    const kernels_t& kernels = ctx.kernels;
    const std::vector<Tag>& tags = ctx.tags;
    const std::vector<Rule>& rules = ctx.rules;

    const size_t ntag = tags.size();
    const size_t nkrn = kernels.size();
    std::vector<size_t> maxv(ntag, 0);
    std::set<tagver_t> uniq;

    for (uint32_t i = 0; i < nkrn; ++i) {
        const kernel_t* k = kernels[i];
        TnfaState** s = k->state;
        const size_t n = k->size;
        const uint32_t* v = k->tvers;

        for (size_t u = 0; u < n;) {
            const size_t r = s[u]->rule;
            const Rule& rule = rules[r];

            const size_t l = u;
            for (; ++u < n && s[u]->rule == r;);
            for (size_t t = rule.ltag; t < rule.htag; ++t) {
                uniq.clear();
                for (size_t m = l; m < u; ++m) {
                    uniq.insert(ctx.tagvertbl[v[m]][t]);
                }
                maxv[t] = std::max(maxv[t], uniq.size());
            }
        }
    }

    for (const Rule& rule : rules) {
        for (size_t t = rule.ltag; t < rule.htag; ++t) {
            const size_t m = maxv[t];
            if (m > 1) {
                warn.nondeterministic_tags(rule.semact->loc, ctx.cond, tags[t].name, m);
            }
        }
    }
}

template<typename history_t>
determ_context_t<history_t>::determ_context_t(Tnfa&& nfa,
                                              Tdfa& dfa,
                                              const opt_t* opts,
                                              Msg& msg,
                                              const std::string& cond)
    : opts(opts),
      msg(msg),
      cond(cond),

      // Move ownership of common data from TNFA to determinization context.
      nfa_root(nfa.root),
      ir_alc(std::move(nfa.ir_alc)),
      charset(std::move(nfa.charset)),
      rules(std::move(nfa.rules)),
      tags(std::move(nfa.tags)),

      dfa(dfa),

      origin(Tdfa::NIL),
      target(Tdfa::NIL),
      symbol(0),
      actions(nullptr),
      tagvertbl(tags.size()),
      history(),
      kernels(),
      kernels_total(0),
      buffers(),
      hc_caches(),
      newvers(newver_cmp_t<history_t>(history, hc_caches)),
      path1(),
      path2(),
      path3(),
      tagcount(),
      reach(),
      state(),
      gor1_topsort(),
      gor1_linear(),
      newprectbl(nullptr),
      oldprectbl(nullptr),
      oldprecdim(0),
      histlevel(nullptr),
      sortcores(),
      fincount(),
      worklist(),
      dump_dfa_tree(*this),
      dump(opts),
      clstats() {
    const size_t nstates = nfa.nstates;
    const size_t ncores = nfa.ncores;
    const size_t ntags = tags.size();

    reach.reserve(nstates);
    state.reserve(nstates);

    hc_caches.resize(ntags);
    path1.reserve(ntags);
    path2.reserve(ntags);
    path3.reserve(ntags);
    tagcount.resize(ntags);

    if (opts->captures_posix) {
        newprectbl = new prectable_t[ncores * ncores];
        histlevel = new histleaf_t[ncores];
        sortcores.reserve(ncores);
        fincount.resize(ncores + 1);
        worklist.reserve(nstates);
    }

    gor1_topsort.reserve(nstates);
    gor1_linear.reserve(nstates);
}

template<typename history_t>
determ_context_t<history_t>::~determ_context_t() {
    delete[] newprectbl;
    delete[] histlevel;
}

// explicit instantiation for context types
template void reach_on_symbol<ldetctx_t>(ldetctx_t& ctx, uint32_t sym);
template void reach_on_symbol<pdetctx_t>(pdetctx_t& ctx, uint32_t sym);
template uint32_t init_tag_versions<ldetctx_t>(ldetctx_t& ctx);
template uint32_t init_tag_versions<pdetctx_t>(pdetctx_t& ctx);
template determ_context_t<lhistory_t>::~determ_context_t();
template determ_context_t<phistory_t>::~determ_context_t();
template determ_context_t<lhistory_t>::determ_context_t(
        Tnfa&& nfa, Tdfa& dfa, const opt_t* opts, Msg& msg, const std::string& cond);
template determ_context_t<phistory_t>::determ_context_t(
        Tnfa&& nfa, Tdfa& dfa, const opt_t* opts, Msg& msg, const std::string& cond);

// C++11 requres outer decl for ODR-used static constexpr data members (not needed in C++17).
constexpr uint32_t Tdfa::NIL;

} // namespace re2c

