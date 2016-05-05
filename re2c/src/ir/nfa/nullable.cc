#include "src/ir/nfa/nfa.h"

namespace re2c {

static bool nullable(const RegExp *re, bool &trail)
{
	if (trail) {
		return true;
	}
	switch (re->tag) {
		case RegExp::NIL:
		case RegExp::ITER:
			return true;
		case RegExp::TAG:
			if (re->pld.ctx.name == NULL) {
				trail = true;
			}
			return true;
		case RegExp::SYM:
			return false;
		case RegExp::ALT:
			return nullable(re->pld.alt.re1, trail)
				|| nullable(re->pld.alt.re2, trail);
		case RegExp::CAT:
			return nullable(re->pld.cat.re1, trail)
				&& nullable(re->pld.cat.re2, trail);
		default:
			assert(false);
	}
}

bool nullable_rule(const RegExpRule *rule)
{
	bool trail = false;
	return nullable(rule->re, trail);
}

} // namespace re2c
