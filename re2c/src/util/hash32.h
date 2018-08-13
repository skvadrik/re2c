#ifndef _RE2C_UTIL_HASH32_
#define _RE2C_UTIL_HASH32_

#include <stddef.h>
#include "src/util/c99_stdint.h"

namespace re2c
{

inline uint32_t hash32(uint32_t h, const void *data, size_t size)
{
    const uint8_t *bytes = static_cast<const uint8_t*>(data);
    for (size_t i = 0; i < size; ++i) {
        h = h ^ ((h << 5) + (h >> 2) + bytes[i]);
    }
    return h;
}

} // namespace re2c

#endif // _RE2C_UTIL_HASH32_
