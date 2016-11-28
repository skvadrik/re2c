#ifndef _RE2C_IR_RULE_
#define _RE2C_IR_RULE_

#include <set>
#include <string>
#include <vector>

#include "src/ir/tag.h"
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
	std::set<uint32_t> shadow;

	// variable tags
	size_t lvar; // first
	size_t hvar; // next to last
	size_t tvar; // trailing context

	// fixed tags
	size_t lfix; // first
	size_t hfix; // next to last
	size_t tfix; // trailing context

	Rule(): info(NULL), shadow(),
		lvar(0), hvar(0), tvar(0),
		lfix(0), hfix(0), tfix(0)
	{}
	FORBID_COPY(Rule);
};

} // namespace re2c

#endif // _RE2C_IR_RULE_
