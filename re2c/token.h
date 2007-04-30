/* $Id$ */
#ifndef _token_h
#define	_token_h

#include "substr.h"

namespace re2c
{

class Token
{
public:
	Str 	text;
	Str*	newcond;
	uint	line;

public:
	Token(const SubStr&, uint);
	Token(const Token& oth);
	~Token();
};

inline Token::Token(const SubStr& t, uint l) : text(t), newcond(NULL), line(l)
{
	;
}

inline Token::Token(const Token& oth)
	: text(oth.text)
	, newcond(oth.newcond ? new Str(*oth.newcond) : NULL)
	, line(oth.line)
{
	;
}

inline Token::~Token()
{
	if (newcond)
	{
		delete newcond;
	}
}

} // end namespace re2c

#endif
