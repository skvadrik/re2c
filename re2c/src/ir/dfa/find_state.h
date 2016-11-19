#ifndef _RE2C_IR_DFA_FIND_STATE_
#define _RE2C_IR_DFA_FIND_STATE_

#include "src/ir/dfa/closure.h"
#include "src/util/forbid_copy.h"
#include "src/util/lookup.h"

namespace re2c
{

struct kernel_t
{
	size_t size;
	nfa_state_t **state;
	size_t *tlook;

	explicit kernel_t(size_t n);
	~kernel_t();
	static kernel_t *copy(const kernel_t &k);
	FORBID_COPY(kernel_t);
};

struct kernels_t
{
private:
	typedef lookup_t<const kernel_t*> index_t;

	index_t lookup;
	size_t maxsize;
	kernel_t *buffer;

public:
	kernels_t();
	~kernels_t();
	size_t size() const;
	const kernel_t* operator[](size_t idx) const;
	size_t insert(const closure_t &clos);
	FORBID_COPY(kernels_t);
};

} // namespace re2c

#endif // _RE2C_IR_DFA_FIND_STATE_
