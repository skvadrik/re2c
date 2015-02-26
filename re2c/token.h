/* $Id$ */
#ifndef _token_h
#define	_token_h

#include "substr.h"

namespace re2c
{

class Token
{
public:
	const Str          text;
	const std::string  newcond;
	const std::string  source;
	uint               line;
	const bool         autogen;

public:
	Token(const SubStr&, const std::string&, uint);
	Token(const Token*, const std::string&, uint, const Str*);
	Token(const Token& oth);
	~Token();
};

inline Token::Token(const SubStr& t, const std::string& s, uint l)
	: text(t)
	, newcond()
	, source(s)
	, line(l)
	, autogen(false)
{
	;
}

inline Token::Token(const Token* t, const std::string& s, uint l, const Str *c)
	: text(t ? t->text.to_string().c_str() : "")
	, newcond(c ? c->to_string() : "")
	, source(t ? t->source : s)
	, line(t ? t->line : l)
	, autogen(t == NULL)
{
	;
}

inline Token::Token(const Token& oth)
	: text(oth.text.to_string().c_str())
	, newcond(oth.newcond)
	, source(oth.source)
	, line(oth.line)
	, autogen(oth.autogen)
{
	;
}

inline Token::~Token()
{
}

} // end namespace re2c

#endif
