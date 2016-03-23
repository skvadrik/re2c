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
	const RegExp * re;
	rules_t rules;
	std::vector<CtxVar> contexts;

	Spec ()
		: re (NULL)
		, rules ()
		, contexts ()
	{}
	Spec (const Spec & spec)
		: re (spec.re)
		, rules (spec.rules)
		, contexts (spec.contexts)
	{}
	bool add_def (const RegExp * r)
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
	void add (const RegExp * r)
	{
		rules.push_back(r->pld.rule.info);
		re = mkAlt (re, r);
	}
	void clear ()
	{
		re = NULL;
		rules.clear ();
		contexts.clear();
	}

private:
	Spec& operator=(const Spec&);
};

struct SpecStar
{
	std::vector<const RegExp*> rules;
	std::vector<CtxVar> contexts;

	SpecStar(): rules(), contexts() {}
	void clear()
	{
		rules.clear();
		contexts.clear();
	}
};

} // namespace re2c

#endif // _RE2C_PARSE_SPEC_
