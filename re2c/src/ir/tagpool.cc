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

void Tagpool::orl(size_t *pt, size_t o)
{
	const size_t t = *pt;
	if (t == o || o == 0) {
		return;
	} else if (t == 0) {
		*pt = o;
		return;
	}

	const bool *tags = operator[](t);
	const bool *ortags = operator[](o);
	for (size_t i = 0; i < ntags; ++i) {
		buff[i] = tags[i] | ortags[i];
	}
	*pt = insert(buff);
}

void Tagpool::orl_with_mask(size_t *pt, size_t o, size_t m)
{
	const size_t t = *pt;
	if (t == o || o == 0) {
		return;
	}

	const bool *tags = operator[](t);
	const bool *ortags = operator[](o);
	const bool *masktags = operator[](m);
	for (size_t i = 0; i < ntags; ++i) {
		buff[i] = tags[i] | (ortags[i] & ~masktags[i]);
	}
	*pt = insert(buff);
}

void Tagpool::andl(size_t *pt, size_t a)
{
	const size_t t = *pt;
	if (t == a) {
		return;
	} else if (t == 0 || a == 0) {
		*pt = 0;
		return;
	}

	const bool *tags = operator[](t);
	const bool *andtags = operator[](a);
	for (size_t i = 0; i < ntags; ++i) {
		buff[i] = tags[i] & andtags[i];
	}
	*pt = insert(buff);
}

void Tagpool::subst(size_t *pt, const std::vector<size_t> &represent)
{
	const bool *tags = operator[](*pt);
	memset(buff, 0, ntags * sizeof(bool));
	for (size_t i = 0; i < ntags; ++i) {
		if (tags[i]) {
			buff[represent[i]] = true;
		}
	}
	*pt = insert(buff);
}

const bool *Tagpool::operator[](size_t idx)
{
	const bool *tags;
	pool.deref<const bool>(idx, tags);
	return tags;
}

} // namespace re2c
