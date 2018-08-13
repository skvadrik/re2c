#include <stddef.h>
#include "src/util/c99_stdint.h"

#include "src/re/encoding/range_suffix.h"
#include "src/re/encoding/utf16/utf16_range.h"
#include "src/re/encoding/utf16/utf16_regexp.h"
#include "src/util/range.h"

namespace re2c {

RE *UTF16Symbol(RE::alc_t &alc, utf16::rune r)
{
    if (r <= utf16::MAX_1WORD_RUNE) {
        return re_sym(alc, Range::sym(r));
    } else {
        const uint32_t ld = utf16::lead_surr(r);
        const uint32_t tr = utf16::trail_surr(r);
        return re_cat(alc,
            re_sym(alc, Range::sym(ld)),
            re_sym(alc, Range::sym(tr)));
    }
}

/*
 * Split Unicode character class {[l1, h1), ..., [lN, hN)} into
 * ranges [l1, h1-1], ..., [lN, hN-1] and return alternation of
 * them. We store partially built range in suffix tree, which
 * allows to eliminate common suffixes while building.
 */
RE *UTF16Range(RE::alc_t &alc, const Range *r)
{
    RangeSuffix * root = NULL;
    for (; r != NULL; r = r->next ())
        UTF16splitByRuneLength(root, r->lower (), r->upper () - 1);
    return to_regexp(alc, root);
}

} // namespace re2c
