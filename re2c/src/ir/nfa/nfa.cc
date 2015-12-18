#include "src/ir/nfa/nfa.h"
#include "src/ir/regexp/regexp.h"
#include "src/ir/regexp/regexp_alt.h"
#include "src/ir/regexp/regexp_cat.h"
#include "src/ir/regexp/regexp_close.h"
#include "src/ir/regexp/regexp_match.h"
#include "src/ir/regexp/regexp_null.h"
#include "src/ir/regexp/regexp_rule.h"

namespace re2c {

nfa_t::nfa_t(RegExp *re)
	: max_size(re->calc_size())
	, size(0)
	, states(new nfa_state_t[max_size])
	, root(re->compile(*this, NULL))
{}

nfa_t::~nfa_t()
{
	delete[] states;
}

nfa_state_t *AltOp::compile(nfa_t &nfa, nfa_state_t *t)
{
	if (ins_cache)
	{
		return ins_cache;
	}
	else
	{
		nfa_state_t *s = &nfa.states[nfa.size++];
		s->alt(exp1->compile(nfa, t)
			, exp2->compile(nfa, t));

		ins_cache = s;
		if (ins_access == PRIVATE)
		{
			decompile();
		}

		return s;
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

nfa_state_t *CatOp::compile(nfa_t &nfa, nfa_state_t *t)
{
	if (ins_cache)
	{
		return ins_cache;
	}
	else
	{
		nfa_state_t *s2 = exp2->compile(nfa, t);
		nfa_state_t *s1 = exp1->compile(nfa, s2);

		ins_cache = s1;
		if (ins_access == PRIVATE)
		{
			decompile();
		}

		return s1;
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

nfa_state_t *CloseOp::compile(nfa_t &nfa, nfa_state_t *t)
{
	if (ins_cache)
	{
		return ins_cache;
	}
	else
	{
		nfa_state_t *s = &nfa.states[nfa.size++];
		s->alt(t, exp->compile(nfa, s));

		ins_cache = s;
		if (ins_access == PRIVATE)
		{
			decompile();
		}

		return s;
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

nfa_state_t *MatchOp::compile(nfa_t &nfa, nfa_state_t *t)
{
	if (ins_cache)
	{
		return ins_cache;
	}
	else
	{
		nfa_state_t *s = &nfa.states[nfa.size++];
		s->ran(t, match);

		ins_cache = s;
		if (ins_access == PRIVATE)
		{
			decompile();
		}

		return s;
	}
}

void MatchOp::decompile ()
{
	ins_cache = NULL;
}

nfa_state_t *NullOp::compile(nfa_t &, nfa_state_t *t)
{
	return t;
}

void NullOp::decompile () {}

nfa_state_t *RuleOp::compile(nfa_t &nfa, nfa_state_t *)
{
	if (ins_cache)
	{
		return ins_cache;
	}
	else
	{
		nfa_state_t *s3 = &nfa.states[nfa.size++];
		s3->fin(this);
		if (ctx->calc_size() > 0)
		{
			nfa_state_t *s2 = &nfa.states[nfa.size++];
			s2->ctx(ctx->compile(nfa, s3));
			s3 = s2;
		}
		nfa_state_t *s1 = exp->compile(nfa, s3);

		ins_cache = s1;
		if (ins_access == PRIVATE)
		{
			decompile();
		}

		return s1;
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

} // namespace re2c
