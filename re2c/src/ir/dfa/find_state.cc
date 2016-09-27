#include <string.h>

#include "src/ir/dfa/find_state.h"
#include "src/util/hash32.h"

namespace re2c
{

static uint32_t hashclos(const closure_t &clos);
static bool eqclos(const closure_t *clos1, const closure_t *clos2);

uint32_t hashclos(const closure_t &clos)
{
	uint32_t h = static_cast<uint32_t>(clos.size()); // seed
	for (cclositer_t c = clos.begin(); c != clos.end(); ++c) {
		h = hash32(h, &c->state, sizeof(c->state));
		h = hash32(h, &c->tagidx, sizeof(c->tagidx));
	}
	return h;
}

bool eqclos(const closure_t *clos1, const closure_t *clos2)
{
	if (clos1->size() != clos2->size()) {
		return false;
	}
	for (cclositer_t c1 = clos1->begin(), c2 = clos2->begin();
		c1 != clos1->end(); ++c1, ++c2) {
		if (c1->state != c2->state
			|| c1->tagidx != c2->tagidx) {
			return false;
		}
	}
	return true;
}

clospool_t::clospool_t(): lookup() {}

clospool_t::~clospool_t()
{
	const size_t n = lookup.size();
	for (size_t i = 0; i < n; ++i) {
		delete lookup[i];
	}
}

size_t clospool_t::size() const
{
	return lookup.size();
}

const closure_t& clospool_t::operator[](size_t idx) const
{
	return *lookup[idx];
}

size_t clospool_t::insert(const closure_t &clos)
{
	const uint32_t hash = hashclos(clos);

	// try to find an identical DFA state
	size_t idx = lookup.find_with(hash, &clos, eqclos);
	if (idx != closlookup_t::NIL) {
		return idx;
	}

	// otherwise add a new state
	return lookup.push(hash, new closure_t(clos));
}

size_t find_state(closure_t &clos, clospool_t &clospool, Tagpool &tagpool)
{
	// empty closure corresponds to default state
	if (clos.empty()) {
		return dfa_t::NIL;
	}

	// dump tagsets to tagpool and address them by index:
	// this simpifies storing and comparing closures
	for (clositer_t c = clos.begin(); c != clos.end(); ++c) {
		bool *tags = c->tagptr;
		c->tagidx = tagpool.insert(tags);
		delete[] tags;
	}

	// sort closure to allow comparison by hash and 'memcmp'
	std::sort(clos.begin(), clos.end(), clos_t::compare);

	return clospool.insert(clos);
}

} // namespace re2c
