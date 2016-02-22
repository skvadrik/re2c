#ifndef _RE2C_PARSE_RULES_
#define _RE2C_PARSE_RULES_

#include "src/util/c99_stdint.h"
#include <set>
#include <string>
#include <vector>

#include "src/ir/rule_rank.h"
#include "src/parse/code.h"
#include "src/parse/loc.h"
#include "src/util/forbid_copy.h"

namespace re2c
{

struct RuleInfo
{
	const Loc loc;

	// ~0u      - dynamic length
	// (0; ~0u) - static length
	// 0        - no context
	uint32_t ctx_len;

	rule_rank_t rank;
	const Code *code;
	const std::string newcond;

	std::set<uint32_t> shadow;
	bool reachable;

	RuleInfo
		( const Loc & l
		, rule_rank_t r
		, const Code * c
		, const std::string * cond
		, uint32_t cl
		)
		: loc (l)
		, ctx_len (cl)
		, rank (r)
		, code (c)
		, newcond (cond ? *cond : "")
		, shadow ()
		, reachable (false)
	{}

	FORBID_COPY(RuleInfo);
};

typedef std::vector<RuleInfo*> rules_t;

} // namespace re2c

#endif // _RE2C_PARSE_RULES_
