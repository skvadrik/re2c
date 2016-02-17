#ifndef _RE2C_IR_REGEXP_REGEXP_RULE_
#define _RE2C_IR_REGEXP_REGEXP_RULE_

#include <string>

#include "src/ir/regexp/regexp.h"
#include "src/parse/code.h"
#include "src/globals.h"

namespace re2c
{

class RuleOp: public RegExp
{
public:
	const Loc loc;

private:
	RegExp * exp;

public:
	RegExp * ctx;
	// ~0u      - dynamic length
	// (0; ~0u) - static length
	// 0        - no context
	uint32_t ctx_len;

	rule_rank_t rank;
	const Code * code;
	const std::string newcond;

	inline RuleOp
		( const Loc & l
		, RegExp * r1
		, RegExp * r2
		, rule_rank_t r
		, const Code * c
		, const std::string * cond
		)
		: loc (l)
		, exp (r1)
		, ctx (r2)
		, ctx_len (ctx->fixedLength())
		, rank (r)
		, code (c)
		, newcond (cond ? *cond : "")
	{
		// cannot emulate 'YYCURSOR -= N' operation with generic API
		if (ctx_len != 0
			&& opts->input_api.type() == InputAPI::CUSTOM)
		{
			ctx_len = ~0u;
		}
	}
	bool nullable() const;
	void nullable_rules(std::set<rule_rank_t>&) const;
	void display (std::ostream & o) const;
	void split (std::set<uint32_t> &);
	uint32_t calc_size() const;
	nfa_state_t *compile(nfa_t &nfa, nfa_state_t *n);

	FORBID_COPY (RuleOp);
};

} // end namespace re2c

#endif // _RE2C_IR_REGEXP_REGEXP_RULE_
