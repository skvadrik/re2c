#include "src/ir/regexp/regexp.h"
#include "src/ir/regexp/regexp_alt.h"
#include "src/ir/regexp/regexp_cat.h"
#include "src/ir/regexp/regexp_close.h"
#include "src/ir/regexp/regexp_match.h"
#include "src/ir/regexp/regexp_null.h"
#include "src/ir/regexp/regexp_rule.h"

namespace re2c
{

bool AltOp::nullable() const
{
	return exp1->nullable()
		|| exp2->nullable();
}

bool CatOp::nullable() const
{
	return exp1->nullable()
		&& exp2->nullable();
}

bool CloseOp::nullable() const
{
	return true;
}

bool MatchOp::nullable() const
{
	return false;
}

bool NullOp::nullable() const
{
	return true;
}

bool RuleOp::nullable() const
{
	return exp->nullable();
}

void RegExp::nullable_rules(std::vector<RuleInfo*>&) const {}

void AltOp::nullable_rules(std::vector<RuleInfo*> &rs) const
{
	exp1->nullable_rules(rs);
	exp2->nullable_rules(rs);
}

void RuleOp::nullable_rules(std::vector<RuleInfo*> &rs) const
{
	if (exp->nullable())
	{
		rs.push_back(info);
	}
}

} // end namespace re2c

