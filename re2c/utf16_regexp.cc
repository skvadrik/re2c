#include "re.h"
#include "utf16_range.h"
#include "utf16_regexp.h"

namespace re2c {

RegExp * UTF16Symbol(utf16::rune r)
{
	if (r <= utf16::MAX_1WORD_RUNE)
		return new MatchOp(new Range(r, r + 1));
	else
	{
		const ushort ld = utf16::lead_surr(r);
		const ushort tr = utf16::trail_surr(r);
		return new CatOp(new MatchOp(new Range(ld, ld + 1)), new MatchOp(new Range(tr, tr + 1)));
	}
}

/*
 * Split Unicode character class {[l1, h1), ..., [lN, hN)} into
 * ranges [l1, h1-1], ..., [lN, hN-1] and return alternation of
 * them. We store partially built range in suffix tree, which
 * allows to eliminate common suffixes while building.
 */
RegExp * UTF16Range(const Range * r)
{
	RangeSuffix * root = NULL;
	for (; r != NULL; r = r->next)
		UTF16splitByRuneLength(root, r->lb, r->ub - 1);
	return emit(root, NULL);
}

} // namespace re2c
