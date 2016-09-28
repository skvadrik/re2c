#ifndef _RE2C_IR_DFA_FIND_STATE_
#define _RE2C_IR_DFA_FIND_STATE_

#include "src/ir/dfa/closure.h"
#include "src/util/lookup.h"

namespace re2c
{

struct Tagpool;

struct clospool_t
{
private:
	typedef lookup_t<const closure_t*> closlookup_t;
	closlookup_t lookup;

public:
	clospool_t();
	~clospool_t();
	size_t size() const;
	const closure_t& operator[](size_t idx) const;
	size_t insert(const closure_t &clos);
};

size_t find_state(const closure_t &clos, clospool_t &clospool);

} // namespace re2c

#endif // _RE2C_IR_DFA_FIND_STATE_
