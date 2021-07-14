#include <stddef.h>
#include <vector>

#include "src/debug/debug.h"
#include "src/options/opt.h"
#include "src/regexp/re.h"
#include "src/regexp/tag.h"


namespace re2c {
namespace {

/* note [fixed and variable tags]
 *
 * If the distance between two tags is constant, then the lexer only needs to
 * track one of the two tags: the value of the other tag equals the value of the
 * first tag plus a static offset. For tags that are under alternative or
 * repetition it is also necessary to check if the base tag has a no-match value
 * (in that case fixed tag should also be set to no-match). For tags in
 * top-level concatenation the check is not needed, because they always match.
 *
 * This optimization does not apply to m-tags (a.k.a. tags with history).
 *
 * A special case is fictive tags (structural POSIX tags that exist only for
 * disambiguation purposes). Such tags are treated as fixed in order to suppress
 * code generation.
 */

struct StackItem {
    RE      *re;   // current sub-RE
    uint8_t  succ; // index of the next successor to be visited
};

// level is increased when descending into alternative or repetition
struct Level {
    size_t   tag;         // current base tag
    uint32_t dist_to_tag; // distance to base tag
    uint32_t dist_to_end; // full level distance
};

static void find_fixed_tags(RESpec &spec, std::vector<StackItem> &stack,
    std::vector<Level> &levels, RE *re0)
{
    static const uint32_t VARDIST = Tag::VARDIST;

    // initial base tag at the topmost level is the fake "rightmost tag" (cursor)
    const Level l0 = {Tag::RIGHTMOST, 0, 0};
    DASSERT(levels.empty());
    levels.push_back(l0);

    const StackItem i0 = {re0, 0};
    stack.push_back(i0);

    while (!stack.empty()) {
        const StackItem i = stack.back();
        stack.pop_back();
        RE *re = i.re;

        if (re->type == RE::SYM) {
            Level &l = levels.back();
            if (l.dist_to_tag != VARDIST) ++l.dist_to_tag;
            if (l.dist_to_end != VARDIST) ++l.dist_to_end;

        } else if (re->type == RE::ALT) {
            if (i.succ == 0) {
                // recurse into the left sub-RE (leave the current RE on stack)
                StackItem k = {re, 1};
                stack.push_back(k);
                StackItem j = {re->alt.re1, 0};
                stack.push_back(j);

                // increase level when descending into the left sub-RE
                Level l = {Tag::NONE, 0, 0};
                levels.push_back(l);

            } else if (i.succ == 1) {
                // recurse into the right sub-RE (leave the current RE on stack)
                StackItem k = {re, 2};
                stack.push_back(k);
                StackItem j = {re->alt.re2, 0};
                stack.push_back(j);

                // increase level when descending into the right sub-RE
                // keep the left sub-RE level on stack, it will be needed to
                // compare left and right distance
                Level l = {Tag::NONE, 0, 0};
                levels.push_back(l);

            } else {
                // both sub-RE visited, pop both levels from stack and compare
                // their distances: if not equal, then set variable distance
                uint32_t rdist = levels.back().dist_to_end;
                levels.pop_back();
                uint32_t ldist = levels.back().dist_to_end;
                levels.pop_back();

                Level &l = levels.back();
                uint32_t dist = ldist == rdist ? ldist : VARDIST;

                l.dist_to_end = l.dist_to_end == VARDIST || dist == VARDIST
                    ? VARDIST : l.dist_to_end + dist;
                l.dist_to_tag = l.dist_to_tag == VARDIST || dist == VARDIST
                    ? VARDIST : l.dist_to_tag + dist;
            }
        } else if (re->type == RE::ITER) {
            if (i.succ == 0) {
                // recurse into sub-RE (leave the current RE on stack)
                StackItem k = {re, 1};
                stack.push_back(k);
                StackItem j = {re->iter.re, 0};
                stack.push_back(j);

                // increase level when descending into sub-RE
                Level l = {Tag::NONE, 0, 0};
                levels.push_back(l);
            } else {
                // sub-RE visited, pop level from stack: if it has fixed distance
                // and repetition count is constant, resulting distance is fixed
                uint32_t dist = levels.back().dist_to_end;
                levels.pop_back();

                Level &l = levels.back();
                dist = dist == VARDIST || re->iter.max != re->iter.min
                    ? VARDIST : dist * re->iter.max;

                l.dist_to_end = l.dist_to_end == VARDIST || dist == VARDIST
                    ? VARDIST : l.dist_to_end + dist;
                l.dist_to_tag = l.dist_to_tag == VARDIST || dist == VARDIST
                    ? VARDIST : l.dist_to_tag + dist;
            }
        } else if (re->type == RE::CAT) {
            // the right sub-RE is pushed on stack after the left sub-RE and
            // visited earlier (because distance is computed from right to left)
            StackItem j1 = {re->cat.re1, 0};
            stack.push_back(j1);
            StackItem j2 = {re->cat.re2, 0};
            stack.push_back(j2);

        } else if (re->type == RE::TAG) {
            Tag &tag = spec.tags[re->tag.idx];
            Level &l = levels.back();
            bool toplevel = levels.size() == 1;

            // Don't check for orbit tags, as they will have VARDIST automatically.
            if (fictive(tag)) {
                // fictive tags are marked as fixed to suppress code generation
                tag.base = tag.dist = 0;
            } else if (history(tag)) {
                // fixed tags do not apply to m-tags
            } else if (spec.opts->fixed_tags == FIXTAG_NONE) {
                // fixed tag optimization is globally disabled
            } else if (spec.opts->subhistories) {
                // Fixed tags with subhistories are possible in principle, but it
                // ends up being too slow (handling special case adds overhead).
            } else if (l.tag != Tag::NONE && l.dist_to_tag != VARDIST
                    && (spec.opts->fixed_tags == FIXTAG_ALL || toplevel)) {
                // this tag can be fixed
                tag.base = l.tag;
                tag.dist = l.dist_to_tag;
                tag.toplevel = toplevel;
            } else {
                // this tag cannot be fixed, make it the new base
                l.tag = re->tag.idx;
                l.dist_to_tag = 0;
            }

            if (trailing(tag)) {
                l.dist_to_tag = 0;
            }
        }
    }

    DASSERT(levels.size() == 1);
    levels.pop_back();
}

} // anonymous namespace

void find_fixed_tags(RESpec &spec)
{
    std::vector<StackItem> stack;
    std::vector<Level> levels;
    for (std::vector<RE*>::iterator i = spec.res.begin(); i != spec.res.end(); ++i) {
        find_fixed_tags(spec, stack, levels, *i);
    }
}

} // namespace re2c
