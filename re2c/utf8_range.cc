#include "re.h"
#include "utf8_range.h"

namespace re2c {

free_list<UTF8RangeSuffix::node*> UTF8RangeSuffix::vFreeList;

RegExp * UTF8RangeSuffix::toRegExp()
{
	emit(root, NULL);
	return regexp;
}

/*
 * Build regexp from suffix tree.
 */
void UTF8RangeSuffix::emit(node * p, RegExp * re)
{
	if (p == NULL)
		regexp = doAlt(regexp, re);
	else
	{
		for (; p != NULL; p = p->next)
		{
			RegExp * re1 = doCat(new MatchOp(new Range(p->l, p->h + 1)), re);
			emit(p->child, re1);
		}
	}
}

/*
 * Now that we have catenation of byte ranges [l1-h1]...[lN-hN],
 * we want to add it to existing range, merging suffixes on the fly.
 */
void UTF8RangeSuffix::addContinuous(utf8::rune l, utf8::rune h, uint n)
{
	uchar cl[utf8::MAX_BYTES];
	uchar ch[utf8::MAX_BYTES];
	utf8::rune_to_bytes(cl, l);
	utf8::rune_to_bytes(ch, h);

	node ** p = &root;
	for (int i = n - 1; i >= 0; --i)
	{
		for (;;)
		{
			if (*p == NULL)
			{
				*p = new node(cl[i], ch[i]);
				p = &(*p)->child;
				break;
			}
			else if ((*p)->l == cl[i] && (*p)->h == ch[i])
			{
				p = &(*p)->child;
				break;
			}
			else
				p = &(*p)->next;
		}
	}
}

/*
 * Split range into sub-ranges that agree on leading bytes.
 *
 * We have two Unicode runes of equal length, L and H, which
 * map to UTF-8 sequences 'L_1 ... L_n' and 'H_1 ... H_n'.
 * We want to represent Unicode range [L - H] as a catenation
 * of byte ranges [L_1 - H_1], ..., [L_n - H_n].
 *
 * This is only possible if for all i > 1:
 * if L_i /= H_i, then L_(i-1) == 0x80 and H_(i-1) == 0xbf.
 * This condition ensures that:
 * 	1) all possible UTF-8 sequences between L and H are allowed
 * 	2) no byte ranges [b1 - b2] appear, such that b1 > b2
 *
 * E.g.:
 * [\U000e0031-\U000e0043] => [f3-f3],[a0-a0],[80-81],[b1-83].
 * The last byte range, [b1-83], is incorrect: its lower bound
 * is greater than its upper bound. To fix this, we must split
 * the original range into two sub-ranges:
 * [\U000e0031-\U000e003f] => [f3-f3],[a0-a0],[80-80],[b1-bf]
 * [\U000e0040-\U000e0043] => [f3-f3],[a0-a0],[81-81],[80-83]
 *
 * This function finds all such 'points of discontinuity'
 * and represents original range as alternation of continuous
 * sub-ranges.
 */
void UTF8RangeSuffix::splitByContinuity(utf8::rune l, utf8::rune h, uint n)
{
	for (uint i = 1; i < n; ++i)
	{
		uint m = (1 << (6 * i)) - 1; // last i bytes of a UTF-8 sequence
		if ((l & ~m) != (h & ~m))
		{
			if ((l & m) != 0)
			{
				splitByContinuity(l, l | m, n);
				splitByContinuity((l | m) + 1, h, n);
				return;
			}
			if ((h & m) != m)
			{
				splitByContinuity(l, (h & ~m) - 1, n);
				splitByContinuity(h & ~m, h, n);
				return;
			}
		}
	}
	addContinuous(l, h, n);
}

/*
 * Split range into sub-ranges, so that all runes in the same
 * sub-range have equal length of UTF-8 sequence. E.g., full
 * Unicode range [0-0x10FFFF] gets split into sub-ranges:
 * [0 - 0x7F]           (1-byte UTF-8 sequences)
 * [0x80 - 0x7FF]       (2-byte UTF-8 sequences)
 * [0x800 - 0xFFFF]     (3-byte UTF-8 sequences)
 * [0x10000 - 0x10FFFF] (4-byte UTF-8 sequences)
 */
void UTF8RangeSuffix::splitByRuneLength(utf8::rune l, utf8::rune h)
{
	const uint nh = utf8::rune_length(h);
	for (uint nl = utf8::rune_length(l); nl < nh; ++nl)
	{
		utf8::rune r = utf8::max_rune(nl);
		splitByContinuity(l, r, nl);
		l = r + 1;
	}
	splitByContinuity(l, h, nh);
}

/*
 * Split Unicode character class {[l1, h1), ..., [lN, hN)} into
 * ranges [l1, h1-1], ..., [lN, hN-1] and return alternation of
 * them. We store partially built range in suffix tree, which
 * allows to eliminate common suffixes while building.
 *
 * Assumes that incoming range is not empty.
 */
RegExp * UTF8Range(const Range * r)
{
	UTF8RangeSuffix t;
	t.splitByRuneLength(r->lb, r->ub - 1);
	while ((r = r->next) != NULL)
		t.splitByRuneLength(r->lb, r->ub - 1);
	return t.toRegExp();
}

} // namespace re2c
