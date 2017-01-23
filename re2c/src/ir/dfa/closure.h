#ifndef _RE2C_IR_DFA_CLOSURE_
#define _RE2C_IR_DFA_CLOSURE_

#include "src/util/c99_stdint.h"

#include "src/ir/dfa/dfa.h"
#include "src/ir/nfa/nfa.h"

namespace re2c
{

struct clos_t
{
	nfa_state_t *origin; // for debug only
	nfa_state_t *state;
	size_t tvers; // tag versions
	size_t ttran; // transition tags (lookahead tags of parent closure)
	size_t tlook; // lookahead tags (transition tags of child closures)

	static inline bool fin(const clos_t &c) { return c.state->type == nfa_state_t::FIN; }
	static inline bool not_fin(const clos_t &c) { return !fin(c); }
};

typedef std::vector<clos_t> closure_t;
typedef closure_t::iterator clositer_t;
typedef closure_t::const_iterator cclositer_t;

void closure(closure_t &clos1, closure_t &clos2, Tagpool &tagpool,
	std::valarray<Rule> &rules, tagver_t &maxver, tagver_t *newvers,
	bool lookahead);

} // namespace re2c

#endif // _RE2C_IR_DFA_CLOSURE_
