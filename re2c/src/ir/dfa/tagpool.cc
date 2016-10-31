#include <assert.h>
#include <stdlib.h> // malloc
#include <string.h> // memcpy, memcmp

#include "src/ir/dfa/tagpool.h"
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

Tagpool::Tagpool(size_t n)
	: lookup()
	, buffer(new tagver_t[n * 3])
	, ntags(n)
	, buffer1(&buffer[n * 1])
	, buffer2(&buffer[n * 2])
{
	// all-zero tag configuration must have static number zero
	std::fill(buffer, buffer + ntags, TAGVER_ZERO);
	assert(ZERO_TAGS == insert(buffer));
}

Tagpool::~Tagpool()
{
	delete[] buffer;
	const size_t n = lookup.size();
	for (size_t i = 0; i < n; ++i) {
		free(const_cast<tagver_t*>(lookup[i]));
	}
}

size_t Tagpool::insert(const tagver_t *tags)
{
	const size_t size = ntags * sizeof(tagver_t);
	const uint32_t hash = hash32(0, tags, size);

	const size_t idx = lookup.find_with(hash, tags, eqtag_t(ntags));
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
