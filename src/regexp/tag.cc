#include "src/regexp/tag.h"
#include <limits>

namespace re2c
{

const size_t Tag::RIGHTMOST = std::numeric_limits<size_t>::max();
const size_t Tag::VARDIST = std::numeric_limits<size_t>::max();
const size_t Tag::FICTIVE = Tag::RIGHTMOST - 1;


Tag::Tag(const std::string *nm, bool hi, int32_t ht)
    : name(nm)
    , ncap(Tag::RIGHTMOST)
    , base(Tag::RIGHTMOST)
    , dist(Tag::VARDIST)
    , history(hi)
    , orbit(false)
    , height(ht)
{}


Tag::Tag(size_t nc, bool ob, int32_t ht)
    : name(NULL)
    , ncap(nc)
    , base(Tag::RIGHTMOST)
    , dist(Tag::VARDIST)
    , history(false)
    , orbit(ob)
    , height(ht)
{}

} // namespace re2c
