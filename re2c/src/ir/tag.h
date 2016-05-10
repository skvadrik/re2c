#ifndef _RE2C_IR_TAG_
#define _RE2C_IR_TAG_

#include <string>

#include "src/util/forbid_copy.h"

namespace re2c
{

struct Tag
{
	static const size_t NONE;

	enum {VAR, FIX} type;
	size_t rule;
	const std::string *name;
	union
	{
		struct
		{
			size_t orig;
		} var;
		struct
		{
			size_t base;
			size_t dist;
		} fix;
	};

	Tag();
	FORBID_COPY(Tag);
};

void init_var_tag(Tag &tag, size_t r, const std::string *n, size_t o);
void init_fix_tag(Tag &tag, size_t r, const std::string *n, size_t b, size_t d);

} // namespace re2c

#endif // _RE2C_IR_TAG_
