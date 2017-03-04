#include "src/conf/msg.h"
#include "src/re/re.h"
#include "src/re/empty_class_policy.h"
#include "src/re/encoding/case.h"
#include "src/re/encoding/enc.h"
#include "src/re/encoding/utf16/utf16_regexp.h"
#include "src/re/encoding/utf8/utf8_regexp.h"

namespace re2c {

/* note [default regexp]
 *
 * Create a byte range that includes all possible input characters.
 * This may include characters, which do not map to any valid symbol
 * in current encoding. For encodings, which directly map symbols to
 * input characters (ASCII, EBCDIC, UTF-32), it equals [^]. For other
 * encodings (UTF-16, UTF-8), [^] and this range are different.
 *
 * Also note that default range doesn't respect encoding policy
 * (the way invalid code points are treated).
 */

static RE *ast_to_re(RESpec &spec, const RegExp *ast, size_t &ncap)
{
	RE::alc_t &alc = spec.alc;
	std::vector<Tag> &tags = spec.tags;
	const opt_t *opts = spec.opts;
	Warn &warn = spec.warn;

	switch (ast->type) {
		default: assert(false);
		case RegExp::NIL:
			return re_nil(alc);
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
		case RegExp::SCHAR:
			return re_schar(alc, ast->line, ast->column, ast->schar, opts);
		case RegExp::ICHAR:
			return re_ichar(alc, ast->line, ast->column, ast->ichar, opts);
		case RegExp::CLASS:
			return re_class(alc, ast->line, ast->column, ast->cls, opts, warn);
		case RegExp::DIFF: {
			RE *x = ast_to_re(spec, ast->diff.re1, ncap);
			RE *y = ast_to_re(spec, ast->diff.re2, ncap);
			if (x->type != RE::SYM || y->type != RE::SYM) {
				fatal_error(ast->line, ast->column, "can only difference char sets");
			}
			return re_class(alc, ast->line, ast->column, Range::sub(x->sym, y->sym), opts, warn);
		}
		case RegExp::DOT: {
			uint32_t c = '\n';
			if (!opts->encoding.encode(c)) {
				fatal_error(ast->line, ast->column, "bad code point: '0x%X'", c);
			}
			return re_class(alc, ast->line, ast->column,
				Range::sub(opts->encoding.fullRange(), Range::sym(c)), opts, warn);
		}
		case RegExp::DEFAULT:
			// see note [default regexp]
			return re_sym(alc, Range::ran(0, opts->encoding.nCodeUnits()));
	}
}

RE *re_schar(RE::alc_t &alc, uint32_t line, uint32_t column, uint32_t c, const opt_t *opts)
{
	if (!opts->encoding.encode(c)) {
		fatal_error(line, column, "bad code point: '0x%X'", c);
	}
	switch (opts->encoding.type ()) {
		case Enc::UTF16: return UTF16Symbol(alc, c);
		case Enc::UTF8: return UTF8Symbol(alc, c);
		default: return re_sym(alc, Range::sym(c));
	}
}

RE *re_ichar(RE::alc_t &alc, uint32_t line, uint32_t column, uint32_t c, const opt_t *opts)
{
	if (is_alpha(c)) {
		return re_alt(alc,
			re_schar(alc, line, column, to_lower_unsafe(c), opts),
			re_schar(alc, line, column, to_upper_unsafe(c), opts));
	} else {
		return re_schar(alc, line, column, c, opts);
	}
}

RE *re_class(RE::alc_t &alc, uint32_t line, uint32_t column, const Range *r, const opt_t *opts, Warn &warn)
{
	if (!r) {
		switch (opts->empty_class_policy) {
			case EMPTY_CLASS_MATCH_EMPTY:
				warn.empty_class(line);
				return re_nil(alc);
			case EMPTY_CLASS_MATCH_NONE:
				warn.empty_class(line);
				break;
			case EMPTY_CLASS_ERROR:
				fatal_error(line, column, "empty character class");
				break;
		}
	}
	switch (opts->encoding.type()) {
		case Enc::UTF16: return UTF16Range(alc, r);
		case Enc::UTF8: return UTF8Range(alc, r);
		default: return re_sym(alc, r);
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

RESpec::RESpec(const std::vector<RegExpRule> &ast, const opt_t *o, Warn &w)
	: alc()
	, res()
	, charset(*new std::vector<uint32_t>)
	, tags(*new std::vector<Tag>)
	, rules(*new std::valarray<Rule>(ast.size()))
	, opts(o)
	, warn(w)
{
	for (size_t i = 0; i < ast.size(); ++i) {
		size_t ltag = tags.size(), ncap = 0;
		res.push_back(ast_to_re(*this, ast[i].re, ncap));
		init_rule(rules[i], ast[i].code, tags, ltag, ncap);
	}
}

} // namespace re2c
