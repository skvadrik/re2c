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
	inline tagver_t operator()(const tagver_t *x, const tagver_t *y)
	{
		return memcmp(x, y, ntags * sizeof(tagver_t)) == 0;
	}
};

const size_t Tag::NONE = std::numeric_limits<size_t>::max();

Tag::Tag()
	: type(VAR)
	, rule(Rule::NONE)
	, name(NULL)
	, fix()
{}

void init_var_tag(Tag &tag, size_t r, const std::string *n)
{
	tag.type = Tag::VAR;
	tag.rule = r;
	tag.name = n;
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

free_list<tagsave_t*> tagsave_t::freelist;

tagsave_t::tagsave_t(tagsave_t *n, tagver_t v)
	: next(n)
	, ver(v)
{
	freelist.insert(this);
}

tagsave_t::~tagsave_t()
{
	freelist.erase(this);
}

tagsave_t *tagsave_t::convert(const tagver_t *vers, size_t ntag)
{
	tagsave_t *s = NULL;
	for (size_t t = ntag; t-- > 0;) {
		const tagver_t v = vers[t];
		if (v != TAGVER_ZERO) {
			s = new tagsave_t(s, v);
		}
	}
	return s;
}

free_list<tagcopy_t*> tagcopy_t::freelist;

tagcopy_t::tagcopy_t(tagcopy_t *n, tagver_t l, tagver_t r)
	: next(n)
	, lhs(l)
	, rhs(r)
{
	freelist.insert(this);
}

tagcopy_t::~tagcopy_t()
{
	freelist.erase(this);
}

} // namespace re2c
