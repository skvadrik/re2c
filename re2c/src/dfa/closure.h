#ifndef _RE2C_DFA_CLOSURE_
#define _RE2C_DFA_CLOSURE_

#include <stddef.h>
#include <map>
#include <vector>

#include "src/dfa/dfa.h"
#include "src/dfa/tagtree.h"
#include "src/nfa/nfa.h"
#include "src/re/tag.h"

namespace re2c
{

struct Tagpool;
struct dfa_t;
struct tcmd_t;

struct clos_t
{
	nfa_state_t *origin; // for debug only
	nfa_state_t *state;
	size_t order; // vector of orders
	size_t tvers; // vector of tag versions (including lookahead tags)
	hidx_t ttran; // history of transition tags
	hidx_t tlook; // history of lookahead tags

	static inline bool fin(const clos_t &c) { return c.state->type == nfa_state_t::FIN; }
	static inline bool ran(const clos_t &c) { return c.state->type == nfa_state_t::RAN; }
};

typedef std::vector<clos_t> closure_t;
typedef closure_t::iterator clositer_t;
typedef closure_t::const_iterator cclositer_t;
typedef closure_t::reverse_iterator rclositer_t;
typedef closure_t::const_reverse_iterator rcclositer_t;

struct newver_t
{
	size_t tag;
	tagver_t base;
	hidx_t history;
};

struct newver_cmp_t
{
	tagtree_t &history;
	bool operator()(const newver_t &x, const newver_t &y) const
	{
		if (x.tag < y.tag) return true;
		if (x.tag > y.tag) return false;

		if (x.base < y.base) return true;
		if (x.base > y.base) return false;

		return history.compare_plain(x.history, y.history, x.tag) < 0;
	}
};

typedef std::map<newver_t, tagver_t, newver_cmp_t> newvers_t;

tcmd_t *closure(dfa_t &dfa, closure_t &clos1, closure_t &clos2,
	Tagpool &tagpool, newvers_t &newvers, closure_t *shadow);

} // namespace re2c

#endif // _RE2C_DFA_CLOSURE_
