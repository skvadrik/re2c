#include <stddef.h>
#include <string>
#include <valarray>
#include <vector>

#include "src/debug/debug.h"
#include "src/msg/msg.h"
#include "src/msg/warn.h"
#include "src/regexp/re.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"


namespace re2c {
namespace {

struct StackItem {
    const RE *re;   // current sub-RE
    uint8_t   succ; // index of the next sucessor to be visited
};

static bool nullable(const RESpec &spec, std::vector<StackItem> &stack, const RE *re0)
{
    // the "nullable" status of the last sub-RE visited by DFS
    bool null = false;

    const StackItem i0 = {re0, 0};
    stack.push_back(i0);

    while (!stack.empty()) {
        const StackItem i = stack.back();
        stack.pop_back();

        const RE *re = i.re;
        if (re->type == RE::NIL) {
            null = true;
        }
        else if (re->type == RE::SYM) {
            null = false;
        }
        else if (re->type == RE::TAG) {
            null = true;

            // Trailing context is always in top-level concatenation, and sub-RE
            // are visited from left to right. Since we are here, sub-RE to the
            // left of the trailing context is nullable (otherwise we would not
            // recurse into the right sub-RE), therefore the whole RE is nullable.
            if (trailing(spec.tags[re->tag.idx])) {
                DASSERT(stack.size() == 1 && stack.back().re->type == RE::CAT);
                stack.pop_back();
                break;
            }
        }
        else if (re->type == RE::ALT) {
            if (i.succ == 0) {
                // recurse into the left sub-RE
                StackItem k = {re, 1};
                stack.push_back(k);
                StackItem j = {re->alt.re1, 0};
                stack.push_back(j);
            }
            else if (!null) {
                // if the left sub-RE is nullable, so is alternative, so stop
                // recursion; otherwise recurse into the right sub-RE
                StackItem j = {re->alt.re2, 0};
                stack.push_back(j);
            }
        }
        else if (re->type == RE::CAT) {
            if (i.succ == 0) {
                // recurse into the left sub-RE
                StackItem k = {re, 1};
                stack.push_back(k);
                StackItem j = {re->cat.re1, 0};
                stack.push_back(j);
            }
            else if (null) {
                // if the left sub-RE is not nullable, neither is concatenation,
                // so stop recursion; otherwise recurse into the right sub-RE
                StackItem j = {re->cat.re2, 0};
                stack.push_back(j);
            }
        }
        else if (re->type == RE::ITER) {
            // iteration is nullable if the sub-RE is nullable
            // (zero repetitions is represented with alternative)
            StackItem j = {re->iter.re, 0};
            stack.push_back(j);
        }
    }

    DASSERT(stack.empty());
    return null;
}

static bool trivially_nullable(const RESpec &spec, const RE *re)
{
    // "" { ... }
    if (re->type == RE::NIL) return true;

    // "" / ... { ... }
    if (re->type == RE::CAT
        && re->cat.re1->type == RE::NIL
        && re->cat.re2->type == RE::CAT
        && re->cat.re2->cat.re1->type == RE::TAG
        && trailing(spec.tags[re->cat.re2->cat.re1->tag.idx])) return true;

    return false;
}

} // anonymous namespace

// Warn about rules that match empty string (including rules with nonempty
// trailing context). False positives on partially self-shadowed rules like [^]?
void warn_nullable(const RESpec &spec, const std::string &cond)
{
    // rule for <> is special -- it doesn't have a regexp
    if (cond == "0") return;

    std::vector<StackItem> stack;
    const size_t nre = spec.res.size();
    for (size_t i = 0; i < nre; ++i) {
        const RE *re = spec.res[i];
        if (trivially_nullable(spec, re)) {
            // Exclude trivial obviously nullable cases like "", as they are
            // often used as a non-consuming default rule. This also captures
            // empty character classes, but they are covered by another warning.
        } else if (nullable(spec, stack, re)) {
            spec.msg.warn.match_empty_string(spec.rules[i].semact->loc, cond);
        }
    }
}

} // namespace re2c
