#ifndef _RE2C_UTIL_RANGE_
#define _RE2C_UTIL_RANGE_

#include <stddef.h> // NULL

#include "src/util/c99_stdint.h"
#include "src/util/forbid_copy.h"
#include "src/util/free_list.h"

namespace re2c
{

struct Range
{
	static free_list<Range*> vFreeList;

	Range * next;
	// [lb,ub)
	uint32_t lb;
	uint32_t ub;

	Range (uint32_t l, uint32_t u)
		: next (NULL)
		, lb (l)
		, ub (u)
	{
		vFreeList.insert (this);
	}
	~Range ()
	{
		vFreeList.erase (this);
	}

	FORBID_COPY (Range);
};

Range * range_union (Range * r1, Range * r2);
Range * range_diff (Range * r1, Range * r2);

} // end namespace re2c

#endif // _RE2C_UTIL_RANGE_
