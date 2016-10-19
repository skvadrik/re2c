#include <assert.h>
#include <limits>
#include <stdlib.h> // malloc
#include <string.h> // memcpy, memcmp

#include "src/ir/rule.h"
#include "src/ir/tag.h"
#include "src/util/hash32.h"

namespace re2c
{

struct eqtag_t
{
	size_t ntags;

	explicit eqtag_t(size_t n): ntags(n) {}
	inline bool operator()(const bool *x, const bool *y)
	{
		return memcmp(x, y, ntags * sizeof(bool)) == 0;
	}
};

const size_t Tag::NONE = std::numeric_limits<size_t>::max();

Tag::Tag()
	: type(VAR)
	, rule(Rule::NONE)
	, name(NULL)
{}

void init_var_tag(Tag &tag, size_t r, const std::string *n, size_t o)
{
	tag.type = Tag::VAR;
	tag.rule = r;
	tag.name = n;
	tag.var.orig = o;
}

void init_fix_tag(Tag &tag, size_t r, const std::string *n, size_t b, size_t d)
{
	tag.type = Tag::FIX;
	tag.rule = r;
	tag.name = n;
	tag.fix.base = b;
	tag.fix.dist = d;
}

Tagpool::Tagpool(size_t n)
	: lookup()
	, buffer(new bool[n * 3])
	, ntags(n)
	, buffer1(&buffer[n * 1])
	, buffer2(&buffer[n * 2])
{
	// all-zero tag configuration must have static number zero
	std::fill(buffer, buffer + ntags, false);
	assert(ZERO_TAGS == insert(buffer));
}

Tagpool::~Tagpool()
{
	delete[] buffer;
	const size_t n = lookup.size();
	for (size_t i = 0; i < n; ++i) {
		free(const_cast<bool*>(lookup[i]));
	}
}

size_t Tagpool::insert(const bool *tags)
{
	const size_t size = ntags * sizeof(bool);
	const uint32_t hash = hash32(0, tags, size);

	eqtag_t eq(ntags);
	const size_t idx = lookup.find_with(hash, tags, eq);
	if (idx != taglookup_t::NIL) {
		return idx;
	}

	bool *copy = static_cast<bool*>(malloc(size));
	memcpy(copy, tags, size);
	return lookup.push(hash, copy);
}

const bool *Tagpool::operator[](size_t idx) const
{
	return lookup[idx];
}

} // namespace re2c
