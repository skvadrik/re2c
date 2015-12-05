#include "src/util/c99_stdint.h"

#include "src/ir/regexp/regexp.h"
#include "src/ir/regexp/regexp_alt.h"
#include "src/ir/regexp/regexp_cat.h"
#include "src/ir/regexp/regexp_close.h"
#include "src/ir/regexp/regexp_match.h"
#include "src/ir/regexp/regexp_null.h"
#include "src/ir/regexp/regexp_rule.h"
#include "src/util/range.h"

namespace re2c
{

void AltOp::calcSize (const charset_t & cs)
{
	exp1->calcSize (cs);
	exp2->calcSize (cs);
	size = exp1->size + exp2->size + 2;
}

void CatOp::calcSize (const charset_t & cs)
{
	exp1->calcSize (cs);
	exp2->calcSize (cs);
	size = exp1->size + exp2->size;
}

void CloseOp::calcSize (const charset_t & cs)
{
	exp->calcSize (cs);
	size = exp->size + 1;
}

void MatchOp::calcSize (const charset_t & cs)
{
	size = 1;
	uint32_t k = 0;
	for (Range * r = match; r; r = r->next ())
	{
		for (; cs[k] != r->lower(); ++k);
		for (; cs[k] != r->upper(); ++k)
		{
			++size;
		}
	}
}

void NullOp::calcSize (const charset_t &)
{
	size = 0;
}

void RuleOp::calcSize (const charset_t & cs)
{
	exp->calcSize (cs);
	ctx->calcSize (cs);
	size = exp->size + (ctx->size ? ctx->size + 2 : 1);
}

} // end namespace re2c
