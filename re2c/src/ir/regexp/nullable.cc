#include "src/ir/regexp/regexp.h"

namespace re2c
{

static bool nullable(const RegExp *re)
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

void nullable_rules(const RegExp *re, std::vector<RuleInfo*> &rs)
{
	switch (re->tag) {
		case RegExp::ALT:
			nullable_rules(re->pld.alt.re1, rs);
			nullable_rules(re->pld.alt.re2, rs);
			break;
		case RegExp::RULE:
			if (nullable(re->pld.rule.re)) {
				rs.push_back(re->pld.rule.info);
			}
			break;
		default:
			break;
	}
}

} // end namespace re2c

