#include "src/conf/msg.h"
#include "src/ir/re/re.h"

namespace re2c {

/* note [Kleene star is expressed in terms of plus]
 *
 * In literature Kleene star 'r*' (zero or more repetitions of 'r')
 * is the basic operation. In practice it is more convenient to use
 * 'r+' (one or more repetitions of 'r'), because expansion 'r+ ::= r r*'
 * duplicates 'r', while expansion 'r* = r+ | <empty>' allows to
 * avoid duplication. This is more efficient in general and crucial
 * in cases when duplication of 'r' is forbidden (e.g. if 'r' has tags).
 */

/*
 * note [counted repetition expansion]
 *
 * r{0} ;;= <empty regexp>
 * r{n} ::= r{n-1} r
 * r{n,m} ::= r{n} (r{0} | ... | r{m-n})
 * r{n,} ::= r{n} r*
 */

static RE *ast_to_re(RESpec &spec, const RegExp *ast)
{
	RE::alc_t &alc = spec.alc;
	switch (ast->type) {
		default: assert(false);
		case RegExp::NIL:
			return re_nil(alc);
		case RegExp::SYM:
			return re_sym(alc, ast->sym);
		case RegExp::ALT: {
			RE *x = ast_to_re(spec, ast->alt.re1);
			RE *y = ast_to_re(spec, ast->alt.re2);
			return re_alt(alc, x, y);
		}
		case RegExp::CAT: {
			RE *x = ast_to_re(spec, ast->cat.re1);
			RE *y = ast_to_re(spec, ast->cat.re2);
			return re_cat(alc, x, y);
		}
		case RegExp::TAG: {
			const size_t ntag = spec.tags.size();
			Tag tag = {ast->tag, ntag, Tag::VARDIST};
			spec.tags.push_back(tag);
			return re_tag(alc, ntag, false);
		}
		case RegExp::ITER: {
			const uint32_t
				n = ast->iter.min,
				m = ast->iter.max;
			const RegExp *x = ast->iter.re;

			if (n == 0 && m == 0) {
				return re_nil(alc);
			}

			RE *y = ast_to_re(spec, x);
			if (m == RegExp::MANY) {
				y = re_iter(alc, y);
			} else if (n == 0) {
				y = re_repeat(alc, y, m - 1);
			} else if (m > n) {
				y = re_repeat(alc, y, m - n);
			}
			if (n == 0) {
				y = re_alt(alc, y, re_nil(alc));
			} else {
				for (uint32_t i = 1; i < n; ++i) {
					y = re_cat(alc, ast_to_re(spec, x), y);
				}
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

static void init_rule(Rule &rule, const Code *code, const std::vector<Tag> &tags, size_t ltag)
{
	rule.code = code;
	rule.ltag = ltag;
	rule.htag = tags.size();
	for (rule.ttag = ltag; rule.ttag < rule.htag && tags[rule.ttag].name; ++rule.ttag);
	assert_tags_used_once(rule, tags);
}

RESpec::RESpec(const std::vector<RegExpRule> &ast)
	: alc()
	, res()
	, charset(*new std::vector<uint32_t>)
	, tags(*new std::vector<Tag>)
	, rules(*new std::valarray<Rule>(ast.size()))
{
	for (size_t i = 0, t; i < ast.size(); ++i) {
		t = tags.size();
		res.push_back(ast_to_re(*this, ast[i].re));
		init_rule(rules[i], ast[i].code, tags, t);
	}
}

} // namespace re2c
