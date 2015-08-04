#ifndef _RE2C_IR_REGEXP_REGEXP_RULE_
#define _RE2C_IR_REGEXP_REGEXP_RULE_

#include <string>

#include "src/ir/regexp/regexp.h"
#include "src/ir/rule_rank.h"
#include "src/parse/token.h"

namespace re2c
{

class RuleOp: public RegExp
{
	RegExp * exp;

public:
	RegExp * ctx;
	Ins * ins;
	rule_rank_t rank;
	Token * code;
	const std::string newcond;

	inline RuleOp (RegExp * e, RegExp * c, Token * t, rule_rank_t r, InsAccess access, const std::string * n)
		: exp (e)
		, ctx (c)
		, ins (NULL)
		, rank (r)
		, code (t)
		, newcond (n ? *n : "")
	{
		ins_access = access;
	}
	inline ~RuleOp ()
	{
		delete code;
	}
	void display (std::ostream & o) const;
	void split (CharSet &);
	void calcSize (Char *);
	uint32_t compile (Char *, Ins *);
	void decompile ();

	FORBID_COPY (RuleOp);
};

} // end namespace re2c

#endif // _RE2C_IR_REGEXP_REGEXP_RULE_
