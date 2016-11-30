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
	size_t *tvers; // tag versions
	size_t *tlook; // lookahead tags

	explicit kernel_t(size_t n);
	~kernel_t();
	static kernel_t *copy(const kernel_t &k);
	FORBID_COPY(kernel_t);
};

struct mapping_t
{
	tcmd_t *cmd;

private:
	const bool INJECTIVE;

	Tagpool &tagpool;
	tcpool_t &tcpool;

	tagver_t max; // maximal tag version
	tagver_t cap; // capacity (greater or equal to max)
	char *mem;
	size_t *x2t;
	tagver_t *x2y;
	tagver_t *y2x;

public:
	mapping_t(Tagpool &tagp, tcpool_t &tcp, bool injective);
	~mapping_t();
	void init(tagver_t v, tcmd_t *c);
	bool operator()(const kernel_t *k1, const kernel_t *k2);
	FORBID_COPY(mapping_t);
};

struct kernels_t
{
private:
	typedef lookup_t<const kernel_t*> index_t;

	index_t lookup;
	mapping_t mapping;
	size_t maxsize;
	kernel_t *buffer;

public:
	kernels_t(Tagpool &tagpool, tcpool_t &tcpool);
	~kernels_t();
	size_t size() const;
	const kernel_t* operator[](size_t idx) const;
	size_t insert(const closure_t &clos, tcmd_t *cmd, tagver_t maxver);
	FORBID_COPY(kernels_t);
};

} // namespace re2c

#endif // _RE2C_IR_DFA_FIND_STATE_
