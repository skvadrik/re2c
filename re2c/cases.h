#ifndef _cases_h
#define _cases_h

#include <vector>

#include "dfa.h"

namespace re2c {

struct Case
{
	std::vector<std::pair<uint, uint> > ranges;
	State * to;
};

class Cases
{
	State * def;
	Case * cases;
	uint cases_size;

	void add (uint lb, uint ub, State * to);

public:
	Cases (const Span * s, uint n);
	~Cases ();
	uint size () const;
	State * default_state () const;
	const Case & operator [] (uint i) const;
};

} //namespace re2c

#endif // _cases_h
