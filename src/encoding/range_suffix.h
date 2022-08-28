#ifndef _RE2C_RE_ENCODING_RANGE_SUFFIX_
#define _RE2C_RE_ENCODING_RANGE_SUFFIX_

#include <stddef.h>
#include <stdint.h>

#include "src/util/forbid_copy.h"

namespace re2c {

struct Regexp;
struct RESpec;

struct RangeSuffix {
    uint32_t l;
    uint32_t h;
    RangeSuffix* next;
    RangeSuffix* child;

    FORBID_COPY(RangeSuffix);
};

template<typename Allocator>
RangeSuffix* make_range_suffix(Allocator& alc, uint32_t lo, uint32_t hi) {
    RangeSuffix* p = alc.template alloct<RangeSuffix>(1);
    p->l = lo;
    p->h = hi;
    p->next = nullptr;
    p->child = nullptr;
    return p;
}

Regexp* to_regexp(RESpec& spec, RangeSuffix* p);

} // namespace re2c

#endif // _RE2C_RE_ENCODING_RANGE_SUFFIX_
