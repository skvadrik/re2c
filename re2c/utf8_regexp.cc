#include "re.h"
#include "utf8_range.h"
#include "utf8_regexp.h"

namespace re2c {

RegExp * UTF8Symbol(utf8::rune r)
{
	uchar chars[utf8::MAX_RUNE_LENGTH];
	const int chars_count = utf8::rune_to_bytes(chars, r);
	RegExp * re = new MatchOp(new Range(chars[0], chars[0] + 1));
	for (int i = 1; i < chars_count; ++i)
		re = new CatOp(re, new MatchOp(new Range(chars[i], chars[i] + 1)));
	return re;
}

/*
 * Split Unicode character class {[l1, h1), ..., [lN, hN)} into
 * ranges [l1, h1-1], ..., [lN, hN-1] and return alternation of
 * them. We store partially built range in suffix tree, which
 * allows to eliminate common suffixes while building.
 */
RegExp * UTF8Range(const Range * r)
{
	RangeSuffix * root = NULL;
	for (; r != NULL; r = r->next)
		UTF8splitByRuneLength(root, r->lb, r->ub - 1);
	return emit(root, NULL);
}

} // namespace re2c
