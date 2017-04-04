#ifndef _RE2C_DFA_TCMD_
#define _RE2C_DFA_TCMD_

#include "src/re/tag.h"
#include "src/util/c99_stdint.h"
#include "src/util/forbid_copy.h"
#include "src/util/lookup.h"
#include "src/util/slab_allocator.h"

namespace re2c
{

struct tcmd_t
{
	tcmd_t *next;
	tagver_t lhs; // left hand side
	tagver_t rhs; // right hand side

	static bool less(const tcmd_t &x, const tcmd_t &y);
	static void swap(tcmd_t &x, tcmd_t &y);
	static bool equal(const tcmd_t &x, const tcmd_t &y);
	static void topsort(tcmd_t **phead, uint32_t *indeg);
	static bool iscopy(tagver_t rhs);
	FORBID_COPY(tcmd_t);
};

typedef uint32_t tcid_t;

static const tcid_t TCID0 = 0;

class tcpool_t
{
	typedef slab_allocator_t<~0u, 4096> alc_t;
	typedef lookup_t<const tcmd_t*> index_t;

	alc_t alc;
	index_t index;

public:
	tcpool_t();
	tcmd_t *make_tcmd(tcmd_t *next, tagver_t lhs, tagver_t rhs);
	tcid_t insert(const tcmd_t *tcmd);
	const tcmd_t *operator[](tcid_t id) const;
};

} // namespace re2c

#endif // _RE2C_DFA_TCMD_
