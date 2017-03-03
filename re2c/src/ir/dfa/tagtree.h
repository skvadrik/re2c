#ifndef _RE2C_IR_DFA_TAGTREE_
#define _RE2C_IR_DFA_TAGTREE_

#include <vector>

#include "src/ir/tag.h"
#include "src/util/forbid_copy.h"

namespace re2c
{

class tagtree_t
{
	// the whole tree of tags found by the epsilon-closure
	// (a bunch of separate subtrees for each tag with common root)
	struct node_t {
		tagver_t pred;
		tagver_t elem;
	};
	std::vector<node_t> nodes;

	// set of leaves (one leaf per tag) corresponding to
	// current deep-first search path in the epsilon-closure
	size_t ntag;
	tagver_t *tags;

public:
	explicit tagtree_t(size_t n);
	~tagtree_t();
	void init();
	tagver_t pred(tagver_t i) const;
	tagver_t elem(tagver_t i) const;
	const tagver_t *leaves() const;
	void push(size_t t, tagver_t v);
	void pop(size_t t);
	FORBID_COPY(tagtree_t);
};

} // namespace re2c

#endif // _RE2C_IR_DFA_TAGTREE_
