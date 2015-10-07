#ifndef _RE2C_PARSE_SPEC_
#define _RE2C_PARSE_SPEC_

#include "src/ir/regexp/regexp.h"

namespace re2c
{

struct Spec
{
	RegExp * re;
	bool def;

	Spec ()
		: re (NULL)
		, def (false)
	{}
	bool add_def (RegExp * r)
	{
		if (def)
		{
			return false;
		}
		else
		{
			def = true;
			addl (r);
			return true;
		}
	}
	void add (RegExp * r)
	{
		re = mkAlt (re, r);
	}
	void addl (RegExp * r)
	{
		re = mkAlt (r, re);
	}
	void clear ()
	{
		re = NULL;
		def = false;
	}
};

} // namespace re2c

#endif // _RE2C_PARSE_SPEC_
