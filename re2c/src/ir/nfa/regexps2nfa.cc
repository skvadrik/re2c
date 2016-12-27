#include <limits>

#include "src/ir/nfa/nfa.h"

namespace re2c {

/* note [fixed and variable tags]
 *
 * If distance between two tags is constant (equal for all strings that
 * match the given regexp), then lexer only needs to track one of them:
 * the second tag equals the first tag plus static offset.
 *
 * However, this optimization is applied only to tags in top-level
 * concatenation, because other tags may be uninitialized and we don't
 * want to mess with conditional calculation of fixed tags.
 *
 * Furthermore, fixed tags are fobidden with generic API because it cannot
 * express fixed offsets.
 */

static const size_t VARDIST = std::numeric_limits<size_t>::max();

// We have to insert default tags during NFA construction: before it,
// we have AST and which is immutable (it may be shared by different
// regexps); after it, we have NFA where join points of alternatives
// are lost.
// We also compute fixed / variable tags during NFA construction, because
// the order of regexp traversal determines the order in which tags are
// assigned indices. Splitting this in two passes would require maintaining
// exactly the same order of traversal, which is fragile.
static nfa_state_t *regexp2nfa(nfa_t &nfa, size_t nrule, size_t &dist,
	size_t &base, bool toplevel, const RegExp *re, nfa_state_t *t)
{
	nfa_state_t *s = NULL;
	switch (re->type) {
		case RegExp::NIL:
			s = t;
			break;
		case RegExp::SYM:
			s = &nfa.states[nfa.size++];
			s->make_ran(nrule, t, re->sym);

			if (dist != VARDIST) ++dist;
			break;
		case RegExp::ALT: {
			nfa_state_t *s1, *s2, *t0, *t1, *t2, *q;
			size_t d1 = dist, d2 = dist, i = nfa.vartags.size();

			t0 = &nfa.states[nfa.size++];
			s1 = regexp2nfa(nfa, nrule, d1, base, false, re->alt.re1, t0);
			for (t2 = t; i < nfa.vartags.size(); ++i) {
				q = &nfa.states[nfa.size++];
				q->make_tag(nrule, t2, i, true);
				t2 = q;
			}

			s2 = regexp2nfa(nfa, nrule, d2, base, false, re->alt.re2, t2);
			for (t1 = t; i < nfa.vartags.size(); ++i) {
				q = &nfa.states[nfa.size++];
				q->make_tag(nrule, t1, i, true);
				t1 = q;
			}
			t0->make_nil(nrule, t1);

			s = &nfa.states[nfa.size++];
			s->make_alt(nrule, s1, s2);

			dist = (d1 == d2) ? d1 : VARDIST;
			break;
		}
		case RegExp::CAT:
			s = regexp2nfa(nfa, nrule, dist, base, toplevel, re->cat.re2, t);
			s = regexp2nfa(nfa, nrule, dist, base, toplevel, re->cat.re1, s);
			break;
		case RegExp::ITER: {
			// see note [Kleene star is expressed in terms of plus]
			nfa_state_t *q = &nfa.states[nfa.size++];
			s = regexp2nfa(nfa, nrule, dist, base, false, re->iter, q);
			q->make_alt(nrule, t, s);

			dist = VARDIST;
			break;
		}
		case RegExp::TAG: {
			const std::string *name = re->tag;
			if (toplevel && dist != VARDIST) {
				FixTag fix = {name, nrule, base, dist};
				nfa.fixtags.push_back(fix);
				s = t;
			} else {
				const size_t ntag = nfa.vartags.size();
				VarTag var = {name, nrule};
				nfa.vartags.push_back(var);
				if (toplevel) {
					base = ntag;
					dist = 0;
				}
				s = &nfa.states[nfa.size++];
				s->make_tag(nrule, t, ntag, false);
			}
			if (name == NULL) dist = 0;
			break;
		}
	}
	return s;
}

static nfa_state_t *regexp2nfa_rule(nfa_t &nfa, size_t nrule,
	const RegExp *re, InputAPI::type_t input)
{
	const bool generic = input == InputAPI::CUSTOM;
	size_t base = FixTag::RIGHTMOST, dist = 0;

	nfa_state_t *s = &nfa.states[nfa.size++];
	s->make_fin(nrule);

	return regexp2nfa(nfa, nrule, dist, base, !generic, re, s);
}

void regexps2nfa(const std::vector<RegExpRule> &regexps,
	nfa_t &nfa, InputAPI::type_t input)
{
	const size_t nregexps = regexps.size();

	if (nregexps == 0) {
		return;
	}

	nfa_state_t *s = regexp2nfa_rule(nfa, 0, regexps[0].re, input);
	for (size_t i = 1; i < nregexps; ++i) {
		nfa_state_t *t = &nfa.states[nfa.size++];
		t->make_alt(i, s, regexp2nfa_rule(nfa, i, regexps[i].re, input));
		s = t;
	}
	nfa.root = s;
}

} // namespace re2c
