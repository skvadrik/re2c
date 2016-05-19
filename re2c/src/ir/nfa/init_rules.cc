#include <stdlib.h>

#include "src/conf/msg.h"
#include "src/ir/nfa/nfa.h"

namespace re2c {

static void assert_no_tags_in_trailing_context(const Rule &rule,
	const std::valarray<Tag> &tags)
{
	// rule tags should not contain other trailing contexts
	for (size_t i = rule.ltag; i < rule.htag; ++i) {
		if (tags[i].name == NULL) {
			error("line %u: tags in trailing context",
				rule.info->loc.line);
			exit(1);
		}
	}
}

static void assert_tags_used_once(const Rule &rule,
	const std::valarray<Tag> &tags)
{
	std::set<std::string> names;
	for (size_t i = rule.ltag; i < rule.htag; ++i) {
		const std::string *name = tags[i].name;
		if (name && !names.insert(*name).second) {
			error("line %u: tag '%s' is used multiple"
				" times in the same rule",
				rule.info->loc.line, name->c_str());
			exit(1);
		}
	}
}

void init_rules(const std::vector<const RegExpRule*> &regexps,
	std::valarray<Rule> &rules,
	const std::valarray<Tag> &tags,
	Tagpool &tagpool)
{
	const size_t nr = rules.size();
	const size_t nt = tags.size();

	for (size_t r = 0, t = 0; r < nr; ++r) {
		Rule &rule = rules[r];
		rule.info = regexps[r]->info;

		rule.ltag = t;
		for (; t < nt && tags[t].rule == r; ++t);
		rule.htag = t;

		// mark *all* variable tags, including trailing context
		bool *mask = new bool[nt]();
		for (size_t i = rule.ltag; i < rule.htag; ++i) {
			mask[i] = tags[i].type == Tag::VAR;
		}
		rule.tags = tagpool.insert(mask);
		delete[] mask;

		// tags in trailing context are forbidden (they make no sense),
		// and since tags are constructed in reversed order, this implies
		// that trailing context, if present, can only be the first tag
		if (rule.ltag < rule.htag && tags[rule.ltag].name == NULL) {
			rule.trail = rule.ltag++;
		}

		// sanity checks
		assert_no_tags_in_trailing_context(rule, tags);
		assert_tags_used_once(rule, tags);
	}
}

} // namespace re2c
