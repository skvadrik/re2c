#include <stddef.h>

#include "src/util/ord_hash_set.h"

namespace re2c
{

ord_hash_set_t::hash_t ord_hash_set_t::hash(const void *data, size_t size)
{
	const uint8_t *bytes = static_cast<const uint8_t*>(data);
	hash_t h = size; // seed
	for (size_t i = 0; i < size; ++i)
	{
		h = h ^ ((h << 5) + (h >> 2) + bytes[i]);
	}
	return h;
}

ord_hash_set_t::elem_t* ord_hash_set_t::make_elem(
	elem_t *next,
	size_t index,
	size_t size,
	const void *data)
{
	elem_t *e = static_cast<elem_t*>(malloc(offsetof(elem_t, data) + size));
	e->next = next;
	e->index = index;
	e->size = size;
	memcpy(e->data, data, size);
	return e;
}

ord_hash_set_t::ord_hash_set_t()
	: elems()
	, lookup()
{}

ord_hash_set_t::~ord_hash_set_t()
{
	std::for_each(elems.begin(), elems.end(), free);
}

size_t ord_hash_set_t::size() const
{
	return elems.size();
}

size_t ord_hash_set_t::insert(const void *data, size_t size)
{
	const hash_t h = hash(data, size);

	std::map<hash_t, elem_t*>::const_iterator i = lookup.find(h);
	if (i != lookup.end())
	{
		for (elem_t *e = i->second; e; e = e->next)
		{
			if (e->size == size
				&& memcmp(e->data, data, size) == 0)
			{
				return e->index;
			}
		}
	}

	const size_t index = elems.size();
	elems.push_back(lookup[h] = make_elem(lookup[h], index, size, data));
	return index;
}

} // namespace re2c
