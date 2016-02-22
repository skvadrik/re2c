#ifndef _RE2C_IR_REGEXP_REGEXP_RULE_
#define _RE2C_IR_REGEXP_REGEXP_RULE_

#include <string>

#include "src/ir/regexp/regexp.h"
#include "src/globals.h"

namespace re2c
{

class RuleOp: public RegExp
{
	RegExp * exp;

public:
	RegExp * ctx;
	RuleInfo *info;

	inline RuleOp
		( const Loc & l
		, RegExp * r1
		, RegExp * r2
		, rule_rank_t r
		, const Code * c
		, const std::string * cond
		)
		: exp (r1)
		, ctx (r2)
		, info (NULL)

	{
		uint32_t ctx_len = r2->fixedLength();
		// cannot emulate 'YYCURSOR -= N' operation with generic API
		if (ctx_len != 0
			&& opts->input_api.type() == InputAPI::CUSTOM)
		{
			ctx_len = ~0u;
		}
		info = new RuleInfo(l, r, c, cond, ctx_len);
	}
	RuleOp(RuleOp *rule, rule_rank_t r)
		: exp(rule->exp)
		, ctx(rule->ctx)
		, info(new RuleInfo(rule->info->loc, r, rule->info->code,
			&rule->info->newcond, rule->info->ctx_len))
	{}
	~RuleOp()
	{
		delete info;
	}
	bool nullable() const;
	void nullable_rules(std::vector<RuleInfo*>&) const;
	void display (std::ostream & o) const;
	void split (std::set<uint32_t> &);
	uint32_t calc_size() const;
	nfa_state_t *compile(nfa_t &nfa, nfa_state_t *n);

	FORBID_COPY (RuleOp);
};

} // end namespace re2c

#endif // _RE2C_IR_REGEXP_REGEXP_RULE_
