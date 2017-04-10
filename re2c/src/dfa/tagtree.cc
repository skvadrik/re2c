#include <assert.h>
#include <string.h>

#include "src/dfa/tagtree.h"

namespace re2c
{

tagtree_t::tagtree_t(size_t n)
	: nodes()
	, path1()
	, path2()
	, ntag(n)
	, tags(new tagver_t[ntag])
{
	node_t x = {-1, TAGVER_ZERO};
	nodes.push_back(x);
	init();
}

tagtree_t::~tagtree_t()
{
	delete[] tags;
}

void tagtree_t::init()
{
	memset(tags, 0, ntag * sizeof(tagver_t));
}

tagver_t tagtree_t::elem(tagver_t i) const
{
	return nodes[static_cast<size_t>(i)].elem;
}

tagver_t tagtree_t::pred(tagver_t i) const
{
	return nodes[static_cast<size_t>(i)].pred;
}

const tagver_t *tagtree_t::leaves() const
{
	return tags;
}

void tagtree_t::push(size_t t, tagver_t v)
{
	node_t x = {tags[t], v};
	nodes.push_back(x);
	tags[t] = static_cast<tagver_t>(nodes.size() - 1);
}

void tagtree_t::pop(size_t t)
{
	// don't destroy the leaf itself, just update pointer to current leaf
	// (pointer to the the old leaf is stored in one of the closure items)
	tags[t] = pred(tags[t]);
}

int32_t tagtree_t::compare_paths(tagver_t x, tagver_t y)
{
	path1.clear();
	for (; x != -1; x = pred(x)) path1.push_back(elem(x));

	path2.clear();
	for (; y != -1; y = pred(y)) path2.push_back(elem(y));

	std::vector<tagver_t>::const_reverse_iterator
		i1 = path1.rbegin(), e1 = path1.rend(),
		i2 = path2.rbegin(), e2 = path2.rend();

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

} // namespace re2c
