#include <limits>

#include "src/conf/opt.h"
#include "src/ir/nfa/nfa.h"
#include "src/globals.h"

namespace re2c {

static const size_t VARDIST = std::numeric_limits<size_t>::max();

static void make_tags_var(size_t nrule,
	std::valarray<Tag> &tags, size_t &tagidx,
	const RegExp *re, size_t &dist)
{
	switch (re->type) {
		case RegExp::NIL: break;
		case RegExp::SYM:
			if (dist != VARDIST) {
				++dist;
			}
			break;
		case RegExp::ALT: {
			size_t d1 = dist, d2 = dist;
			make_tags_var(nrule, tags, tagidx, re->alt.re1, d1);
			make_tags_var(nrule, tags, tagidx, re->alt.re2, d2);
			dist = (d1 == d2) ? d1 : VARDIST;
			break;
		}
		case RegExp::CAT:
			make_tags_var(nrule, tags, tagidx, re->cat.re2, dist);
			make_tags_var(nrule, tags, tagidx, re->cat.re1, dist);
			break;
		case RegExp::ITER:
			dist = VARDIST;
			make_tags_var(nrule, tags, tagidx, re->iter, dist);
			break;
		case RegExp::TAG: {
			const size_t orig = tagidx;
			init_var_tag(tags[tagidx++], nrule, re->tag, orig);
			break;
		}
	}
}

static void make_tags_var_fix(size_t nrule,
	std::valarray<Tag> &tags, size_t &tagidx,
	const RegExp *re, size_t &dist, size_t &base)
{
	switch (re->type) {
		case RegExp::NIL:
		case RegExp::SYM:
		case RegExp::ALT:
		case RegExp::ITER:
			make_tags_var(nrule, tags, tagidx, re, dist);
			break;
		case RegExp::CAT:
			make_tags_var_fix(nrule, tags, tagidx, re->cat.re2, dist, base);
			make_tags_var_fix(nrule, tags, tagidx, re->cat.re1, dist, base);
			break;
		case RegExp::TAG: {
			const std::string *name = re->tag;
			if (dist == VARDIST) {
				base = tagidx;
				init_var_tag(tags[tagidx++], nrule, name, base);
				dist = 0;
			} else {
				init_fix_tag(tags[tagidx++], nrule, name, base, dist);
			}
			if (name == NULL) {
				dist = 0;
			}
			break;
		}
	}
}

/* note [fixed and variable tags]
 *
 * If distance between two tags is constant (fixed for all
 * strings that match the given regular expression), then
 * lexer needs to track only one of the two tags: the other
 * tag can be statically calculated from the first one.
 *
 * However, this optimization can only be applied to tags
 * that appear in top-level concatenation, because these
 * are the only tags that are guaranteed to be initialized.
 *
 * One may observe that the same argument can be applied to
 * subregexps: tags on top-level concatenation of a subregexp
 * are either initialized all at once, or none of them is
 * initialized. It may therefore seem that we can fix
 * same-level tags on each other. However, fixed tags do not
 * preserve default value: if the tag they are fixed on
 * remains uninitialized, lexer will still statically
 * calculate fixed tag value based on initialized value
 * (and spoil default value expected by the programmer).
 */
void make_tags(const std::vector<const RegExpRule*> &rs, std::valarray<Tag> &tags)
{
	const size_t nrs = rs.size();
	for (size_t i = 0, tagidx = 0; i < nrs; ++i) {
		size_t base = Tag::NONE, dist = 0;
		// don't optimize fixed-length trailing context with generic API
		// unless tags are explicitly enabled: generic API needs base tag
		// to restore fixed-length trailing context, and base existence
		// is only guaranteed if tags are mandatory
		if (!opts->contexts && opts->input_api.type() == InputAPI::CUSTOM) {
			dist = VARDIST;
		}
		make_tags_var_fix(i, tags, tagidx, rs[i]->re, dist, base);
	}

}

} // namespace re2c
