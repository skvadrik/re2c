#ifndef _RE2C_PARSE_TOKEN_
#define _RE2C_PARSE_TOKEN_

#include "src/parse/loc.h"
#include "src/util/c99_stdint.h"
#include "src/util/forbid_copy.h"

namespace re2c
{

class Token
{
public:
	const Loc loc;
	const std::string text;
	const bool autogen;

	inline Token (const char * t, uint32_t t_len, const std::string & s, uint32_t l)
		: loc (s, l)
		, text (t, t_len)
		, autogen (false)
	{}
	inline Token (const Token * t, const std::string & s, uint32_t l)
		: loc (t ? t->loc : Loc (s, l))
		, text (t ? t->text : "")
		, autogen (t == NULL)
	{}

	FORBID_COPY (Token);
};

} // namespace re2c

#endif // _RE2C_PARSE_TOKEN_
