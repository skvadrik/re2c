#include "src/regexp/tag.h"
#include <limits>


namespace re2c {

const size_t Tag::RIGHTMOST = std::numeric_limits<size_t>::max();
const uint32_t Tag::VARDIST = std::numeric_limits<uint32_t>::max();
const size_t Tag::FICTIVE = Tag::RIGHTMOST - 1;
const size_t Tag::NONE = Tag::RIGHTMOST - 2;


Tag::Tag(const std::string *nm, bool hi, int32_t ht)
    : name(nm)
    , lsub(Tag::RIGHTMOST)
    , hsub(Tag::RIGHTMOST)
    , base(Tag::RIGHTMOST)
    , dist(Tag::VARDIST)
    , lnest(Tag::RIGHTMOST)
    , hnest(Tag::RIGHTMOST)
    , history(hi)
    , orbit(false)
    , toplevel(false)
    , height(ht)
{}


Tag::Tag(size_t lsub, size_t hsub, bool history, bool orbit, int32_t height)
    : name(NULL)
    , lsub(lsub)
    , hsub(hsub)
    , base(Tag::RIGHTMOST)
    , dist(Tag::VARDIST)
    , lnest(Tag::RIGHTMOST)
    , hnest(Tag::RIGHTMOST)
    , history(history)
    , orbit(orbit)
    , toplevel(false)
    , height(height)
{}

} // namespace re2c
