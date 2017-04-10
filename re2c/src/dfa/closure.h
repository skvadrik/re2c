#ifndef _RE2C_DFA_CLOSURE_
#define _RE2C_DFA_CLOSURE_

#include "src/util/c99_stdint.h"
#include <map>

#include "src/dfa/dfa.h"
#include "src/nfa/nfa.h"

namespace re2c
{

struct clos_t
{
	nfa_state_t *origin; // for debug only
	nfa_state_t *state;
	size_t tvers; // vector of tag versions (including lookahead tags)
	size_t ttran; // vector of transition tags
	size_t tlook; // vector of lookahead tags
	size_t order; // vector of orders
	size_t index; // leftmost order in NFA traversal

	static inline bool fin(const clos_t &c) { return c.state->type == nfa_state_t::FIN; }
};

typedef std::vector<clos_t> closure_t;
typedef closure_t::iterator clositer_t;
typedef closure_t::const_iterator cclositer_t;

struct newver_t
{
	size_t tag;
	tagver_t ver;
	tagver_t act;
};

inline bool operator<(const newver_t &x, const newver_t &y)
{
	if (x.tag < y.tag) return true;
	if (x.tag > y.tag) return false;

	if (x.ver < y.ver) return true;
	if (x.ver > y.ver) return false;

	if (x.act < y.act) return true;
	if (x.act > y.act) return false;

	return false;
}

typedef std::map<newver_t, tagver_t> newvers_t;

tcmd_t *closure(closure_t &clos1, closure_t &clos2, Tagpool &tagpool,
	tcpool_t &tcpool, std::valarray<Rule> &rules, tagver_t &maxver,
	newvers_t &newvers, bool lookahead, closure_t *shadow, const std::vector<Tag> &tags);

} // namespace re2c

#endif // _RE2C_DFA_CLOSURE_
