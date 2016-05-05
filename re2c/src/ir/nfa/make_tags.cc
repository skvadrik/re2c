#include <limits>

#include "src/conf/opt.h"
#include "src/ir/nfa/nfa.h"
#include "src/globals.h"

namespace re2c {

static const size_t VARDIST = std::numeric_limits<size_t>::max();

static void make_tags_var(size_t nrule,
	std::vector<CtxVar> &vartags,
	const RegExp *re, size_t &dist)
{
	switch (re->tag) {
		case RegExp::NIL: break;
		case RegExp::SYM:
			if (dist != VARDIST) {
				++dist;
			}
			break;
		case RegExp::ALT: {
			size_t d1 = dist, d2 = dist;
			make_tags_var(nrule, vartags, re->pld.alt.re1, d1);
			make_tags_var(nrule, vartags, re->pld.alt.re2, d2);
			dist = (d1 == d2) ? d1 : VARDIST;
			break;
		}
		case RegExp::CAT:
			make_tags_var(nrule, vartags, re->pld.cat.re2, dist);
			make_tags_var(nrule, vartags, re->pld.cat.re1, dist);
			break;
		case RegExp::ITER:
			dist = VARDIST;
			make_tags_var(nrule, vartags, re->pld.iter.re, dist);
			break;
		case RegExp::TAG:
			(size_t&)re->pld.ctx.idx = vartags.size();
			vartags.push_back(CtxVar(re->pld.ctx.name, nrule));
			break;
	}
}

static void make_tags_var_fix(size_t nrule,
	std::vector<CtxVar> &vartags, std::vector<CtxFix> &fixtags,
	const RegExp *re, size_t &dist, size_t &base)
{
	switch (re->tag) {
		case RegExp::NIL:
		case RegExp::SYM:
		case RegExp::ALT:
		case RegExp::ITER:
			make_tags_var(nrule, vartags, re, dist);
			break;
		case RegExp::CAT:
			make_tags_var_fix(nrule, vartags, fixtags, re->pld.cat.re2, dist, base);
			make_tags_var_fix(nrule, vartags, fixtags, re->pld.cat.re1, dist, base);
			break;
		case RegExp::TAG: {
			const std::string *name = re->pld.ctx.name;
			if (dist == VARDIST) {
				base = (size_t&)re->pld.ctx.idx = vartags.size();
				vartags.push_back(CtxVar(name, nrule));
				dist = 0;
			} else {
				fixtags.push_back(CtxFix(name, nrule, base, dist));
			}
			if (name == NULL) {
				dist = 0;
			}
			break;
		}
	}
}

void make_tags(const std::vector<const RegExpRule*> &rs,
	std::vector<CtxVar> &vartags, std::vector<CtxFix> &fixtags)
{
	const size_t nrs = rs.size();
	for (size_t i = 0; i < nrs; ++i) {
		size_t base = CtxFix::RIGHTMOST, dist = 0;
		// don't optimize fixed-length trailing context with generic API
		// unless tags are explicitly enabled: generic API needs base tag
		// to restore fixed-length trailing context, and base existence
		// is only guaranteed if tags are mandatory
		if (!opts->contexts && opts->input_api.type() == InputAPI::CUSTOM) {
			dist = VARDIST;
		}
		make_tags_var_fix(i, vartags, fixtags, rs[i]->re, dist, base);
	}

}

} // namespace re2c
