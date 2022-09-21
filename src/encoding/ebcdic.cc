#include <stddef.h>
#include <stdint.h>

#include "src/encoding/ebcdic.h"
#include "src/regexp/regexp.h"
#include "src/util/range.h"

namespace re2c {
namespace ebcdic {

Regexp* range(RESpec& spec, const Range* r) {
    RangeMgr& rm = spec.rangemgr;

    Range* s = nullptr;
    for (; r; r = r->next()) {
        const uint32_t l = r->lower(), u = r->upper();
        for (uint32_t c = l; c < u; ++c) {
            s = rm.add(s, rm.sym(asc2ebc[c]));
        }
    }
    return re_sym(spec, s);
}

} // namespace ebcdic
} // namespace re2c
