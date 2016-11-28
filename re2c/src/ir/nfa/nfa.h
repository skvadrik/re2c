#ifndef _RE2C_IR_NFA_NFA_
#define _RE2C_IR_NFA_NFA_

#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <valarray>
#include <vector>

#include "src/ir/regexp/regexp.h"
#include "src/ir/rule.h"
#include "src/ir/tag.h"
#include "src/util/forbid_copy.h"

namespace re2c
{

struct nfa_state_t
{
	enum type_t {ALT, RAN, TAG, FIN, NIL} type;
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
			bool bottom;
		} tag;
		struct
		{
			nfa_state_t *out;
		} nil;
	};
	size_t rule;
	uint8_t loop;

	void make_alt(size_t r, nfa_state_t *s1, nfa_state_t *s2)
	{
		type = ALT;
		alt.out1 = s1;
		alt.out2 = s2;
		rule = r;
		loop = 0;
	}
	void make_ran(size_t r, nfa_state_t *s, const Range *p)
	{
		type = RAN;
		ran.out = s;
		ran.ran = p;
		rule = r;
		loop = 0;
	}
	void make_tag(size_t r, nfa_state_t *s, size_t i, bool bottom)
	{
		type = TAG;
		tag.out = s;
		tag.info = i;
		tag.bottom = bottom;
		rule = r;
		loop = 0;
	}
	void make_fin(size_t r)
	{
		type = FIN;
		rule = r;
		loop = 0;
	}
	void make_nil(size_t r, nfa_state_t *s)
	{
		type = NIL;
		nil.out = s;
		rule = r;
		loop = 0;
	}
};

struct nfa_t
{
	size_t max_size;
	size_t size;
	nfa_state_t *states;
	std::valarray<Rule> &rules;
	std::vector<VarTag> &vartags;
	std::vector<FixTag> &fixtags;
	nfa_state_t *root;

	nfa_t(const std::vector<const RegExpRule*> &rs);
	~nfa_t();

	FORBID_COPY(nfa_t);
};

size_t counters(const std::vector<const RegExpRule*> &regexps, size_t &ntags);
void regexps2nfa(const std::vector<const RegExpRule*> &regexps, nfa_t &nfa);
bool nullable_rule(const RegExpRule *rule);
void init_rules(const std::vector<const RegExpRule*> &regexps, std::valarray<Rule> &rules,
	const std::vector<VarTag> &vartags, const std::vector<FixTag> &fixtags);

} // namespace re2c

#endif // _RE2C_IR_NFA_NFA_
