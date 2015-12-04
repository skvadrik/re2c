#include "src/util/c99_stdint.h"

#include "src/ir/regexp/regexp.h"
#include "src/ir/regexp/regexp_alt.h"
#include "src/ir/regexp/regexp_cat.h"
#include "src/ir/regexp/regexp_close.h"
#include "src/ir/regexp/regexp_match.h"
#include "src/ir/regexp/regexp_null.h"
#include "src/ir/regexp/regexp_rule.h"
#include "src/util/range.h"

namespace re2c {

void AltOp::split (charset_t & cs)
{
	exp1->split (cs);
	exp2->split (cs);
}

void CatOp::split (charset_t & cs)
{
	exp1->split (cs);
	exp2->split (cs);
}

void CloseOp::split (charset_t & cs)
{
	exp->split (cs);
}

void MatchOp::split (charset_t & cs)
{
	for (Range *r = match; r; r = r->next ())
	{
		cs.insert (r->lower ());
		cs.insert (r->upper ());
	}
}

void NullOp::split (charset_t &) {}

void RuleOp::split (charset_t & cs)
{
	exp->split (cs);
	ctx->split (cs);
}

} // namespace re2c
