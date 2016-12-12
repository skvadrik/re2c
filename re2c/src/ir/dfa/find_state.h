#ifndef _RE2C_IR_DFA_FIND_STATE_
#define _RE2C_IR_DFA_FIND_STATE_

#include "src/ir/dfa/closure.h"
#include "src/ir/dfa/dump.h"
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
private:
	Tagpool &tagpool;
	tagver_t cap; // capacity (greater or equal to max)
	char *mem;
	size_t *x2t;
	tagver_t *x2y;
	tagver_t *y2x;

public:
	const bool bijective;
	tagver_t max; // maximal tag version
	size_t *x2t_backup;
	tagver_t *x2y_backup;
	uint32_t *indeg;

	explicit mapping_t(Tagpool &pool);
	~mapping_t();
	void init(tagver_t v);
	bool better() const;
	void backup();
	bool operator()(const kernel_t *k1, const kernel_t *k2);
	FORBID_COPY(mapping_t);
};

struct kernels_t
{
	struct result_t
	{
		size_t state;
		mapping_t *mapping;
		bool isnew;

		result_t(size_t s, mapping_t *m, bool n)
			: state(s)
			, mapping(m)
			, isnew(n)
		{}
	};

private:
	typedef lookup_t<const kernel_t*> index_t;

	index_t lookup;
	mapping_t mapping;
	size_t maxsize;
	kernel_t *buffer;

public:
	explicit kernels_t(Tagpool &tagpool);
	~kernels_t();
	size_t size() const;
	const kernel_t* operator[](size_t idx) const;
	result_t insert(const closure_t &clos, tagver_t maxver);
	FORBID_COPY(kernels_t);
};

void find_state(dfa_t &dfa, size_t state, size_t symbol,
	const Tagpool &tagpool, kernels_t &kernels,
	const closure_t &closure, dump_dfa_t &dump);

} // namespace re2c

#endif // _RE2C_IR_DFA_FIND_STATE_
