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

struct tag_info_t {
    uint32_t idx; // tag index (starting from zero)
    uint32_t neg; // tag sign (1 for negative, 0 for positive)
};

struct Tag
{
    static const size_t RIGHTMOST;
    static const uint32_t VARDIST;
    static const size_t FICTIVE;
    static const size_t NONE;

    const std::string *name;
    size_t lsub;
    size_t hsub;
    size_t base;
    size_t dist;
    size_t lnest;
    size_t hnest;
    bool history;
    bool orbit;
    bool toplevel;
    int32_t height;

    Tag(const std::string *nm, bool hi, int32_t ht);
    Tag(size_t lsub, size_t hsub, bool history, bool orbit, int32_t height);
};

inline bool operator == (const tag_info_t &x, const tag_info_t &y)
{
    return x.idx == y.idx && x.neg == y.neg;
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
