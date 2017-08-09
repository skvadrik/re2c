#ifndef _RE2C_RE_TAG_
#define _RE2C_RE_TAG_

#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <limits>
#include <string>
#include <vector>

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
	static const size_t FICTIVE;

	const std::string *name;
	size_t ncap;
	size_t base;
	size_t dist;
	bool history;
	bool orbit;

	Tag(const std::string *n, bool h)
		: name(n)
		, ncap(Tag::RIGHTMOST)
		, base(Tag::RIGHTMOST)
		, dist(Tag::VARDIST)
		, history(h)
		, orbit(false)
	{}
	Tag(size_t c, bool o)
		: name(NULL)
		, ncap(c)
		, base(Tag::RIGHTMOST)
		, dist(Tag::VARDIST)
		, history(false)
		, orbit(o)
	{}
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
