#ifndef _RE2C_IR_DFA_DFA_
#define _RE2C_IR_DFA_DFA_

#include "src/util/c99_stdint.h"
#include <vector>
#include <set>

#include "src/ir/regexp/regexp.h"
#include "src/ir/rule.h"
#include "src/util/forbid_copy.h"
#include "src/util/ord_hash_set.h"

namespace re2c
{

struct nfa_t;

struct dfa_state_t
{
	size_t *arcs;
	size_t rule;
	std::set<size_t> ctxs;

	dfa_state_t()
		: arcs(NULL)
		, rule(Rule::NONE)
		, ctxs()
	{}
	~dfa_state_t()
	{
		delete[] arcs;
	}

	FORBID_COPY(dfa_state_t);
};

struct dfa_t
{
	static const size_t NIL;

	std::vector<dfa_state_t*> states;
	const size_t nchars;
	std::vector<CtxVar> &contexts;
	std::vector<Rule> &rules;

	dfa_t(const nfa_t &nfa, const charset_t &charset,
		uint32_t line, const std::string &cond);
	~dfa_t();

	FORBID_COPY(dfa_t);
};

enum dfa_minimization_t
{
	DFA_MINIMIZATION_TABLE,
	DFA_MINIMIZATION_MOORE
};

void check_context_selfoverlap(ord_hash_set_t &kernels,
	const std::vector<CtxVar> &contexts,
	uint32_t line, const std::string &cond);
void minimization(dfa_t &dfa);
void fillpoints(const dfa_t &dfa, std::vector<size_t> &fill);
void fallback_states(const dfa_t &dfa, std::vector<size_t> &fallback);
bool deduplicate_contexts(const dfa_t &dfa, const std::vector<size_t> &fallback);

} // namespace re2c

#endif // _RE2C_IR_DFA_DFA_
