#include <ostream>

#include "src/ir/rule_rank.h"

namespace re2c
{

const uint32_t rule_rank_t::NONE = 0xFFFFffff;

rule_rank_t::rule_rank_t ()
	: value (0)
{}

void rule_rank_t::inc ()
{
	++value;
}

rule_rank_t rule_rank_t::none ()
{
	rule_rank_t r;
	r.value = NONE;
	return r;
}

bool rule_rank_t::is_none () const
{
	return value == NONE;
}

bool rule_rank_t::operator < (const rule_rank_t & r) const
{
	return value < r.value;
}

std::ostream & operator << (std::ostream & o, rule_rank_t r)
{
	o << r.value;
	return o;
}

} // namespace re2c
