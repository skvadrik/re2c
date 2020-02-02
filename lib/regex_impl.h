#ifndef _RE2C_LIB_REGEX_IMPL_
#define _RE2C_LIB_REGEX_IMPL_

#include "regex.h"
#include <stddef.h>
#include <map>
#include <vector>
#include <queue>

#include "src/dfa/determinization.h"
#include "src/nfa/nfa.h"


namespace re2c {
namespace libre2c {

typedef std::vector<tag_info_t> tag_path_t;

struct conf_t
{
    nfa_state_t *state;
    uint32_t origin;
    int32_t thist;

    inline conf_t(): state(NULL), origin(0), thist(HROOT) {}
    inline conf_t(nfa_state_t *s, uint32_t o, int32_t h)
        : state(s), origin(o), thist(h) {}
    inline conf_t(const conf_t &c, nfa_state_t *s)
        : state(s), origin(c.origin), thist(c.thist) {}
    inline conf_t(const conf_t &c, nfa_state_t *s, int32_t h)
        : state(s), origin(c.origin), thist(h) {}
};

struct ran_or_fin_t
{
    inline bool operator()(const conf_t &c);
};

typedef std::vector<conf_t> confset_t;
typedef confset_t::iterator confiter_t;
typedef confset_t::const_iterator cconfiter_t;
typedef confset_t::const_reverse_iterator rcconfiter_t;

template<typename history_type_t>
struct simctx_t
{
    typedef libre2c::conf_t conf_t;
    typedef std::vector<conf_t> confset_t;
    typedef confset_t::iterator confiter_t;
    typedef confset_t::const_iterator cconfiter_t;
    typedef confset_t::reverse_iterator rconfiter_t;
    typedef confset_t::const_reverse_iterator rcconfiter_t;
    typedef history_type_t history_t;

    const nfa_t &nfa;
    const nfa_t *nfa0;
    const size_t nsub;
    const int flags;

    history_t history;
    int32_t hidx;

    uint32_t step;

    size_t rule;

    const char *cursor;
    const char *marker;

    regoff_t *offsets1;
    regoff_t *offsets2;
    regoff_t *offsets3;
    bool *done;

    int32_t *newprectbl;
    int32_t *oldprectbl;
    size_t oldprecdim;
    histleaf_t *histlevel;
    std::vector<uint32_t> sortcores;
    std::vector<uint32_t> fincount;
    std::vector<int32_t> worklist;
    std::vector<cconfiter_t> stateiters;

    confset_t reach;
    confset_t state;
    std::vector<nfa_state_t*> gor1_topsort;
    std::vector<nfa_state_t*> gor1_linear;
    std::vector<nfa_state_t*> gtop_heap_storage;
    cmp_gtop_t gtop_cmp;
    gtop_heap_t gtop_heap;
    closure_stats_t dc_clstats;

    simctx_t(const nfa_t &nfa, const nfa_t *nfa0, size_t re_nsub, int flags);
    ~simctx_t();
    FORBID_COPY(simctx_t);
};

// tag history for lazy disambiguation (both POSIX and leftmost greedy)
struct zhistory_t
{
    struct node_t {
        tag_info_t info;
        hidx_t pred;
        uint32_t orig;
        uint32_t step;

        inline node_t(tag_info_t info, hidx_t pred, uint32_t orig, uint32_t step)
            : info(info), pred(pred), orig(orig), step(step) {}
    };

    struct cache_entry_t
    {
        int32_t prec1;
        int32_t prec2;
        int32_t prec;
    };
    typedef std::map<uint64_t, cache_entry_t> cache_t;

    std::vector<node_t> nodes;
    cache_t cache;

    inline zhistory_t(): nodes(), cache() { init(); }
    inline void init();
    inline node_t &node(hidx_t i) { return nodes[static_cast<uint32_t>(i)]; }
    inline const node_t &node(hidx_t i) const { return nodes[static_cast<uint32_t>(i)]; }
    template<typename ctx_t> inline hidx_t link(ctx_t &ctx
        , const typename ctx_t::conf_t &conf);
    template<typename ctx_t> static int32_t precedence(ctx_t &ctx
        , const typename ctx_t::conf_t &x, const typename ctx_t::conf_t &y
        , int32_t &prec1, int32_t &prec2);
    FORBID_COPY(zhistory_t);
};

// tag history for Kuklewicz disambiguation (POSIX semantics)
struct khistory_t
{
    struct node_t {
        tag_info_t info;
        hidx_t pred;

        inline node_t(tag_info_t info, hidx_t pred)
            : info(info), pred(pred) {}
    };

    std::vector<node_t> nodes;
    std::vector<int32_t> path1;
    std::vector<int32_t> path2;

    inline khistory_t(): nodes(), path1(), path2() { init(); }
    inline void init();
    inline node_t &node(hidx_t i) { return nodes[static_cast<uint32_t>(i)]; }
    inline const node_t &node(hidx_t i) const { return nodes[static_cast<uint32_t>(i)]; }
    template<typename ctx_t> inline hidx_t link(ctx_t &ctx
        , const typename ctx_t::conf_t &conf);
    template<typename ctx_t> static int32_t precedence(ctx_t &ctx
        , const typename ctx_t::conf_t &x, const typename ctx_t::conf_t &y
        , int32_t &prec1, int32_t &prec2);
    FORBID_COPY(khistory_t);
};

typedef simctx_t<phistory_t> psimctx_t;
typedef simctx_t<lhistory_t> lsimctx_t;
typedef simctx_t<zhistory_t> pzsimctx_t;
typedef simctx_t<zhistory_t> lzsimctx_t;
typedef simctx_t<khistory_t> ksimctx_t;

int regexec_dfa(const regex_t *preg, const char *string, size_t nmatch, regmatch_t pmatch[], int eflags);
int regexec_nfa_posix(const regex_t *preg, const char *string, size_t nmatch, regmatch_t pmatch[], int eflags);
int regexec_nfa_posix_trie(const regex_t *preg, const char *string, size_t nmatch, regmatch_t pmatch[], int eflags);
int regexec_nfa_posix_backward(const regex_t *preg, const char *string, size_t nmatch, regmatch_t pmatch[], int eflags);
int regexec_nfa_posix_kuklewicz(const regex_t *preg, const char *string, size_t nmatch, regmatch_t pmatch[], int eflags);
int regexec_nfa_leftmost(const regex_t *preg, const char *string, size_t nmatch, regmatch_t pmatch[], int eflags);
int regexec_nfa_leftmost_trie(const regex_t *preg, const char *string, size_t nmatch, regmatch_t pmatch[], int eflags);

template<typename history_t>
simctx_t<history_t>::simctx_t(const nfa_t &nfa, const nfa_t *nfa0, size_t re_nsub, int flags)
    : nfa(nfa)
    , nfa0(nfa0)
    , nsub(2 * (re_nsub - 1))
    , flags(flags)
    , history()
    , hidx(HROOT)
    , step(0)
    , rule(Rule::NONE)
    , cursor(NULL)
    , marker(NULL)
    , offsets1(NULL)
    , offsets2(NULL)
    , offsets3(NULL)
    , done(NULL)
    , newprectbl(NULL)
    , oldprectbl(NULL)
    , oldprecdim(0)
    , histlevel(NULL)
    , sortcores()
    , fincount()
    , worklist()
    , stateiters()
    , reach()
    , state()
    , gor1_topsort()
    , gor1_linear()
    , gtop_heap_storage()
    , gtop_cmp()
    , gtop_heap(gtop_cmp, gtop_heap_storage)
    , dc_clstats()
{
    const size_t
        ntags = nfa.tags.size(),
        nstates = nfa.size,
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
        const size_t dim = (flags & REG_KUKLEWICZ) ? ntags : ncores;
        newprectbl = new int32_t[ncores * dim];
        oldprectbl = new int32_t[ncores * dim];
        histlevel = new histleaf_t[ncores];
        sortcores.reserve(ncores);
        fincount.resize(ncores + 1);
        worklist.reserve(nstates);
    }
    if (flags & REG_KUKLEWICZ) {
        stateiters.reserve(ncores);
    }

    if (flags & REG_GTOP) {
        gtop_heap_storage.reserve(nstates);
    }
    else {
        gor1_topsort.reserve(nstates);
        gor1_linear.reserve(nstates);
    }
}

template<typename history_t>
simctx_t<history_t>::~simctx_t()
{
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
    if (flags & REG_BACKWARD) {
        delete &nfa0->charset;
        delete &nfa0->rules;
        delete &nfa0->tags;
        delete nfa0;
    }
}

template<typename history_t>
void init(simctx_t<history_t> &ctx, const char *string)
{
    ctx.reach.clear();
    ctx.state.clear();
    ctx.history.init();
    ctx.hidx = HROOT;
    ctx.step = 0;
    ctx.rule = Rule::NONE;
    ctx.cursor = ctx.marker = string;
    ctx.sortcores.clear();
    DASSERT(ctx.worklist.empty());
    DASSERT(ctx.gor1_topsort.empty());
    DASSERT(ctx.gor1_linear.empty());
    DASSERT(ctx.gtop_heap.empty());
}

static inline regoff_t *offs_addr(regmatch_t pmatch[], size_t t)
{
    regmatch_t *m = &pmatch[t / 2 + 1];
    return t % 2 == 0 ? &m->rm_so : &m->rm_eo;
}

struct getoff_nfa_t
{
    const regoff_t *offsets;
    inline regoff_t operator()(size_t idx) const { return offsets[idx]; }
};

struct getoff_dfa_t
{
    const dfa_t *dfa;
    const regoff_t *regs;
    const regoff_t len;

    regoff_t operator()(size_t idx) const
    {
        const Tag &tag = dfa->tags[idx];
        regoff_t off;
        if (!fixed(tag)) {
            off = regs[dfa->finvers[idx]];
        }
        else {
            off = tag.base == Tag::RIGHTMOST
                ? len : regs[dfa->finvers[tag.base]];
            DASSERT (off != -1);
            off -= static_cast<regoff_t>(tag.dist);
        }
        return off;
    }
};

template<typename getoff_t>
void tags_to_submatch(const std::vector<Tag> &tags, size_t nmatch,
    regmatch_t pmatch[], regoff_t len, const getoff_t &getoff)
{
    const size_t ntags = tags.size();
    regmatch_t *m = pmatch, *e = pmatch + nmatch;

    m->rm_so = 0;
    m->rm_eo = len;
    ++m;

    for (size_t t = 0; t < ntags && m < e; t += 2) {
        const Tag &tag = tags[t];
        if (!fictive(tag)) {
            const regoff_t so = getoff(t);
            const regoff_t eo = getoff(t + 1);

            for (size_t j = tag.lsub; j <= tag.hsub && m < e; j += 2, ++m) {
                DASSERT(m - 1 == &pmatch[j / 2]);
                m->rm_so = so;
                m->rm_eo = eo;
            }
        }
    }
}

template<typename history_t>
int finalize(const simctx_t<history_t> &ctx, const char *string, size_t nmatch,
    regmatch_t pmatch[])
{
    if (ctx.rule == Rule::NONE) {
        return REG_NOMATCH;
    }

    const std::vector<Tag> &tags = ctx.nfa.tags;
    const size_t ntags = tags.size();
    bool *done = ctx.done;

    memset(done, 0, ntags * sizeof(bool));

    for (int32_t i = ctx.hidx; i != HROOT; ) {
        const typename history_t::node_t &n = ctx.history.node(i);
        i = n.pred;
        const size_t t = n.info.idx;

        // If already updated, skip.
        if (done[t]) continue;

        // Update positive tag.
        if (!n.info.neg) {
            done[t] = true;
            ctx.offsets3[t] = static_cast<regoff_t>(n.step);
        }

        // Update negative tag together with its sibling and nested tags (if any).
        else {
            const Tag &tag = tags[t];
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
void update_offsets(simctx_t<history_t> &ctx, const conf_t &c, uint32_t id)
{
    regoff_t *o;
    const std::vector<Tag> &tags = ctx.nfa.tags;
    const size_t ntags = tags.size();
    nfa_state_t *s = c.state;
    bool *done = ctx.done;

    if (s->type == nfa_state_t::FIN) {
        ctx.marker = ctx.cursor;
        ctx.rule = 0;
        o = ctx.offsets3;
    }
    else {
        o = ctx.offsets1 + id * ntags;
    }

    memcpy(o, ctx.offsets2 + c.origin * ntags, ntags * sizeof(regoff_t));
    memset(done, 0, ntags * sizeof(bool));

    for (int32_t i = c.thist; i != HROOT; ) {
        const typename history_t::node_t &n = ctx.history.node(i);
        i = n.pred;
        const size_t t = n.info.idx;

        // If already updated, skip.
        if (done[t]) continue;

        // Update positive tag.
        if (!n.info.neg) {
            done[t] = true;
            o[t] = static_cast<regoff_t>(ctx.step);
        }

        // Update negative tag together with its sibling and nested tags (if any).
        else {
            const Tag &tag = tags[t];
            for (size_t l = tag.lnest; l < tag.hnest; ++l) {
                if (!done[l]) {
                    done[l] = true;
                    o[l] = -1;
                }
            }
        }
    }
}

bool ran_or_fin_t::operator()(const conf_t &c)
{
    return c.state->type == nfa_state_t::RAN
        || c.state->type == nfa_state_t::FIN;
}

void zhistory_t::init()
{
    nodes.clear();
    nodes.push_back(node_t(NOINFO, -1, 0, 0));
    cache.clear();
}

void khistory_t::init()
{
    nodes.clear();
    nodes.push_back(node_t(NOINFO, -1));
}

template<typename ctx_t>
hidx_t zhistory_t::link(ctx_t &ctx, const typename ctx_t::conf_t &conf)
{
    const int32_t i = static_cast<int32_t>(nodes.size());
    nodes.push_back(node_t(conf.state->tag.info, conf.thist, conf.origin, ctx.step));
    return i;
}

template<typename ctx_t>
hidx_t khistory_t::link(ctx_t &/* ctx */, const typename ctx_t::conf_t &conf)
{
    const int32_t i = static_cast<int32_t>(nodes.size());
    nodes.push_back(node_t(conf.state->tag.info, conf.thist));
    return i;
}

} // namespace libre2c
} // namespace re2c

#endif // _RE2C_LIB_REGEX_IMPL_
