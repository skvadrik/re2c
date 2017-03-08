#ifndef _RE2C_RE_TAG_
#define _RE2C_RE_TAG_

#include <limits>
#include <string>
#include <vector>

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
	size_t ncap;
	size_t base;
	size_t dist;

	explicit Tag(const std::string *n)
		: name(n)
		, ncap(Tag::RIGHTMOST)
		, base(Tag::RIGHTMOST)
		, dist(Tag::VARDIST)
	{}
	explicit Tag(size_t c)
		: name(NULL)
		, ncap(c)
		, base(Tag::RIGHTMOST)
		, dist(Tag::VARDIST)
	{}
};

inline bool fixed(const Tag &tag)
{
	return tag.dist != Tag::VARDIST;
}

inline bool capture(const Tag &tag)
{
	return tag.ncap != Tag::RIGHTMOST;
}

inline bool orbit(const Tag &tag)
{
	return capture(tag) && tag.ncap % 3 == 2;
}

inline bool trailing(const Tag &tag)
{
	return !capture(tag) && tag.name == NULL;
}

inline bool preorbit(const std::vector<Tag> &tags, size_t idx)
{
	const size_t ncap = tags[idx].ncap;
	return ncap % 3 == 0
		&& idx + 2 < tags.size()
		&& tags[idx + 2].ncap == ncap + 2;
}

} // namespace re2c

#endif // _RE2C_RE_TAG_
