#include "src/codegen/skeleton/skeleton.h"

namespace re2c
{

// see note [estimating total size of paths in skeleton]
// neither do we need all default paths, nor default path cover:
// just one path per each default final state, the shorter the better
arccount_t Node::generate_paths_default (const way_t & prefix, std::vector<way_t> & ways)
{
	if (!rule.is_none ())
	{
		return arccount_t (0u);
	}
	else if (end ())
	{
		ways.push_back (prefix);
		return arccount_t (prefix.size ());
	}
	else if (loop < 2)
	{
		local_inc _ (loop);
		arccount_t size (0u);
		for (arcsets_t::iterator i = arcsets.begin (); i != arcsets.end (); ++i)
		{
			way_t w = prefix;
			w.push_back (&i->second);
			size = size + i->first->generate_paths_default (w, ways);
			if (size.overflow ())
			{
				return arccount_t::limit ();
			}
		}
		return size;
	}
	else
	{
		return arccount_t (0u);
	}
}

void Skeleton::warn_undefined_control_flow (uint32_t line, const std::string & cond)
{
	way_t prefix;
	std::vector<way_t> ways;
	const bool overflow = nodes->generate_paths_default (prefix, ways).overflow ();
	if (!ways.empty ())
	{
		warn.undefined_control_flow (line, cond, ways, overflow);
	}
	else if (overflow)
	{
		warn.fail (Warn::UNDEFINED_CONTROL_FLOW, line, "DFA is too large to check undefined control flow");
	}
}

} // namespace re2c
