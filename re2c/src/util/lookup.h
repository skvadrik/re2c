#ifndef _RE2C_UTIL_LOOKUP_
#define _RE2C_UTIL_LOOKUP_

#include "src/util/c99_stdint.h"
#include <limits>
#include <map>
#include <vector>
#include <stddef.h>

namespace re2c
{

/*
 * O(1) random access
 * O(log(n)) insertion
 */
template<typename data_t, typename hash_t = uint32_t>
struct lookup_t
{
	static const size_t NIL;

private:
	struct elem_t
	{
		size_t next;
		data_t data;

		elem_t(size_t n, const data_t &d)
			: next(n), data(d) {}
	};

	std::vector<elem_t> elems;
	std::map<hash_t, size_t> lookup;

public:
	lookup_t();
	size_t size() const;
	data_t& operator[](size_t idx);
	const data_t& operator[](size_t idx) const;
	size_t push(hash_t hash, const data_t &data);
	template<typename pred_t> size_t find_with(hash_t hash, const data_t &data, pred_t &pred) const;
	template<typename pred_t> size_t find_next_with(size_t prev, const data_t &data, pred_t &pred) const;

private:
	size_t head(hash_t) const;
	template<typename pred_t> size_t find(size_t next, const data_t &data, pred_t &pred) const;
};

template<typename data_t, typename hash_t>
const size_t lookup_t<data_t, hash_t>::NIL = std::numeric_limits<size_t>::max();

template<typename data_t, typename hash_t>
lookup_t<data_t, hash_t>::lookup_t()
	: elems()
	, lookup()
{}

template<typename data_t, typename hash_t>
size_t lookup_t<data_t, hash_t>::size() const
{
	return elems.size();
}

template<typename data_t, typename hash_t>
data_t& lookup_t<data_t, hash_t>::operator[](size_t idx)
{
	return elems[idx].data;
}

template<typename data_t, typename hash_t>
const data_t& lookup_t<data_t, hash_t>::operator[](size_t idx) const
{
	return elems[idx].data;
}

template<typename data_t, typename hash_t>
size_t lookup_t<data_t, hash_t>::head(hash_t h) const
{
	typename std::map<hash_t, size_t>::const_iterator x = lookup.find(h);
	return x == lookup.end() ? NIL : x->second;
}

template<typename data_t, typename hash_t>
size_t lookup_t<data_t, hash_t>::push(hash_t hash, const data_t &data)
{
	const size_t idx = elems.size();
	elems.push_back(elem_t(head(hash), data));
	lookup[hash] = idx;
	return idx;
}

template<typename data_t, typename hash_t>
template<typename pred_t>
size_t lookup_t<data_t, hash_t>::find(size_t next, const data_t &data, pred_t &pred) const
{
	for (size_t i = next; i != NIL;) {
		const elem_t &e = elems[i];
		if (pred(e.data, data)) {
			return i;
		}
		i = e.next;
	}
	return NIL;
}

template<typename data_t, typename hash_t>
template<typename pred_t>
size_t lookup_t<data_t, hash_t>::find_with(hash_t hash, const data_t &data, pred_t &pred) const
{
	return find(head(hash), data, pred);
}

template<typename data_t, typename hash_t>
template<typename pred_t>
size_t lookup_t<data_t, hash_t>::find_next_with(size_t prev, const data_t &data, pred_t &pred) const
{
	return find(elems[prev].next, data, pred);
}

} // namespace re2c

#endif // _RE2C_UTIL_LOOKUP_
