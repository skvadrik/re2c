#include "src/ir/nfa/nfa.h"

namespace re2c {

static nfa_state_t *re_to_nfa(nfa_t &nfa, size_t nrule, const RE *re, nfa_state_t *t)
{
	nfa_state_t *s = NULL;
	switch (re->type) {
		case RE::NIL:
			s = t;
			break;
		case RE::SYM:
			s = &nfa.states[nfa.size++];
			s->make_ran(nrule, t, re->sym);
			break;
		case RE::ALT: {
			nfa_state_t
				*s1 = re_to_nfa(nfa, nrule, re->alt.re1, t),
				*s2 = re_to_nfa(nfa, nrule, re->alt.re2, t);
			s = &nfa.states[nfa.size++];
			s->make_alt(nrule, s1, s2);
			break;
		}
		case RE::CAT:
			s = re_to_nfa(nfa, nrule, re->cat.re2, t);
			s = re_to_nfa(nfa, nrule, re->cat.re1, s);
			break;
		case RE::ITER: {
			// see note [Kleene star is expressed in terms of plus]
			nfa_state_t *q = &nfa.states[nfa.size++];
			s = re_to_nfa(nfa, nrule, re->iter, q);
			q->make_alt(nrule, s, t);
			break;
		}
		case RE::REPEAT:
			s = re_to_nfa(nfa, nrule, re->repeat.re, t);
			for (uint32_t i = 0; i < re->repeat.upto; ++i) {
				nfa_state_t *q = &nfa.states[nfa.size++];
				q->make_alt(nrule, s, t);
				s = re_to_nfa(nfa, nrule, re->repeat.re, q);
			}
			break;
		case RE::TAG:
			if (fixed(nfa.tags[re->tag.idx])) {
				s = t;
			} else {
				s = &nfa.states[nfa.size++];
				s->make_tag(nrule, t, re->tag.idx, re->tag.bottom);
			}
			break;
	}
	return s;
}

nfa_t::nfa_t(const RESpec &spec)
	: max_size(estimate_size(spec.res))
	, size(0)
	, states(new nfa_state_t[max_size])
	, charset(spec.charset)
	, rules(spec.rules)
	, tags(spec.tags)
	, root(NULL)
{
	const size_t nre = spec.res.size();

	if (nre == 0) return;

	for (size_t i = 0; i < nre; ++i) {
		nfa_state_t *s = &states[size++];
		s->make_fin(i);
		s = re_to_nfa(*this, i, spec.res[i], s);

		if (root) {
			nfa_state_t *t = &states[size++];
			t->make_alt(i, root, s);
			root = t;
		} else {
			root = s;
		}
	}
}

nfa_t::~nfa_t()
{
	delete[] states;
}

} // namespace re2c
