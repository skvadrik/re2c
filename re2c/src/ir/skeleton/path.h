#ifndef _RE2C_IR_SKELETON_PATH_
#define _RE2C_IR_SKELETON_PATH_

#include "src/util/c99_stdint.h"
#include <vector>

#include "src/parse/rules.h"

namespace re2c
{

class path_t
{
public:
	typedef std::vector<uint32_t> arc_t;

private:
	std::vector<const arc_t *> arcs;

	const RuleInfo *rule;
	size_t rule_pos;

	bool ctx;
	size_t ctx_pos;

public:
	explicit path_t (const RuleInfo *r, bool c)
		: arcs ()
		, rule (r)
		, rule_pos (0)
		, ctx (c)
		, ctx_pos (0)
	{}
	path_t(const path_t &p)
		: arcs(p.arcs)
		, rule(p.rule)
		, rule_pos(p.rule_pos)
		, ctx(p.ctx)
		, ctx_pos(p.ctx_pos)
	{}
	path_t &operator=(const path_t &p)
	{
		new (this) path_t(p);
		return *this;
	}
	size_t len () const
	{
		return arcs.size ();
	}
	size_t len_matching () const
	{
		return rule && rule->ctx_len == ~0u
			? ctx_pos
			: rule_pos;
	}
	rule_rank_t match () const
	{
		return rule ? rule->rank : rule_rank_t::none();
	}
	const arc_t * operator [] (size_t i) const
	{
		return arcs[i];
	}
	void extend (const RuleInfo *r, bool c, const arc_t * a)
	{
		arcs.push_back (a);
		if (r)
		{
			rule = r;
			rule_pos = arcs.size ();
		}
		if (c)
		{
			ctx = true;
			ctx_pos = arcs.size ();
		}
	}
	void append (const path_t * p)
	{
		if (p->rule)
		{
			rule = p->rule;
			rule_pos = arcs.size () + p->rule_pos;
		}
		if (p->ctx)
		{
			ctx = true;
			ctx_pos = arcs.size () + p->ctx_pos;
		}
		arcs.insert (arcs.end (), p->arcs.begin (), p->arcs.end ());
	}
};

} // namespace re2c

#endif // _RE2C_IR_SKELETON_PATH_
