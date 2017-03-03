#include <assert.h>
#include <string.h>

#include "src/ir/dfa/tagtree.h"

namespace re2c
{

tagtree_t::tagtree_t(size_t n)
	: nodes()
	, ntag(n)
	, tags(new tagver_t[ntag])
{
	init();
}

tagtree_t::~tagtree_t()
{
	delete[] tags;
}

void tagtree_t::init()
{
	nodes.clear();
	node_t x = {-1, TAGVER_ZERO};
	nodes.push_back(x);
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

} // namespace re2c
