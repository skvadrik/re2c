#include "src/util/c99_stdint.h"
#include <set>

#include "src/ir/regexp/regexp.h"
#include "src/util/range.h"

namespace re2c {

static void split(const RegExp* re, std::set<uint32_t> &cs)
{
	switch (re->type) {
		case RegExp::NIL:
		case RegExp::TAG:
			break;
		case RegExp::SYM:
			for (const Range *r = re->sym; r; r = r->next()) {
				cs.insert(r->lower());
				cs.insert(r->upper());
			}
			break;
		case RegExp::ALT:
			split(re->alt.re1, cs);
			split(re->alt.re2, cs);
			break;
		case RegExp::CAT:
			split(re->cat.re1, cs);
			split(re->cat.re2, cs);
			break;
		case RegExp::ITER:
			split(re->iter.re, cs);
			break;
	}
}

void split(const std::vector<RegExpRule> &rs, std::set<uint32_t> &cs)
{
	const size_t nrs = rs.size();
	for (size_t i = 0; i < nrs; ++i) {
		split(rs[i].re, cs);
	}
}

} // namespace re2c
