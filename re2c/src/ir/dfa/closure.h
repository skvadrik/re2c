#ifndef _RE2C_IR_DFA_CLOSURE_
#define _RE2C_IR_DFA_CLOSURE_

#include "src/util/c99_stdint.h"

#include "src/ir/dfa/dfa.h"
#include "src/ir/nfa/nfa.h"

namespace re2c
{

struct kitem_t
{
	nfa_state_t *state;
	union
	{
		bool *tagptr;
		size_t tagidx;
	};

	static bool compare(const kitem_t &k1, const kitem_t &k2)
	{
		return k1.state < k2.state
			|| (k1.state == k2.state && k1.tagidx < k2.tagidx);
	}
};

void closure(kitem_t *const kernel, kitem_t *&kend, nfa_state_t *n,
	bool *tags, bool *badtags, size_t ntags);

} // namespace re2c

#endif // _RE2C_IR_DFA_CLOSURE_
