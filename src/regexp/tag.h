#ifndef _RE2C_RE_TAG_
#define _RE2C_RE_TAG_

#include <stddef.h>
#include "src/util/c99_stdint.h"
#include "src/util/static_assert.h"
#include <limits>
#include <string>


namespace re2c {

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
    size_t lsub;
    size_t hsub;
    size_t base;
    size_t dist;
    size_t lnest;
    size_t hnest;
    bool history;
    bool orbit;
    int32_t height;

    Tag(const std::string *nm, bool hi, int32_t ht);
    Tag(size_t lsub, size_t hsub, bool ob, int32_t ht);
};

inline bool operator == (const tag_info_t &x, const tag_info_t &y)
{
    // per-component comparison is slower
    RE2C_STATIC_ASSERT(sizeof(tag_info_t) == sizeof(uint32_t));
    return *reinterpret_cast<const uint32_t*>(&x)
        == *reinterpret_cast<const uint32_t*>(&y);
}

inline bool fixed(const Tag &tag)
{
    return tag.dist != Tag::VARDIST;
}

inline bool fictive(const Tag &tag)
{
    return tag.lsub == Tag::FICTIVE;
}

inline bool capture(const Tag &tag)
{
    return tag.lsub != Tag::RIGHTMOST;
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
