#include <stddef.h>
#include <string>
#include <vector>

#include "src/msg/msg.h"
#include "src/msg/warn.h"
#include "src/regexp/regexp.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"
#include "src/util/check.h"

namespace re2c {
namespace {

struct StackItem {
    const Regexp* re; // current sub-regexp
    uint8_t succ;     // index of the next sucessor to be visited
};

static bool nullable(const RESpec& spec, std::vector<StackItem>& stack, const Regexp* re0) {
    // the "nullable" status of the last sub-regexp visited by DFS
    bool null = false;

    stack.push_back({re0, 0});

    while (!stack.empty()) {
        const StackItem i = stack.back();
        stack.pop_back();

        const Regexp* re = i.re;
        if (re->kind == Regexp::Kind::NIL) {
            null = true;
        } else if (re->kind == Regexp::Kind::SYM) {
            null = false;
        } else if (re->kind == Regexp::Kind::TAG) {
            null = true;
            // Trailing context is always in top-level concatenation, and sub-regexp are visited
            // from left to right. Since we are here, sub-regexp to the left of the trailing context
            // is nullable (otherwise we would not recurse into the right sub-regexp), therefore the
            // whole regexp is nullable.
            if (trailing(spec.tags[re->tag.idx])) {
                DCHECK(stack.size() == 1 && stack.back().re->kind == Regexp::Kind::CAT);
                stack.pop_back();
                break;
            }
        } else if (re->kind == Regexp::Kind::ALT) {
            if (i.succ == 0) {
                // recurse into the left sub-regexp
                stack.push_back({re, 1});
                stack.push_back({re->alt.re1, 0});
            } else if (!null) {
                // if the left sub-regexp is nullable, so is alternative, so stop recursion;
                // otherwise recurse into the right sub-regexp
                stack.push_back({re->alt.re2, 0});
            }
        } else if (re->kind == Regexp::Kind::CAT) {
            if (i.succ == 0) {
                // recurse into the left sub-regexp
                stack.push_back({re, 1});
                stack.push_back({re->cat.re1, 0});
            } else if (null) {
                // if the left sub-regexp is not nullable, neither is concatenation, so stop
                // recursion; otherwise recurse into the right sub-regexp
                stack.push_back({re->cat.re2, 0});
            }
        } else if (re->kind == Regexp::Kind::ITER) {
            // iteration is nullable if the sub-regexp is nullable (zero repetitions is represented
            // with alternative)
            stack.push_back({re->iter.re, 0});
        }
    }

    DCHECK(stack.empty());
    return null;
}

static bool trivially_nullable(const RESpec& spec, const Regexp* re) {
    // "" { ... }
    if (re->kind == Regexp::Kind::NIL) return true;

    // "" / ... { ... }
    if (re->kind == Regexp::Kind::CAT
            && re->cat.re1->kind == Regexp::Kind::NIL
            && re->cat.re2->kind == Regexp::Kind::CAT
            && re->cat.re2->cat.re1->kind == Regexp::Kind::TAG
            && trailing(spec.tags[re->cat.re2->cat.re1->tag.idx])) return true;

    return false;
}

} // anonymous namespace

// Warn about rules that match empty string (including rules with nonempty trailing context). False
// positives on partially self-shadowed rules like `[^]?`.
void warn_nullable(const RESpec& spec, const std::string& cond) {
    // rule for <> is special -- it doesn't have a regexp
    if (cond == "0") return;

    std::vector<StackItem> stack;
    const size_t nre = spec.res.size();
    for (size_t i = 0; i < nre; ++i) {
        const Regexp* re = spec.res[i];
        if (trivially_nullable(spec, re)) {
            // Exclude trivial obviously nullable cases like "", as they are often used as a
            // non-consuming default rule. This also captures empty character classes, but they are
            // covered by another warning.
        } else if (nullable(spec, stack, re)) {
            spec.msg.warn.match_empty_string(spec.rules[i].semact->loc, cond);
        }
    }
}

} // namespace re2c
