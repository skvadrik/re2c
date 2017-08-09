#include <assert.h>
#include <stdlib.h>

#include "src/dfa/tagtree.h"

namespace re2c
{

static const tagver_t DELIM = TAGVER_CURSOR - 1;

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

static size_t boundary_tag(size_t tag)
{
	// for start tags, return itself; for end tags, return start tag
	// (start tags have even numbers, end tags have odd numbers)
	return tag & ~1u;
}

// returns all subhistories of the given tag as one list (individual
// subhistories are separated by delimiter)
static int32_t subhistory_list(const tagtree_t &history,
	std::vector<tagver_t> &path, hidx_t idx, size_t tag)
{
	path.clear();
	int32_t nsub = 0;
	hidx_t i = idx;

	const size_t bound = boundary_tag(tag);
	path.push_back(DELIM);
	for (;;) {
		for (; i != HROOT && history.tag(i) >= bound; i = history.pred(i)) {
			if (history.tag(i) == tag) {
				path.push_back(history.elem(i));
			}
		}
		if (i == HROOT) break;
		++nsub;
		path.push_back(DELIM);
		for (; i != HROOT && history.tag(i) != tag; i = history.pred(i));
	}

	return nsub;
}

// Lookahead may consist of multiple subhistories (each containing either
// a single bottom value, or one or more cursor values (exactly one for
// non-orbit subhistories). Because of the shortest-path algorithm earlier
// subhistories do not necessarily coincide, so comparing only the last
// pair of subhistories is not enough. See note [POSIX orbit tags].
int32_t tagtree_t::compare_histories(hidx_t x, hidx_t y,
	tagver_t ox, tagver_t oy, size_t t)
{
	const int32_t
		n1 = subhistory_list(*this, path1, x, t),
		n2 = subhistory_list(*this, path2, y, t);

	assert(n1 == n2);
	path1.push_back(ox);
	path2.push_back(oy);

	std::vector<tagver_t>::const_reverse_iterator
		i1 = path1.rbegin(), e1 = path1.rend(),
		i2 = path2.rbegin(), e2 = path2.rend();
	for (;;) {
		if (i1 == e1 && i2 == e2) return 0;
		assert(i1 != e1 && i2 != e2);
		const tagver_t v1 = *i1++, v2 = *i2++;
		if (v1 == DELIM && v2 == DELIM) continue;
		if (v1 == DELIM) return -1;
		if (v2 == DELIM) return 1;
		if (v1 > v2) return -1;
		if (v1 < v2) return 1;
	}
}

static void last_subhistory(const tagtree_t &history, std::vector<tagver_t> &path,
	hidx_t idx, tagver_t order, size_t tag)
{
	path.clear();
	hidx_t i = idx;
	const size_t bound = boundary_tag(tag);
	for (; i != HROOT && history.tag(i) >= bound; i = history.pred(i)) {
		if (history.tag(i) == tag) {
			path.push_back(history.elem(i));
		}
	}
	if (i == HROOT) path.push_back(order);
}

int32_t tagtree_t::compare_last_subhistories(hidx_t x, hidx_t y,
	tagver_t ox, tagver_t oy, size_t t)
{
	last_subhistory(*this, path1, x, ox, t);
	last_subhistory(*this, path2, y, oy, t);
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
