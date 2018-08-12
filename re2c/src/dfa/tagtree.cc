#include <assert.h>
#include <stdlib.h>

#include "src/dfa/closure.h"
#include "src/dfa/determinization.h"
#include "src/dfa/tagtree.h"

namespace re2c
{

static const tagver_t DELIM = TAGVER_CURSOR - 1;


tagtree_t::tagtree_t(): nodes(), path1(), path2() {}


hidx_t tagtree_t::pred(hidx_t i) const { return nodes[i].pred; }


tag_info_t tagtree_t::info(hidx_t i) const { return nodes[i].info; }


tagver_t tagtree_t::elem(hidx_t i) const { return nodes[i].info.neg ? TAGVER_BOTTOM : TAGVER_CURSOR; }


size_t tagtree_t::tag(hidx_t i) const { return nodes[i].info.idx; }


hidx_t tagtree_t::push(hidx_t idx, tag_info_t info)
{
	node_t x = {idx, info};
	nodes.push_back(x);
	return static_cast<hidx_t>(nodes.size() - 1);
}


tagver_t tagtree_t::last(hidx_t i, size_t t) const
{
	for (; i != HROOT; i = pred(i)) {
		if (tag(i) == t) return elem(i);
	}
	return TAGVER_ZERO;
}


int32_t tagtree_t::compare_reversed(hidx_t x, hidx_t y, size_t t) const
{
	// compare in reverse, from tail to head: direction makes
	// no difference when comparing for exact coincidence
	for (;;) {
		for (; x != HROOT && tag(x) != t; x = pred(x));
		for (; y != HROOT && tag(y) != t; y = pred(y));
		if (x == HROOT && y == HROOT) return 0;
		if (x == HROOT) return -1;
		if (y == HROOT) return 1;
		if (elem(x) > elem(y)) return -1;
		if (elem(x) < elem(y)) return 1;
		x = pred(x);
		y = pred(y);
	}
}


static void reconstruct_history(const tagtree_t &history,
	tag_path_t &path, hidx_t idx)
{
	path.clear();
	for (; idx != HROOT; idx = history.pred(idx)) {
		path.push_back(history.info(idx));
	}
}


static inline int32_t unpack_longest(int32_t value)
{
	// lower 30 bits
	return value & 0x3fffFFFF;
}


static inline int32_t unpack_leftmost(int32_t value)
{
	// higher 2 bits
	return value >> 30u;
}


int32_t precedence(determ_context_t &ctx,
	const clos_t &x, const clos_t &y, int32_t &rhox, int32_t &rhoy)
{
	const hidx_t xl = x.tlook, yl = y.tlook;
	const uint32_t xo = x.origin, yo = y.origin;

	if (xl == yl && xo == yo) {
		rhox = rhoy = -1;
		return 0;
	}

	tagtree_t &trie = ctx.dc_tagtrie;
	tag_path_t &p1 = trie.path1, &p2 = trie.path2;
	reconstruct_history(trie, p1, xl);
	reconstruct_history(trie, p2, yl);
	tag_path_t::const_reverse_iterator
		i1 = p1.rbegin(), e1 = p1.rend(), j1 = i1, g1,
		i2 = p2.rbegin(), e2 = p2.rend(), j2 = i2, g2;

	const std::vector<Tag> &tags = ctx.dc_dfa.tags;
	size_t nclos = 0;
	const prectable_t *prectbl = NULL;
	const bool fork_frame = xo == yo;

	if (fork_frame) {
		// find fork
		for (; j1 != e1 && j2 != e2 && *j1 == *j2; ++j1, ++j2);
	}
	else {
		// get precedence table and size of the origin state
		const kernel_t *k = ctx.dc_kernels[ctx.dc_origin];
		nclos = k->size;
		prectbl = k->prectbl;
	}

	// longest precedence
	if (!fork_frame) {
		rhox = unpack_longest(prectbl[xo * nclos + yo]);
		rhoy = unpack_longest(prectbl[yo * nclos + xo]);
	}
	else {
		rhox = rhoy = std::numeric_limits<int>::max();
		if (j1 > i1) rhox = rhoy = tags[(j1 - 1)->idx].height;
	}
	for (g1 = j1; g1 != e1; ++g1) {
		rhox = std::min(rhox, tags[g1->idx].height);
	}
	for (g2 = j2; g2 != e2; ++g2) {
		rhoy = std::min(rhoy, tags[g2->idx].height);
	}
	if (rhox > rhoy) return -1;
	if (rhox < rhoy) return 1;

	// leftmost precedence
	if (!fork_frame) {
		return unpack_leftmost(prectbl[xo * nclos + yo]);
	}
	else {
		// equal => not less
		if (j1 == e1 && j2 == e2) return 0;

		// shorter => less
		if (j1 == e1) return -1;
		if (j2 == e2) return 1;

		const uint32_t idx1 = j1->idx, idx2 = j2->idx;
		const bool neg1 = j1->neg, neg2 = j2->neg;

		// can't be both closing
		assert(!(idx1 % 2 == 1 && idx2 % 2 == 1));

		// closing vs opening: closing wins
		if (idx1 % 2 == 1) return -1;
		if (idx2 % 2 == 1) return 1;

		// can't be both negative
		assert(!(neg1 && neg2));

		// positive vs negative: positive wins
		if (neg1) return 1;
		if (neg2) return -1;

		// positive vs positive: smaller wins
		// (this case is only possible because multiple
		// top-level RE don't have proper negative tags)
		if (idx1 < idx2) return -1;
		if (idx1 > idx2) return 1;
	}

	// unreachable
	assert(false);
	return 0;
}

} // namespace re2c
