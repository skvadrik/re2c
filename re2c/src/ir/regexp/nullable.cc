#include "src/conf/opt.h"
#include "src/ir/regexp/regexp.h"
#include "src/globals.h"

namespace re2c {

static bool nullable(const RegExp *re, bool &trail)
{
	if (trail) {
		return true;
	}
	switch (re->type) {
		case RegExp::NIL:
		case RegExp::ITER:
			return true;
		case RegExp::TAG:
			if (re->tag == NULL) {
				trail = true;
			}
			return true;
		case RegExp::SYM:
			return false;
		case RegExp::ALT:
			return nullable(re->alt.re1, trail)
				|| nullable(re->alt.re2, trail);
		case RegExp::CAT:
			return nullable(re->cat.re1, trail)
				&& nullable(re->cat.re2, trail);
		default:
			assert(false);
	}
}

/*
 * warn about rules that match empty string
 * (including rules with nonempty trailing context)
 * false positives on partially self-shadowed rules like [^]?
 */
void warn_nullable(const std::vector<const RegExpRule*> &regexps,
	const std::string &cond)
{
	const size_t nregexps = regexps.size();
	for (size_t i = 0; i < nregexps; ++i) {
		const RegExpRule *r = regexps[i];
		bool trail = false;
		if (nullable(r->re, trail)) {
			warn.match_empty_string(r->info->loc.line, cond);
		}
	}
}

} // namespace re2c
