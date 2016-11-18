#include "src/ir/nfa/nfa.h"

namespace re2c {

// We have to insert default tags during NFA construction: before it,
// we have AST and which is immutable (it may be shared by different
// regexps); after it, we have NFA where join points of alternatives
// are lost.
static nfa_state_t *regexp2nfa(nfa_t &nfa, size_t nrule,
	bool *tbit, size_t &tidx, const RegExp *re, nfa_state_t *t)
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
		case RegExp::ALT: {
			nfa_state_t *s1, *s2, *t0, *t1, *t2, *q;
			size_t i = tidx;

			t0 = &nfa.states[nfa.size++];
			s1 = regexp2nfa(nfa, nrule, tbit, tidx, re->alt.re1, t0);
			for (t2 = t; i < tidx; ++i) {
				if (tbit[i]) {
					q = &nfa.states[nfa.size++];
					q->make_tag(nrule, t2, i, true);
					t2 = q;
				}
			}

			s2 = regexp2nfa(nfa, nrule, tbit, tidx, re->alt.re2, t2);
			for (t1 = t; i < tidx; ++i) {
				if (tbit[i]) {
					q = &nfa.states[nfa.size++];
					q->make_tag(nrule, t1, i, true);
					t1 = q;
				}
			}
			t0->make_nil(nrule, t1);

			s = &nfa.states[nfa.size++];
			s->make_alt(nrule, s1, s2);
			break;
		}
		case RegExp::CAT:
			s = regexp2nfa(nfa, nrule, tbit, tidx, re->cat.re2, t);
			s = regexp2nfa(nfa, nrule, tbit, tidx, re->cat.re1, s);
			break;
		case RegExp::ITER: {
			// see note [Kleene star is expressed in terms of plus]
			nfa_state_t *q = &nfa.states[nfa.size++];
			s = regexp2nfa(nfa, nrule, tbit, tidx, re->iter, q);
			q->make_alt(nrule, t, s);
			break;
		}
		case RegExp::TAG:
			if ((*nfa.tags)[tidx].type == Tag::VAR) {
				s = &nfa.states[nfa.size++];
				s->make_tag(nrule, t, tidx, false);
			} else {
				s = t;
			}
			tbit[tidx++] = true;
			break;
	}
	return s;
}

static nfa_state_t *regexp2nfa_rule(nfa_t &nfa, size_t nrule,
	bool *tbit, size_t &tidx, const RegExpRule *rule)
{
	nfa_state_t *s = &nfa.states[nfa.size++];
	s->make_fin(nrule);
	return regexp2nfa(nfa, nrule, tbit, tidx, rule->re, s);
}

void regexps2nfa(const std::vector<const RegExpRule*> &regexps, nfa_t &nfa)
{
	const size_t nregexps = regexps.size();

	if (nregexps == 0) {
		return;
	}

	bool *tbit = new bool[nfa.tags->size()]();
	size_t tidx = 0;

	nfa_state_t *s = regexp2nfa_rule(nfa, 0, tbit, tidx, regexps[0]);
	for (size_t i = 1; i < nregexps; ++i) {
		nfa_state_t *t = &nfa.states[nfa.size++];
		t->make_alt(i, s, regexp2nfa_rule(nfa, i, tbit, tidx, regexps[i]));
		s = t;
	}
	nfa.root = s;

	delete[] tbit;
}

} // namespace re2c
