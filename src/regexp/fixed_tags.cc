#include <stddef.h>
#include <vector>

#include "src/codegen/input_api.h"
#include "src/options/opt.h"
#include "src/regexp/re.h"
#include "src/regexp/tag.h"


namespace re2c {
namespace {

/* note [fixed and variable tags]
 *
 * If distance between two tags is constant (equal for all strings that match
 * the given regexp), then lexer only needs to track one of them: the second
 * tag equals the first tag plus static offset.
 *
 * This optimization is applied only to tags in top-level concatenation,
 * because in other cases the base tag may be NULL, and the calculation of
 * the fixed tag value is not as simple as substracting a fixed offset.
 * Furthermore, fixed tags are fobidden with generic API because it cannot
 * express fixed offsets. M-tags (with history) also cannot be fixed.
 *
 * Another special case is fictive tags (those that exist only to impose
 * hierarchical laws of POSIX disambiguation). We treat them as fixed in order
 * to suppress code generation.
 */

struct StackItem {
    RE       *re;       // current sub-RE
    uint32_t  dist;     // distance backup for alternative, unused for other RE
    uint8_t   succ;     // index of the next successor to be visited
    bool      toplevel; // if this sub-RE is in top-level concatenation
};

static void find_fixed_tags(RESpec &spec, std::vector<StackItem> &stack, RE *re0)
{
    static const uint32_t VARDIST = Tag::VARDIST;
    bool toplevel = spec.opts->input_api != INPUT_CUSTOM;

    // base tag, intially the fake "rightmost tag" (the end of RE)
    size_t base = Tag::RIGHTMOST;

    // the distance to the nearest top-level tag to the right (base tag)
    uint32_t dist = 0;

    const StackItem i0 = {re0, VARDIST, 0, toplevel};
    stack.push_back(i0);

    while (!stack.empty()) {
        const StackItem i = stack.back();
        stack.pop_back();
        RE *re = i.re;

        if (re->type == RE::SYM) {
            if (dist != VARDIST) ++dist;
        }
        else if (re->type == RE::ALT) {
            if (i.succ == 0) {
                // save the current distance on stack (from the alternative end
                // to base) and recurse into the left sub-RE
                StackItem k = {re, dist, 1, i.toplevel};
                stack.push_back(k);
                StackItem j = {re->alt.re1, VARDIST, 0, false};
                stack.push_back(j);
            }
            else if (i.succ == 1) {
                // save the current distance on stack (from the left sub-RE to
                // base), reset distance to the distance popped from stack (from
                // the alternative end to base), recurse into the right sub-RE
                StackItem k = {re, dist, 2, i.toplevel};
                stack.push_back(k);
                StackItem j = {re->alt.re2, VARDIST, 0, false};
                stack.push_back(j);
                dist = i.dist;
            }
            else {
                // both sub-RE visited, compare the distance on stack (from the
                // left sub-RE to base) to the current distance (from the right
                // sub-RE to base), if not equal set variable distance
                dist = (i.dist == dist) ? i.dist : VARDIST;
            }
        }
        else if (re->type == RE::ITER) {
            if (i.succ == 0) {
                // recurse into the sub-RE
                StackItem k = {re, VARDIST, 1, i.toplevel};
                stack.push_back(k);
                StackItem j = {re->iter.re, VARDIST, 0, false};
                stack.push_back(j);
            }
            else {
                // sub-RE visited, assume unknown number of iterations
                // TODO: find precise distance for fixed repetition counter
                dist = VARDIST;
            }
        }
        else if (re->type == RE::CAT) {
            // the right sub-RE is pushed on stack after the left sub-RE and
            // visited earlier (because distance is computed from right to left)
            StackItem j1 = {re->cat.re1, VARDIST, 0, i.toplevel};
            stack.push_back(j1);
            StackItem j2 = {re->cat.re2, VARDIST, 0, i.toplevel};
            stack.push_back(j2);
        }
        else if (re->type == RE::TAG) {
            // see note [fixed and variable tags]
            Tag &tag = spec.tags[re->tag.idx];
            if (fictive(tag)) {
                tag.base = tag.dist = 0;
            }
            else if (i.toplevel && dist != VARDIST && !history(tag)) {
                tag.base = base;
                tag.dist = dist;
            }
            else if (i.toplevel) {
                base = re->tag.idx;
                dist = 0;
            }
            if (trailing(tag)) {
                dist = 0;
            }
        }
    }
}

} // anonymous namespace

void find_fixed_tags(RESpec &spec)
{
    std::vector<StackItem> stack;
    for (std::vector<RE*>::iterator i = spec.res.begin(); i != spec.res.end(); ++i) {
        find_fixed_tags(spec, stack, *i);
    }
}

} // namespace re2c
