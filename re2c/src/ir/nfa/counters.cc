#include "src/ir/nfa/nfa.h"

namespace re2c {

static size_t count(const RegExp *re, size_t &ntags)
{
	switch (re->type) {
		case RegExp::NIL:
			return 0;
		case RegExp::SYM:
			return 1;
		case RegExp::ALT: {
			const size_t n = ntags;
			return count(re->alt.re1, ntags)
				+ count(re->alt.re2, ntags)
				+ 1 /* alternative */
				+ (ntags - n + 1); /* default tags */
		}
		case RegExp::CAT:
			return count(re->cat.re1, ntags)
				+ count(re->cat.re2, ntags);
		case RegExp::ITER:
			return count(re->iter, ntags)
				+ 1;
		case RegExp::TAG:
			++ntags;
			return 1;
		default:
			assert(false);
	}
}

size_t counters(const std::vector<const RegExpRule*> &regexps, size_t &ntags)
{
	const size_t nregexps = regexps.size();
	size_t size = nregexps - 1;
	for (size_t i = 0; i < nregexps; ++i) {
		size += count(regexps[i]->re, ntags) + 1;
	}
	return size;
}

} // namespace re2c
