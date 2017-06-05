#include <assert.h>
#include <string.h>

#include "src/dfa/tagtree.h"

namespace re2c
{

tagtree_t::tagtree_t(): nodes(), path1(), path2() {}

tagver_t tagtree_t::elem(hidx_t i) const { return nodes[i].elem; }

hidx_t tagtree_t::pred(hidx_t i) const { return nodes[i].pred; }

size_t tagtree_t::tag(hidx_t i) const { return nodes[i].tag; }

hidx_t tagtree_t::push(hidx_t i, size_t t, tagver_t v)
{
	node_t x = {i, v, t};
	nodes.push_back(x);
	return static_cast<hidx_t>(nodes.size() - 1);
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

// cut out a list of subhistories of this tag separated by occurences
// of higher-priority tags (separator has the highest value: 2, elements
// have lower values: 1 for cursor and 0 for bottom --- this way comparison
// will stop at separator and shorter subhistory will dominate).
static void subhistory_list(const tagtree_t &history,
	std::vector<tagver_t> &path, hidx_t idx, size_t tag)
{
	path.clear();
	hidx_t i = idx;
	for (;;) {
		for (; i != HROOT && history.tag(i) != tag; i = history.pred(i));
		if (i == HROOT) break;
		path.push_back(2);
		for (; i != HROOT && history.tag(i) >= tag; i = history.pred(i)) {
			if (history.tag(i) == tag) {
				path.push_back(history.elem(i) == TAGVER_CURSOR ? 1 : 0);
			}
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

int32_t tagtree_t::compare_plain(hidx_t x, hidx_t y, size_t t)
{
	subhistory(*this, path1, x, t);
	subhistory(*this, path2, y, t);
	return compare_reversed(path1, path2);
}

int32_t tagtree_t::compare_orbit(hidx_t x, hidx_t y, size_t t)
{
	subhistory_list(*this, path1, x, t);
	subhistory_list(*this, path2, y, t);
	return compare_reversed(path1, path2);
}

int32_t tagtree_t::compare_max(hidx_t x, hidx_t y, size_t t)
{
	// compare starting from tail: at the first mismatch maximal value
	// wins; if one subhistory is shorter, it's last value is assumed
	// to be zero, so that comparison depends on the next value of the
	// longer subgistory
	for (;;) {
		for (; x != HROOT && tag(x) != t; x = pred(x));
		for (; y != HROOT && tag(y) != t; y = pred(y));
		if (x == HROOT && y == HROOT) return 0;
		if (x == HROOT) return (elem(y) == TAGVER_BOTTOM ? -1 : 1);
		if (y == HROOT) return (elem(x) == TAGVER_BOTTOM ? 1 : -1);
		if (elem(x) > elem(y)) return -1;
		if (elem(x) < elem(y)) return 1;
		x = pred(x); y = pred(y);
	}
}

tagver_t tagtree_t::last(hidx_t i, size_t t) const
{
	for (; i != HROOT; i = pred(i)) {
		if (tag(i) == t) return elem(i);
	}
	return TAGVER_ZERO;
}

} // namespace re2c
