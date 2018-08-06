#ifndef _RE2C_RE_TAG_
#define _RE2C_RE_TAG_

#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <limits>
#include <string>

namespace re2c
{

typedef int32_t tagver_t;


static const tagver_t TAGVER_BOTTOM = std::numeric_limits<tagver_t>::min(); // default value, lowest priority
static const tagver_t TAGVER_ZERO = 0; // absense of tag
static const tagver_t TAGVER_CURSOR = std::numeric_limits<tagver_t>::max(); // current position, highest priority


struct tag_info_t
{
	uint32_t idx : 31;
	uint32_t neg : 1;
};


struct Tag
{
	static const size_t RIGHTMOST;
	static const size_t VARDIST;
	static const size_t FICTIVE;

	const std::string *name;
	size_t ncap;
	size_t base;
	size_t dist;
	bool history;
	bool orbit;
	uint32_t height;

	Tag(const std::string *nm, bool hi, uint32_t ht);
	Tag(size_t nc, bool ob, uint32_t ht);
};


inline bool fixed(const Tag &tag)
{
	return tag.dist != Tag::VARDIST;
}


inline bool fictive(const Tag &tag)
{
	return tag.ncap == Tag::FICTIVE;
}


inline bool capture(const Tag &tag)
{
	return tag.ncap != Tag::RIGHTMOST;
}


inline bool orbit(const Tag &tag)
{
	return tag.orbit;
}


inline bool trailing(const Tag &tag)
{
	return !capture(tag) && tag.name == NULL;
}


inline bool history(const Tag &tag)
{
	return tag.history;
}

} // namespace re2c

#endif // _RE2C_RE_TAG_
