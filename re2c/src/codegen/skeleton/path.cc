#include "src/codegen/skeleton/path.h"

namespace re2c
{

namespace skeleton
{

Path::Path (const chars_t & cs, size_t l, rule_rank_t r)
	: chars (cs)
	, length (l)
	, rule (r)
{}

void Path::update (rule_rank_t r)
{
	if (!r.is_none ())
	{
		length = chars.size ();
		rule = r;
	}
}

void Path::extend (rule_rank_t r, uint32_t c)
{
	update (r);
	chars.push_back (c);
}

void Path::append (const Path * p)
{
	if (!p->rule.is_none ())
	{
		length = chars.size () + p->length;
		rule = p->rule;
	}
	const size_t sz = p->chars.size ();
	for (size_t i = 0; i < sz; ++i)
	{
		chars.push_back (p->chars[i]);
	}
}

} // namespace skeleton

} // namespace re2c
