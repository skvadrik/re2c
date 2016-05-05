#include <stdlib.h>

#include "src/conf/msg.h"
#include "src/ir/nfa/nfa.h"

namespace re2c {

static void fatal_tags_in_trail(uint32_t line)
{
	error("line %u: tags in trailing context", line);
	exit(1);
}

static void assert_no_tags_in_trailing_context(const Rule &rule,
	const std::vector<CtxVar> &vartags,
	const std::vector<CtxFix> &fixtags)
{
	const uint32_t line = rule.info->loc.line;
	// rule tags should not contain other trailing contexts
	for (size_t i = rule.lfixtag; i < rule.hfixtag; ++i) {
		if (fixtags[i].codename == NULL) {
			fatal_tags_in_trail(line);
		}
	}
	for (size_t i = rule.lvartag; i < rule.hvartag; ++i) {
		if (vartags[i].codename == NULL) {
			fatal_tags_in_trail(line);
		}
	}
	// fixed trailing context must be fixed on cursor
	if (rule.trail.type == Trail::FIX
		&& fixtags[rule.trail.fix].base != CtxFix::RIGHTMOST) {
		fatal_tags_in_trail(line);
	}
}

static void fatal_tag_reuse(uint32_t line, const char *tag)
{
	error("line %u: tag '%s' is used multiple times in the same rule", line, tag);
	exit(1);
}

static void assert_tags_used_once(const Rule &rule,
	const std::vector<CtxVar> &vartags,
	const std::vector<CtxFix> &fixtags)
{
	const uint32_t line = rule.info->loc.line;
	std::set<std::string> names;
	for (size_t i = rule.lfixtag; i < rule.hfixtag; ++i) {
		const std::string *name = fixtags[i].codename;
		if (name && !names.insert(*name).second) {
			fatal_tag_reuse(line, name->c_str());
		}
	}
	for (size_t i = rule.lvartag; i < rule.hvartag; ++i) {
		const std::string *name = vartags[i].codename;
		if (name && !names.insert(*name).second) {
			fatal_tag_reuse(line, name->c_str());
		}
	}
}

void init_rules(std::valarray<Rule> &rules,
	const std::vector<const RegExpRule*> &regexps,
	const std::vector<CtxVar> &vartags,
	const std::vector<CtxFix> &fixtags)
{
	const size_t nf = fixtags.size();
	const size_t nv = vartags.size();
	const size_t nr = rules.size();

	for (size_t r = 0, f = 0, v = 0; r < nr; ++r) {
		Rule &rule = rules[r];
		rule.info = regexps[r]->info;
		rule.nullable = nullable_rule(regexps[r]);

		rule.lfixtag = f;
		for (; f < nf && fixtags[f].rule == r; ++f);
		rule.hfixtag = f;

		rule.lvartag = v;
		for (; v < nv && vartags[v].rule == r; ++v);
		rule.hvartag = v;

		// mark *all* variable tags, including trailing context
		rule.tags = new bool[nv]();
		for (size_t t = rule.lvartag; t < rule.hvartag; ++t) {
			rule.tags[t] = true;
		}

		// tags in trailing context are forbidden (they make no sense),
		// and since tags are constructed in reversed order, this implies
		// that trailing context, if present, can only be the first tag
		if (rule.lfixtag < rule.hfixtag && fixtags[rule.lfixtag].codename == NULL) {
			rule.trail.make_fix(rule.lfixtag++);
		} else if (rule.lvartag < rule.hvartag && vartags[rule.lvartag].codename == NULL) {
			rule.trail.make_var(rule.lvartag++);
		}

		// sanity checks
		assert_no_tags_in_trailing_context(rule, vartags, fixtags);
		assert_tags_used_once(rule, vartags, fixtags);
	}
}

} // namespace re2c
