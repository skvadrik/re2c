#ifndef _go_h
#define _go_h

#include <iostream>

#include "basics.h"
#include "code.h"

namespace re2c
{

class State;

struct Span
{
	uint ub;
	State * to;

	uint show(std::ostream&, uint) const;
};

struct Go
{
	uint nSpans; // number of spans
	uint hSpans; // number of spans with upper bound > 0x100
	Span * span;
	Span * hspan;
	uint nBitmaps;
	const BitMap ** bitmaps;

	Go ();
	~Go ();
	void init ();
};

bool matches(const Go * g1, const State * s1, const Go * g2, const State * s2);

} // namespace re2c

#endif // _go_h
