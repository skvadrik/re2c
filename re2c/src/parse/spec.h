#ifndef _RE2C_PARSE_SPEC_
#define _RE2C_PARSE_SPEC_

#include "src/ir/regexp/regexp.h"

namespace re2c
{

struct Spec
{
	const RegExpRule *def;
	std::vector<const RegExpRule*> res;

	Spec(): def(NULL), res() {}
	Spec(const Spec &spec): def(spec.def), res(spec.res) {}
	bool add_def(const RegExpRule *r)
	{
		if (def) {
			return false;
		} else {
			def = r;
			return true;
		}
	}
	void add(const RegExpRule *r)
	{
		res.push_back(r);
	}
	void clear()
	{
		def = NULL;
		res.clear();
	}

private:
	Spec& operator=(const Spec&);
};

} // namespace re2c

#endif // _RE2C_PARSE_SPEC_
