#include <stddef.h>
#include <map>

#include "src/encoding/ebcdic.h"
#include "src/encoding/enc.h"
#include "src/util/range.h"

namespace re2c {

extern std::map<uint32_t, uint32_t> unicode_to_lower;
extern std::map<uint32_t, uint32_t> unicode_to_upper;


// Returns code point representation with regard to the current policy (overwrites the argument code
// point). The code point is specified by the user; re2c validates it. A code point is invalid if it
// exceeds maximum allowed value, or if it falls into the surrogates range. In the latter case the
// current policy determines whether to ignore a surrogate, to replace it, or to fail.
//
bool Enc::validate_char(uint32_t& c) const {
    if (c >= cpoint_count()) return false;

    switch (type_) {
    case Type::ASCII:
    case Type::EBCDIC:
        return true;
    case Type::UCS2:
    case Type::UTF16:
    case Type::UTF32:
    case Type::UTF8:
        if (c < SURR_MIN || c > SURR_MAX)
            return true;
        switch (policy_) {
        case Policy::FAIL:
            return false;
        case Policy::SUBSTITUTE:
            c = UNICODE_ERROR;
            return true;
        case Policy::IGNORE:
            return true;
        }
    }

    return false; // to silence gcc warning
}

// Returns the  original representation of code point; assumes that the code point is valid.
uint32_t Enc::decode_unsafe(uint32_t c) const {
    switch (type_) {
    case Type::EBCDIC:
        c = ebcdic::ebc2asc[c & 0xFF];
        break;
    case Type::ASCII:
    case Type::UCS2:
    case Type::UTF16:
    case Type::UTF32:
    case Type::UTF8:
        break;
    }
    return c;
}

// Returns [l - h] range representation with regard to current policy. re2c validates all code
// points in the range (which is specified by the user). The function returns nullptr if range
// contains code points that exceed maximum or are forbidden by current policy, otherwise it
// returns the newly constructed range.
//
Range* Enc::validate_range(RangeMgr& rm, uint32_t l, uint32_t h) const {
    if (l >= cpoint_count() || h >= cpoint_count()) return nullptr;

    Range* r = nullptr;
    switch (type_) {
    case Type::ASCII:
    case Type::EBCDIC:
        r = rm.ran(l, h + 1);
        break;
    case Type::UCS2:
    case Type::UTF16:
    case Type::UTF32:
    case Type::UTF8:
        r = rm.ran(l, h + 1);
        if (l <= SURR_MAX && h >= SURR_MIN) {
            switch (policy_) {
            case Policy::FAIL:
                r = nullptr;
                break;
            case Policy::SUBSTITUTE:
                // exclude surrogates, add error code point
                r = rm.sub(r, rm.ran(SURR_MIN, SURR_MAX + 1));
                r = rm.add(r, rm.sym(UNICODE_ERROR));
                break;
            case Policy::IGNORE:
                break;
            }
        }
        break;
    }
    return r;
}

Range* Enc::full_range(RangeMgr& rm) const {
    Range* r = rm.ran(0, cpoint_count());
    if (policy_ != Policy::IGNORE) {
        // exclude surrogates
        r = rm.sub(r, rm.ran(SURR_MIN, SURR_MAX + 1));
    }
    return r;
}

static inline bool is_alpha(uint32_t c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

static inline uint32_t to_lower_unsafe(uint32_t c) {
    return c | 0x20u;
}

static inline uint32_t to_upper_unsafe(uint32_t c) {
    return c & ~0x20u;
}

uint32_t Enc::to_lower(uint32_t c) const {
    switch (type_) {
    case Type::UCS2:
    case Type::UTF16:
    case Type::UTF32:
    case Type::UTF8: {
        auto i = unicode_to_lower.find(c);
        if (i != unicode_to_lower.end()) {
            c = i->second;
        }
        break;
    }
    case Type::ASCII:
    case Type::EBCDIC:
        if (is_alpha(c)) {
            c = to_lower_unsafe(c);
        }
        break;
    }
    return c;
}

uint32_t Enc::to_upper(uint32_t c) const {
    switch (type_) {
    case Type::UCS2:
    case Type::UTF16:
    case Type::UTF32:
    case Type::UTF8: {
        auto i = unicode_to_upper.find(c);
        if (i != unicode_to_upper.end()) {
            c = i->second;
        }
        break;
    }
    case Type::ASCII:
    case Type::EBCDIC:
        if (is_alpha(c)) {
            c = to_upper_unsafe(c);
        }
        break;
    }
    return c;
}

// C++11 requres outer decl for ODR-used static constexpr data members (not needed in C++17).
constexpr uint32_t Enc::SURR_MIN;
constexpr uint32_t Enc::SURR_MAX;
constexpr uint32_t Enc::UNICODE_ERROR;

} // namespace re2c
