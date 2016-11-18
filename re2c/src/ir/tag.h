#ifndef _RE2C_IR_TAG_
#define _RE2C_IR_TAG_

#include <string>

#include "src/util/c99_stdint.h"
#include "src/util/forbid_copy.h"

namespace re2c
{

typedef int32_t tagver_t;

static const tagver_t TAGVER_BOTTOM = -1; // default value for tag
static const tagver_t TAGVER_ZERO = 0; // absense of tag

struct Tag
{
	static const size_t NONE;

	enum {VAR, FIX} type;
	size_t rule;
	const std::string *name;
	struct
	{
		size_t base;
		size_t dist;
	} fix;

	Tag();
	FORBID_COPY(Tag);
};

void init_var_tag(Tag &tag, size_t r, const std::string *n);
void init_fix_tag(Tag &tag, size_t r, const std::string *n, size_t b, size_t d);

} // namespace re2c

#endif // _RE2C_IR_TAG_
