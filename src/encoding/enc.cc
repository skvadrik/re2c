#include <stddef.h>

#include "src/encoding/ebcdic/ebcdic.h"
#include "src/encoding/enc.h"
#include "src/util/range.h"


namespace re2c {

const uint32_t Enc::SURR_MIN = 0xD800;
const uint32_t Enc::SURR_MAX = 0xDFFF;
const uint32_t Enc::UNICODE_ERROR = 0xFFFD;

/*
 * Returns code point representation with regard to current policy.
 *
 * Since code point is specified by user, it is assumed that the user
 * considers it to be valid. re2c must check it.
 *
 * Returns false if this code point exceeds maximum or is forbidden
 * by current policy, otherwise returns true. Overwrites code point.
 */
bool Enc::validateChar(uint32_t &c) const
{
    if (c >= nCodePoints()) return false;

    switch (type_) {
        case ASCII:
        case EBCDIC:
            return true;
        case UCS2:
        case UTF16:
        case UTF32:
        case UTF8:
            if (c < SURR_MIN || c > SURR_MAX)
                return true;
            switch (policy_) {
                case POLICY_FAIL:
                    return false;
                case POLICY_SUBSTITUTE:
                    c = UNICODE_ERROR;
                    return true;
                case POLICY_IGNORE:
                    return true;
            }
    }

    return false; // to silence gcc warning
}

/*
 * Returns original representation of code point.
 * Assumes code point is valid (hence 'unsafe').
 */
uint32_t Enc::decodeUnsafe(uint32_t c) const
{
    switch (type_) {
        case EBCDIC:
            c = ebc2asc[c & 0xFF];
            break;
        case ASCII:
        case UCS2:
        case UTF16:
        case UTF32:
        case UTF8:
            break;
    }
    return c;
}

/*
 * Returns [l - h] range representation with regard to current policy.
 *
 * Since range borders are specified by user, it is assumed that the user
 * considers all code points from this range to be valid. re2c must check.
 *
 * Returns NULL if range contains code points that exceed maximum or are
 * forbidden by current policy, otherwise returns newly constructed range.
 */
Range * Enc::validateRange(RangeMgr &rm, uint32_t l, uint32_t h) const
{
    if (l >= nCodePoints () || h >= nCodePoints ()) return NULL;

    Range * r = NULL;
    switch (type_) {
        case ASCII:
        case EBCDIC:
            r = rm.ran(l, h + 1);
            break;
        case UCS2:
        case UTF16:
        case UTF32:
        case UTF8:
            r = rm.ran(l, h + 1);
            if (l <= SURR_MAX && h >= SURR_MIN) {
                switch (policy_) {
                    case POLICY_FAIL:
                        r = NULL;
                        break;
                    case POLICY_SUBSTITUTE:
                        // exclude surrogates, add error code point
                        r = rm.sub(r, rm.ran(SURR_MIN, SURR_MAX + 1));
                        r = rm.add(r, rm.sym(UNICODE_ERROR));
                        break;
                    case POLICY_IGNORE:
                        break;
                }
            }
            break;
    }
    return r;
}

Range * Enc::fullRange(RangeMgr &rm) const
{
    Range * r = rm.ran(0, nCodePoints());
    if (policy_ != POLICY_IGNORE) {
        // exclude surrogates
        r = rm.sub(r, rm.ran (SURR_MIN, SURR_MAX + 1));
    }
    return r;
}

} // namespace re2c
