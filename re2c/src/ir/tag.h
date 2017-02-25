#ifndef _RE2C_IR_TAG_
#define _RE2C_IR_TAG_

#include <limits>
#include <string>

#include "src/util/c99_stdint.h"

namespace re2c
{

typedef int32_t tagver_t;

static const tagver_t TAGVER_BOTTOM = std::numeric_limits<tagver_t>::min(); // default value, lowest priority
static const tagver_t TAGVER_ZERO = 0; // absense of tag
static const tagver_t TAGVER_CURSOR = std::numeric_limits<tagver_t>::max(); // current position, highest priority

struct Tag
{
	static const size_t RIGHTMOST;
	static const size_t VARDIST;

	const std::string *name;
	size_t base;
	size_t dist;
};

inline bool fixed(const Tag &tag)
{
	return tag.dist != Tag::VARDIST;
}

} // namespace re2c

#endif // _RE2C_IR_TAG_
