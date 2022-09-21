#include <stddef.h>
#include <vector>

#include "src/options/opt.h"
#include "src/regexp/regexp.h"
#include "src/regexp/tag.h"
#include "src/util/check.h"

namespace re2c {
namespace {

// note [fixed and variable tags]
//
// If the distance between two tags is constant, then the lexer only needs to track one of the two
// tags: the value of the other tag equals the value of the first tag plus a static offset. For tags
// that are under alternative or repetition it is also necessary to check if the base tag has a
// no-match value (in that case fixed tag should also be set to no-match). For tags in top-level
// concatenation the check is not needed, because they always match.
//
// This optimization does not apply to m-tags (a.k.a. tags with history).
//
// A special case is fictive tags (structural POSIX tags that exist only for disambiguation
// purposes). Such tags are treated as fixed in order to suppress code generation.

struct StackItem {
    Regexp* re;   // current sub-regexp
    uint8_t succ; // index of the next successor to be visited
};

// level is increased when descending into alternative or repetition
struct Level {
    size_t tag;           // current base tag
    uint32_t dist_to_tag; // distance to base tag
    uint32_t dist_to_end; // full level distance
};

static void find_fixed_tags(
        RESpec& spec, std::vector<StackItem>& stack, std::vector<Level>& levels, Regexp* re0) {
    static constexpr uint32_t VARDIST = Tag::VARDIST;

    // initial base tag at the topmost level is the fake "rightmost tag" (cursor)
    DCHECK(levels.empty());
    levels.push_back({Tag::RIGHTMOST, 0, 0});

    stack.push_back({re0, 0});

    while (!stack.empty()) {
        const StackItem i = stack.back();
        stack.pop_back();
        Regexp* re = i.re;

        if (re->kind == Regexp::Kind::SYM) {
            Level& l = levels.back();
            if (l.dist_to_tag != VARDIST) ++l.dist_to_tag;
            if (l.dist_to_end != VARDIST) ++l.dist_to_end;

        } else if (re->kind == Regexp::Kind::ALT) {
            if (i.succ == 0) {
                // recurse into the left sub-regexp (leave the current regexp on stack)
                stack.push_back({re, 1});
                stack.push_back({re->alt.re1, 0});

                // increase level when descending into the left sub-regexp
                levels.push_back({Tag::NONE, 0, 0});

            } else if (i.succ == 1) {
                // recurse into the right sub-regexp (leave the current regexp on stack)
                stack.push_back({re, 2});
                stack.push_back({re->alt.re2, 0});

                // increase level when descending into the right sub-regexp (keep the left
                // sub-regexp level on stack, it will be needed to compare left and right distance)
                levels.push_back({Tag::NONE, 0, 0});

            } else {
                // both sub-regexp visited, pop both levels from stack and compare their distances:
                // if not equal, then set variable distance
                uint32_t rdist = levels.back().dist_to_end;
                levels.pop_back();
                uint32_t ldist = levels.back().dist_to_end;
                levels.pop_back();

                Level& l = levels.back();
                uint32_t dist = ldist == rdist ? ldist : VARDIST;

                l.dist_to_end = l.dist_to_end == VARDIST || dist == VARDIST
                        ? VARDIST : l.dist_to_end + dist;
                l.dist_to_tag = l.dist_to_tag == VARDIST || dist == VARDIST
                        ? VARDIST : l.dist_to_tag + dist;
            }
        } else if (re->kind == Regexp::Kind::ITER) {
            if (i.succ == 0) {
                // recurse into sub-regexp (leave the current regexp on stack)
                stack.push_back({re, 1});
                stack.push_back({re->iter.re, 0});

                // increase level when descending into sub-regexp
                levels.push_back({Tag::NONE, 0, 0});
            } else {
                // sub-regexp visited, pop level from stack: if it has fixed distance and repetition
                // count is constant, resulting distance is fixed
                uint32_t dist = levels.back().dist_to_end;
                levels.pop_back();

                Level& l = levels.back();
                dist = dist == VARDIST || re->iter.max != re->iter.min
                        ? VARDIST : dist * re->iter.max;

                l.dist_to_end = l.dist_to_end == VARDIST || dist == VARDIST
                        ? VARDIST : l.dist_to_end + dist;
                l.dist_to_tag = l.dist_to_tag == VARDIST || dist == VARDIST
                        ? VARDIST : l.dist_to_tag + dist;
            }
        } else if (re->kind == Regexp::Kind::CAT) {
            // the right sub-regexp is pushed on stack after the left sub-regexp and visited earlier
            // (because distance is computed from right to left)
            stack.push_back({re->cat.re1, 0});
            stack.push_back({re->cat.re2, 0});

        } else if (re->kind == Regexp::Kind::TAG) {
            Tag& tag = spec.tags[re->tag.idx];
            Level& l = levels.back();
            bool toplevel = levels.size() == 1;

            // Don't check for orbit tags, as they will have VARDIST automatically.
            if (fictive(tag)) {
                // fictive tags are marked as fixed to suppress code generation
                tag.base = tag.dist = 0;
            } else if (history(tag)) {
                // fixed tags do not apply to m-tags
            } else if (spec.opts->fixed_tags == FixedTags::NONE) {
                // fixed tag optimization is globally disabled
            } else if (spec.opts->tags_history) {
                // Fixed tags with subhistories are possible in principle, but it ends up being too
                // slow (handling special case adds overhead).
            } else if (l.tag != Tag::NONE && l.dist_to_tag != VARDIST
                    && (spec.opts->fixed_tags == FixedTags::ALL || toplevel)) {
                // this tag can be fixed
                tag.base = l.tag;
                tag.dist = l.dist_to_tag;
                tag.toplevel = toplevel;
            } else {
                // this tag cannot be fixed, make it the new base
                l.tag = re->tag.idx;
                l.dist_to_tag = 0;
            }
            // Trailing context is not special: tags are fixed on the rightmost cursor position, and
            // trailing context is just another tag.
        }
    }

    DCHECK(levels.size() == 1);
    levels.pop_back();
}

} // anonymous namespace

void find_fixed_tags(RESpec& spec) {
    std::vector<StackItem> stack;
    std::vector<Level> levels;
    for (Regexp* re : spec.res) {
        find_fixed_tags(spec, stack, levels, re);
    }
}

} // namespace re2c
