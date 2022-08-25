#ifndef _RE2C_DEBUG_DEBUG_
#define _RE2C_DEBUG_DEBUG_

#ifndef RE2C_DEBUG

namespace re2c {

struct opt_t;

struct closure_stats_t {};

struct dump_dfa_t {
    dump_dfa_t(const opt_t*) {}
};

template<typename ctx_t>
struct dump_dfa_tree_t {
    dump_dfa_tree_t(const ctx_t&) {}
};

#define DDUMP_NFA(opts, nfa)
#define DDUMP_DFA_TREE(isnew)
#define DDUMP_DFA_RAW(ctx, isnew)
#define DDUMP_DFA_DET(opts, dfa)
#define DDUMP_DFA_TAGOPT(opts, dfa)
#define DDUMP_DFA_MIN(opts, dfa)
#define DDUMP_ADFA(opts, adfa)
#define DDUMP_CLSTATS(ctx)
#define DDUMP_CFG(opts, cfg, live)
#define DDUMP_INTERF(opts, cfg, itf)
#define DINCCOUNT_CLSCANS(ctx)
#define DINCCOUNT_CLPREC(ctx)
#define DINCCOUNT_CLLENGTH(ctx, len)
#define DRESET_CLSTATS(ctx)

} // namespace re2c

#else // RE2C_DEBUG

#include <stdint.h>
#include <stddef.h>
#include <map>
#include <set>
#include <vector>

namespace re2c {

struct Adfa;
struct cfg_t;
struct Tdfa;
struct Tnfa;
struct TnfaState;
struct opt_t;
struct tcmd_t;
struct Tag;

struct closure_stats_t {
    uint32_t nscans; // number of configuration scans
    uint32_t nprec;  // number of POSIX comparisons of configurations
    size_t length;   // total length of compared histories
};

struct dump_dfa_t {
    const bool debug;
    uint32_t uniqidx;

    explicit dump_dfa_t(const opt_t*);
    ~dump_dfa_t();
    template<typename ctx_t> void state(const ctx_t&, bool);
};

template<typename ctx_t>
struct dump_dfa_tree_t {
    const ctx_t& ctx;

    using origins_t = std::vector<const TnfaState*>;
    using origmap_t = std::map<std::pair<uint32_t, uint32_t>, origins_t>;
    origmap_t origmap;

    uint32_t uniqidx;
    std::set<int32_t> used_nodes;

    explicit dump_dfa_tree_t(const ctx_t&);
    ~dump_dfa_tree_t();
    void state(bool);
    void path_tree(const std::vector<uint32_t>&, const std::vector<uint32_t>&, bool);
};

#define DDUMP_NFA(opts, nfa)         if (opts->dump_nfa) dump_nfa(nfa)
#define DDUMP_DFA_TREE(isnew)        do { ctx.dump_dfa_tree.state(is_new); } while(0)
#define DDUMP_DFA_RAW(ctx, isnew)    do { ctx.dump.state(ctx, is_new); } while(0)
#define DDUMP_DFA_DET(opts, dfa)     if (opts->dump_dfa_det) dump_dfa(dfa)
#define DDUMP_DFA_TAGOPT(opts, dfa)  if (opts->dump_dfa_tagopt) dump_dfa(dfa)
#define DDUMP_DFA_MIN(opts, dfa)     if (opts->dump_dfa_min) dump_dfa(dfa)
#define DDUMP_ADFA(opts, adfa)       if (opts->dump_adfa) dump_adfa(adfa)
#define DDUMP_CLSTATS(ctx)           dump_clstats(ctx)
#define DDUMP_CFG(opts, cfg, live)   if (opts->dump_cfg) dump_cfg(cfg, live)
#define DDUMP_INTERF(opts, cfg, itf) if (opts->dump_interf) dump_interf(cfg, itf)
#define DINCCOUNT_CLSCANS(ctx)       ++ctx.clstats.nscans
#define DINCCOUNT_CLPREC(ctx)        ++ctx.clstats.nprec
#define DINCCOUNT_CLLENGTH(ctx, len) ctx.clstats.length += len
#define DRESET_CLSTATS(ctx)          reset_clstats(ctx)

void dump_nfa(const Tnfa&);
void dump_dfa(const Tdfa&);
void dump_adfa(const Adfa&);
void dump_cfg(const cfg_t&, const bool*);
void dump_interf(const cfg_t&, const bool*);
void dump_tcmd(const tcmd_t*);
void dump_tag(const Tag& tag, bool negative);
template<typename ctx_t> void dump_clstats(const ctx_t&);
template<typename ctx_t> void reset_clstats(ctx_t&);

} // namespace re2c

#endif // RE2C_DEBUG

#endif // _RE2C_DEBUG_DEBUG_
