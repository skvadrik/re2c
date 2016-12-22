#include <stdlib.h>

#include "src/conf/msg.h"
#include "src/ir/nfa/nfa.h"

namespace re2c {

static void assert_tags_used_once(const Rule &rule,
	const std::vector<VarTag> &vartags, const std::vector<FixTag> &fixtags)
{
	std::set<std::string> names;
	const std::string *name = NULL;

	for (size_t t = rule.lvar; t < rule.hvar; ++t) {
		name = vartags[t].name;
		if (name && !names.insert(*name).second) goto error;
	}

	for (size_t t = rule.lfix; t < rule.hfix; ++t) {
		name = fixtags[t].name;
		if (name && !names.insert(*name).second) goto error;
	}

	return;

error:
	error("line %u: tag '%s' is used multiple times in the same rule",
		rule.code->fline, name->c_str());
	exit(1);
}

void init_rules(const std::vector<const RegExpRule*> &regexps,
	std::valarray<Rule> &rules, const std::vector<VarTag> &vartags,
	const std::vector<FixTag> &fixtags)
{
	const size_t
		nr = rules.size(),
		nv = vartags.size(),
		nf = fixtags.size();

	for (size_t r = 0, v = 0, f = 0, t; r < nr; ++r) {
		Rule &rule = rules[r];
		rule.code = regexps[r]->code;

		rule.lvar = v;
		for (; v < nv && vartags[v].rule == r; ++v);
		rule.hvar = v;

		rule.lfix = f;
		for (; f < nf && fixtags[f].rule == r; ++f);
		rule.hfix = f;

		for (t = rule.lvar; t < rule.hvar && vartags[t].name; ++t);
		rule.tvar = t;

		for (t = rule.lfix; t < rule.hfix && fixtags[t].name; ++t);
		rule.tfix = t;

		assert_tags_used_once(rule, vartags, fixtags);
	}
}

} // namespace re2c
