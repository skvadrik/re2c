/* $Id$ */
#ifndef _code_h
#define _code_h

#include "re.h"
#include "dfa.h"

namespace re2c
{

class BitMap
{
public:
	static BitMap	*first;

	const Go        *go;
	const State     *on;
	const BitMap    *next;
	uint            i;
	uint            m;

public:
	static const BitMap *find(const Go*, const State*);
	static const BitMap *find(const State*);
	static void gen(std::ostream&, uint ind, uint, uint);
	static void stats();
	BitMap(const Go*, const State*);
	~BitMap();

#if PEDANTIC
	BitMap(const BitMap& oth)
		: go(oth.go)
		, on(oth.on)
		, next(oth.next)
		, i(oth.i)
		, m(oth.m)
	{
	}
	BitMap& operator = (const BitMap& oth)
	{
		new(this) BitMap(oth);
		return *this;
	}
#endif
};

template<class char_type>
class basic_null_streambuf
	: public std::basic_streambuf<char_type>
{
public:
	basic_null_streambuf()
		: std::basic_streambuf<char_type>()
	{
	}	
};

template <class char_type>
class basic_null_stream
	: protected basic_null_streambuf<char_type>
	, public std::basic_ostream<char_type>
{
public:
	basic_null_stream()
		: basic_null_streambuf<char_type>()
		, std::basic_ostream<char_type>(static_cast<basic_null_streambuf<char_type>*>(this))
	{
	}

	basic_null_stream& put(char_type)
	{
		// nothing to do
		return *this;
	}
	
	basic_null_stream& write(const char_type *, std::streamsize)
	{
		// nothing to do
		return *this;
	}
};

typedef basic_null_stream<char> null_stream;

} // end namespace re2c

#endif
