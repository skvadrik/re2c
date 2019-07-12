#include <stddef.h>
#include <vector>

#include "src/codegen/input_api.h"
#include "src/options/opt.h"
#include "src/regexp/re.h"
#include "src/regexp/tag.h"


namespace re2c {

/* note [fixed and variable tags]
 *
 * If distance between two tags is constant (equal for all strings that
 * match the given regexp), then lexer only needs to track one of them:
 * the second tag equals the first tag plus static offset.
 *
 * However, this optimization is applied only to tags in top-level
 * concatenation, because other tags may be uninitialized and we don't
 * want to mess with conditional calculation of fixed tags.
 *
 * Furthermore, fixed tags are fobidden with generic API because it cannot
 * express fixed offsets.
 *
 * Tags with history also cannot be fixed.
 *
 * Another special case is fictive tags (those that exist only to impose
 * hierarchical laws of POSIX disambiguation). We treat them as fixed
 * in order to suppress code generation.
 */

static void find_fixed_tags(RE *re, std::vector<Tag> &tags,
    size_t &dist, size_t &base, bool toplevel)
{
    switch (re->type) {
        case RE::NIL: break;
        case RE::SYM:
            if (dist != Tag::VARDIST) ++dist;
            break;
        case RE::ALT: {
            size_t d1 = dist, d2 = dist;
            find_fixed_tags(re->alt.re1, tags, d1, base, false);
            find_fixed_tags(re->alt.re2, tags, d2, base, false);
            dist = (d1 == d2) ? d1 : Tag::VARDIST;
            break;
        }
        case RE::CAT:
            find_fixed_tags(re->cat.re2, tags, dist, base, toplevel);
            find_fixed_tags(re->cat.re1, tags, dist, base, toplevel);
            break;
        case RE::ITER:
            find_fixed_tags(re->iter.re, tags, dist, base, false);
            dist = Tag::VARDIST;
            break;
        case RE::TAG: {
            // see note [fixed and variable tags]
            Tag &tag = tags[re->tag.idx];
            if (fictive(tag)) {
                tag.base = tag.dist = 0;
            } else if (toplevel && dist != Tag::VARDIST && !history(tag)) {
                tag.base = base;
                tag.dist = dist;
            } else if (toplevel) {
                base = re->tag.idx;
                dist = 0;
            }
            if (trailing(tag)) dist = 0;
            break;
        }
    }
}

void find_fixed_tags(RESpec &spec)
{
    const bool generic = spec.opts->input_api == INPUT_CUSTOM;
    std::vector<RE*>::iterator
        i = spec.res.begin(),
        e = spec.res.end();
    for (; i != e; ++i) {
        size_t base = Tag::RIGHTMOST, dist = 0;
        find_fixed_tags(*i, spec.tags, dist, base, !generic);
    }
}

} // namespace re2c
