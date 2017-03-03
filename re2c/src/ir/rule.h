#ifndef _RE2C_IR_RULE_
#define _RE2C_IR_RULE_

#include "src/util/c99_stdint.h"
#include <set>
#include <string>

#include "src/ir/tag.h"
#include "src/util/free_list.h"
#include "src/util/forbid_copy.h"

namespace re2c
{

struct Code
{
	static free_list<Code*> flist;

	std::string fname;
	uint32_t fline;
	bool autogen;
	const std::string text;
	std::string cond;

	Code(const std::string &file, uint32_t line)
		: fname(file)
		, fline(line)
		, autogen(true)
		, text("")
		, cond("")
	{
		flist.insert(this);
	}
	Code(const std::string &file, uint32_t line, const char *s, size_t slen)
		: fname(file)
		, fline(line)
		, autogen(false)
		, text(s, slen)
		, cond("")
	{
		flist.insert(this);
	}
	~Code()
	{
		flist.erase(this);
	}
};

struct Rule
{
	static const size_t NONE;

	const Code *code;
	std::set<uint32_t> shadow;

	// tags
	size_t ltag; // first
	size_t htag; // next to last
	size_t ttag; // trailing context

	size_t ncap; // number of POSIX captures

	Rule(): code(NULL), shadow(),
		ltag(0), htag(0), ttag(0), ncap(0) {}
	FORBID_COPY(Rule);
};

} // namespace re2c

#endif // _RE2C_IR_RULE_
