#include "src/ir/regexp/regexp.h"

namespace re2c {

static bool nullable(const RegExp *re, bool &trail)
{
	if (trail) {
		return true;
	}
	switch (re->type) {
		default: assert(false);
		case RegExp::NIL: return true;
		case RegExp::SYM: return false;
		case RegExp::ITER:
			return re->iter.min == 0
				|| nullable(re->iter.re, trail);
		case RegExp::TAG:
			if (re->tag == NULL) {
				trail = true;
			}
			return true;
		case RegExp::ALT:
			return nullable(re->alt.re1, trail)
				|| nullable(re->alt.re2, trail);
		case RegExp::CAT:
			return nullable(re->cat.re1, trail)
				&& nullable(re->cat.re2, trail);
	}
}

/*
 * warn about rules that match empty string
 * (including rules with nonempty trailing context)
 * false positives on partially self-shadowed rules like [^]?
 */
void warn_nullable(const std::vector<RegExpRule> &regexps,
	const std::string &cond, Warn &warn)
{
	const size_t nregexps = regexps.size();
	for (size_t i = 0; i < nregexps; ++i) {
		const RegExpRule &r = regexps[i];
		bool trail = false;
		if (nullable(r.re, trail)) {
			warn.match_empty_string(r.code->fline, cond);
		}
	}
}

} // namespace re2c
