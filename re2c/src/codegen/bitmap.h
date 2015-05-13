#ifndef _bitmap_h
#define _bitmap_h

#include "src/codegen/output.h"
#include "src/util/c99_stdint.h"
#include "src/util/forbid_copy.h"

namespace re2c
{

struct Go;
class State;

class BitMap
{
public:
	static BitMap	*first;

	const Go        *go;
	const State     *on;
	const BitMap    *next;
	uint32_t        i;
	uint32_t        m;

public:
	static const BitMap *find(const Go*, const State*);
	static const BitMap *find(const State*);
	static void gen(OutputFile &, uint32_t ind, uint32_t, uint32_t);
	BitMap(const Go*, const State*);
	~BitMap();

	FORBID_COPY (BitMap);
};

#ifdef _MSC_VER
# pragma warning(disable: 4355) /* 'this' : used in base member initializer list */
#endif

} // end namespace re2c

#endif // _bitmap_h
