#include "src/ir/nfa/nfa.h"

namespace re2c {

static size_t sizeof_regexp(const RegExp *re)
{
	switch (re->tag) {
		case RegExp::NIL:
			return 0;
		case RegExp::SYM:
			return 1;
		case RegExp::ALT:
			return sizeof_regexp(re->pld.alt.re1)
				+ sizeof_regexp(re->pld.alt.re2)
				+ 1;
		case RegExp::CAT:
			return sizeof_regexp(re->pld.cat.re1)
				+ sizeof_regexp(re->pld.cat.re2);
		case RegExp::ITER:
			return sizeof_regexp(re->pld.iter.re)
				+ 1;
		case RegExp::TAG:
			return 1;
		default:
			assert(false);
	}
}

size_t sizeof_regexps(const std::vector<const RegExpRule*> &regexps)
{
	const size_t nregexps = regexps.size();
	size_t size = nregexps - 1;
	for (size_t i = 0; i < nregexps; ++i) {
		size += sizeof_regexp(regexps[i]->re) + 1;
	}
	return size;
}

} // namespace re2c
