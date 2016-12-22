#ifndef _RE2C_IR_RULE_
#define _RE2C_IR_RULE_

#include "src/util/c99_stdint.h"
#include <set>
#include <string>

#include "src/ir/tag.h"
#include "src/util/forbid_copy.h"

namespace re2c
{

struct Code
{
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
	{}
	Code(const std::string &file, uint32_t line, const char *s, size_t slen)
		: fname(file)
		, fline(line)
		, autogen(false)
		, text(s, slen)
		, cond("")
	{}
};

struct Rule
{
	static const size_t NONE;

	const Code *code;
	std::set<uint32_t> shadow;

	// variable tags
	size_t lvar; // first
	size_t hvar; // next to last
	size_t tvar; // trailing context

	// fixed tags
	size_t lfix; // first
	size_t hfix; // next to last
	size_t tfix; // trailing context

	Rule(): code(NULL), shadow(),
		lvar(0), hvar(0), tvar(0),
		lfix(0), hfix(0), tfix(0)
	{}
	FORBID_COPY(Rule);
};

} // namespace re2c

#endif // _RE2C_IR_RULE_
