#include <limits>

#include "src/ir/rule.h"

namespace re2c
{

const size_t Rule::NONE = std::numeric_limits<size_t>::max();

void init_tags(Rule &rule, size_t ntags)
{
	bool *tags = new bool[ntags]();
	for (size_t t = rule.ltag; t < rule.htag; ++t) {
		tags[t] = true;
	}
	if (rule.trail.type == Trail::VAR) {
		tags[rule.trail.pld.var] = true;
	}
	rule.tags = tags;
}

} // namespace re2c
