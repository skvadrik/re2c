#include "src/ir/nfa/nfa.h"
#include "src/ir/regexp/regexp.h"

namespace re2c {

static uint32_t calc_size(const RegExp *re);
static nfa_state_t *compile(const RegExp *re, nfa_t &nfa, nfa_state_t *n);

nfa_t::nfa_t(Spec &spec)
	: max_size(calc_size(spec.re))
	, size(0)
	, states(new nfa_state_t[max_size])
	, contexts(spec.contexts)
	, root(compile(spec.re, *this, NULL))
{}

nfa_t::~nfa_t()
{
	delete[] states;
}

uint32_t calc_size(const RegExp *re)
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
		case RegExp::CTX:
			return calc_size(re->pld.ctx.re)
				+ 1;
		case RegExp::RULE:
			return calc_size(re->pld.rule.re)
				+ 1;
	}
}

nfa_state_t *compile(const RegExp *re, nfa_t &nfa, nfa_state_t *t)
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
		case RegExp::CTX:
			s = &nfa.states[nfa.size++];
			s->ctx(compile(re->pld.ctx.re, nfa, t),
				re->pld.ctx.info);
			break;
		case RegExp::RULE:
			s = &nfa.states[nfa.size++];
			s->fin(re->pld.rule.info);
			s = compile(re->pld.rule.re, nfa, s);
			break;
	}
	return s;
}

} // namespace re2c
