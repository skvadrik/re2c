#ifndef _RE2C_LIB_REGCOMP_DFA_MULTIPASS_
#define _RE2C_LIB_REGCOMP_DFA_MULTIPASS_

#include <string.h>

#include "regex.h"
#include "src/dfa/dfa.h"
#include "src/dfa/determinization.h"
#include "src/nfa/nfa.h"
#include "src/options/opt.h"
#include "src/util/check.h"

namespace re2c {
namespace libre2c {

static constexpr regoff_t NORESULT = std::numeric_limits<regoff_t>::max();
static constexpr uint32_t NOCONF = std::numeric_limits<uint32_t>::max();

// A backlink connects target and origin states of a TDFA transition at the level of TNFA
// configurations. This allows one to follow TNFA path backwards from the final state to the initial
// one.
struct MpTdfaBacklink {
    // Index of configuration in the origin TDFA state.
    uint32_t conf;
    // T-string fragment corresponding to tagged path from the origin configuration.
    tchar_t* tfrag;
    // Length of t-string fragment.
    size_t tfrag_size;
};

// Multi-pass TDFA arc (transition). There are no registers and register operations, tag actions are
// hidden in tag histories (stored in backlinks).
struct MpTdfaArc {
    // Target TDFA state where this arc goes to.
    size_t state;
    // Array of backlinks (one per TNFA path that reaches the target state).
    MpTdfaBacklink* backlinks;
};

// Multi-pass TDFA state.
struct MpTdfaState {
    // Outgoing arcs from this state. Each arc has target state and backlinks.
    MpTdfaArc* arcs;
    // Final link stores final configuration index (if any) and its history.
    MpTdfaBacklink finlink;

    MpTdfaState(size_t nchars, const MpTdfaBacklink& link);
    ~MpTdfaState();
    FORBID_COPY(MpTdfaState);
};

// Multi-pass TDFA.
struct MpTdfa {
    const opt_t* opts;
    const int flags;
    std::vector<Tag> tags;

    DfaAllocator alc;

    // RLDFA own states with backlinks in them.
    std::vector<MpTdfaState*> states;

    // Array of submatch values (used during matching).
    mutable regoff_t* result;
    // Log stores a sequence of backlink arrays on the matching TDFA path. This allows one to unwind
    // tag history back and get submatch values in the absence of registers. Backlink arrays (rather
    // than single backlinks) are needed because there is a set of active TNFA paths on the way
    // forward, and it is unknown until the final state which of them will match.
    mutable std::vector<const MpTdfaBacklink* const*> log;

    MpTdfa(Tnfa&& nfa, const opt_t* opts, int flags);
    ~MpTdfa();
    FORBID_COPY(MpTdfa);
};

static inline tchar_t encode_tag(size_t tag) {
    // Tags in the t-string are indexed from 1 rather than 0 (so that negative tags can be
    // represented by negating tag index).
    tag += 1;
    // Two extra tags for the outermost capture that wraps the whole regexp.
    tag += 2;
    // T-string characters store either symbols or tags. Symbols use the lower half of the range (so
    // they don't need to be translated), and tags use the upper half.
    tag += TAG_BASE;

    return static_cast<tchar_t>(tag);
}

template<typename history_t>
static inline void get_tstring_fragment(history_t& history,
                                        DfaAllocator& alc,
                                        hidx_t hidx,
                                        std::vector<tchar_t>& tfrag,
                                        MpTdfaBacklink& link,
                                        bool tstring) {
    tfrag.clear();
    for (int32_t i = hidx; i != HROOT; ) {
        const typename history_t::node_t& n = history.node(i);
        const size_t t = n.info.idx;
        const bool negative = n.info.neg;
        i = n.pred;

        if (tstring) {
            // For t-string construction add only positive tags. The idea is to get the cheapest
            // possible representation of parse results, and adding negative tags slows it down
            // quite a bit.
            if (!negative) tfrag.push_back(encode_tag(t));
        } else {
            // For offset construction add both positive and negative tags. Shift negative tags by
            // TAG_BASE to make them distinguishable from positive tags. Do not expand nested
            // negative tags here: it makes regexec() slower, because it cannot skip all nested tags
            // with one check when a tag has already been set.
            tfrag.push_back(static_cast<tchar_t>(t + (negative ? TAG_BASE : 0)));
        }
    }

    std::reverse(tfrag.begin(), tfrag.end());

    link.tfrag_size = tfrag.size();
    link.tfrag = alc.template alloct<tchar_t>(tfrag.size());
    memcpy(link.tfrag, tfrag.data(), tfrag.size() * sizeof(tchar_t));
}

template<typename ctx_t>
static MpTdfaBacklink* construct_backlinks(const ctx_t& ctx,
                                           MpTdfa& mptdfa,
                                           std::vector<tchar_t>& tfrag,
                                           const std::vector<std::vector<uint32_t>>& uniq_orig) {
    if (ctx.target == Tdfa::NIL) return nullptr;

    const bool tstring = mptdfa.flags & REG_TSTRING;
    const std::vector<uint32_t>& uo = uniq_orig[ctx.target];
    uint32_t nbacklinks = *std::max_element(uo.begin(), uo.end()) + 1;
    MpTdfaBacklink* links = mptdfa.alc.alloct<MpTdfaBacklink>(nbacklinks);

    for (size_t j = 0, k; j < nbacklinks; ++j) {
        for (k = 0; k < ctx.state.size() && uo[k] != j; ++k);
        const typename ctx_t::conf_t& x = ctx.state[k];
        MpTdfaBacklink& l = links[j];
        l.conf = uniq_orig[ctx.origin][x.origin];
        get_tstring_fragment(ctx.history, mptdfa.alc, x.ttran, tfrag, l, tstring);
    }

    return links;
}

template<typename ctx_t>
static void determinization_multipass(Tnfa&& nfa, MpTdfa& mptdfa) {
    Msg msg;
    // Determinization context lifetime must cover regexec, as some of the data stored in the
    // context is used during matching.
    Tdfa dfa(mptdfa.alc, nfa.charset.size(), Rule::NONE, Rule::NONE);
    ctx_t ctx(std::move(nfa), dfa, mptdfa.opts, msg, "");

    std::vector<tchar_t> tfrag;
    // Per-state array of mappings from configuration index to a unique origin index. This is needed
    // to compress identical backlinks into one. Note that configurations with identical origin also
    // have identical transition tags (because those are the lookahead tags in the origin
    // configuration).
    std::vector<std::vector<uint32_t> > uniq_orig;

    // Construct initial TDFA state.
    const uint32_t INITIAL_TAGS = init_tag_versions(ctx);
    const clos_t c0(ctx.nfa_root, 0, INITIAL_TAGS, HROOT, HROOT);
    ctx.reach.push_back(c0);
    closure(ctx);
    find_state_multipass(ctx, mptdfa, tfrag, uniq_orig);

    // Iterate while new states are added: for each alphabet symbol build tagged epsilon-closure of
    // all reachable NFA states, then find identical or mappable TDFA state, or add a new one.
    for (uint32_t i = 0; i < ctx.kernels.size(); ++i) {
        ctx.origin = i;

        for (uint32_t c = 0; c < dfa.nchars; ++c) {
            reach_on_symbol(ctx, c);
            closure(ctx);
            find_state_multipass(ctx, mptdfa, tfrag, uniq_orig);

            // Multi-pass TDFA stores backlinks instead of tag actions.
            mptdfa.states[ctx.origin]->arcs[c].backlinks =
                    construct_backlinks(ctx, mptdfa, tfrag, uniq_orig);
        }
    }

    mptdfa.tags = std::move(ctx.tags);
}

template<typename ctx_t>
static void find_state_multipass(ctx_t& ctx,
                                 MpTdfa& mptdfa,
                                 std::vector<tchar_t>& tfrag,
                                 std::vector<std::vector<uint32_t>>& uniq_orig) {
    const bool tstring = mptdfa.flags & REG_TSTRING;

    // Find or add the new state in the existing set of states.
    const bool is_new = do_find_state<ctx_t, true>(ctx);

    if (is_new) {
        const typename ctx_t::confset_t& state = ctx.state;

        // Map configuration index to a unique origin index.
        uniq_orig.push_back(std::vector<uint32_t>(state.size(), UINT32_MAX));
        std::vector<uint32_t>& uo = uniq_orig.back();
        for (uint32_t i = 0, j = 0; j < state.size(); ++j) {
            if (uo[j] != UINT32_MAX) continue;
            for (size_t k = j + 1; k < state.size(); ++k) {
                if (state[j].origin == state[k].origin) {
                    DCHECK(state[j].ttran == state[k].ttran); // TDFA(1) property
                    uo[k] = i;
                }
            }
            uo[j] = i++;
        }

        // Check if the new TDFA state is final. See note [at most one final item per closure].
        MpTdfaBacklink finlink = {NOCONF, nullptr, 0};
        for (uint32_t i = 0; i < state.size(); ++i) {
            if (state[i].state->kind == TnfaState::Kind::FIN) {
                finlink.conf = uo[i];
                get_tstring_fragment(
                        ctx.history, mptdfa.alc, state[i].thist, tfrag, finlink, tstring);
                break;
            }
        }

        // Create a new multipass-DFA state.
        MpTdfaState* s = new MpTdfaState(ctx.dfa.nchars, finlink);
        mptdfa.states.push_back(s);
    }

    if (ctx.origin != Tdfa::NIL) {
        mptdfa.states[ctx.origin]->arcs[ctx.symbol].state = ctx.target;
    }
}

inline MpTdfaState::MpTdfaState(size_t nchars, const MpTdfaBacklink& link)
    : arcs(new MpTdfaArc[nchars]), finlink() {
    finlink.conf = link.conf;
    finlink.tfrag = link.tfrag;
    finlink.tfrag_size = link.tfrag_size;
}

inline MpTdfaState::~MpTdfaState() {
    delete[] arcs;
}

inline MpTdfa::MpTdfa(Tnfa&& nfa, const opt_t* opts, int flags)
    : opts(opts),
      flags(flags),
      tags(),
      alc(),
      states(),
      result(new regoff_t[nfa.tags.size()]),
      log() {
    if (opts->captures_posix) {
        determinization_multipass<pdetctx_t>(std::move(nfa), *this);
    } else {
        determinization_multipass<ldetctx_t>(std::move(nfa), *this);
    }
}

inline MpTdfa::~MpTdfa() {
    for (size_t i = 0; i < states.size(); ++i) {
        delete states[i];
    }
}

} // namespace libre2c
} // namespace re2c

#endif // _RE2C_LIB_REGCOMP_DFA_MULTIPASS_
