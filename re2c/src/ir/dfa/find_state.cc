#include <string.h>

#include "src/ir/dfa/find_state.h"
#include "src/util/hash32.h"

namespace re2c
{

kernel_t::kernel_t(size_t n)
	: size(n)
	, state(new nfa_state_t*[size])
	, tlook(new size_t[size])
{}

kernel_t *kernel_t::copy(const kernel_t &k)
{
	const size_t n = k.size;
	kernel_t *kcopy = new kernel_t(n);
	memcpy(kcopy->state, k.state, n * sizeof(void*));
	memcpy(kcopy->tlook, k.tlook, n * sizeof(size_t));
	return kcopy;
}

kernel_t::~kernel_t()
{
	delete[] state;
	delete[] tlook;
}

struct kernel_eq_t
{
	bool operator()(const kernel_t *x, const kernel_t *y) const
	{
		return x->size == y->size
			&& memcmp(x->state, y->state, x->size * sizeof(void*)) == 0
			&& memcmp(x->tlook, y->tlook, x->size * sizeof(size_t)) == 0;
	}
};

kernels_t::kernels_t()
	: lookup()
	, maxsize(256) // usually ranges from one to some twenty
	, buffer(new kernel_t(maxsize))
{}

kernels_t::~kernels_t()
{
	delete buffer;

	const size_t n = lookup.size();
	for (size_t i = 0; i < n; ++i) {
		delete lookup[i];
	}
}

size_t kernels_t::size() const
{
	return lookup.size();
}

const kernel_t *kernels_t::operator[](size_t idx) const
{
	return lookup[idx];
}

size_t kernels_t::insert(const closure_t &clos)
{
	const size_t nkern = clos.size();

	// empty closure corresponds to default state
	if (nkern == 0) return dfa_t::NIL;

	// resize buffer if closure is too large
	if (maxsize < nkern) {
		maxsize = nkern * 2; // in advance
		delete buffer;
		buffer = new kernel_t(maxsize);
	}

	// copy closure to buffer kernel
	buffer->size = nkern;
	for (size_t i = 0; i < nkern; ++i) {
		const clos_t &c = clos[i];
		buffer->state[i] = c.state;
		buffer->tlook[i] = c.tagidx;
	}

	// get kernel hash
	uint32_t hash = static_cast<uint32_t>(nkern); // seed
	hash = hash32(hash, buffer->state, nkern * sizeof(void*));
	hash = hash32(hash, buffer->tlook, nkern * sizeof(size_t));

	// try to find identical kernel
	size_t idx = lookup.find_with(hash, buffer, kernel_eq_t());
	if (idx != index_t::NIL) return idx;

	// otherwise add new kernel
	return lookup.push(hash, kernel_t::copy(*buffer));
}

} // namespace re2c
