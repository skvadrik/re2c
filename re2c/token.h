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
	uint	line;

public:
	Token(const SubStr&, uint);
	Token(const Token& oth);
};

inline Token::Token(const SubStr& t, uint l) : text(t), line(l)
{
	;
}

inline Token::Token(const Token& oth) : text(oth.text), line(oth.line)
{
	;
}

} // end namespace re2c

#endif
