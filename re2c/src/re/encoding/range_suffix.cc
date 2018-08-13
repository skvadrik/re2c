#include "src/re/encoding/range_suffix.h"
#include "src/util/range.h"

namespace re2c {

static RE *emit(RE::alc_t &alc, RangeSuffix *p, RE *re);

free_list<RangeSuffix *> RangeSuffix::freeList;

RE *to_regexp(RE::alc_t &alc, RangeSuffix *p)
{
    return p ? emit(alc, p, NULL) : re_sym(alc, NULL);
}

/*
 * Build regexp from suffix tree.
 */
RE *emit(RE::alc_t &alc, RangeSuffix *p, RE *re)
{
    if (p == NULL) {
        return re;
    } else {
        RE *regexp = NULL;
        for (; p != NULL; p = p->next) {
            RE *re1 = re_cat(alc, re_sym(alc, Range::ran(p->l, p->h + 1)), re);
            regexp = re_alt(alc, regexp, emit(alc, p->child, re1));
        }
        return regexp;
    }
}

} // namespace re2c
