#include <stddef.h>
#include <stdint.h>

#include "src/encoding/range_suffix.h"
#include "src/encoding/utf8/utf8.h"
#include "src/encoding/utf8/utf8_regexp.h"
#include "src/regexp/re.h"
#include "src/util/range.h"

namespace re2c {
namespace utf8_impl {

// Now that we have catenation of byte ranges [l1-h1]...[lN-hN], we want to add it to existing
// range, merging suffixes on the fly.
static void add_continuous(
        RangeSuffix*& root, RE::alc_t& alc, utf8::rune l, utf8::rune h, uint32_t n) {
    uint32_t lcs[utf8::MAX_RUNE_LENGTH];
    uint32_t hcs[utf8::MAX_RUNE_LENGTH];
    utf8::rune_to_bytes(lcs, l);
    utf8::rune_to_bytes(hcs, h);

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
static void split_by_continuity(
        RangeSuffix*& root, RE::alc_t& alc, utf8::rune l, utf8::rune h, uint32_t n) {
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
static void split_by_rune_length(RangeSuffix*& root, RE::alc_t& alc, utf8::rune l, utf8::rune h) {
    const uint32_t nh = utf8::rune_length(h);
    for (uint32_t nl = utf8::rune_length(l); nl < nh; ++nl) {
        utf8::rune r = utf8::max_rune(nl);
        split_by_continuity(root, alc, l, r, nl);
        l = r + 1;
    }
    split_by_continuity(root, alc, l, h, nh);
}

static RE* symbol(RESpec& spec, utf8::rune r) {
    RangeMgr& rm = spec.rangemgr;

    uint32_t chars[utf8::MAX_RUNE_LENGTH];
    const uint32_t chars_count = utf8::rune_to_bytes(chars, r);
    RE* re = re_sym(spec, rm.sym(chars[0]));
    for (uint32_t i = 1; i < chars_count; ++i) {
        re = re_cat(spec, re, re_sym(spec, rm.sym(chars[i])));
    }
    return re;
}

} // namespace utf8_impl

// Split Unicode character class {[l1, h1), ..., [lN, hN)} into ranges [l1, h1-1], ..., [lN, hN-1]
// and return an alternation of them. We store partially built range in suffix tree, which allows us
// to eliminate common suffixes while building.
//
RE* utf8_range(RESpec& spec, const Range* r) {
    // empty range
    if (!r) return nullptr;

    // one-symbol range
    if (!r->next() && r->lower() == r->upper() - 1) {
        return utf8_impl::symbol(spec, r->lower());
    }

    RangeSuffix* root = nullptr;
    for (; r != nullptr; r = r->next()) {
        utf8_impl::split_by_rune_length(root, spec.alc, r->lower(), r->upper() - 1);
    }
    return to_regexp(spec, root);
}

} // namespace re2c
