#include "src/ir/nfa/nfa.h"

namespace re2c {

nfa_t::nfa_t(const std::vector<const RegExpRule*> &regexps)
	: max_size(sizeof_regexps(regexps))
	, size(0)
	, states(new nfa_state_t[max_size])
	, rules(*new std::valarray<Rule>(regexps.size()))
	, vartags(*new std::vector<CtxVar>)
	, fixtags(*new std::vector<CtxFix>)
	, root(NULL)
{
	std::vector<size_t> tagidxs;
	make_tags(regexps, vartags, fixtags, tagidxs);

	regexps2nfa(regexps, *this, tagidxs.begin());

	init_rules(rules, regexps, vartags, fixtags);
}

nfa_t::~nfa_t()
{
	delete[] states;
}

} // namespace re2c
