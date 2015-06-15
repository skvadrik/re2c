#ifndef _RE2C_UTIL_RANGE_
#define _RE2C_UTIL_RANGE_

#include <stddef.h> // NULL

#include "src/util/c99_stdint.h"
#include "src/util/forbid_copy.h"
#include "src/util/free_list.h"

namespace re2c
{

class Range
{
public:
	static free_list<Range*> vFreeList;

private:
	Range * nx;
	// [lb,ub)
	uint32_t lb;
	uint32_t ub;

public:
	Range (uint32_t l, uint32_t u)
		: nx (NULL)
		, lb (l)
		, ub (u)
	{
		vFreeList.insert (this);
	}
	~Range ()
	{
		vFreeList.erase (this);
	}
	Range * next () const { return nx; }
	uint32_t lower () const { return lb; }
	uint32_t upper () const { return ub; }
	friend Range * range_union (Range * r1, Range * r2);
	friend Range * range_diff (Range * r1, Range * r2);

	FORBID_COPY (Range);
};

} // end namespace re2c

#endif // _RE2C_UTIL_RANGE_
