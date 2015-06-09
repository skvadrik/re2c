#ifndef _RE2C_PARSE_TOKEN_
#define _RE2C_PARSE_TOKEN_

#include "src/util/c99_stdint.h"
#include "src/util/forbid_copy.h"

namespace re2c
{

class Token
{
public:
	const std::string text;
	const std::string newcond;
	const std::string source;
	uint32_t line;
	const bool autogen;

	Token (const char *, uint32_t, const std::string &, uint32_t);
	Token (const Token *, const std::string &, uint32_t, const std::string *);

	FORBID_COPY (Token);
};

inline Token::Token (const char * t, uint32_t t_len, const std::string & s, uint32_t l)
	: text (t, t_len)
	, newcond ()
	, source (s)
	, line (l)
	, autogen (false)
{}

inline Token::Token (const Token * t, const std::string & s, uint32_t l, const std::string * c)
	: text (t ? t->text : "")
	, newcond (c ? * c : "")
	, source (t ? t->source : s)
	, line (t ? t->line : l)
	, autogen (t == NULL)
{}

inline Token::Token (const Token & t)
	: text (t.text)
	, newcond (t.newcond)
	, source (t.source)
	, line (t.line)
	, autogen (t.autogen)
{}

} // namespace re2c

#endif // _RE2C_PARSE_TOKEN_
