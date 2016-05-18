#include "src/ir/tagpool.h"
#include "src/util/forbid_copy.h"

namespace re2c
{

Tagpool::Tagpool(size_t n)
	: ntags(n)
	, pool()
	, buff(new bool[ntags]())
{
	// all-no tag set must have number 0
	insert(buff);
}

Tagpool::~Tagpool()
{
	delete[] buff;
}

size_t Tagpool::insert(const bool *tags)
{
	return pool.insert(tags, ntags * sizeof(bool));
}

size_t Tagpool::orl(size_t t, size_t o)
{
	if (t == o || o == 0) {
		return t;
	} else if (t == 0) {
		return o;
	}

	const bool *tags = operator[](t);
	const bool *ortags = operator[](o);
	for (size_t i = 0; i < ntags; ++i) {
		buff[i] = tags[i] | ortags[i];
	}
	return insert(buff);
}

size_t Tagpool::andl(size_t t, size_t a)
{
	if (t == a) {
		return t;
	} else if (t == 0 || a == 0) {
		return 0;
	}

	const bool *tags = operator[](t);
	const bool *andtags = operator[](a);
	for (size_t i = 0; i < ntags; ++i) {
		buff[i] = tags[i] & andtags[i];
	}
	return insert(buff);
}

size_t Tagpool::andlinv(size_t t, size_t a)
{
	if (a == 0) {
		return t;
	} else if (t == 0 || t == a) {
		return 0;
	}

	const bool *tags = operator[](t);
	const bool *andinvtags = operator[](a);
	for (size_t i = 0; i < ntags; ++i) {
		buff[i] = tags[i] & ~andinvtags[i];
	}
	return insert(buff);
}

size_t Tagpool::subst(size_t t, const size_t *represent)
{
	const bool *tags = operator[](t);
	memset(buff, 0, ntags * sizeof(bool));
	for (size_t i = 0; i < ntags; ++i) {
		if (tags[i]) {
			buff[represent[i]] = true;
		}
	}
	return insert(buff);
}

const bool *Tagpool::operator[](size_t idx)
{
	const bool *tags;
	pool.deref<const bool>(idx, tags);
	return tags;
}

} // namespace re2c
