#include "src/conf/opt.h"
#include "src/ir/nfa/nfa.h"
#include "src/ir/regexp/regexp.h"
#include "src/globals.h"

namespace re2c {

static size_t calc_size(const RegExp *re)
{
	switch (re->tag) {
		case RegExp::NIL:
			return 0;
		case RegExp::SYM:
			return 1;
		case RegExp::ALT:
			return calc_size(re->pld.alt.re1)
				+ calc_size(re->pld.alt.re2)
				+ 1;
		case RegExp::CAT:
			return calc_size(re->pld.cat.re1)
				+ calc_size(re->pld.cat.re2);
		case RegExp::ITER:
			return calc_size(re->pld.iter.re)
				+ 1;
		default:
			assert(false);
	}
}

static size_t calc_size_all(const std::vector<const RegExpRule*> &rs)
{
	size_t size = rs.size() - 1;
	for (size_t i = 0; i < rs.size(); ++i) {
		const std::vector<const RegExp*> &regexps = rs[i]->regexps;
		for (size_t j = 0; j < regexps.size(); ++j) {
			size += calc_size(regexps[j]);
		}
		size += regexps.size();
	}
	return size;
}

static nfa_state_t *compile(const RegExp *re, nfa_t &nfa, nfa_state_t *t)
{
	nfa_state_t *s = NULL;
	switch (re->tag) {
		case RegExp::NIL:
			s = t;
			break;
		case RegExp::SYM:
			s = &nfa.states[nfa.size++];
			s->ran(t, re->pld.sym.range);
			break;
		case RegExp::ALT:
			s = &nfa.states[nfa.size++];
			s->alt(compile(re->pld.alt.re1, nfa, t),
				compile(re->pld.alt.re2, nfa, t));
			break;
		case RegExp::CAT:
			s = compile(re->pld.cat.re2, nfa, t);
			s = compile(re->pld.cat.re1, nfa, s);
			break;
		case RegExp::ITER:
			s = &nfa.states[nfa.size++];
			s->alt(t, compile(re->pld.iter.re, nfa, s));
			break;
	}
	return s;
}

static uint32_t fixlen(const RegExp *re)
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
		case RegExp::ITER:
			return ~0u;
		default:
			assert(false);
	}
}

static bool nullable(const RegExp *re)
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
		default:
			assert(false);
	}
}

static nfa_state_t *compile_rule(
	const RegExpRule *rule,
	nfa_t &nfa)
{
	const std::vector<const RegExp*> &rs = rule->regexps;
	const std::vector<const std::string*> &ctxnames = rule->ctxnames;
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

	nfa_state_t *t = &nfa.states[nfa.size++];
	const size_t nrule = nfa.rules.size();
	t->fin(nrule);
	Rule r(rule->info);

	std::vector<size_t> &ctxvar = r.ctxvar;
	std::vector<CtxFix> &ctxfix = r.ctxfix;
	Trail &trail = r.trail;
	// base2var is filled in right-to-left, this is crucial
	std::vector<size_t> base2var(nctxs + 1, CtxFix::RIGHTMOST);
	for (size_t i = nctxs; i > 0; --i) {
		t = compile(rs[i], nfa, t);
		const std::string *name = ctxnames[i - 1];
		if (base[i - 1] == i - 1) {
			const size_t idx = nfa.contexts.size();
			base2var[i - 1] = idx;
			nfa.contexts.push_back(CtxVar(name, nrule));
			if (name != NULL) {
				ctxvar.push_back(idx);
			} else {
				trail.make_var(idx);
			}
			nfa_state_t *q = &nfa.states[nfa.size++];
			q->ctx(t, idx);
			t = q;
		} else {
			if (name != NULL) {
				CtxFix ctx(name, base2var[base[i - 1]], dist[i - 1]);
				ctxfix.push_back(ctx);
			} else {
				trail.make_fix(dist[i - 1]);
			}
		}
	}
	t = compile(rs[0], nfa, t);

	bool null = nullable(rs[0]);
	for (size_t i = 0; i < nctxs && null && ctxnames[i] != NULL; ++i) {
		null = nullable(rs[i + 1]);
	}
	r.nullable = null;

	nfa.rules.push_back(r);

	return t;
}

static nfa_state_t *compile_rules(
	const std::vector<const RegExpRule*> &rs,
	nfa_t &nfa)
{
	nfa_state_t *s = NULL;
	const size_t nrs = rs.size();
	if (nrs > 0) {
		s = compile_rule(rs[0], nfa);
		for (size_t i = 1; i < nrs; ++i) {
			nfa_state_t *q = &nfa.states[nfa.size++];
			q->alt(s, compile_rule(rs[i], nfa));
			s = q;
		}
	}
	return s;
}

nfa_t::nfa_t(const std::vector<const RegExpRule*> &rs)
	: max_size(calc_size_all(rs))
	, size(0)
	, states(new nfa_state_t[max_size])
	, rules(*new std::vector<Rule>)
	, contexts(*new std::vector<CtxVar>)
	, root(compile_rules(rs, *this))
{}


nfa_t::~nfa_t()
{
	delete[] states;
}

} // namespace re2c
