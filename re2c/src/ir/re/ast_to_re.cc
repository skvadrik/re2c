#include "src/conf/msg.h"
#include "src/ir/re/re.h"

namespace re2c {

static RE *ast_to_re(RESpec &spec, const RegExp *ast, size_t &ncap)
{
	RE::alc_t &alc = spec.alc;
	std::vector<Tag> &tags = spec.tags;

	switch (ast->type) {
		default: assert(false);
		case RegExp::NIL:
			return re_nil(alc);
		case RegExp::SYM:
			return re_sym(alc, ast->sym);
		case RegExp::ALT: {
			RE *x = ast_to_re(spec, ast->alt.re1, ncap);
			RE *y = ast_to_re(spec, ast->alt.re2, ncap);
			return re_alt(alc, x, y);
		}
		case RegExp::CAT: {
			RE *x = ast_to_re(spec, ast->cat.re1, ncap);
			RE *y = ast_to_re(spec, ast->cat.re2, ncap);
			return re_cat(alc, x, y);
		}
		case RegExp::TAG: {
			RE *t = re_tag(alc, tags.size(), false);
			tags.push_back(Tag(ast->tag));
			return t;
		}
		case RegExp::CAP: {
			const RegExp *x = ast->cap;
			if (x->type == RegExp::REF) x = x->ref.re;

			RE *t1 = re_tag(alc, tags.size(), false);
			tags.push_back(Tag(3 * ncap));

			RE *t2 = re_tag(alc, tags.size(), false);
			tags.push_back(Tag(3 * ncap + 1));

			++ncap;
			return re_cat(alc, t1, re_cat(alc, ast_to_re(spec, x, ncap), t2));
		}
		case RegExp::REF:
			error("implicit grouping is forbidden with '--posix-captures'"
				" option, please wrap '%s' in capturing parenthesis",
				ast->ref.name->c_str());
			exit(1);
		case RegExp::ITER: {
			const uint32_t
				n = ast->iter.min,
				n1 = std::max(n, 1u),
				m = std::max(n, ast->iter.max);
			const RegExp *x = ast->iter.re;

			RE *t1 = NULL, *t2 = NULL, *t3 = NULL;
			if (x->type == RegExp::CAP) {
				x = x->cap;
				if (x->type == RegExp::REF) x = x->ref.re;

				t1 = re_tag(alc, tags.size(), false);
				tags.push_back(Tag(3 * ncap));

				t2 = re_tag(alc, tags.size(), false);
				tags.push_back(Tag(3 * ncap + 1));

				if (m > 1) {
					t3 = re_tag(alc, tags.size(), false);
					tags.push_back(Tag(3 * ncap + 2));
				}

				++ncap;
			}

			RE *y = NULL;
			if (m > 0) {
				y = ast_to_re(spec, x, ncap);
				y = re_cat(alc, t3, y);
				y = re_iter(alc, y, n1, m);
			}
			y = re_cat(alc, t1, re_cat(alc, y, t2));
			if (n == 0) {
				y = re_alt(alc, y, re_nil(alc));
			}
			return y;
		}
	}
}

static void assert_tags_used_once(const Rule &rule, const std::vector<Tag> &tags)
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

static void init_rule(Rule &rule, const Code *code, const std::vector<Tag> &tags,
	size_t ltag, size_t ncap)
{
	rule.code = code;
	rule.ltag = ltag;
	rule.htag = tags.size();
	for (rule.ttag = ltag; rule.ttag < rule.htag && !trailing(tags[rule.ttag]); ++rule.ttag);
	rule.ncap = ncap;
	assert_tags_used_once(rule, tags);
}

RESpec::RESpec(const std::vector<RegExpRule> &ast)
	: alc()
	, res()
	, charset(*new std::vector<uint32_t>)
	, tags(*new std::vector<Tag>)
	, rules(*new std::valarray<Rule>(ast.size()))
{
	for (size_t i = 0; i < ast.size(); ++i) {
		size_t ltag = tags.size(), ncap = 0;
		res.push_back(ast_to_re(*this, ast[i].re, ncap));
		init_rule(rules[i], ast[i].code, tags, ltag, ncap);
	}
}

} // namespace re2c
