#include "src/codegen/skeleton/path.h"

namespace re2c
{

path_t::path_t ()
	: arcs ()
	, rule (rule_rank_t::none ())
	, rule_pos (0)
{}

size_t path_t::len () const
{
	return arcs.size ();
}

size_t path_t::len_matching () const
{
	return rule_pos;
}

rule_rank_t path_t::match () const
{
	return rule;
}

uint32_t path_t::operator [] (size_t i) const
{
	return arcs[i];
}

void path_t::update (rule_rank_t r)
{
	if (!r.is_none ())
	{
		rule = r;
		rule_pos = arcs.size ();
	}
}

void path_t::extend (rule_rank_t r, uint32_t c)
{
	update (r);
	arcs.push_back (c);
}

void path_t::append (const path_t * p)
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

} // namespace re2c
