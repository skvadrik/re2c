#ifndef _RE2C_IR_NFA_NFA_
#define _RE2C_IR_NFA_NFA_

#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <valarray>
#include <vector>

#include "src/ir/rule.h"
#include "src/util/forbid_copy.h"

namespace re2c
{

struct Range;
struct RegExp;
struct RuleInfo;

struct nfa_state_t
{
	enum type_t
	{
		ALT,
		RAN,
		CTX,
		FIN
	} type;
	union
	{
		struct
		{
			nfa_state_t *out1;
			nfa_state_t *out2;
		} alt;
		struct
		{
			nfa_state_t *out;
			const Range *ran;
		} ran;
		struct
		{
			nfa_state_t *out;
			size_t info;
		} ctx;
	} value;
	size_t rule;
	bool mark;

	void alt(size_t r, nfa_state_t *s1, nfa_state_t *s2)
	{
		type = ALT;
		value.alt.out1 = s1;
		value.alt.out2 = s2;
		rule = r;
		mark = false;
	}
	void ran(size_t r, nfa_state_t *s, const Range *p)
	{
		type = RAN;
		value.ran.out = s;
		value.ran.ran = p;
		rule = r;
		mark = false;
	}
	void ctx(size_t r, nfa_state_t *s, size_t i)
	{
		type = CTX;
		value.ctx.out = s;
		value.ctx.info = i;
		rule = r;
		mark = false;
	}
	void fin(size_t r)
	{
		type = FIN;
		rule = r;
		mark = false;
	}
};

struct nfa_t
{
	const size_t max_size;
	size_t size;
	nfa_state_t *states;
	std::valarray<Rule> &rules;
	std::vector<CtxVar> &contexts;
	nfa_state_t *root;

	nfa_t(const std::vector<const RegExpRule*> &rs);
	~nfa_t();

	FORBID_COPY(nfa_t);
};

} // namespace re2c

#endif // _RE2C_IR_NFA_NFA_
