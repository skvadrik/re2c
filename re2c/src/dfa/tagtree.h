#ifndef _RE2C_DFA_TAGTREE_
#define _RE2C_DFA_TAGTREE_

#include <vector>

#include "src/re/tag.h"
#include "src/util/forbid_copy.h"

namespace re2c
{

typedef uint32_t hidx_t;

static const hidx_t HROOT = ~0u;

struct tagtree_t
{
	// the whole tree of tags found by the epsilon-closure
	// (a bunch of separate subtrees for each tag with common root)
	struct node_t {
		hidx_t pred;
		tagver_t elem;
		size_t tag;
	};
	std::vector<node_t> nodes;
	hidx_t tail;

	// reconstruct paths for comparison
	std::vector<tagver_t> path1;
	std::vector<tagver_t> path2;

	tagtree_t();
	hidx_t pred(hidx_t i) const;
	tagver_t elem(hidx_t i) const;
	size_t tag(hidx_t i) const;
	void push(size_t t, tagver_t v);
	void pop();
	int32_t compare_actions(hidx_t x, hidx_t y, size_t t);
	int32_t compare_orbits(hidx_t x, hidx_t y, size_t t);
	tagver_t last(hidx_t i, size_t t) const;
	FORBID_COPY(tagtree_t);
};

} // namespace re2c

#endif // _RE2C_DFA_TAGTREE_
