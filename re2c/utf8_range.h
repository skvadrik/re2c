#ifndef _utf8_range_h
#define _utf8_range_h

#include "utf8.h"

namespace re2c {

struct RegExp; // forward

class UTF8RangeSuffix
{
	struct node
	{
		uchar l;
		uchar h;
		node * next;
		node * child;
		
		node (uchar lo, uchar hi)
			: l     (lo)
			, h     (hi)
			, next  (NULL)
			, child (NULL)
		{
			vFreeList.insert(this);
		}
	};

	static free_list<node*> vFreeList;
	node * root;
	RegExp * regexp;

	UTF8RangeSuffix()
		: root   (NULL)
		, regexp (NULL)
	{ }

	void emit(node * p, RegExp * re);
	void addContinuous(utf8::rune l, utf8::rune h, uint n);
	void splitByContinuity(utf8::rune l, utf8::rune h, uint n);
	void splitByRuneLength(utf8::rune l, utf8::rune h);
	RegExp * toRegExp();

	friend RegExp * UTF8Range(const Range * r);
};

RegExp * UTF8Range(const Range * r);

} // namespace re2c

#endif // _utf8_range_h
