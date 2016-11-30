#ifndef _RE2C_IR_TAG_
#define _RE2C_IR_TAG_

#include <string>

#include "src/util/c99_stdint.h"

namespace re2c
{

typedef int32_t tagver_t;

static const tagver_t TAGVER_BOTTOM = -1; // default value for tag
static const tagver_t TAGVER_ZERO = 0; // absense of tag
static const tagver_t TAGVER_CURSOR = 1; // current position

struct VarTag
{
	const std::string *name;
	size_t rule;
};

struct FixTag
{
	static const size_t RIGHTMOST;

	const std::string *name;
	size_t rule;
	size_t base;
	size_t dist;
};

} // namespace re2c

#endif // _RE2C_IR_TAG_
