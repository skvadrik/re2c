#include "src/ir/nfa/nfa.h"

namespace re2c {

static bool nullable(const RegExp *re, bool &trail)
{
	if (trail) {
		return true;
	}
	switch (re->type) {
		case RegExp::NIL:
		case RegExp::ITER:
			return true;
		case RegExp::TAG:
			if (re->tag == NULL) {
				trail = true;
			}
			return true;
		case RegExp::SYM:
			return false;
		case RegExp::ALT:
			return nullable(re->alt.re1, trail)
				|| nullable(re->alt.re2, trail);
		case RegExp::CAT:
			return nullable(re->cat.re1, trail)
				&& nullable(re->cat.re2, trail);
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
