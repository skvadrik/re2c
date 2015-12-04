#ifndef _RE2C_IR_REGEXP_REGEXP_RULE_
#define _RE2C_IR_REGEXP_REGEXP_RULE_

#include <string>

#include "src/ir/regexp/regexp.h"
#include "src/ir/rule_rank.h"
#include "src/parse/code.h"

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
	Ins * ins;
	rule_rank_t rank;
	const Code * code;
	const std::string newcond;

	inline RuleOp
		( const Loc & l
		, RegExp * r1
		, RegExp * r2
		, rule_rank_t r
		, InsAccess access
		, const Code * c
		, const std::string * cond
		)
		: loc (l)
		, exp (r1)
		, ctx (r2)
		, ins (NULL)
		, rank (r)
		, code (c)
		, newcond (cond ? *cond : "")
	{
		ins_access = access;
	}
	void display (std::ostream & o) const;
	void split (charset_t &);
	void calcSize (const charset_t &);
	uint32_t compile (const charset_t &, Ins *);
	void decompile ();

	FORBID_COPY (RuleOp);
};

} // end namespace re2c

#endif // _RE2C_IR_REGEXP_REGEXP_RULE_
