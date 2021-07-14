#ifndef _RE2C_LIB_REGCOMP_DFA_REGLESS_
#define _RE2C_LIB_REGCOMP_DFA_REGLESS_

#include <string.h>

#include "regex.h"
#include "src/dfa/dfa.h"
#include "src/dfa/determinization.h"
#include "src/nfa/nfa.h"
#include "src/options/opt.h"


namespace re2c {
namespace libre2c {

static const regoff_t NORESULT = std::numeric_limits<regoff_t>::max();
static const uint32_t NOCONF = std::numeric_limits<uint32_t>::max();

// A backlink connects target and origin states of a TDFA transition at the
// level of TNFA configurations. This allows to follow TNFA path backwards from
// the final state to the initial one.
struct rldfa_backlink_t {
    // Index of configuration in the origin TDFA state.
    uint32_t conf;
    // Index of tag history corresponding to the origin configuration.
    hidx_t hidx;
    // T-string fragment corresponding to tagged path from the origin configuration.
    tchar_t *tfrag;
    // Length of t-string fragment.
    size_t tfrag_size;
};

// Registerless TDFA arc (transition). There are no registers and register
// operations, tag actions are hidden in tag histories (stored in backlinks).
struct rldfa_arc_t {
    // Target TDFA state where this arc goes to.
    size_t state;
    // Array of backlinks (one per TNFA path that reaches the target state).
    rldfa_backlink_t *backlinks;
};

// Registerless TDFA state.
struct rldfa_state_t {
    // Outgoing arcs from this state. Each arc has target state and backlinks.
    rldfa_arc_t *arcs;
    // Final link stores final configuration index (if any) and its history.
    rldfa_backlink_t finlink;

    rldfa_state_t(size_t nchars, const rldfa_backlink_t &link);
    ~rldfa_state_t();
    FORBID_COPY(rldfa_state_t);
};

// Registerless TDFA.
struct rldfa_t {
    const opt_t *opts;
    const int flags;

    // Determinization context, specialized either for leftmost greedy policy or
    // for POSIX policy. Context lifetime should cover regexec, as it needs some
    // of the data stored in it (TDFA, tag history, etc.).
    void *ctx;

    // RLDFA own states with backlinks in them.
    std::vector<rldfa_state_t*> states;

    // Array of submatch values (used during matching).
    mutable regoff_t *result;
    // Log stores a sequence of backlink arrays on the matching TDFA path. This
    // allows to unwind tag history back and get submatch values in the absence
    // of registers. Backlink arrays (rather than single backlinks) are needed
    // because there is a set of active TNFA paths on the way forward, and it is
    // unknown until the final state which of them will match.
    mutable std::vector<const rldfa_backlink_t* const*> log;

    rldfa_t(const nfa_t &nfa, dfa_t &dfa, const opt_t *opts, int flags);
    ~rldfa_t();
    FORBID_COPY(rldfa_t);
};

static inline tchar_t encode_tag(size_t tag)
{
    // Tags in the t-string are indexed from 1 rather than 0 (so that
    // negative tags can be represented by negating tag index).
    tag += 1;
    // Two extra tags for the outermost capture that wraps the whole RE.
    tag += 2;
    // T-string characters store either symbols or tags. Symbols use the
    // lower half of the range (so they don't need to be translated),
    // and tags use the upper half.
    tag += TAG_BASE;

    return static_cast<tchar_t>(tag);
}

template<typename history_t>
static inline void get_tstring_fragment(determ_context_t<history_t> &ctx,
    hidx_t hidx, std::vector<tchar_t> &tfrag, rldfa_backlink_t &link, bool tstring)
{
    tfrag.clear();
    for (int32_t i = hidx; i != HROOT; ) {
        const typename history_t::node_t &n = ctx.history.node(i);
        const size_t t = n.info.idx;
        const bool negative = n.info.neg;
        i = n.pred;

        if (tstring) {
            // For t-string construction add only positive tags. The idea is to
            // get the cheapest possible representation of parse results, and
            // adding negative tags slows it down quite a bit.
            if (!negative) tfrag.push_back(encode_tag(t));
        } else {
            // For offset construction add both positive and negative tags.
            // Shift negative tags by TAG_BASE to make them distinguishable from
            // positive tags. Do not expand nested negative tags here: it makes
            // regexec() slower, because it cannot skip all nested tags with one
            // check when a tag has already been set.
            tfrag.push_back(static_cast<tchar_t>(t + (negative ? TAG_BASE : 0)));
        }
    }

    std::reverse(tfrag.begin(), tfrag.end());

    link.tfrag_size = tfrag.size();
    link.tfrag = ctx.dc_allocator.template alloct<tchar_t>(tfrag.size());
    memcpy(link.tfrag, tfrag.data(), tfrag.size() * sizeof(tchar_t));
}

template<typename ctx_t>
static void determinization_regless(const nfa_t &nfa, dfa_t &dfa, rldfa_t &rldfa)
{
    Msg msg;
    // Determinization context lifetime must cover regexec, as some of the data
    // stored in the context is used during matching.
    ctx_t &ctx = *new ctx_t(rldfa.opts, msg, "", nfa, dfa);
    rldfa.ctx = &ctx;
    allocator_t &alc = ctx.dc_allocator;
    const bool tstring = rldfa.flags & REG_TSTRING;
    std::vector<tchar_t> tfrag;

    // Construct initial TDFA state.
    const uint32_t INITIAL_TAGS = init_tag_versions(ctx);
    const clos_t c0(ctx.nfa.root, 0, INITIAL_TAGS, HROOT, HROOT);
    ctx.reach.push_back(c0);
    closure(ctx);
    find_state_regless(ctx, rldfa, tfrag);

    // Iterate while new states are added: for each alphabet symbol build tagged
    // epsilon-closure of all reachable NFA states, then find identical or
    // mappable TDFA state, or add a new one.
    for (uint32_t i = 0; i < ctx.dc_kernels.size(); ++i) {
        ctx.dc_origin = i;

        for (uint32_t c = 0; c < ctx.dfa.nchars; ++c) {
            reach_on_symbol(ctx, c);
            closure(ctx);
            find_state_regless(ctx, rldfa, tfrag);

            // Unlike TDFA, RLDFA stores backlinks instead of tag actions.
            rldfa_backlink_t *links = alc.alloct<rldfa_backlink_t>(ctx.state.size());
            for (size_t j = 0; j < ctx.state.size(); ++j) {
                const typename ctx_t::conf_t &x = ctx.state[j];
                rldfa_backlink_t &l = links[j];
                l.conf = x.origin;
                l.hidx = x.ttran;
                get_tstring_fragment(ctx, x.ttran, tfrag, l, tstring);
            }
            rldfa.states[ctx.dc_origin]->arcs[c].backlinks = links;
        }
    }
}

template<typename ctx_t>
static void find_state_regless(ctx_t &ctx, rldfa_t &rldfa, std::vector<tchar_t> &tfrag)
{
    const bool tstring = rldfa.flags & REG_TSTRING;
    dfa_t &dfa = ctx.dfa;

    // Find or add the new state in the existing set of states.
    const bool is_new = do_find_state<ctx_t, false, true>(ctx);

    if (is_new) {
        // Check if the new TDFA state is final.
        // See note [at most one final item per closure].
        rldfa_backlink_t finlink = {NOCONF, HROOT, NULL, 0};
        for (uint32_t i = 0; i < ctx.state.size(); ++i) {
            const typename ctx_t::conf_t &x = ctx.state[i];
            if (x.state->type == nfa_state_t::FIN) {
                finlink.conf = i;
                finlink.hidx = x.thist;
                get_tstring_fragment(ctx, x.thist, tfrag, finlink, tstring);
                break;
            }
        }

        // Create a new regless-DFA state.
        rldfa_state_t *s = new rldfa_state_t(dfa.nchars, finlink);
        rldfa.states.push_back(s);
    }

    if (ctx.dc_origin != dfa_t::NIL) {
        rldfa.states[ctx.dc_origin]->arcs[ctx.dc_symbol].state = ctx.dc_target;
    }

    DDUMP_DFA_RAW(ctx, is_new);
    DDUMP_DFA_TREE(is_new);
}

inline rldfa_state_t::rldfa_state_t(size_t nchars, const rldfa_backlink_t &link)
    : arcs(new rldfa_arc_t[nchars])
    , finlink()
{
    finlink.conf = link.conf;
    finlink.hidx = link.hidx;
    finlink.tfrag = link.tfrag;
    finlink.tfrag_size = link.tfrag_size;
}

inline rldfa_state_t::~rldfa_state_t()
{
    delete[] arcs;
}

inline rldfa_t::rldfa_t(const nfa_t &nfa, dfa_t &dfa, const opt_t *opts, int flags)
    : opts(opts)
    , flags(flags)
    , ctx(NULL)
    , states()
    , result(new regoff_t[nfa.tags.size()])
    , log()
{
    if (opts->posix_semantics) {
        determinization_regless<pdetctx_t>(nfa, dfa, *this);
    } else {
        determinization_regless<ldetctx_t>(nfa, dfa, *this);
    }
}

inline rldfa_t::~rldfa_t()
{
    for (size_t i = 0; i < states.size(); ++i) {
        delete states[i];
    }
}

} // namespace libre2c
} // namespace re2c

#endif // _RE2C_LIB_REGCOMP_DFA_REGLESS_
