/* $Id$ */
#ifndef _scanner_h
#define	_scanner_h

#include <iosfwd>
#include <string>
#include "token.h"
#include "re.h"
#include "globals.h"

namespace re2c
{

class Scanner:
	public line_number
{
private:
	std::istream&	in;
	std::ostream&   out;
	char	*bot, *tok, *ptr, *cur, *pos, *lim, *top, *eof, *ctx;
	uint	tchar, tline, cline, iscfg;

private:
	char *fill(char*);
	Scanner(const Scanner&); //unimplemented
	Scanner& operator=(const Scanner&); //unimplemented

public:
	Scanner(std::istream&, std::ostream&);
	~Scanner();

	int echo();
	int scan();
	
	void fatalf(const char*, ...) const;
	void fatal(const char*) const;
	void fatal(uint, const char*) const;

	void config(const Str&, int);
	void config(const Str&, const Str&);

	void check_token_length(uint len) const;
	SubStr token() const;
	SubStr token(uint start, uint len) const;
	SubStr raw_token(std::string enclosure) const;
	virtual uint get_line() const;	
	uint xlat(uint c) const;

	uint unescape(SubStr &s) const;
	std::string& unescape(SubStr& str_in, std::string& str_out) const;

	Range * getRange(SubStr &s) const;
	RegExp * matchChar(uint c) const;
	RegExp * strToName(SubStr s) const;
	RegExp * strToRE(SubStr s) const;
	RegExp * strToCaseInsensitiveRE(SubStr s) const;
	RegExp * ranToRE(SubStr s) const;
	RegExp * invToRE(SubStr s) const;
	RegExp * mkDot() const;
};

inline void Scanner::fatal(const char *msg) const
{
	fatal(0, msg);
}

inline SubStr Scanner::token() const
{
	check_token_length(cur - tok);
	return SubStr(tok, cur - tok);
}

inline SubStr Scanner::token(uint start, uint len) const
{
	check_token_length(len);
	return SubStr(tok + start, len);
}

inline uint Scanner::xlat(uint c) const
{
	return re2c::wFlag ? c : re2c::xlat[c & 0xFF];
}

} // end namespace re2c

#endif
