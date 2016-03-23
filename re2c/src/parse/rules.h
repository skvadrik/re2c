#ifndef _RE2C_PARSE_RULES_
#define _RE2C_PARSE_RULES_

#include "src/util/c99_stdint.h"
#include <set>
#include <string>
#include <vector>

#include "src/ir/rule_rank.h"
#include "src/parse/code.h"
#include "src/parse/loc.h"
#include "src/util/forbid_copy.h"

namespace re2c
{

struct CtxVar
{
	const std::string *name;
	std::string fullname;

	CtxVar(const std::string *n, rule_rank_t rank);
	CtxVar(const CtxVar &ctx):
		name(ctx.name),
		fullname(ctx.fullname)
	{}
	CtxVar& operator=(const CtxVar &ctx)
	{
		name = ctx.name;
		fullname = ctx.fullname;
		return *this;
	}
};

struct CtxFix
{
	static const size_t RIGHTMOST;

	const std::string *name;
	size_t base;
	size_t dist;

	CtxFix(const std::string *n, size_t b, size_t d);
};

struct Trail
{
	enum {NONE, VAR, FIX} type;
	union
	{
		size_t var;
		size_t fix; // trailing context must be the rightmost; no need for base
	} pld;

	Trail(): type(NONE), pld() {}
	void make_var(size_t v)
	{
		type = VAR;
		pld.var = v;
	}
	void make_fix(size_t f)
	{
		type = FIX;
		pld.fix = f;
	}
};

struct RuleInfo
{
	const Loc loc;

	std::vector<size_t> ctxvar;
	std::vector<CtxFix> ctxfix;
	Trail trail;

	rule_rank_t rank;
	const Code *code;
	const std::string newcond;

	std::set<uint32_t> shadow;
	bool reachable;
	bool nullable;

	RuleInfo
		( const Loc & l
		, rule_rank_t r
		, const Code * c
		, const std::string * cond
		, bool nl
		, const std::vector<size_t> &ctxv
		, const std::vector<CtxFix> &ctxf
		, const Trail &tr
		)
		: loc (l)
		, ctxvar (ctxv)
		, ctxfix (ctxf)
		, trail (tr)
		, rank (r)
		, code (c)
		, newcond (cond ? *cond : "")
		, shadow ()
		, reachable (false)
		, nullable (nl)
	{}

	static RuleInfo *copy_rebase(const RuleInfo *rule, rule_rank_t rank, size_t shift)
	{
		RuleInfo *r = new RuleInfo(rule->loc, rank,
			rule->code, &rule->newcond, rule->nullable,
			rule->ctxvar, rule->ctxfix, rule->trail);
		for (size_t i = 0; i < r->ctxvar.size(); ++i) {
			r->ctxvar[i] += shift;
		}
		if (r->trail.type == Trail::VAR) {
			r->trail.pld.var += shift;
		}
		return r;
	}

	FORBID_COPY(RuleInfo);
};

typedef std::vector<RuleInfo*> rules_t;

} // namespace re2c

#endif // _RE2C_PARSE_RULES_
