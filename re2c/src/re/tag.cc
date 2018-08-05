#include "src/re/tag.h"
#include <assert.h>
#include <limits>

namespace re2c
{

static uint32_t fix_height(size_t, uint32_t);


const size_t Tag::RIGHTMOST = std::numeric_limits<size_t>::max();
const size_t Tag::VARDIST = std::numeric_limits<size_t>::max();
const size_t Tag::FICTIVE = Tag::RIGHTMOST - 1;


Tag::Tag(const std::string *nm, bool hi, uint32_t ht)
	: name(nm)
	, ncap(Tag::RIGHTMOST)
	, base(Tag::RIGHTMOST)
	, dist(Tag::VARDIST)
	, history(hi)
	, orbit(false)
	, height(fix_height(ncap, ht))
{}


Tag::Tag(size_t nc, bool ob, uint32_t ht)
	: name(NULL)
	, ncap(nc)
	, base(Tag::RIGHTMOST)
	, dist(Tag::VARDIST)
	, history(false)
	, orbit(ob)
	, height(fix_height(ncap, ht))
{}


uint32_t fix_height(size_t ncap, uint32_t height)
{
	// height of the closing parenthesis is one less
	// than height of the opening parenthesis
	return ncap % 2 == 0 ? height + 1 : height;
}

} // namespace re2c
