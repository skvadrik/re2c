#include <stddef.h>
#include <vector>

#include "src/dfa/dfa.h"
#include "src/dfa/tcmd.h"

namespace re2c {

// note [tag freezing]
//
// Comparison of tag commands should be very fast (constant time): many optimizations rely on this
// (like tunnelling, hoisting and especially Moore's minimization, which compares whole classes of
// tagged transition at once). So we bring each command to some 'normal form' and insert it into
// common index. After that commands can be addressed and compared by index. They also become
// immutable, because different commands may share representation in memory.

void freeze_tags(Tdfa& dfa) {
    tcpool_t& pool = dfa.tcpool;
    const size_t nsym = dfa.nchars;

    for (TdfaState* s : dfa.states) {
        tcmd_t** cmd = s->tcmd,
                 **const fin = cmd + nsym,
                         **const fall = fin + 1;
        tcid_t* id = s->tcid = new tcid_t[nsym + 2];

        // transition commands
        for(; cmd < fin; ++cmd) {
            *id++ = pool.insert(*cmd);
        }

        // final epsilon-transition command
        *id++ = pool.insert(*fin);

        // fallback epsilon-transition command
        *id++ = pool.insert(*fall);

        delete[] s->tcmd;
        s->tcmd = nullptr;
    }
}

} // namespace re2c

