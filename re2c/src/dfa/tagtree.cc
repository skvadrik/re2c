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
static void full_subhistory(const tagtree_t &history,
	std::vector<tagver_t> &path, hidx_t idx, size_t tag)
{
	path.clear();
	for (hidx_t i = idx; i != HROOT; i = history.pred(i)) {
		if (history.tag(i) == tag) {
			path.push_back(history.elem(i));
		}
	}
}

// the last subhistory of this tag: it begins at the first occurence
// and ends at the next occurence of tag with higher priority (in POSIX
// they correspond to outer captures) or when the whole history ends
static void last_subhistory(const tagtree_t &history,
	std::vector<tagver_t> &path, hidx_t idx, size_t tag)
{
	path.clear();
	hidx_t i = idx;
	for (; i != HROOT && history.tag(i) != tag; i = history.pred(i));
	for (; i != HROOT && history.tag(i) >= tag; i = history.pred(i)) {
		if (history.tag(i) == tag) {
			path.push_back(history.elem(i));
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

int32_t tagtree_t::compare_full(hidx_t x, hidx_t y, size_t t)
{
	full_subhistory(*this, path1, x, t);
	full_subhistory(*this, path2, y, t);
	return compare_reversed(path1, path2);
}

int32_t tagtree_t::compare_last(hidx_t x, hidx_t y, size_t t)
{
	last_subhistory(*this, path1, x, t);
	last_subhistory(*this, path2, y, t);
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
