/* $Id$ */
#ifndef _token_h
#define	_token_h

#include "substr.h"

namespace re2c
{

class Token
{
public:
	const Str   text;
	const Str*  newcond;
	const uint  line;
	const bool  autogen;
	const bool  condchange;

public:
	Token(const SubStr&, uint);
	Token(const Token*, uint, Str*, bool);
	Token(const Token& oth);
	~Token();
};

inline Token::Token(const SubStr& t, uint l)
	: text(t)
	, newcond(NULL)
	, line(l)
	, autogen(false)
	, condchange(false)
{
	;
}

inline Token::Token(const Token* t, uint l, Str *c, bool chg)
	: text(t ? t->text.to_string().c_str() : "")
	, newcond(c)
	, line(t ? t->line : l)
	, autogen(t == NULL)
	, condchange(chg)
{
	;
}

inline Token::Token(const Token& oth)
	: text(oth.text.to_string().c_str())
	, newcond(oth.newcond ? new Str(*oth.newcond) : NULL)
	, line(oth.line)
	, autogen(oth.autogen)
	, condchange(oth.autogen)
{
	;
}

inline Token::~Token()
{
	delete newcond;
}

} // end namespace re2c

#endif
