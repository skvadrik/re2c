#ifndef _RE2C_UTIL_ORD_HASH_SET_
#define _RE2C_UTIL_ORD_HASH_SET_

#include "src/util/c99_stdint.h"
#include <stdlib.h> // malloc, free
#include <string.h> // memcpy
#include <algorithm> // for_each
#include <map>
#include <vector>

namespace re2c
{

/*
 * ordered hash set:
 *   - access element by index: O(1)
 *   - insert element (find existing or add new): O(log(n))
 *
 */
class ord_hash_set_t
{
	struct elem_t
	{
		elem_t *next;
		size_t index;
		size_t size;
		char data[1]; // inlined array of variable length
	};
	typedef size_t hash_t;

	std::vector<elem_t*> elems;
	std::map<hash_t, elem_t*> lookup;

	static hash_t hash(const void *data, size_t size);
	elem_t *make_elem(elem_t *next, size_t index, size_t size, const void *data);

public:
	ord_hash_set_t();
	~ord_hash_set_t();
	size_t size() const;
	size_t insert(const void *data, size_t size);
	template<typename data_t> size_t deref(size_t i, data_t *&data);
};

template<typename data_t> size_t ord_hash_set_t::deref(size_t i, data_t *&data)
{
	elem_t *e = elems[i];
	data = reinterpret_cast<data_t*>(e->data);
	return e->size / sizeof(data_t);
}

} // namespace re2c

#endif // _RE2C_UTIL_ORD_HASH_SET_
