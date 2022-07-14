#include <stddef.h>
#include <stdint.h>

#include "src/cfg/cfg.h"
#include "src/debug/debug.h"
#include "src/dfa/dfa.h"
#include "src/options/opt.h"
#include "src/regexp/tag.h"

namespace re2c {

void compact_and_optimize_tags(const opt_t* opts, Tdfa& dfa) {
    tagver_t maxver = dfa.maxtagver;
    if (maxver > 0) {
        cfg_t cfg(dfa);

        size_t nver = static_cast<size_t>(maxver) + 1;
        tagver_t* ver2new = new tagver_t[nver];

        maxver = cfg_t::compact(cfg, ver2new);
        cfg_t::renaming(cfg, ver2new, maxver);

        if (opts->optimize_tags && maxver > 0) {
            nver = static_cast<size_t>(maxver) + 1;
            bool* live = new bool[cfg.nbbfall * nver];
            bool* interf = new bool[nver * nver];

            static constexpr uint32_t NPASS = 2;
            for (uint32_t n = 0; n < NPASS; ++n) {

                cfg_t::liveness_analysis(cfg, live);
                DDUMP_CFG(opts, cfg, live);

                cfg_t::dead_code_elimination(cfg, live);

                cfg_t::interference(cfg, live, interf);
                DDUMP_INTERF(opts, cfg, interf);

                maxver = cfg_t::variable_allocation(cfg, interf, ver2new);

                cfg_t::renaming(cfg, ver2new, maxver);

                cfg_t::normalization(cfg);
            }

            delete[] live;
            delete[] interf;
        }

        delete[] ver2new;
    }
}

} // namespace re2c

