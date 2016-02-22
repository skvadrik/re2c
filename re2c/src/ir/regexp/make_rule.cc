#include "src/conf/opt.h"
#include "src/globals.h"
#include "src/ir/regexp/regexp.h"

namespace re2c
{

static uint32_t fixlen(const RegExp *re);
static bool nullable(const RegExp *re);

const RegExp *make_rule(const Loc &loc, const RegExp *r1, const RegExp *r2,
	rule_rank_t rank, const Code *code, const std::string *newcond)
{
	uint32_t ctx_len = fixlen(r2);
	// cannot emulate 'YYCURSOR -= N' operation with generic API
	if (ctx_len != 0
		&& opts->input_api.type() == InputAPI::CUSTOM) {
		ctx_len = ~0u;
	}
	RuleInfo *info = new RuleInfo(loc, rank, code,
		newcond, ctx_len, nullable(r1));
	return RegExp::rule(r1, r2, info);
}

// Shallow-copy rule's regexps, but deep-copy rule's info.
// Used to duplicate <*> rules in conditions: different conditions
// share regexps (regexps are immutable anyway), but must have an
// individual copy of rule info (rule reachability and shadow set
// are different). Also update rule rank.
const RegExp *make_rule_copy(const RegExp *re, rule_rank_t rank)
{
	const RuleInfo *info = re->pld.rule.info;
	RuleInfo *info_copy = new RuleInfo(info->loc, rank, info->code,
		&info->newcond, info->ctx_len, info->nullable);
	return RegExp::rule(re->pld.rule.re, re->pld.rule.ctx, info_copy);
}

uint32_t fixlen(const RegExp *re)
{
	switch (re->tag) {
		case RegExp::NIL:
			return 0;
		case RegExp::SYM:
			return 1;
		case RegExp::ALT:
		{
			const uint32_t l1 = fixlen(re->pld.alt.re1);
			const uint32_t l2 = fixlen(re->pld.alt.re2);
			return l1 == l2 ? l1 : ~0u;
		}
		case RegExp::CAT:
		{
			const uint32_t l1 = fixlen(re->pld.cat.re1);
			if (l1 == ~0u) {
				return ~0u;
			}
			const uint32_t l2 = fixlen(re->pld.cat.re2);
			if (l2 == ~0u) {
				return ~0u;
			}
			return l1 + l2;
		}
		case RegExp::ITER:
		case RegExp::RULE:
		default:
			return ~0u;
	}
}

bool nullable(const RegExp *re)
{
	switch (re->tag) {
		default:
		case RegExp::NIL:
			return true;
		case RegExp::SYM:
			return false;
		case RegExp::ALT:
			return nullable(re->pld.alt.re1)
				|| nullable(re->pld.alt.re2);
		case RegExp::CAT:
			return nullable(re->pld.cat.re1)
				&& nullable(re->pld.cat.re2);
		case RegExp::ITER:
			return true;
		case RegExp::RULE:
			return nullable(re->pld.rule.re);
	}
}

} // namespace re2c
