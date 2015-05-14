/* $Id$ */
#ifndef _token_h
#define	_token_h

#include "src/util/substr.h"

namespace re2c
{

class Token
{
public:
	const Str          text;
	const std::string  newcond;
	const std::string  source;
	uint32_t           line;
	const bool         autogen;

public:
	Token(const SubStr&, const std::string&, uint32_t);
	Token(const Token*, const std::string&, uint32_t, const std::string *);
	Token (const Token & t);
	~Token();

private:
	Token & operator = (const Token &);
};

inline Token::Token(const SubStr& t, const std::string& s, uint32_t l)
	: text(t)
	, newcond()
	, source(s)
	, line(l)
	, autogen(false)
{
	;
}

inline Token::Token(const Token* t, const std::string& s, uint32_t l, const std::string * c)
	: text(t ? t->text.to_string().c_str() : "")
	, newcond(c ? * c : "")
	, source(t ? t->source : s)
	, line(t ? t->line : l)
	, autogen(t == NULL)
{
	;
}

inline Token::Token (const Token & t)
	: text (t.text.to_string().c_str())
	, newcond (t.newcond)
	, source (t.source)
	, line (t.line)
	, autogen (t.autogen)
{}

inline Token::~Token()
{
}

} // end namespace re2c

#endif
