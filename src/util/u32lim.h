#ifndef _RE2C_UTIL_U32LIM_
#define _RE2C_UTIL_U32LIM_

#include <stdint.h>

namespace re2c {

// uint32_t truncated to LIMIT. Any overflow (either result of a binary operation or conversion from
// another type) results in LIMIT (LIMIT is a fixpoint).
template<uint32_t LIMIT>
class u32lim_t {
    uint32_t value;
    explicit u32lim_t(uint32_t x): value(x < LIMIT ? x : LIMIT) {}
    explicit u32lim_t(uint64_t x): value(x < LIMIT ? static_cast<uint32_t>(x) : LIMIT) {}

  public:
    // Implicit conversion is forbidden, because operands should be converted before operation:
    //     uint32_t x, y; ... u32lim_t z = x + y;
    // would result in 32-bit addition and may overflow. Don't export overloaded constructors: it
    // breaks OS X builds (size_t causes resolution ambiguity).
    static u32lim_t from32(uint32_t x) { return u32lim_t(x); }
    static u32lim_t from64(uint64_t x) { return u32lim_t(x); }

    static u32lim_t limit() { return u32lim_t(LIMIT); }

    uint32_t uint32() const { return value; }

    bool overflow() const {
        return value == LIMIT;
    }

    friend u32lim_t operator+(u32lim_t x, u32lim_t y) {
        const uint64_t z = static_cast<uint64_t>(x.value) + static_cast<uint64_t>(y.value);
        return z < LIMIT ? u32lim_t(z): u32lim_t(LIMIT);
    }

    friend u32lim_t operator * (u32lim_t x, u32lim_t y) {
        const uint64_t z = static_cast<uint64_t>(x.value) * static_cast<uint64_t>(y.value);
        return z < LIMIT ? u32lim_t(z) : u32lim_t(LIMIT);
    }

    friend bool operator < (u32lim_t x, u32lim_t y) {
        return x.value < y.value;
    }
};

} // namespace re2c

#endif // _RE2C_UTIL_U32LIM_
