#include "src/ir/nfa/nfa.h"

namespace re2c {

static nfa_state_t *regexp2nfa(nfa_t &nfa, size_t nrule, const RegExp *re, nfa_state_t *t)
{
	nfa_state_t *s = NULL;
	switch (re->tag) {
		case RegExp::NIL:
			s = t;
			break;
		case RegExp::SYM:
			s = &nfa.states[nfa.size++];
			s->ran(nrule, t, re->pld.sym.range);
			break;
		case RegExp::ALT:
			s = &nfa.states[nfa.size++];
			s->alt(nrule,
				regexp2nfa(nfa, nrule, re->pld.alt.re1, t),
				regexp2nfa(nfa, nrule, re->pld.alt.re2, t));
			break;
		case RegExp::CAT:
			s = regexp2nfa(nfa, nrule, re->pld.cat.re2, t);
			s = regexp2nfa(nfa, nrule, re->pld.cat.re1, s);
			break;
		case RegExp::ITER:
			s = &nfa.states[nfa.size++];
			s->alt(nrule, t, regexp2nfa(nfa, nrule, re->pld.iter.re, s));
			break;
		case RegExp::TAG: {
			const size_t idx = re->pld.ctx.idx;
			if (idx != ~0u) {
				s = &nfa.states[nfa.size++];
				s->ctx(nrule, t, idx);
			} else {
				s = t;
			}
			break;
		}
	}
	return s;
}

static nfa_state_t *regexp2nfa_rule(nfa_t &nfa, size_t nrule, const RegExpRule *rule)
{
	nfa_state_t *s = &nfa.states[nfa.size++];
	s->fin(nrule);
	return regexp2nfa(nfa, nrule, rule->re, s);
}

void regexps2nfa(const std::vector<const RegExpRule*> &rs, nfa_t &nfa)
{
	const size_t nrs = rs.size();

	if (nrs == 0) {
		return;
	}

	nfa_state_t *s = regexp2nfa_rule(nfa, 0, rs[0]);
	for (size_t i = 1; i < nrs; ++i) {
		nfa_state_t *t = &nfa.states[nfa.size++];
		t->alt(i, s, regexp2nfa_rule(nfa, i, rs[i]));
		s = t;
	}
	nfa.root = s;
}

} // namespace re2c
