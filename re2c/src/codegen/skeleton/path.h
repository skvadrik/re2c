#ifndef __PATH__
#define __PATH__

#include <vector>

#include "src/util/c99_stdint.h"

namespace re2c
{

namespace skeleton
{

const uint32_t NO_RULE = 0xFFFFffff;

struct Path
{
	typedef std::vector<uint32_t> chars_t;

	chars_t chars;
	uint32_t length;
	uint32_t rule;

	Path (const chars_t & cs, uint32_t l, uint32_t r);
	void update (uint32_t r);
	void extend (uint32_t r, uint32_t c);
	void append (const Path * p);
};

} // namespace skeleton

} // namespace re2c

#endif // __PATH__
