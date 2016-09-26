#include "src/ir/nfa/nfa.h"

namespace re2c {

static nfa_state_t *regexp2nfa(nfa_t &nfa, size_t nrule,
	size_t &tagidx, const RegExp *re, nfa_state_t *t)
{
	nfa_state_t *s = NULL;
	switch (re->type) {
		case RegExp::NIL:
			s = t;
			break;
		case RegExp::SYM:
			s = &nfa.states[nfa.size++];
			s->make_ran(nrule, t, re->sym);
			break;
		case RegExp::ALT:
			s = &nfa.states[nfa.size++];
			s->make_alt(nrule,
				regexp2nfa(nfa, nrule, tagidx, re->alt.re1, t),
				regexp2nfa(nfa, nrule, tagidx, re->alt.re2, t));
			break;
		case RegExp::CAT:
			s = regexp2nfa(nfa, nrule, tagidx, re->cat.re2, t);
			s = regexp2nfa(nfa, nrule, tagidx, re->cat.re1, s);
			break;
		case RegExp::ITER: {
			// see note [Kleene star is expressed in terms of plus]
			nfa_state_t *q = &nfa.states[nfa.size++];
			s = regexp2nfa(nfa, nrule, tagidx, re->iter, q);
			q->make_alt(nrule, t, s);
			break;
		}
		case RegExp::TAG:
			if ((*nfa.tags)[tagidx].type == Tag::VAR) {
				s = &nfa.states[nfa.size++];
				s->make_tag(nrule, t, tagidx);
			} else {
				s = t;
			}
			++tagidx;
			break;
	}
	return s;
}

static nfa_state_t *regexp2nfa_rule(nfa_t &nfa, size_t nrule,
	size_t &tagidx, const RegExpRule *rule)
{
	nfa_state_t *s = &nfa.states[nfa.size++];
	s->make_fin(nrule);
	return regexp2nfa(nfa, nrule, tagidx, rule->re, s);
}

void regexps2nfa(const std::vector<const RegExpRule*> &regexps, nfa_t &nfa)
{
	const size_t nregexps = regexps.size();

	if (nregexps == 0) {
		return;
	}

	size_t tagidx = 0;
	nfa_state_t *s = regexp2nfa_rule(nfa, 0, tagidx, regexps[0]);
	for (size_t i = 1; i < nregexps; ++i) {
		nfa_state_t *t = &nfa.states[nfa.size++];
		t->make_alt(i, s, regexp2nfa_rule(nfa, i, tagidx, regexps[i]));
		s = t;
	}
	nfa.root = s;
}

} // namespace re2c
