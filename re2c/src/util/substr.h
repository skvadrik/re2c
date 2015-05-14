#ifndef __SUBSTR__
#define __SUBSTR__

#include "src/util/c99_stdint.h"
#include "src/util/forbid_copy.h"

namespace re2c
{

class SubStr
{
public:
	const char * str;
	const char * const org;
	uint32_t len;

	inline SubStr (const char * s, uint32_t l)
		: str (s)
		, org (s)
		, len (l)
	{}
	inline uint32_t ofs () const
	{
		return str - org;
	}

	FORBID_COPY (SubStr);
};

} // namespace re2c

#endif // __SUBSTR__
