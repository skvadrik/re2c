#include "src/ir/regexp/encoding/range_suffix.h"
#include "src/ir/regexp/regexp.h"
#include "src/util/range.h"

namespace re2c {

static RegExp * emit (RangeSuffix * p, RegExp * re);

free_list<RangeSuffix *> RangeSuffix::freeList;

RegExp * to_regexp (RangeSuffix * p)
{
	return p
		? emit (p, NULL)
		: RegExp::sym(NULL);
}

/*
 * Build regexp from suffix tree.
 */
RegExp * emit(RangeSuffix * p, RegExp * re)
{
	if (p == NULL)
		return re;
	else
	{
		RegExp * regexp = NULL;
		for (; p != NULL; p = p->next)
		{
			RegExp * re1 = doCat(RegExp::sym(Range::ran (p->l, p->h + 1)), re);
			regexp = doAlt(regexp, emit(p->child, re1));
		}
		return regexp;
	}
}

} // namespace re2c
