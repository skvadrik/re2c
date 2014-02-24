#include "re.h"
#include "range_suffix.h"

namespace re2c {

free_list<RangeSuffix *> RangeSuffix::freeList;

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
			RegExp * re1 = doCat(new MatchOp(new Range(p->l, p->h + 1)), re);
			regexp = doAlt(regexp, emit(p->child, re1));
		}
		return regexp;
	}
}

} // namespace re2c
