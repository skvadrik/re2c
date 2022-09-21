#include "src/encoding/range_suffix.h"
#include "src/regexp/regexp.h"
#include "src/util/range.h"

namespace re2c {

static Regexp* emit(RESpec& spec, RangeSuffix* p, Regexp* re);

Regexp* to_regexp(RESpec& spec, RangeSuffix* p) {
    return p ? emit(spec, p, nullptr) : re_sym(spec, nullptr);
}

// Build a regexp from a suffix tree.
Regexp* emit(RESpec& spec, RangeSuffix* p, Regexp* re) {
    if (p == nullptr) return re;

    RangeMgr& rm = spec.rangemgr;
    Regexp* regexp = nullptr;
    for (; p != nullptr; p = p->next) {
        Regexp* re1 = re_cat(spec, re_sym(spec, rm.ran(p->l, p->h + 1)), re);
        regexp = re_alt(spec, regexp, emit(spec, p->child, re1));
    }
    return regexp;
}

} // namespace re2c
