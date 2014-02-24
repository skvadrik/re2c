#include "re.h"
#include "utf8_range.h"

namespace re2c {

/*
 * Now that we have catenation of byte ranges [l1-h1]...[lN-hN],
 * we want to add it to existing range, merging suffixes on the fly.
 */
void UTF8addContinuous(RangeSuffix * & root, utf8::rune l, utf8::rune h, uint n)
{
	uchar cl[utf8::MAX_RUNE_LENGTH];
	uchar ch[utf8::MAX_RUNE_LENGTH];
	utf8::rune_to_bytes(cl, l);
	utf8::rune_to_bytes(ch, h);

	RangeSuffix ** p = &root;
	for (int i = n - 1; i >= 0; --i)
	{
		for (;;)
		{
			if (*p == NULL)
			{
				*p = new RangeSuffix(cl[i], ch[i]);
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
 * if L_i /= H_i, then L_(i+1) == 0x80 and H_(i+1) == 0xbf.
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
void UTF8splitByContinuity(RangeSuffix * & root, utf8::rune l, utf8::rune h, uint n)
{
	for (uint i = 1; i < n; ++i)
	{
		uint m = (1 << (6 * i)) - 1; // last i bytes of a UTF-8 sequence
		if ((l & ~m) != (h & ~m))
		{
			if ((l & m) != 0)
			{
				UTF8splitByContinuity(root, l, l | m, n);
				UTF8splitByContinuity(root, (l | m) + 1, h, n);
				return;
			}
			if ((h & m) != m)
			{
				UTF8splitByContinuity(root, l, (h & ~m) - 1, n);
				UTF8splitByContinuity(root, h & ~m, h, n);
				return;
			}
		}
	}
	UTF8addContinuous(root, l, h, n);
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
void UTF8splitByRuneLength(RangeSuffix * & root, utf8::rune l, utf8::rune h)
{
	const uint nh = utf8::rune_length(h);
	for (uint nl = utf8::rune_length(l); nl < nh; ++nl)
	{
		utf8::rune r = utf8::max_rune(nl);
		UTF8splitByContinuity(root, l, r, nl);
		l = r + 1;
	}
	UTF8splitByContinuity(root, l, h, nh);
}

} // namespace re2c
