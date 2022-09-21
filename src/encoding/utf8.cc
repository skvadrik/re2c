#include <stddef.h>
#include <stdint.h>

#include "src/encoding/range_suffix.h"
#include "src/encoding/utf8.h"
#include "src/regexp/regexp.h"
#include "src/util/range.h"

namespace re2c {
namespace utf8 {

// Now that we have catenation of byte ranges [l1-h1]...[lN-hN], we want to add it to existing
// range, merging suffixes on the fly.
static void add_continuous( RangeSuffix*& root, IrAllocator& alc, rune l, rune h, uint32_t n) {
    uint32_t lcs[MAX_RUNE_LENGTH];
    uint32_t hcs[MAX_RUNE_LENGTH];
    rune_to_bytes(lcs, l);
    rune_to_bytes(hcs, h);

    RangeSuffix** p = &root;
    for (uint32_t i = 1; i <= n; ++i) {
        const uint32_t lc = lcs[n - i];
        const uint32_t hc = hcs[n - i];
        for (;;) {
            if (*p == nullptr) {
                *p = make_range_suffix(alc, lc, hc);
                p = &(*p)->child;
                break;
            } else if ((*p)->l == lc && (*p)->h == hc) {
                p = &(*p)->child;
                break;
            } else
                p = &(*p)->next;
        }
    }
}

// Split range into sub-ranges that agree on leading bytes.
//
// We have two Unicode runes of equal length, L and H, which map to UTF-8 sequences 'L_1 ... L_n'
// and 'H_1 ... H_n'. We want to represent Unicode range [L - H] as a catenation of byte ranges
// [L_1 - H_1], ..., [L_n - H_n].
//
// This is only possible if for all i > 1: if L_i /= H_i, then L_(i+1) == 0x80 and H_(i+1) == 0xbf.
// This condition ensures that:
//     1) all possible UTF-8 sequences between L and H are allowed
//     2) no byte ranges [b1 - b2] appear, such that b1 > b2
//
// E.g. [\U000e0031-\U000e0043] => [f3-f3],[a0-a0],[80-81],[b1-83]. The last byte range, [b1-83],
// is incorrect: its lower bound is greater than its upper bound. To fix this, we must split the
// original range into two sub-ranges:
//     [\U000e0031-\U000e003f] => [f3-f3],[a0-a0],[80-80],[b1-bf]
//     [\U000e0040-\U000e0043] => [f3-f3],[a0-a0],[81-81],[80-83]
//
// This function finds all such 'points of discontinuity' and represents original range as
// alternation of continuous sub-ranges.
//
static void split_by_continuity(RangeSuffix*& root, IrAllocator& alc, rune l, rune h, uint32_t n) {
    for (uint32_t i = 1; i < n; ++i) {
        uint32_t m = (1u << (6u * i)) - 1u; // last i bytes of a UTF-8 sequence
        if ((l & ~m) != (h & ~m)) {
            if ((l & m) != 0) {
                split_by_continuity(root, alc, l, l | m, n);
                split_by_continuity(root, alc, (l | m) + 1, h, n);
                return;
            }
            if ((h & m) != m) {
                split_by_continuity(root, alc, l, (h & ~m) - 1, n);
                split_by_continuity(root, alc, h & ~m, h, n);
                return;
            }
        }
    }
    add_continuous(root, alc, l, h, n);
}

// Split range into sub-ranges, so that all runes in the same sub-range have equal length of UTF-8
// sequence. E.g. the full Unicode range [0-0x10FFFF] gets split into sub-ranges:
//     [0 - 0x7F]           (1-byte UTF-8 sequences)
//     [0x80 - 0x7FF]       (2-byte UTF-8 sequences)
//     [0x800 - 0xFFFF]     (3-byte UTF-8 sequences)
//     [0x10000 - 0x10FFFF] (4-byte UTF-8 sequences)
//
static void split_by_rune_length(RangeSuffix*& root, IrAllocator& alc, rune l, rune h) {
    const uint32_t nh = rune_length(h);
    for (uint32_t nl = rune_length(l); nl < nh; ++nl) {
        rune r = max_rune(nl);
        split_by_continuity(root, alc, l, r, nl);
        l = r + 1;
    }
    split_by_continuity(root, alc, l, h, nh);
}

static Regexp* symbol(RESpec& spec, rune r) {
    RangeMgr& rm = spec.rangemgr;

    uint32_t chars[MAX_RUNE_LENGTH];
    const uint32_t chars_count = rune_to_bytes(chars, r);
    Regexp* re = re_sym(spec, rm.sym(chars[0]));
    for (uint32_t i = 1; i < chars_count; ++i) {
        re = re_cat(spec, re, re_sym(spec, rm.sym(chars[i])));
    }
    return re;
}

// Split Unicode character class {[l1, h1), ..., [lN, hN)} into ranges [l1, h1-1], ..., [lN, hN-1]
// and return an alternation of them. We store partially built range in suffix tree, which allows us
// to eliminate common suffixes while building.
//
Regexp* range(RESpec& spec, const Range* r) {
    // empty range
    if (!r) return nullptr;

    // one-symbol range
    if (!r->next() && r->lower() == r->upper() - 1) {
        return symbol(spec, r->lower());
    }

    RangeSuffix* root = nullptr;
    for (; r != nullptr; r = r->next()) {
        split_by_rune_length(root, spec.ir_alc, r->lower(), r->upper() - 1);
    }
    return to_regexp(spec, root);
}

uint32_t rune_to_bytes(uint32_t* str, rune c) {
    // one byte sequence: 0-0x7F => 0xxxxxxx
    if (c <= MAX_1BYTE_RUNE) {
        str[0] = PREFIX_1BYTE | c;
        return 1;
    }

    // two byte sequence: 0x80-0x7FF => 110xxxxx 10xxxxxx
    if (c <= MAX_2BYTE_RUNE) {
        str[0] = PREFIX_2BYTE | (c >> 1*SHIFT);
        str[1] = INFIX        | (c & MASK);
        return 2;
    }

    // If the Rune is out of range, convert it to the error rune. Do this test here because the
    // error rune encodes to three bytes. Doing it earlier would duplicate work, since an out of
    // range Rune wouldn't have fit in one or two bytes.
    if (c > MAX_RUNE) {
        c = ERROR;
    }

    // three byte sequence: 0x800 - 0xFFFF => 1110xxxx 10xxxxxx 10xxxxxx
    if (c <= MAX_3BYTE_RUNE) {
        str[0] = PREFIX_3BYTE | (c >> 2*SHIFT);
        str[1] = INFIX        | ((c >> 1*SHIFT) & MASK);
        str[2] = INFIX        | (c & MASK);
        return 3;
    }

    // four byte sequence (21-bit value): 0x10000 - 0x1FFFFF => 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
    str[0] = PREFIX_4BYTE | (c >> 3*SHIFT);
    str[1] = INFIX        | ((c >> 2*SHIFT) & MASK);
    str[2] = INFIX        | ((c >> 1*SHIFT) & MASK);
    str[3] = INFIX        | (c & MASK);
    return 4;
}

// this function assumes that the input has been validated
uint32_t decode_unsafe(const uint8_t* str) {
    // 1-unit sequence: 0-0x7F => 0xxxxxxx
    const uint32_t c = str[0];
    if (c < INFIX) {
        return c;
    }

    // 2-unit sequence: 0x80-0x7FF => 110xxxxx 10xxxxxx
    const uint32_t c1 = str[1] ^ INFIX;
    if (c < PREFIX_3BYTE) {
        return ((c << SHIFT) | c1) & MAX_2BYTE_RUNE;
    }

    // 3-unit sequence: 0x800 - 0xFFFF => 1110xxxx 10xxxxxx 10xxxxxx
    const uint32_t c2 = str[2] ^ INFIX;
    if (c < PREFIX_4BYTE) {
        return ((((c << SHIFT) | c1) << SHIFT) | c2) & MAX_3BYTE_RUNE;
    }

    // 4-unit sequence (21-bit value): 0x10000 - 0x1FFFFF => 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
    const uint32_t c3 = str[3] ^ INFIX;
    if (c < PREFIX_5BYTE) {
        return ((((((c << SHIFT) | c1) << SHIFT) | c2) << SHIFT) | c3) & MAX_4BYTE_RUNE;
    }

    return ERROR;
}

uint32_t rune_length(rune r) {
    if (r <= MAX_2BYTE_RUNE) {
        return r <= MAX_1BYTE_RUNE ? 1 : 2;
    } else {
        return r <= MAX_3BYTE_RUNE ? 3 : 4;
    }
}

rune max_rune(uint32_t i) {
    switch (i) {
    case 1:
        return MAX_1BYTE_RUNE;
    case 2:
        return MAX_2BYTE_RUNE;
    case 3:
        return MAX_3BYTE_RUNE;
    case 4:
        return MAX_4BYTE_RUNE;
    default:
        return ERROR;
    }
}

} // namespace utf8
} // namespace re2c
