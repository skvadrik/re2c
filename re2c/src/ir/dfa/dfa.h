#ifndef _RE2C_IR_DFA_DFA_
#define _RE2C_IR_DFA_DFA_

#include "src/util/c99_stdint.h"
#include <valarray>
#include <vector>
#include <set>

#include "src/ir/regexp/regexp.h"
#include "src/ir/rule.h"
#include "src/ir/tag.h"
#include "src/util/forbid_copy.h"

namespace re2c
{

struct nfa_t;

struct dfa_state_t
{
	size_t *arcs;
	tagcmd_t *tags;
	size_t rule;
	tagcmd_t rule_tags;
	bool fallthru;
	bool fallback;

	explicit dfa_state_t(size_t nchars)
		: arcs(new size_t[nchars])
		, tags(new tagcmd_t[nchars])
		, rule(Rule::NONE)
		, rule_tags()
		, fallthru(false)
		, fallback(false)
	{}
	~dfa_state_t()
	{
		delete[] arcs;
		delete[] tags;
	}

	FORBID_COPY(dfa_state_t);
};

struct dfa_t
{
	static const size_t NIL;

	std::vector<dfa_state_t*> states;
	const size_t nchars;
	std::valarray<Rule> &rules;
	std::valarray<Tag> &tags;
	Tagpool &tagpool;
	tagver_t maxtagver;

	dfa_t(const nfa_t &nfa, const charset_t &charset,
		const std::string &cond);
	~dfa_t();

	FORBID_COPY(dfa_t);
};

enum dfa_minimization_t
{
	DFA_MINIMIZATION_TABLE,
	DFA_MINIMIZATION_MOORE
};

void minimization(dfa_t &dfa);
void fillpoints(const dfa_t &dfa, std::vector<size_t> &fill);
void cutoff_dead_rules(dfa_t &dfa, size_t defrule, const std::string &cond);
void insert_fallback_tags(dfa_t &dfa);
void optimize_tags(dfa_t &dfa);

} // namespace re2c

#endif // _RE2C_IR_DFA_DFA_
