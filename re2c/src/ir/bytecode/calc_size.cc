#include "src/ir/regexp/regexp_alt.h"
#include "src/ir/regexp/regexp_cat.h"
#include "src/ir/regexp/regexp_close.h"
#include "src/ir/regexp/regexp_closev.h"
#include "src/ir/regexp/regexp_match.h"
#include "src/ir/regexp/regexp_null.h"
#include "src/ir/regexp/regexp_rule.h"

namespace re2c
{

void AltOp::calcSize (Char * rep)
{
	exp1->calcSize (rep);
	exp2->calcSize (rep);
	size = exp1->size + exp2->size + 2;
}

void CatOp::calcSize (Char * rep)
{
	exp1->calcSize (rep);
	exp2->calcSize (rep);
	size = exp1->size + exp2->size;
}

void CloseOp::calcSize (Char * rep)
{
	exp->calcSize (rep);
	size = exp->size + 1;
}

void CloseVOp::calcSize (Char * rep)
{
	exp->calcSize (rep);
	if (max >= 0)
	{
		size = (exp->size * min) + ((1 + exp->size) * (max - min));
	}
	else
	{
		size = (exp->size * min) + 1;
	}
}

void MatchOp::calcSize (Char * rep)
{
	size = 1;
	for (Range * r = match; r; r = r->next ())
	{
		for (uint32_t c = r->lower (); c < r->upper (); ++c)
		{
			if (rep[c] == c)
			{
				++size;
			}
		}
	}
}

void NullOp::calcSize (Char *)
{
	size = 0;
}

void RuleOp::calcSize (Char * rep)
{
	exp->calcSize (rep);
	ctx->calcSize (rep);
	size = exp->size + (ctx->size ? ctx->size + 2 : 1);
}

} // end namespace re2c
