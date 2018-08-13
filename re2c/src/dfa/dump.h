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

} // namespace re2c

#endif // _RE2C_DFA_DUMP_
