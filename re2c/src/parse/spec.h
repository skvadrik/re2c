#ifndef _RE2C_PARSE_SPEC_
#define _RE2C_PARSE_SPEC_

#include <algorithm>

#include "src/ir/regexp/regexp.h"
#include "src/parse/rules.h"

namespace re2c
{

// for std::find_if
static bool is_def(const RuleInfo *r)
{
	return r->rank.is_def();
}

struct Spec
{
	RegExp * re;
	rules_t rules;

	Spec ()
		: re (NULL)
		, rules ()
	{}
	Spec (const Spec & spec)
		: re (spec.re)
		, rules (spec.rules)
	{}
	Spec & operator = (const Spec & spec)
	{
		re = spec.re;
		rules = spec.rules;
		return *this;
	}
	bool add_def (RegExp * r)
	{
		if (std::find_if(rules.begin(), rules.end(), is_def) != rules.end())
		{
			return false;
		}
		else
		{
			add (r);
			return true;
		}
	}
	void add (RegExp * r)
	{
		rules.push_back(r->pld.rule.info);
		re = mkAlt (re, r);
	}
	void clear ()
	{
		re = NULL;
		rules.clear ();
	}
};

} // namespace re2c

#endif // _RE2C_PARSE_SPEC_
