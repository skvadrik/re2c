#ifndef _RE2C_UTIL_UNIQ_VECTOR_
#define _RE2C_UTIL_UNIQ_VECTOR_

#include <vector>

#include "src/util/c99_stdint.h"

namespace re2c
{

// wrapper over std::vector
// O(n) lookup
// O(n^2) insertion
template <typename value_t>
class uniq_vector_t
{
	typedef std::vector<value_t> elems_t;
	elems_t elems;
public:
	uniq_vector_t ()
		: elems ()
	{}
	uint32_t size () const
	{
		return elems.size ();
	}
	const value_t & operator [] (uint32_t i) const
	{
		return elems[i];
	}
	uint32_t find_or_add (const value_t & v)
	{
		const uint32_t size = elems.size ();
		for (uint32_t i = 0; i < size; ++i)
		{
			if (elems[i] == v)
			{
				return i;
			}
		}
		elems.push_back (v);
		return size;
	}
};

} // namespace re2c

#endif // _RE2C_UTIL_UNIQ_VECTOR_
