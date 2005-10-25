/* $Id$ */
#ifndef _substr_h
#define _substr_h

#include <iostream>
#include <string>
#include "basics.h"

namespace re2c
{

class SubStr
{

public:
	char	*str;
	uint	len;

public:
	friend bool operator==(const SubStr &, const SubStr &);
	SubStr(uchar*, uint);
	SubStr(char*, uint);
	SubStr(char*);
	SubStr(const SubStr&);
	void out(std::ostream&) const;
	std::string to_string() const
	{
		return std::string(str, len);
	}
};

class Str: public SubStr
{

public:
	Str(const SubStr&);
	Str(Str&);
	Str();
	~Str();
};

inline std::ostream& operator<<(std::ostream& o, const SubStr &s)
{
	s.out(o);
	return o;
}

inline std::ostream& operator<<(std::ostream& o, const SubStr* s)
{
	return o << *s;
}

inline SubStr::SubStr(uchar *s, uint l)
		: str((char*) s), len(l)
{ }

inline SubStr::SubStr(char *s, uint l)
		: str(s), len(l)
{ }

inline SubStr::SubStr(char *s)
		: str(s), len(strlen(s))
{ }

inline SubStr::SubStr(const SubStr &s)
		: str(s.str), len(s.len)
{ }

} // end namespace re2c

#endif
