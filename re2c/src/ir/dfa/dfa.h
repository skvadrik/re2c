#ifndef _RE2C_IR_DFA_DFA_
#define _RE2C_IR_DFA_DFA_

#include "src/util/c99_stdint.h"
#include <vector>

#include "src/ir/regexp/regexp.h"
#include "src/parse/rules.h"
#include "src/util/forbid_copy.h"

namespace re2c
{

struct nfa_state_t;
struct nfa_t;
class RuleOp;

struct dfa_state_t
{
	size_t kCount;
	nfa_state_t **kernel;
	size_t *arcs;
	RuleOp *rule;
	bool ctx;

	dfa_state_t()
		: kCount(0)
		, kernel(NULL)
		, arcs(NULL)
		, rule(NULL)
		, ctx(false)
	{}
	~dfa_state_t()
	{
		delete[] kernel;
		delete[] arcs;
	}

	FORBID_COPY(dfa_state_t);
};

struct dfa_t
{
	enum minimization_t
	{
		TABLE,
		MOORE
	};
	static const size_t NIL;

	std::vector<dfa_state_t*> states;
	const size_t nchars;

	dfa_t(const nfa_t &nfa, const charset_t &charset, rules_t &rules);
	~dfa_t();
	void minimization();

private:
	void minimization_table(size_t *part);
	void minimization_moore(size_t *part);
};

} // namespace re2c

#endif // _RE2C_IR_DFA_DFA_
