#include "src/codegen/skeleton/path.h"

namespace re2c
{

namespace skeleton
{

Path::Path (const chars_t & cs, uint32_t l, uint32_t r)
	: chars (cs)
	, length (l)
	, rule (r)
{}

void Path::update (uint32_t r)
{
	if (r != NO_RULE)
	{
		length = chars.size ();
		rule = r;
	}
}

void Path::extend (uint32_t r, uint32_t c)
{
	update (r);
	chars.push_back (c);
}

void Path::append (const Path * p)
{
	if (p->rule != NO_RULE)
	{
		length = chars.size () + p->length;
		rule = p->rule;
	}
	for (uint32_t i = 0; i < p->chars.size (); ++i)
	{
		chars.push_back (p->chars[i]);
	}
}

} // namespace skeleton

} // namespace re2c
