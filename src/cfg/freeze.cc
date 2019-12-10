#include <stddef.h>
#include <vector>

#include "src/dfa/dfa.h"
#include "src/dfa/tcmd.h"


namespace re2c {

/* note [tag freezing]
 *
 * Comparison of tag commands should be very fast (constant time):
 * many optimizations rely on this (like tunnelling, hoisting and
 * especially Moore's minimization, which compares whole classes
 * of tagged transition at once). So we bring each command to some
 * 'normal form' and insert it into common index.
 *
 * After that commands can be addressed and compared by index.
 * They also become immutable, because different commands may
 * share representation in memory.
 */
void freeze_tags(dfa_t &dfa)
{
    tcpool_t &pool = dfa.tcpool;
    const size_t
        nstate = dfa.states.size(),
        nsym = dfa.nchars;

    dfa.tcid0 = pool.insert(dfa.tcmd0);
    dfa.tcmd0 = NULL;

    for (size_t i = 0; i < nstate; ++i) {
        dfa_state_t *s = dfa.states[i];
        tcmd_t **cmd = s->tcmd,
            **const fin = cmd + nsym,
            **const fall = fin + 1;
        tcid_t *id = s->tcid = new tcid_t[nsym + 2];

        // transition commands
        for(; cmd < fin; ++cmd) {
            *id++ = pool.insert(*cmd);
        }

        // final epsilon-transition command
        *id++ = pool.insert(*fin);

        // fallback epsilon-transition command
        *id++ = pool.insert(*fall);

        s->stacid = pool.insert(s->stacmd);

        delete[] s->tcmd;
        s->tcmd = NULL;
        s->stacmd = NULL;
    }
}

} // namespace re2c

