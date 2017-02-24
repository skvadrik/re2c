#include "src/ir/nfa/nfa.h"

namespace re2c {

nfa_t::nfa_t(const std::vector<RegExpRule> &regexps, input_api_t input)
	: max_size(0)
	, size(0)
	, states(NULL)
	, rules(*new std::valarray<Rule>(regexps.size()))
	, tags(*new std::vector<Tag>())
	, root(NULL)
{
	size_t ntags = 0;
	max_size = counters(regexps, ntags);

	states = new nfa_state_t[max_size];
	regexps2nfa(regexps, *this, input);

	init_rules(regexps, rules, tags);
}

nfa_t::~nfa_t()
{
	delete[] states;
}

} // namespace re2c
