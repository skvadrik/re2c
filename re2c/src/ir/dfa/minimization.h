#ifndef _RE2C_IR_DFA_MINIMIZATION_
#define _RE2C_IR_DFA_MINIMIZATION_

namespace re2c
{

struct dfa_t;

enum dfa_minimization_t
{
	DFA_MINIMIZATION_TABLE,
	DFA_MINIMIZATION_MOORE
};

void minimization(dfa_t &dfa);

} // namespace re2c

#endif // _RE2C_IR_DFA_MINIMIZATION_
