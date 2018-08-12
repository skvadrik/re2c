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
	const prectable_t *prectbl;
	nfa_state_t **state;
	uint32_t *tvers; // tag versions
	hidx_t *tlook; // lookahead tags

	FORBID_COPY(kernel_t);
};

struct kernel_buffers_t
{
	size_t maxsize;
	kernel_t *kernel;
	tagver_t cap; // capacity (greater or equal to max)
	tagver_t max; // maximal tag version
	char *memory;
	tagver_t *x2y;
	tagver_t *y2x;
	size_t *x2t;
	uint32_t *indegree;
	tcmd_t *backup_actions;

	explicit kernel_buffers_t(allocator_t &alc);
};

typedef lookup_t<const kernel_t*> kernels_t;

} // namespace re2c

#endif // _RE2C_DFA_FIND_STATE_
