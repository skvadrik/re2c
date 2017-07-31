#include "src/util/c99_stdint.h"
#include <set>

#include "src/re/re.h"

namespace re2c {

static void split(const RE* re, std::set<uint32_t> &cs)
{
	switch (re->type) {
		case RE::NIL: break;
		case RE::TAG: break;
		case RE::SYM:
			for (const Range *r = re->sym; r; r = r->next()) {
				cs.insert(r->lower());
				cs.insert(r->upper());
			}
			break;
		case RE::ALT:
			split(re->alt.re1, cs);
			split(re->alt.re2, cs);
			break;
		case RE::CAT:
			split(re->cat.re1, cs);
			split(re->cat.re2, cs);
			break;
		case RE::ITER:
			split(re->iter.re, cs);
			break;
	}
}

/* The original set of code units (charset) might be very large.
 * A common trick it is to split charset into disjoint character ranges
 * and choose a representative of each range (we choose lower bound).
 * The set of all representatives is the new (compacted) charset.
 * Don't forget to include zero and upper bound, even if they
 * do not explicitely apper in ranges.
 */
void split_charset(RESpec &spec)
{
	std::set<uint32_t> cs;

	std::vector<RE*>::const_iterator
		i = spec.res.begin(),
		e = spec.res.end();
	for (; i != e; ++i) {
		split(*i, cs);
	}
	cs.insert(0);
	cs.insert(spec.opts->encoding.nCodeUnits());

	spec.charset.insert(spec.charset.end(), cs.begin(), cs.end());
}

} // namespace re2c
