#include "src/ir/regexp/regexp_alt.h"
#include "src/ir/regexp/regexp_cat.h"
#include "src/ir/regexp/regexp_close.h"
#include "src/ir/regexp/regexp_closev.h"
#include "src/ir/regexp/regexp_match.h"
#include "src/ir/regexp/regexp_null.h"
#include "src/ir/regexp/regexp_rule.h"

namespace re2c {

void AltOp::split (CharSet & s)
{
	exp1->split (s);
	exp2->split (s);
}

void CatOp::split (CharSet & s)
{
	exp1->split (s);
	exp2->split (s);
}

void CloseOp::split (CharSet & s)
{
	exp->split (s);
}

void CloseVOp::split (CharSet & s)
{
	exp->split (s);
}

void MatchOp::split (CharSet & s)
{
	for (Range *r = match; r; r = r->next ())
	{
		for (uint32_t c = r->lower (); c < r->upper (); ++c)
		{
			CharPtn * x = s.rep[c];
			CharPtn * a = x->nxt;
			if (!a)
			{
				if (x->card == 1)
				{
					continue;
				}
				x->nxt = a = s.freeHead;
				if (!(s.freeHead = s.freeHead->nxt))
				{
					s.freeTail = &s.freeHead;
				}
				a->nxt = NULL;
				x->fix = s.fix;
				s.fix = x;
			}
			if (--(x->card) == 0)
			{
				*s.freeTail = x;
				*(s.freeTail = &x->nxt) = NULL;
			}
			s.rep[c] = a;
			++(a->card);
		}
	}
	for (; s.fix; s.fix = s.fix->fix)
	{
		if (s.fix->card)
		{
			s.fix->nxt = NULL;
		}
	}
}

void NullOp::split (CharSet &) {}

void RuleOp::split (CharSet & s)
{
	exp->split (s);
	ctx->split (s);
}

} // namespace re2c
