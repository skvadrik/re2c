#include <string.h>

#include "src/ir/dfa/find_state.h"

namespace re2c
{

size_t find_state(kitem_t *kernel, kitem_t *kend,
	ord_hash_set_t &kernels, Tagpool &tagpool)
{
	const size_t kcount = static_cast<size_t>(kend - kernel);

	// zero-sized kernel corresponds to default state
	if (kcount == 0) {
		return dfa_t::NIL;
	}

	// dump tagsets to tagpool and address them by index:
	// this simpifies storing and comparing kernels
	for (kitem_t *k = kernel; k != kend; ++k) {
		bool *tags = k->tagptr;
		k->tagidx = tagpool.insert(tags);
		delete[] tags;
	}

	// sort kernel items to allow comparison by hash and 'memcmp'
	std::sort(kernel, kend, kitem_t::compare);

	return kernels.insert(kernel, kcount * sizeof(kitem_t));
}

} // namespace re2c
