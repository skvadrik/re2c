#include "src/ir/regexp/encoding/range_suffix.h"
#include "src/ir/regexp/regexp.h"
#include "src/util/range.h"

namespace re2c {

static const RegExp *emit(uint32_t l, uint32_t c, RangeSuffix * p, const RegExp * re);

free_list<RangeSuffix *> RangeSuffix::freeList;

const RegExp *to_regexp(uint32_t l, uint32_t c, RangeSuffix * p)
{
	return p ? emit(l, c, p, NULL)
		: RegExp::make_sym(l, c, NULL);
}

/*
 * Build regexp from suffix tree.
 */
const RegExp *emit(uint32_t l, uint32_t c, RangeSuffix * p, const RegExp * re)
{
	if (p == NULL) {
		return re;
	} else {
		const RegExp *regexp = NULL;
		for (; p != NULL; p = p->next) {
			const RegExp *re1 = RegExp::make_cat(
				RegExp::make_sym(l, c, Range::ran(p->l, p->h + 1)), re);
			regexp = RegExp::make_alt(regexp, emit(l, c, p->child, re1));
		}
		return regexp;
	}
}

} // namespace re2c
