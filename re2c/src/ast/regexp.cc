#include <limits>

#include "src/ast/regexp.h"

namespace re2c
{

free_list<RegExp*> RegExp::flist;

const uint32_t RegExp::MANY = std::numeric_limits<uint32_t>::max();

bool RegExp::need_wrap(const RegExp *re)
{
	switch (re->type) {
		case RegExp::ITER:
		case RegExp::NIL:
		case RegExp::SCHAR:
		case RegExp::ICHAR:
		case RegExp::CLASS:
		case RegExp::DOT:
		case RegExp::DEFAULT:
		case RegExp::TAG:
		case RegExp::CAP:
			return false;
		case RegExp::ALT:
		case RegExp::CAT:
		case RegExp::DIFF:
		case RegExp::REF:
			return true;
	}
	assert(false);
}

} // namespace re2c
