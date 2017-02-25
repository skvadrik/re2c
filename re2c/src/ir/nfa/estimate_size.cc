#include "src/ir/nfa/nfa.h"

namespace re2c {

static size_t estimate(const RE *re)
{
	switch (re->type) {
		default: assert(false);
		case RE::NIL: return 0;
		case RE::SYM: return 1;
		case RE::TAG: return 1;
		case RE::ALT:
			return estimate(re->alt.re1)
				+ estimate(re->alt.re2)
				+ 1;
		case RE::CAT:
			return estimate(re->cat.re1)
				+ estimate(re->cat.re2);
		case RE::ITER:
			return estimate(re->iter)
				+ 1;
		case RE::REPEAT:
			return estimate(re->repeat.re) * (re->repeat.upto + 1)
				+ re->repeat.upto;
	}
}

size_t estimate_size(const std::vector<RE*> &res)
{
	const size_t nre = res.size();
	size_t size = nre - 1;
	for (size_t i = 0; i < nre; ++i) {
		size += estimate(res[i]) + 1;
	}
	return size;
}

} // namespace re2c
