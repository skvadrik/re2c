#include "src/encoding/ebcdic/ebcdic.h"
#include "src/encoding/ebcdic/ebcdic_regexp.h"
#include "src/util/range.h"


namespace re2c {

RE *EBCDICRange(RE::alc_t &alc, const Range *r)
{
    Range *s = NULL;
    for (; r; r = r->next()) {
        const uint32_t l = r->lower(), u = r->upper();
        for (uint32_t c = l; c < u; ++c) {
            s = Range::add(s, Range::sym(asc2ebc[c]));
        }
    }
    return re_sym(alc, s);
}

} // namespace re2c
