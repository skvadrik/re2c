#include <assert.h>
#include <string.h>

#include "src/dfa/tagtree.h"

namespace re2c
{

tagtree_t::tagtree_t(): nodes(), tail(HROOT), path1(), path2() {}

tagver_t tagtree_t::elem(hidx_t i) const { return nodes[i].elem; }

hidx_t tagtree_t::pred(hidx_t i) const { return nodes[i].pred; }

size_t tagtree_t::tag(hidx_t i) const { return nodes[i].tag; }

void tagtree_t::push(size_t t, tagver_t v)
{
	node_t x = {tail, v, t};
	nodes.push_back(x);
	tail = static_cast<hidx_t>(nodes.size() - 1);
}

void tagtree_t::pop()
{
	// don't destroy the leaf itself, just update pointer to current leaf
	// (pointer to the the old leaf is stored in one of the closure items)
	tail = pred(tail);
}

// cut out subhistory of this tag (just skip all other tags)
static void subhistory(const tagtree_t &history,
	std::vector<tagver_t> &path, hidx_t idx, size_t tag)
{
	path.clear();
	for (hidx_t i = idx; i != HROOT; i = history.pred(i)) {
		if (history.tag(i) == tag) {
			path.push_back(history.elem(i));
		}
	}
}

// cut out a list of subhistories of this tag separated by tags
// with higher priority (in POSIX they correspond to outer captures)
static void subhistories(const tagtree_t &history,
	std::vector<tagver_t> &path, hidx_t idx, size_t tag)
{
	// 0 -- bottom, 1 -- cursor, 2 -- subhistory delimiter, so that
	// short history which is a prefix of a longer history dominates
	path.clear();
	for (hidx_t i = idx;;) {

		// subhistory begins at the next occurence of this tag
		for (; i != HROOT && history.tag(i) != tag; i = history.pred(i));
		if (i == HROOT) break;
		path.push_back(2);

		// subhistory ends at the next occurence of tag with
		// higher priority or when the whole history ends
		for (; i != HROOT && history.tag(i) >= tag; i = history.pred(i)) {
			// skip tags with lower priority
			if (history.tag(i) > tag) continue;
			path.push_back(history.elem(i) == TAGVER_CURSOR ? 1 : 0);
		}
	}
}

static int32_t compare_reversed(
	const std::vector<tagver_t> &h1,
	const std::vector<tagver_t> &h2)
{
	std::vector<tagver_t>::const_reverse_iterator
		i1 = h1.rbegin(), e1 = h1.rend(),
		i2 = h2.rbegin(), e2 = h2.rend();

	for (;;) {
		if (i1 == e1 && i2 == e2) break;
		if (i1 == e1) return -1;
		if (i2 == e2) return 1;
		if (*i1 > *i2) return -1;
		if (*i1 < *i2) return 1;
		++i1; ++i2;
	}

	return 0;
}

int32_t tagtree_t::compare_actions(hidx_t x, hidx_t y, size_t t)
{
	subhistory(*this, path1, x, t);
	subhistory(*this, path2, y, t);
	return compare_reversed(path1, path2);
}

int32_t tagtree_t::compare_orbits(hidx_t x, hidx_t y, size_t t)
{
	subhistories(*this, path1, x, t);
	subhistories(*this, path2, y, t);
	return compare_reversed(path1, path2);
}

tagver_t tagtree_t::last(hidx_t i, size_t t) const
{
	for (; i != HROOT; i = pred(i)) {
		if (tag(i) == t) return elem(i);
	}
	return TAGVER_ZERO;
}

} // namespace re2c
