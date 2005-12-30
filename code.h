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
};

class null_stream: public std::ostream
{
public:
	null_stream()
		: std::ostream(&ns)
	{
	}

	null_stream& put(char_type)
	{
		// nothing to do
		return *this;
	}
	
	null_stream& write(const char_type *, std::streamsize)
	{
		// nothing to do
		return *this;
	}

protected:
	class null_streambuf: public std::streambuf
	{
	public:
		null_streambuf()
			: std::streambuf()
		{
		}	
	};
	null_streambuf   ns;
};

} // end namespace re2c

#endif
