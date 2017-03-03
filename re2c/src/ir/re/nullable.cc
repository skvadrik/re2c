#include "src/ir/re/re.h"

namespace re2c {

static bool nullable(const RESpec &spec, const RE *re, bool &trail)
{
	if (trail) return true;

	switch (re->type) {
		default: assert(false);
		case RE::NIL: return true;
		case RE::SYM: return false;
		case RE::ITER:
			return nullable(spec, re->iter.re, trail);
		case RE::TAG:
			trail |= spec.tags[re->tag.idx].name == NULL;
			return true;
		case RE::ALT:
			return nullable(spec, re->alt.re1, trail)
				|| nullable(spec, re->alt.re2, trail);
		case RE::CAT:
			return nullable(spec, re->cat.re1, trail)
				&& nullable(spec, re->cat.re2, trail);
	}
}

/*
 * warn about rules that match empty string
 * (including rules with nonempty trailing context)
 * false positives on partially self-shadowed rules like [^]?
 */
void warn_nullable(const RESpec &spec, const std::string &cond, Warn &warn)
{
	const size_t nre = spec.res.size();
	for (size_t i = 0; i < nre; ++i) {
		bool trail = false;
		if (nullable(spec, spec.res[i], trail)) {
			warn.match_empty_string(spec.rules[i].code->fline, cond);
		}
	}
}

} // namespace re2c
