#ifndef _RE2C_IR_DFA_CLOSURE_
#define _RE2C_IR_DFA_CLOSURE_

#include "src/util/c99_stdint.h"

#include "src/ir/dfa/dfa.h"
#include "src/ir/nfa/nfa.h"

namespace re2c
{

struct clos_t
{
	nfa_state_t *state;
	size_t tagidx;

	inline clos_t();
	inline clos_t(nfa_state_t *s, size_t i);
	static inline bool final(const clos_t &c);
	static inline bool not_final(const clos_t &c);
};

typedef std::vector<clos_t> closure_t;
typedef closure_t::iterator clositer_t;
typedef closure_t::const_iterator cclositer_t;

size_t closure(const closure_t &clos1, closure_t &clos2,
	Tagpool &tagpool, std::valarray<Rule> &rules, bool *badtags);

clos_t::clos_t()
	: state(NULL)
	, tagidx(0)
{}

clos_t::clos_t(nfa_state_t *s, size_t i)
	: state(s)
	, tagidx(i)
{}

bool clos_t::final(const clos_t &c)
{
	return c.state->type == nfa_state_t::FIN;
}

bool clos_t::not_final(const clos_t &c)
{
	return !clos_t::final(c);
}

} // namespace re2c

#endif // _RE2C_IR_DFA_CLOSURE_
