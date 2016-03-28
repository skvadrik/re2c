#include "src/util/c99_stdint.h"
#include <set>

#include "src/ir/regexp/regexp.h"
#include "src/util/range.h"

namespace re2c {

static void split(const RegExp* re, std::set<uint32_t> &cs)
{
	switch (re->tag) {
		case RegExp::NIL:
			break;
		case RegExp::SYM:
			for (const Range *r = re->pld.sym.range; r; r = r->next()) {
				cs.insert(r->lower());
				cs.insert(r->upper());
			}
			break;
		case RegExp::ALT:
			split(re->pld.alt.re1, cs);
			split(re->pld.alt.re2, cs);
			break;
		case RegExp::CAT:
			split(re->pld.cat.re1, cs);
			split(re->pld.cat.re2, cs);
			break;
		case RegExp::ITER:
			split(re->pld.iter.re, cs);
			break;
	}
}

void split(const std::vector<const RegExpRule*> &rs, std::set<uint32_t> &cs)
{
	for (size_t i = 0; i < rs.size(); ++i) {
		const std::vector<const RegExp*> &regexps = rs[i]->regexps;
		for (size_t j = 0; j < regexps.size(); ++j) {
			split(regexps[j], cs);
		}
	}
}

} // namespace re2c
