#ifndef _RE2C_LIB_REGEX_IMPL_
#define _RE2C_LIB_REGEX_IMPL_

#include <stddef.h>
#include <string.h>
#include <map>
#include <vector>
#include <queue>

#include "regex.h"
#include "src/dfa/dfa.h"
#include "src/dfa/determinization.h"
#include "src/nfa/nfa.h"
#include "src/util/check.h"

namespace re2c {
namespace libre2c {

using tag_path_t = std::vector<tag_info_t>;

struct conf_t {
    TnfaState* state;
    uint32_t origin;
    int32_t thist;

    inline conf_t(): state(nullptr), origin(0), thist(HROOT) {}
    inline conf_t(TnfaState* s, uint32_t o, int32_t h)
        : state(s), origin(o), thist(h) {}
    inline conf_t(const conf_t& c, TnfaState* s)
        : state(s), origin(c.origin), thist(c.thist) {}
    inline conf_t(const conf_t& c, TnfaState* s, int32_t h)
        : state(s), origin(c.origin), thist(h) {}
};

struct ran_or_fin_t {
    inline bool operator()(const conf_t& c);
};

using confset_t = std::vector<conf_t>;
using confiter_t = confset_t::iterator;
using cconfiter_t = confset_t::const_iterator;
using rcconfiter_t = confset_t::const_reverse_iterator;

template<typename history_type_t>
struct simctx_t {
    using conf_t = libre2c::conf_t;
    using confset_t = std::vector<conf_t>;
    using confiter_t = confset_t::iterator;
    using cconfiter_t = confset_t::const_iterator;
    using rconfiter_t = confset_t::reverse_iterator;
    using rcconfiter_t = confset_t::const_reverse_iterator;
    using history_t = history_type_t;

    const Tnfa& nfa;
    const size_t nsub;
    const int flags;

    const std::vector<Tag>& tags;

    history_t history;
    int32_t hidx;

    uint32_t step;

    size_t rule;

    const char* cursor;
    const char* marker;

    regoff_t* offsets1;
    regoff_t* offsets2;
    regoff_t* offsets3;
    bool* done;

    int32_t* newprectbl;
    int32_t* oldprectbl;
    size_t oldprecdim;
    histleaf_t* histlevel;
    std::vector<uint32_t> sortcores;
    std::vector<uint32_t> fincount;
    std::vector<int32_t> worklist;
    std::vector<cconfiter_t> stateiters;

    confset_t reach;
    confset_t state;
    std::vector<TnfaState*> gor1_topsort;
    std::vector<TnfaState*> gor1_linear;
    closure_stats_t clstats;

    simctx_t(const Tnfa& nfa, size_t re_nsub, int flags);
    ~simctx_t();
    FORBID_COPY(simctx_t);
};

// tag history for lazy disambiguation (both POSIX and leftmost greedy)
struct zhistory_t {
    struct node_t {
        tag_info_t info;
        hidx_t pred;
        uint32_t orig;
        uint32_t step;

        inline node_t(tag_info_t info, hidx_t pred, uint32_t orig, uint32_t step)
            : info(info), pred(pred), orig(orig), step(step) {}
    };

    struct cache_entry_t {
        int32_t prec1;
        int32_t prec2;
        int32_t prec;
    };
    using cache_t = std::map<uint64_t, cache_entry_t>;

    std::vector<node_t> nodes;
    cache_t cache;

    inline zhistory_t(): nodes(), cache() { init(); }
    inline void init();
    inline node_t& node(hidx_t i) { return nodes[static_cast<uint32_t>(i)]; }
    inline const node_t& node(hidx_t i) const { return nodes[static_cast<uint32_t>(i)]; }

    template<typename ctx_t> inline hidx_t link(ctx_t& ctx, const typename ctx_t::conf_t& conf);
    template<typename ctx_t> static int32_t precedence(ctx_t& ctx,
                                                       const typename ctx_t::conf_t& x,
                                                       const typename ctx_t::conf_t& y,
                                                       int32_t& prec1,
                                                       int32_t& prec2);
    FORBID_COPY(zhistory_t);
};

using psimctx_t = simctx_t<phistory_t>;
using lsimctx_t = simctx_t<lhistory_t>;
using pzsimctx_t = simctx_t<zhistory_t>;
using lzsimctx_t = simctx_t<zhistory_t>;

// regexec functions
using regexec_t = int (const regex_t*, const char*, size_t, regmatch_t[], int);
regexec_t regexec_dfa;
template<typename ctx_t> regexec_t regexec_dfa_multipass;
regexec_t regexec_nfa_posix;
regexec_t regexec_nfa_posix_trie;
regexec_t regexec_nfa_leftmost;
regexec_t regexec_nfa_leftmost_trie;

// regparse functions (non-standard)
using regparse_t = subhistory_t* (const regex_t*, const char*, size_t);
regparse_t regparse_dfa;
template<typename ctx_t> regparse_t regparse_dfa_multipass;

// regtstring function (non-standard)
template<typename ctx_t>
const tstring_t* regtstring_dfa_multipass(const regex_t*, const char*);

template<typename history_t>
simctx_t<history_t>::simctx_t(const Tnfa& nfa, size_t re_nsub, int flags)
    : nfa(nfa),
      nsub(2 * (re_nsub - 1)),
      flags(flags),
      tags(nfa.tags),
      history(),
      hidx(HROOT),
      step(0),
      rule(Rule::NONE),
      cursor(nullptr),
      marker(nullptr),
      offsets1(nullptr),
      offsets2(nullptr),
      offsets3(nullptr),
      done(nullptr),
      newprectbl(nullptr),
      oldprectbl(nullptr),
      oldprecdim(0),
      histlevel(nullptr),
      sortcores(),
      fincount(),
      worklist(),
      stateiters(),
      reach(),
      state(),
      gor1_topsort(),
      gor1_linear(),
      clstats() {
    const size_t
    ntags = nfa.tags.size(),
    nstates = nfa.nstates,
    ncores = nfa.ncores;

    state.reserve(nstates);
    reach.reserve(nstates);

    done = new bool[ntags];
    offsets3 = new regoff_t[ntags];

    if (!(flags & REG_TRIE)) {
        offsets1 = new regoff_t[ntags * ncores];
        offsets2 = new regoff_t[ntags * ncores];
    }
    if (!(flags & REG_LEFTMOST) && !(flags & REG_TRIE)) {
        const size_t dim = ncores;
        newprectbl = new int32_t[ncores * dim];
        oldprectbl = new int32_t[ncores * dim];
        histlevel = new histleaf_t[ncores];
        sortcores.reserve(ncores);
        fincount.resize(ncores + 1);
        worklist.reserve(nstates);
    }

    gor1_topsort.reserve(nstates);
    gor1_linear.reserve(nstates);
}

template<typename history_t>
simctx_t<history_t>::~simctx_t() {
    delete[] done;
    delete[] offsets3;
    if (!(flags & REG_TRIE)) {
        delete[] offsets1;
        delete[] offsets2;
    }
    if (!(flags & REG_LEFTMOST) && !(flags & REG_TRIE)) {
        delete[] newprectbl;
        delete[] oldprectbl;
        delete[] histlevel;
    }
}

template<typename history_t>
void init(simctx_t<history_t>& ctx, const char* string) {
    ctx.reach.clear();
    ctx.state.clear();
    ctx.history.init();
    ctx.hidx = HROOT;
    ctx.step = 0;
    ctx.rule = Rule::NONE;
    ctx.cursor = ctx.marker = string;
    ctx.sortcores.clear();
    DCHECK(ctx.worklist.empty());
    DCHECK(ctx.gor1_topsort.empty());
    DCHECK(ctx.gor1_linear.empty());
}

static inline regoff_t* offs_addr(regmatch_t pmatch[], size_t t) {
    regmatch_t* m = &pmatch[t / 2 + 1];
    return t % 2 == 0 ? &m->rm_so : &m->rm_eo;
}

struct getoff_nfa_t {
    const regoff_t* offsets;
    inline regoff_t operator()(size_t idx) const {
        return offsets[idx];
    }
};

struct getoff_dfa_t {
    const Tdfa* dfa;
    const regoff_t* regs;
    const regoff_t len;

    regoff_t operator()(size_t idx) const {
        const Tag& tag = dfa->tags[idx];
        regoff_t off;
        if (!fixed(tag)) {
            off = regs[dfa->finvers[idx]];
        } else {
            off = tag.base == Tag::RIGHTMOST ? len : regs[dfa->finvers[tag.base]];
            if (off != -1) {
                off -= static_cast<regoff_t>(tag.dist);
            }
        }
        return off;
    }
};

template<typename getoff_t>
void tags_to_submatch(const std::vector<Tag>& tags,
                      size_t nmatch,
                      regmatch_t pmatch[],
                      regoff_t len,
                      const getoff_t& getoff) {
    const size_t ntags = tags.size();
    regmatch_t* m = pmatch, *e = pmatch + nmatch;

    m->rm_so = 0;
    m->rm_eo = len;
    ++m;

    for (size_t t = 0; t < ntags && m < e; t += 2) {
        const Tag& tag = tags[t];
        if (!fictive(tag)) {
            const regoff_t so = getoff(t);
            const regoff_t eo = getoff(t + 1);

            for (size_t j = tag.lsub; j <= tag.hsub && m < e; j += 2, ++m) {
                DCHECK(m - 1 == &pmatch[j / 2]);
                m->rm_so = so;
                m->rm_eo = eo;
            }
        }
    }
}

template<typename history_t>
int finalize(const simctx_t<history_t>& ctx,
             const char* string,
             size_t nmatch,
             regmatch_t pmatch[]) {
    if (ctx.rule == Rule::NONE) {
        return REG_NOMATCH;
    }

    const std::vector<Tag>& tags = ctx.nfa.tags;
    const size_t ntags = tags.size();
    bool* done = ctx.done;

    memset(done, 0, ntags * sizeof(bool));

    for (int32_t i = ctx.hidx; i != HROOT; ) {
        const typename history_t::node_t& n = ctx.history.node(i);
        i = n.pred;
        const size_t t = n.info.idx;

        // If already updated, skip.
        if (done[t]) continue;

        if (!n.info.neg) {
            // Update positive tag.
            done[t] = true;
            ctx.offsets3[t] = static_cast<regoff_t>(n.step);
        } else {
            // Update negative tag together with its sibling and nested tags (if any).
            const Tag& tag = tags[t];
            for (size_t l = tag.lnest; l < tag.hnest; ++l) {
                if (!done[l]) {
                    done[l] = true;
                    ctx.offsets3[l] = -1;
                }
            }
        }
    }

    const getoff_nfa_t fn = { ctx.offsets3 };
    tags_to_submatch(tags, nmatch, pmatch, ctx.marker - string - 1, fn);

    return 0;
}

template<typename history_t>
void update_offsets(simctx_t<history_t>& ctx, const conf_t& c, uint32_t id) {
    regoff_t* o;
    const std::vector<Tag>& tags = ctx.nfa.tags;
    const size_t ntags = tags.size();
    TnfaState* s = c.state;
    bool* done = ctx.done;

    if (s->kind == TnfaState::Kind::FIN) {
        ctx.marker = ctx.cursor;
        ctx.rule = 0;
        o = ctx.offsets3;
    } else {
        o = ctx.offsets1 + id * ntags;
    }

    memcpy(o, ctx.offsets2 + c.origin * ntags, ntags * sizeof(regoff_t));
    memset(done, 0, ntags * sizeof(bool));

    for (int32_t i = c.thist; i != HROOT; ) {
        const typename history_t::node_t& n = ctx.history.node(i);
        i = n.pred;
        const size_t t = n.info.idx;

        // If already updated, skip.
        if (done[t]) continue;

        if (!n.info.neg) {
            // Update positive tag.
            done[t] = true;
            o[t] = static_cast<regoff_t>(ctx.step);
        } else {
            // Update negative tag together with its sibling and nested tags (if any).
            const Tag& tag = tags[t];
            for (size_t l = tag.lnest; l < tag.hnest; ++l) {
                if (!done[l]) {
                    done[l] = true;
                    o[l] = -1;
                }
            }
        }
    }
}

bool ran_or_fin_t::operator()(const conf_t& c) {
    return c.state->kind == TnfaState::Kind::RAN
        || c.state->kind == TnfaState::Kind::FIN;
}

void zhistory_t::init() {
    nodes.clear();
    nodes.push_back(node_t(NOINFO, -1, 0, 0));
    cache.clear();
}

template<typename ctx_t>
hidx_t zhistory_t::link(ctx_t& ctx, const typename ctx_t::conf_t& conf) {
    const int32_t i = static_cast<int32_t>(nodes.size());
    nodes.push_back(node_t(conf.state->tag, conf.thist, conf.origin, ctx.step));
    return i;
}

} // namespace libre2c
} // namespace re2c

#endif // _RE2C_LIB_REGEX_IMPL_
