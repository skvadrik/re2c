#include "src/ir/re/re.h"

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
 * One special case is pre-orbit tags: tags that correspond to the opening
 * of capturing group under iteration. We don't need to know the value of
 * such tags: we only need the last iteration which is captured by the
 * orbit tag. Pre-orbit tags are used for disambiguation only (they have
 * higher priority than orbit and closing tags). So we make pre-orbit tags
 * fixed on orbit tags with zero offset: this has no affect on disambiguation,
 * but this way pre-orbit tags will always have the same value as their orbit
 * tags (even if uninitialized, because of the zero offset) and we'll reduce
 * the amount of tag variables.
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
			if (toplevel && dist != Tag::VARDIST) {
				tag.base = base;
				tag.dist = dist;
			} else if (preorbit(tags, re->tag.idx)) {
				tag.base = re->tag.idx + 2;
				tag.dist = 0;
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
