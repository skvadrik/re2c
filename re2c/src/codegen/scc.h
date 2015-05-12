#ifndef __SCC__
#define __SCC__

#include "src/util/c99_stdint.h"

namespace re2c {

class State;

static const uint32_t cInfinity = ~0u;

class SCC
{
public:
	State ** top;
	State ** stk;

	SCC (uint32_t);
	~SCC ();
	void traverse (State *);

private:
	SCC (const SCC &);
	SCC & operator = (const SCC &);
};

bool state_is_in_non_trivial_SCC (const State * s);
uint32_t maxDist (State * s);
void calcDepth (State * head);

} // namespace re2c

#endif // __SCC__
