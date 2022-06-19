#ifndef _RE2C_UTIL_HASH32_
#define _RE2C_UTIL_HASH32_

#include <stddef.h>
#include <stdint.h>

namespace re2c {

static inline uint32_t hash4(uint32_t h, uint32_t k) {
    return h ^ ((h << 5) + (h >> 2) + k);
}

// hash in 4-byte chunks for speed
inline uint32_t hash32(uint32_t h, const void* data, size_t size) {
    static constexpr uintptr_t ALIGN = sizeof(uint32_t);
    static constexpr uintptr_t MASK = ~(ALIGN - 1);

    uintptr_t p = reinterpret_cast<uintptr_t>(data);
    const uintptr_t e = p + size;

    // first aligned address in range
    const uintptr_t p1 = (p + ALIGN - 1) & MASK;

    // last aligned address in range
    const uintptr_t p2 = e & MASK;

    for (; p < p1; ++p) {
        h = hash4(h, *reinterpret_cast<uint8_t*>(p));
    }
    for (; p < p2; p += 4) {
        h = hash4(h, *reinterpret_cast<uint32_t*>(p));
    }
    for (; p < e; ++p) {
        h = hash4(h, *reinterpret_cast<uint8_t*>(p));
    }

    return h;
}

} // namespace re2c

#endif // _RE2C_UTIL_HASH32_
