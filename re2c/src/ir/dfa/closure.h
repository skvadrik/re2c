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
	static inline bool compare(const clos_t &c1, const clos_t &c2);
	static inline bool final(const clos_t &c);
	static inline bool not_final(const clos_t &c);
};

typedef std::vector<clos_t> closure_t;
typedef closure_t::iterator clositer_t;
typedef closure_t::const_iterator cclositer_t;

void closure(const closure_t &clos1, closure_t &clos2,
	Tagpool &tagpool, std::valarray<Rule> &rules,
	bool *tags, bool *badtags);

clos_t::clos_t()
	: state(NULL)
	, tagidx(0)
{}

clos_t::clos_t(nfa_state_t *s, size_t i)
	: state(s)
	, tagidx(i)
{}

bool clos_t::compare(const clos_t &c1, const clos_t &c2)
{
	const nfa_state_t
		*s1 = c1.state,
		*s2 = c2.state;
	return s1 < s2
		|| (s1 == s2 && c1.tagidx < c2.tagidx);
}

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
