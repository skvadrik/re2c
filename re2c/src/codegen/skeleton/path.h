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
	explicit generic_path_t (rule_rank_t r)
		: arcs ()
		, rule (r)
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
	void extend (rule_rank_t r, const arc_t & a)
	{
		arcs.push_back (a);
		if (!r.is_none ())
		{
			rule = r;
			rule_pos = arcs.size ();
		}
	}
	void append (const arc_t & a, const generic_path_t<arc_t> * p)
	{
		arcs.push_back (a);
		if (!p->rule.is_none ())
		{
			rule = p->rule;
			rule_pos = arcs.size () + p->rule_pos;
		}
		arcs.insert (arcs.end (), p->arcs.begin (), p->arcs.end ());
	}

	template <typename arc1_t, typename arc2_t>
		friend size_t len_matching (const generic_path_t<arc1_t> & prefix, const generic_path_t<arc2_t> & suffix);
	template <typename arc1_t, typename arc2_t>
		friend rule_rank_t match (const generic_path_t<arc1_t> & prefix, const generic_path_t<arc2_t> & suffix);
};

template <typename arc1_t, typename arc2_t>
	size_t len_matching (const generic_path_t<arc1_t> & prefix, const generic_path_t<arc2_t> & suffix)
{
	return suffix.rule.is_none ()
		? prefix.rule_pos
		: prefix.arcs.size () + suffix.rule_pos;
}

template <typename arc1_t, typename arc2_t>
	rule_rank_t match (const generic_path_t<arc1_t> & prefix, const generic_path_t<arc2_t> & suffix)
{
	return suffix.match ().is_none ()
		? prefix.match ()
		: suffix.match ();
}

typedef generic_path_t<uint32_t> path_t;

typedef std::vector<uint32_t> multiarc_t;
typedef generic_path_t<const multiarc_t *> multipath_t;

} // namespace re2c

#endif // _RE2C_CODEGEN_SKELETON_PATH_
