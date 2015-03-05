#include "cases.h"

namespace re2c {

Cases::Cases (const Span * span, uint span_size)
	: def (span[span_size - 1].to)
	, cases (new Case[span_size - 1])
	, cases_size (0)
{
	for (uint i = 0, lb = 0; i < span_size - 1; ++ i)
	{
		if (span[i].to != def)
		{
			add (lb, span[i].ub, span[i].to);
		}
		lb = span[i].ub;
	}
}

void Cases::add (uint lb, uint ub, State * to)
{
	for (uint i = 0; i < cases_size; ++i)
	{
		if (cases[i].to == to)
		{
			cases[i].ranges.push_back (std::make_pair (lb, ub));
			return;
		}
	}
	cases[cases_size].ranges.push_back (std::make_pair (lb, ub));
	cases[cases_size].to = to;
	++cases_size;
}

uint Cases::size () const
{
	return cases_size;
}

State * Cases::default_case () const
{
	return def;
}

const Case & Cases::operator [] (uint i) const
{
	return cases[i];
}

Cases::~Cases ()
{
	delete [] cases;
}

} // namespace re2c
