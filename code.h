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
	uchar           m;

public:
	static const BitMap *find(const Go*, const State*);
	static const BitMap *find(const State*);
	static void gen(std::ostream&, uint, uint);
	static void stats();
	BitMap(const Go*, const State*);
	~BitMap();
};

} // end namespace re2c

#endif
