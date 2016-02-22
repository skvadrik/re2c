#include "src/ir/nfa/nfa.h"
#include "src/ir/regexp/regexp.h"

namespace re2c {

static uint32_t calc_size(const RegExp *re);
static nfa_state_t *compile(const RegExp *re, nfa_t &nfa, nfa_state_t *n);

nfa_t::nfa_t(const RegExp *re)
	: max_size(calc_size(re))
	, size(0)
	, states(new nfa_state_t[max_size])
	, root(compile(re, *this, NULL))
{}

nfa_t::~nfa_t()
{
	delete[] states;
}

uint32_t calc_size(const RegExp *re)
{
	switch (re->tag) {
		default:
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
		case RegExp::RULE: {
			const uint32_t re_size  = calc_size(re->pld.rule.re) + 1;
			uint32_t ctx_size = calc_size(re->pld.rule.ctx);
			if (ctx_size > 0) {
				ctx_size += 1;
			}
			return re_size + ctx_size;
		}
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
		case RegExp::RULE: {
			s = &nfa.states[nfa.size++];
			RuleInfo *info = re->pld.rule.info;
			s->fin(info);
			if (info->ctx_len == ~0u) {
				// dynamic context
				nfa_state_t *q = compile(re->pld.rule.ctx, nfa, s);
				s = &nfa.states[nfa.size++];
				s->ctx(q);
			} else if (info->ctx_len > 0) {
				// static context
				s = compile(re->pld.rule.ctx, nfa, s);
			}
			s = compile(re->pld.rule.re, nfa, s);
			break;
		}
	}
	return s;
}

} // namespace re2c
