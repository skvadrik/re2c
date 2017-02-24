#include <stdlib.h>

#include "src/conf/msg.h"
#include "src/ir/nfa/nfa.h"

namespace re2c {

static void assert_tags_used_once(const Rule &rule,
	const std::vector<Tag> &tags)
{
	std::set<std::string> names;
	const std::string *name = NULL;

	for (size_t t = rule.ltag; t < rule.htag; ++t) {
		name = tags[t].name;
		if (name && !names.insert(*name).second) {
			error("line %u: tag '%s' is used multiple times in the same rule",
				rule.code->fline, name->c_str());
			exit(1);
		}
	}
}

void init_rules(const std::vector<RegExpRule> &regexps,
	std::valarray<Rule> &rules, const std::vector<Tag> &tags)
{
	const size_t
		nr = rules.size(),
		nt = tags.size();

	for (size_t r = 0, t = 0; r < nr; ++r) {
		Rule &rule = rules[r];
		rule.code = regexps[r].code;

		rule.ltag = t;
		for (; t < nt && tags[t].rule == r; ++t);
		rule.htag = t;

		rule.ttag = rule.htag;
		if (rule.ltag < rule.ttag && tags[rule.ttag - 1].name == NULL) --rule.ttag;

		assert_tags_used_once(rule, tags);
	}
}

} // namespace re2c
