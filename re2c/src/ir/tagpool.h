#ifndef _RE2C_IR_TAGPOOL_
#define _RE2C_IR_TAGPOOL_

#include "src/util/ord_hash_set.h"

namespace re2c
{

struct Tagpool
{
	const size_t ntags;

private:
	ord_hash_set_t pool;

public:
	explicit inline Tagpool(size_t n);
	inline size_t insert(const bool *tags);
	inline const bool *operator[](size_t idx);
};

Tagpool::Tagpool(size_t n)
	: ntags(n)
	, pool()
{
	const bool *zerotags = new bool[ntags]();
	insert(zerotags);
	delete[] zerotags;
}

size_t Tagpool::insert(const bool *tags)
{
	return pool.insert(tags, ntags * sizeof(bool));
}

const bool *Tagpool::operator[](size_t idx)
{
	const bool *tags;
	pool.deref<const bool>(idx, tags);
	return tags;
}

inline void add_tags(bool *oldtags, const bool *newtags, size_t ntags)
{
	for (size_t i = 0; i < ntags; ++i) {
		oldtags[i] |= newtags[i];
	}
}

inline void add_tags_with_mask(bool *oldtags, const bool *newtags,
	const bool *mask, size_t ntags)
{
	for (size_t i = 0; i < ntags; ++i) {
		oldtags[i] |= newtags[i] & ~mask[i];
	}
}

inline bool addcmp_tags_with_mask(bool *oldtags, const bool *newtags,
	const bool *mask, size_t ntags)
{
	bool diff = false;
	for (size_t i = 0; i < ntags; ++i) {
		const bool old = oldtags[i];
		oldtags[i] |= newtags[i] & ~mask[i];
		diff |= old != oldtags[i];
	}
	return diff;
}

} // namespace re2c

#endif // _RE2C_IR_TAGPOOL_
