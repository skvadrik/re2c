#include "src/util/c99_stdint.h"

#include "src/ir/bytecode/ins.h"
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

static uint32_t compile_goto (Ins * ins, Ins * i);

uint32_t AltOp::compile (const charset_t & cs, Ins * i)
{
	if (ins_cache)
	{
		return compile_goto (ins_cache, i);
	}
	else
	{
		ins_cache = i;

		i->i.tag = FORK;
		const uint32_t sz1 = exp1->compile (cs, &i[1]);
		Ins * const j = &i[sz1 + 1];
		i->i.link = &j[1];
		j->i.tag = GOTO;
		const uint32_t sz2 = exp2->compile (cs, &j[1]);
		j->i.link = &j[sz2 + 1];

		if (ins_access == PRIVATE)
		{
			decompile ();
		}

		return sz1 + sz2 + 2;
	}
}

void AltOp::decompile ()
{
	if (ins_cache)
	{
		exp1->decompile ();
		exp2->decompile ();
		ins_cache = NULL;
	}
}

uint32_t CatOp::compile (const charset_t & cs, Ins * i)
{
	if (ins_cache)
	{
		return compile_goto (ins_cache, i);
	}
	else
	{
		ins_cache = i;

		const uint32_t sz1 = exp1->compile (cs, &i[0]);
		const uint32_t sz2 = exp2->compile (cs, &i[sz1]);

		if (ins_access == PRIVATE)
		{
			decompile ();
		}

		return sz1 + sz2;
	}
}

void CatOp::decompile ()
{
	if (ins_cache)
	{
		exp1->decompile ();
		exp2->decompile ();
		ins_cache = NULL;
	}
}

uint32_t CloseOp::compile (const charset_t & cs, Ins * i)
{
	if (ins_cache)
	{
		return compile_goto (ins_cache, i);
	}
	else
	{
		ins_cache = i;

		i += exp->compile (cs, &i[0]);
		i->i.tag = FORK;
		i->i.link = ins_cache;
		++i;

		const uint32_t sz = static_cast<uint32_t> (i - ins_cache);
		if (ins_access == PRIVATE)
		{
			decompile ();
		}

		return sz;
	}
}

void CloseOp::decompile ()
{
	if (ins_cache)
	{
		exp->decompile ();
		ins_cache = NULL;
	}
}

uint32_t MatchOp::compile (const charset_t & cs, Ins * i)
{
	if (ins_cache)
	{
		return compile_goto (ins_cache, i);
	}
	else
	{
		ins_cache = i;

		i->i.tag = CHAR;
		i->i.link = &i[size];
		Ins *j = &i[1];
		uint32_t bump = size;
		uint32_t k = 0;
		for (Range *r = match; r; r = r->next ())
		{
			for (; cs[k] != r->lower(); ++k);
			for (; cs[k] != r->upper(); ++k)
			{
				j->c.value = k;
				j->c.bump = --bump;
				j++;
			}
		}

		if (ins_access == PRIVATE)
		{
			decompile ();
		}

		return size;
	}
}

void MatchOp::decompile ()
{
	ins_cache = NULL;
}

uint32_t NullOp::compile (const charset_t &, Ins *)
{
	return 0;
}

void NullOp::decompile () {}

uint32_t RuleOp::compile (const charset_t & cs, Ins * i)
{
	if (ins_cache)
	{
		return compile_goto (ins_cache, i);
	}
	else
	{
		ins_cache = i;

		i += exp->compile (cs, &i[0]);
		if (ctx->size)
		{
			i->i.tag = CTXT;
			i->i.link = &i[1];
			++i;
			i += ctx->compile (cs, &i[0]);
		}
		i->i.tag = TERM;
		i->i.link = this;
		++i;
		const uint32_t sz = static_cast<uint32_t> (i - ins_cache);

		if (ins_access == PRIVATE)
		{
			decompile ();
		}

		return sz;
	}
}

void RuleOp::decompile ()
{
	if (ins_cache)
	{
		exp->decompile ();
		ctx->decompile ();
		ins_cache = NULL;
	}
}

uint32_t compile_goto (Ins * ins, Ins * i)
{
	i->i.tag = GOTO;
	i->i.link = ins;
	return 1;
}

} // end namespace re2c
