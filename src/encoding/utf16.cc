#include <stddef.h>
#include <stdint.h>

#include "src/encoding/range_suffix.h"
#include "src/encoding/utf16.h"
#include "src/regexp/regexp.h"
#include "src/util/range.h"

namespace re2c {
namespace utf16 {

// Add word range [w1-w2].
static void add_continuous1(RangeSuffix*& root, IrAllocator& alc, uint32_t l, uint32_t h) {
    RangeSuffix** p = &root;
    for (;;) {
        if (*p == nullptr) {
            *p = make_range_suffix(alc, l, h);
            break;
        } else if ((*p)->l == l && (*p)->h == h) {
            break;
        } else {
            p = &(*p)->next;
        }
    }
}

// Now that we have catenation of word ranges [l1-h1],[l2-h2], we want to add it to existing range,
// merging suffixes on the fly.
static void add_continuous2(RangeSuffix*& root,
                            IrAllocator& alc,
                            uint32_t l_ld,
                            uint32_t h_ld,
                            uint32_t l_tr,
                            uint32_t h_tr) {
    RangeSuffix** p = &root;
    for (;;) {
        if (*p == nullptr) {
            *p = make_range_suffix(alc, l_tr, h_tr);
            p = &(*p)->child;
            break;
        } else if ((*p)->l == l_tr && (*p)->h == h_tr) {
            p = &(*p)->child;
            break;
        } else {
            p = &(*p)->next;
        }
    }
    for (;;) {
        if (*p == nullptr) {
            *p = make_range_suffix(alc, l_ld, h_ld);
            break;
        } else if ((*p)->l == l_ld && (*p)->h == h_ld) {
            break;
        } else {
            p = &(*p)->next;
        }
    }
}

// Split range into sub-ranges that agree on leading surrogates.
//
// We have two Unicode runes, L and H, both map to UTF-16 surrogate pairs 'L1 L2' and 'H1 H2'. We
// want to represent Unicode range [L - H] as a catenation of word ranges [L1 - H1],[L2 - H2].
//
// This is only possible if the following condition holds: if L1 /= H1, then L2 == 0xdc00 and
// H2 == 0xdfff. This condition ensures that:
//     1) all possible UTF-16 sequences between L and H are allowed
//     2) no word ranges [w1 - w2] appear, such that w1 > w2
//
// E.g. [\U00010001-\U00010400] => [d800-d801],[dc01-dc00]. The last word range, [dc01-dc00], is
// incorrect: its lower bound is greater than its upper bound. To fix this, we must split the
// original range into two sub-ranges:
//    [\U00010001-\U000103ff] => [d800-d800],[dc01-dfff]
//    [\U00010400-\U00010400] => [d801-d801],[dc00-dc00]
//
// This function finds all such 'points of discontinuity' and represents original range as
// alternation of continuous sub-ranges.
//
static void split_by_continuity(RangeSuffix*& root,
                                IrAllocator& alc,
                                uint32_t l_ld,
                                uint32_t h_ld,
                                uint32_t l_tr,
                                uint32_t h_tr) {
    if (l_ld != h_ld) {
        if (l_tr > MIN_TRAIL_SURR) {
            split_by_continuity(root, alc, l_ld, l_ld, l_tr, MAX_TRAIL_SURR);
            split_by_continuity(root, alc, l_ld + 1, h_ld, MIN_TRAIL_SURR, h_tr);
            return;
        }
        if (h_tr < MAX_TRAIL_SURR) {
            split_by_continuity(root, alc, l_ld, h_ld - 1, l_tr, MAX_TRAIL_SURR);
            split_by_continuity(root, alc, h_ld, h_ld, MIN_TRAIL_SURR, h_tr);
            return;
        }
    }
    add_continuous2(root, alc, l_ld, h_ld, l_tr, h_tr);
}

// Split range into sub-ranges, so that all runes in the same sub-range have equal length of UTF-16
// sequence. E.g., full Unicode range [0-0x10FFFF] gets split into sub-ranges:
//    [0 - 0xFFFF]         (2-byte UTF-16 sequences)
//    [0x10000 - 0x10FFFF] (4-byte UTF-16 sequences)
//
static void split_by_rune_length(RangeSuffix*& root, IrAllocator& alc, rune l, rune h) {
    if (l <= MAX_1WORD_RUNE) {
        if (h <= MAX_1WORD_RUNE) {
            add_continuous1(root, alc, l, h);
        } else {
            add_continuous1(root, alc, l, MAX_1WORD_RUNE);
            const uint32_t h_ld = lead_surr(h);
            const uint32_t h_tr = trail_surr(h);
            split_by_continuity(root, alc, MIN_LEAD_SURR, h_ld, MIN_TRAIL_SURR, h_tr);
        }
    } else {
        const uint32_t l_ld = lead_surr(l);
        const uint32_t l_tr = trail_surr(l);
        const uint32_t h_ld = lead_surr(h);
        const uint32_t h_tr = trail_surr(h);
        split_by_continuity(root, alc, l_ld, h_ld, l_tr, h_tr);
    }
}

static Regexp* symbol(RESpec& spec, rune r) {
    RangeMgr& rm = spec.rangemgr;
    if (r <= MAX_1WORD_RUNE) {
        return re_sym(spec, rm.sym(r));
    } else {
        return re_cat(spec,
                      re_sym(spec, rm.sym(lead_surr(r))),
                      re_sym(spec, rm.sym(trail_surr(r))));
    }
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

} // namespace utf16
} // namespace re2c
