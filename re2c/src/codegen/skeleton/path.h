#ifndef _RE2C_CODEGEN_SKELETON_PATH_
#define _RE2C_CODEGEN_SKELETON_PATH_

#include <vector>

#include "src/ir/rule_rank.h"
#include "src/util/c99_stdint.h"

namespace re2c
{

template <typename arc_t>
class generic_path_t
{
	std::vector<arc_t> arcs;
	rule_rank_t rule;
	size_t rule_pos;

public:
	generic_path_t ()
		: arcs ()
		, rule (rule_rank_t::none ())
		, rule_pos (0)
	{}
	size_t len () const
	{
		return arcs.size ();
	}
	size_t len_matching () const
	{
		return rule_pos;
	}
	rule_rank_t match () const
	{
		return rule;
	}
	const arc_t & operator [] (size_t i) const
	{
		return arcs[i];
	}
	void update (rule_rank_t r)
	{
		if (!r.is_none ())
		{
			rule = r;
			rule_pos = arcs.size ();
		}
	}
	void extend (rule_rank_t r, arc_t a)
	{
		update (r);
		arcs.push_back (a);
	}
	void append (const generic_path_t<arc_t> * p)
	{
		if (!p->rule.is_none ())
		{
			rule = p->rule;
			rule_pos = arcs.size () + p->rule_pos;
		}
		const size_t sz = p->arcs.size ();
		for (size_t i = 0; i < sz; ++i)
		{
			arcs.push_back (p->arcs[i]);
		}
	}
};

typedef generic_path_t<uint32_t> path_t;

typedef std::vector<uint32_t> multiarc_t;
typedef generic_path_t<const multiarc_t *> multipath_t;

} // namespace re2c

#endif // _RE2C_CODEGEN_SKELETON_PATH_
