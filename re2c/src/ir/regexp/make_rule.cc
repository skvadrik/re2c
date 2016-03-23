#include <limits>
#include <sstream>

#include "src/conf/opt.h"
#include "src/globals.h"
#include "src/ir/regexp/regexp.h"

namespace re2c
{

static uint32_t fixlen(const RegExp *re);
static bool nullable(const RegExp *re);
static const RegExp *copy_rebase(const RegExp *re, size_t shift);

CtxVar::CtxVar(const std::string *n, rule_rank_t rank)
	: name(n)
	, fullname()
{
	std::ostringstream s;
	s << "yyctx" << rank;
	if (name != NULL) {
		s << *name;
	}
	fullname = s.str();
}

CtxFix::CtxFix(const std::string *n, size_t b, size_t d):
	name(n),
	base(b),
	dist(d)
{}

const size_t CtxFix::RIGHTMOST = std::numeric_limits<size_t>::max();

const RegExp *make_rule(
	std::vector<CtxVar> &contexts,
	const Loc &loc,
	std::pair<std::vector<const RegExp*>, std::vector<std::string*> > *ctxs,
	rule_rank_t rank,
	const Code *code,
	const std::string *newcond)
{
	std::vector<const RegExp*> &rs = ctxs->first;
	std::vector<std::string*> &ctxnames = ctxs->second;
	const size_t nctxs = ctxnames.size();
	assert(rs.size() == nctxs + 1);

	std::vector<size_t> dist(nctxs + 1, 0);
	std::vector<size_t> base(nctxs + 1, nctxs);
	// right-fix all contexts
	for (size_t i = nctxs; i > 0; --i) {
		const size_t fl = fixlen(rs[i]);

		// generic API needs base to restore fixed-length trailing contexts
		// and base is only guaranteed when non-trailing contexts are enabled
		const bool lack_api = !opts->contexts // => every context is trailing
			&& opts->input_api.type() == InputAPI::CUSTOM;

		if (fl == ~0u || lack_api) {
			base[i - 1] = i - 1;
		} else {
			base[i - 1] = base[i];
			dist[i - 1] = fl;
			if (i < nctxs && ctxnames[i] != NULL) {
				dist[i - 1] += dist[i];
			}
		}
	}

	Trail trail;

	std::vector<size_t> base2var(nctxs + 1, CtxFix::RIGHTMOST);
	std::vector<size_t> ctxvar;
	const RegExp *r = rs[0];
	for (size_t i = 0; i < nctxs; ++i) {
		const RegExp *s = rs[i + 1];
		if (base[i] == i) {
			const std::string *name = ctxnames[i];
			const size_t idx = contexts.size();
			base2var[i] = idx;
			contexts.push_back(CtxVar(name, rank));
			if (name != NULL) {
				ctxvar.push_back(idx);
			} else {
				trail.make_var(idx);
			}
			s = RegExp::ctx(s, idx);
		}
		r = RegExp::cat(r, s);
	}

	std::vector<CtxFix> ctxfix;
	for (size_t i = 0; i < nctxs; ++i) {
		if (base[i] != i) {
			const std::string *name = ctxnames[i];
			if (name != NULL) {
				CtxFix ctx(name, base2var[base[i]], dist[i]);
				ctxfix.push_back(ctx);
			} else {
				trail.make_fix(dist[i]);
			}
		}
	}

	bool null = nullable(rs[0]);
	for (size_t i = 0; i < nctxs && null && ctxnames[i] != NULL; ++i) {
		null = nullable(rs[i + 1]);
	}

	RuleInfo *info = new RuleInfo(loc, rank, code, newcond, null, ctxvar, ctxfix, trail);
	r = RegExp::rule(r, info);

	return r;
}

const RegExp *make_rule_ctxfree(
	const Loc &loc,
	const RegExp *re,
	rule_rank_t rank,
	const Code *code,
	const std::string *newcond)
{
	RuleInfo *info = new RuleInfo(loc, rank, code, newcond, nullable(re),
		std::vector<size_t>(), std::vector<CtxFix>(), Trail());
	return RegExp::rule(re, info);
}

// Used to duplicate <*> rules in conditions.
// Duplicates part of regexp containing contexts that must be fixed
// (the rest of regexp is shared: it's immutable anyway).
// Duplicates rule info (rule reachability and shadow set differ for
// different specs, rule rank must be updated).
const RegExp *make_rule_copy(const RegExp *re, rule_rank_t rank, size_t shift)
{
	return RegExp::rule(
		copy_rebase(re->pld.rule.re, shift),
		RuleInfo::copy_rebase(re->pld.rule.info, rank, shift));
}

const RegExp *copy_rebase(const RegExp *re, size_t shift)
{
	const RegExp *r = re;
	switch (re->tag) {
		case RegExp::CAT:
			r = RegExp::cat(
				copy_rebase(re->pld.cat.re1, shift),
				copy_rebase(re->pld.cat.re2, shift));
			break;
		case RegExp::CTX:
			r = RegExp::ctx(
				copy_rebase(re->pld.ctx.re, shift),
				re->pld.ctx.info + shift);
			break;
		case RegExp::NIL:
		case RegExp::SYM:
		case RegExp::ALT:
		case RegExp::ITER:
		case RegExp::RULE:
			break;
	}
	return r;
}

uint32_t fixlen(const RegExp *re)
{
	switch (re->tag) {
		case RegExp::NIL:
			return 0;
		case RegExp::SYM:
			return 1;
		case RegExp::ALT: {
			const uint32_t l1 = fixlen(re->pld.alt.re1);
			const uint32_t l2 = fixlen(re->pld.alt.re2);
			return l1 == l2 ? l1 : ~0u;
		}
		case RegExp::CAT: {
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
		case RegExp::CTX:
			return fixlen(re->pld.ctx.re);
		case RegExp::ITER:
		case RegExp::RULE:
			return ~0u;
	}
}

bool nullable(const RegExp *re)
{
	switch (re->tag) {
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
		case RegExp::CTX:
		case RegExp::RULE:
			assert(false);
			return false;
	}
}

} // namespace re2c
