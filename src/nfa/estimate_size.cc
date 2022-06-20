#include <stddef.h>
#include <vector>

#include "src/debug/debug.h"
#include "src/nfa/nfa.h"
#include "src/parse/ast.h"
#include "src/regexp/re.h"

namespace re2c {
namespace {

struct StackItem {
    const RE* re;   // current sub-RE
    uint32_t size;  // RE size (only for alternative and concatenation)
    uint32_t depth; // RE depth (only for alternative and concatenation)
    uint8_t succ;   // index of the next sucessor to be visited
};

static void compute_re_size_and_depth(
    const RE* re0, std::vector<StackItem>& stack, size_t* psize, size_t* pdepth) {

    // the estimated size and depth of the last sub-RE visited by DFS
    uint32_t size = 0, depth = 0;

    stack.push_back({re0, 0, 0, 0});

    while (!stack.empty()) {
        const StackItem i = stack.back();
        stack.pop_back();

        const RE* re = i.re;
        if (re->kind == RE::Kind::NIL) {
            size = depth = 0;
        } else if (re->kind == RE::Kind::SYM || re->kind == RE::Kind::TAG) {
            size = depth = 1;
        } else if (re->kind == RE::Kind::ALT) {
            if (i.succ == 0) {
                // recurse into the left sub-RE
                stack.push_back({re, 0, 0, 1});
                stack.push_back({re->alt.re1, 0, 0, 0});
            } else if (i.succ == 1) {
                // recurse into the right sub-RE
                stack.push_back({re, size, depth, 2});
                stack.push_back({re->alt.re2, 0, 0, 0});
            } else {
                // both sub-RE visited, recursive return
                // (left one is on stack, right one was just visited by DFS)
                size = 1 + i.size + size;
                depth = 1 + std::max(i.depth, depth);
            }
        } else if (re->kind == RE::Kind::CAT) {
            if (i.succ == 0) {
                // recurse into the left sub-RE
                stack.push_back({re, 0, 0, 1});
                stack.push_back({re->cat.re1, 0, 0, 0});
            } else if (i.succ == 1) {
                // recurse into the right sub-RE
                stack.push_back({re, size, depth, 2});
                stack.push_back({re->cat.re2, 0, 0, 0});
            } else {
                // both sub-RE visited, recursive return
                // (left one is on stack, right one was just visited by DFS)
                size = i.size + size;
                depth = i.depth + depth;
            }
        } else if (re->kind == RE::Kind::ITER) {
            if (i.succ == 0) {
                // recurse into the sub-RE
                stack.push_back({re, 0, 0, 1});
                stack.push_back({re->iter.re, 0, 0, 0});
            } else {
                // sub-RE visited, recursive return
                // formula is the same for size and depth (it reflects NFA construction)
                const uint32_t min = re->iter.min, max = re->iter.max;
                size = max == Ast::MANY ? size * min + 1 : size * max + (max - min);
                depth = max == Ast::MANY ? depth * min + 1 : depth * max + (max - min);
            }
        }
    }
    DASSERT(stack.empty());

    *psize = *psize + size + 1;
    *pdepth = std::max(*pdepth, static_cast<size_t>(depth));
}

} // anonymous namespace

void compute_size_and_depth(const std::vector<RE*>& res, size_t* psize, size_t* pdepth) {
    std::vector<StackItem> stack;

    DASSERT(!res.empty());
    *psize = res.size() - 1;
    *pdepth = 0;

    for (const RE* re : res) {
        compute_re_size_and_depth(re, stack, psize, pdepth);
    }
}

} // namespace re2c
