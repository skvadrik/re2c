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
	const uint         line;
	const bool         autogen;

public:
	Token(const SubStr&, uint);
	Token(const Token*, uint, const Str*);
	Token(const Token& oth);
	~Token();
};

inline Token::Token(const SubStr& t, uint l)
	: text(t)
	, newcond()
	, line(l)
	, autogen(false)
{
	;
}

inline Token::Token(const Token* t, uint l, const Str *c)
	: text(t ? t->text.to_string().c_str() : "")
	, newcond(c ? c->to_string() : "")
	, line(t ? t->line : l)
	, autogen(t == NULL)
{
	;
}

inline Token::Token(const Token& oth)
	: text(oth.text.to_string().c_str())
	, newcond(oth.newcond)
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
