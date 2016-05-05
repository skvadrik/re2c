#ifndef _RE2C_IR_RULE_
#define _RE2C_IR_RULE_

#include <set>
#include <string>
#include <vector>

#include "src/ir/ctx.h"
#include "src/parse/code.h"
#include "src/parse/loc.h"
#include "src/util/forbid_copy.h"

namespace re2c
{

struct RuleInfo
{
	const Loc loc;
	const Code *code;
	const std::string newcond;

	RuleInfo(const Loc &l, const Code *c,
		const std::string *cond)
		: loc(l)
		, code(c)
		, newcond(cond ? *cond : "")
	{}

	FORBID_COPY(RuleInfo);
};

struct Rule
{
	static const size_t NONE;

	const RuleInfo *info;

	size_t lvartag;
	size_t hvartag;
	size_t lfixtag;
	size_t hfixtag;
	Trail trail;
	bool nullable;
	bool *tags;
	std::set<uint32_t> shadow;
	bool reachable;

	Rule()
		: info(NULL)
		, lvartag(0)
		, hvartag(0)
		, lfixtag(0)
		, hfixtag(0)
		, trail()
		, nullable(false)
		, tags(NULL)
		, shadow()
		, reachable(false)
	{}
	~Rule()
	{
		delete[] tags;
	}

	FORBID_COPY(Rule);
};

} // namespace re2c

#endif // _RE2C_IR_RULE_
