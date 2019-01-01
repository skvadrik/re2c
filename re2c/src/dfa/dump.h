#ifndef _RE2C_DFA_DUMP_
#define _RE2C_DFA_DUMP_

#include <stddef.h>
#include "src/util/c99_stdint.h"

namespace re2c
{

struct determ_context_t;
struct dfa_t;
struct opt_t;
struct tcmd_t;

struct closure_stats_t
{
    uint32_t nscans;   // number of configuration scans
    uint32_t nprec;    // number of POSIX comparisons of configurations
    size_t length;     // total length of compared histories
};

struct dump_dfa_t
{
    const bool debug;
    uint32_t uniqidx;

    explicit dump_dfa_t(const opt_t *);
    ~dump_dfa_t();
    void state(const determ_context_t &, bool);
};

void dump_dfa(const dfa_t &dfa);
void dump_tcmd(const tcmd_t *p);


#ifndef RE2C_DEBUG

#define DRESET_CLSTATS(ctx)
#define DDUMP_CLSTATS(ctx)
#define DINCCOUNT_CLSCANS(ctx)
#define DINCCOUNT_CLPREC(ctx)
#define DINCCOUNT_CLLENGTH(ctx, len)

#else // RE2C_DEBUG

#define DRESET_CLSTATS(ctx)            reset_clstats(ctx)
#define DDUMP_CLSTATS(ctx)             dump_clstats(ctx)
#define DINCCOUNT_CLSCANS(ctx)         ++ctx.dc_clstats.nscans
#define DINCCOUNT_CLPREC(ctx)          ++ctx.dc_clstats.nprec
#define DINCCOUNT_CLLENGTH(ctx, len)   ctx.dc_clstats.length += len

void reset_clstats(determ_context_t &);
void dump_clstats(const determ_context_t &);

#endif // RE2C_DEBUG


} // namespace re2c

#endif // _RE2C_DFA_DUMP_
