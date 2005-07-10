/* $Id$ */
#ifndef _scanner_h
#define	_scanner_h

#include <iosfwd>
#include "token.h"
#include "re.h"

namespace re2c
{

class Scanner
{

private:
	std::istream&	in;
	char	*bot, *tok, *ptr, *cur, *pos, *lim, *top, *eof;
	uint	tchar, tline, cline;

private:
	char *fill(char*);
	Scanner(const Scanner&); //unimplemented
	Scanner& operator=(const Scanner&); //unimplemented

public:
	Scanner(std::istream&);
	int echo(std::ostream&);
	int scan();
	void fatal(char*) const;
	SubStr token();
	uint line();
	
	uchar unescape(SubStr &s) const;
	Range * getRange(SubStr &s) const;
	RegExp * matchChar(uint c) const;
	RegExp * strToRE(SubStr s) const;
	RegExp * strToCaseInsensitiveRE(SubStr s) const;
	RegExp * ranToRE(SubStr s) const;
	RegExp * invToRE(SubStr s) const;
	RegExp * mkDot() const;
};

inline SubStr Scanner::token()
{
	return SubStr(tok, cur - tok);
}

inline uint Scanner::line()
{
	return cline;
}

} // end namespace re2c

#endif
