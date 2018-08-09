#include "src/util/c99_stdint.h"
#include <stdlib.h> // malloc
#include <string.h> // memcpy, memcmp
#include <algorithm>

#include "src/dfa/tagpool.h"
#include "src/util/hash32.h"

namespace re2c
{

struct eqtag_t
{
	size_t ntags;

	explicit eqtag_t(size_t n): ntags(n) {}
	inline tagver_t operator()(const tagver_t *x, const tagver_t *y) const
	{
		return memcmp(x, y, ntags * sizeof(tagver_t)) == 0;
	}
};

Tagpool::Tagpool(const opt_t *o, size_t n)
	: lookup()
	, opts(o)
	, ntags(n)
	, buffer(new tagver_t[n])
	, alc()
	, history()
	, astack()
	, bstack()
	, cstack()
{}

Tagpool::~Tagpool()
{
	delete[] buffer;
	const size_t n = lookup.size();
	for (size_t i = 0; i < n; ++i) {
		free(const_cast<tagver_t*>(lookup[i]));
	}
}

size_t Tagpool::insert_const(tagver_t ver)
{
	std::fill(buffer, buffer + ntags, ver);
	return insert(buffer);
}

size_t Tagpool::insert_succ(tagver_t fst)
{
	for (size_t i = 0; i < ntags; ++i) {
		buffer[i] = fst++;
	}
	return insert(buffer);
}

size_t Tagpool::insert(const tagver_t *tags)
{
	const size_t size = ntags * sizeof(tagver_t);
	const uint32_t hash = hash32(0, tags, size);

	eqtag_t eq(ntags);
	const size_t idx = lookup.find_with(hash, tags, eq);
	if (idx != taglookup_t::NIL) {
		return idx;
	}

	tagver_t *copy = static_cast<tagver_t*>(malloc(size));
	memcpy(copy, tags, size);
	return lookup.push(hash, copy);
}

const tagver_t *Tagpool::operator[](size_t idx) const
{
	return lookup[idx];
}

} // namespace re2c
