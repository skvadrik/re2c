#ifndef _RE2C_DFA_FIND_STATE_
#define _RE2C_DFA_FIND_STATE_

#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <vector>

#include "src/dfa/closure.h"
#include "src/dfa/dump.h"
#include "src/dfa/tagtree.h"
#include "src/re/tag.h"
#include "src/util/forbid_copy.h"
#include "src/util/lookup.h"

namespace re2c
{

class tcpool_t;
struct Tagpool;
struct dfa_t;
struct dump_dfa_t;
struct nfa_state_t;
struct tcmd_t;

struct kernel_t
{
	size_t size;
	nfa_state_t **state;
	size_t *tvers; // tag versions
	hidx_t *tlook; // lookahead tags
	size_t *order; // see note [orbit order of closure items]

	explicit kernel_t(size_t n);
	~kernel_t();
	static kernel_t *copy(const kernel_t &k);
	FORBID_COPY(kernel_t);
};

struct kernels_t
{
	struct result_t
	{
		size_t state;
		tcmd_t *cmd;
		bool isnew;

		result_t(size_t s, tcmd_t *p, bool n)
			: state(s)
			, cmd(p)
			, isnew(n)
		{}
	};

private:
	typedef lookup_t<const kernel_t*> index_t;
	index_t lookup;

public:
	Tagpool &tagpool;
	tcpool_t &tcpool;
	const std::vector<Tag> &tags;

private:
	size_t maxsize;
	kernel_t *buffer;

	tagver_t cap; // capacity (greater or equal to max)
	tagver_t max; // maximal tag version
	char *mem;
	tagver_t *x2y;
	tagver_t *y2x;
	size_t *x2t;
	uint32_t *indeg;

	tcmd_t **pacts;
	tcmd_t **actnext;
	tagver_t *actlhs;

public:
	kernels_t(Tagpool &tagp, tcpool_t &tcp, const std::vector<Tag> &ts);
	~kernels_t();
	void init(tagver_t v, size_t nkern);
	size_t size() const;
	const kernel_t* operator[](size_t idx) const;
	result_t insert(const closure_t &clos, tcmd_t *acts, tagver_t maxver);
	bool operator()(const kernel_t *k1, const kernel_t *k2);
	FORBID_COPY(kernels_t);
};

void find_state(dfa_t &dfa, size_t state, size_t symbol, kernels_t &kernels,
	const closure_t &closure, tcmd_t *acts, dump_dfa_t &dump);

} // namespace re2c

#endif // _RE2C_DFA_FIND_STATE_
