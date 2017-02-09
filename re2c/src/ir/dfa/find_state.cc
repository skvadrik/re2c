#include <string.h>

#include "src/ir/dfa/find_state.h"
#include "src/util/hash32.h"

namespace re2c
{

kernel_t::kernel_t(size_t n)
	: size(n)
	, state(new nfa_state_t*[size])
	, tvers(new size_t[size])
	, tnorm(new size_t[size])
{}

kernel_t *kernel_t::copy(const kernel_t &k)
{
	const size_t n = k.size;
	kernel_t *kcopy = new kernel_t(n);
	memcpy(kcopy->state, k.state, n * sizeof(void*));
	memcpy(kcopy->tvers, k.tvers, n * sizeof(size_t));
	memcpy(kcopy->tnorm, k.tnorm, n * sizeof(size_t));
	return kcopy;
}

kernel_t::~kernel_t()
{
	delete[] state;
	delete[] tvers;
	delete[] tnorm;
}

struct kernel_eq_t
{
	bool operator()(const kernel_t *x, const kernel_t *y) const
	{
		return x->size == y->size
			&& memcmp(x->state, y->state, x->size * sizeof(void*)) == 0
			&& memcmp(x->tvers, y->tvers, x->size * sizeof(size_t)) == 0;
	}
};

struct kernel_map_t
{
	bool operator()(const kernel_t *x, const kernel_t *y) const
	{
		return x->size == y->size
			&& memcmp(x->state, y->state, x->size * sizeof(void*)) == 0
			&& memcmp(x->tnorm, y->tnorm, x->size * sizeof(size_t)) == 0;
	}
};

kernels_t::kernels_t(Tagpool &tagp, tcpool_t &tcp)
	: lookup()
	, tagpool(tagp)
	, tcpool(tcp)

	, maxsize(0) // usually ranges from one to some twenty
	, buffer(new kernel_t(maxsize))
	, nform(NULL)

	, cap(0)
	, max(0)
	, mem(NULL)
	, x2y(NULL)
	, y2x(NULL)
	, indeg(NULL)
{}

kernels_t::~kernels_t()
{
	delete buffer;
	delete[] mem;
	delete[] nform;

	const size_t n = lookup.size();
	for (size_t i = 0; i < n; ++i) {
		delete lookup[i];
	}
}

void kernels_t::init(tagver_t v, size_t nkern)
{
	if (maxsize < nkern) {
		maxsize = nkern * 2; // in advance
		delete buffer;
		delete[] nform;
		buffer = new kernel_t(maxsize);
		nform = new tagver_t[tagpool.ntags * maxsize];
	}

	// +1 to ensure max tag version is not forgotten in loops
	max = v + 1;
	if (cap < max) {
		cap = max * 2; // in advance

		const size_t
			n = static_cast<size_t>(cap),
			m = 2 * n + 1,
			sz_x2y = 2 * m * sizeof(tagver_t),
			sz_indeg = n * sizeof(uint32_t);
		delete[] mem;
		mem = new char[sz_x2y + sz_indeg];

		// point to the center (zero index) of each buffer
		// indexes in range [-N .. N] must be valid, where N is capacity
		x2y   = reinterpret_cast<tagver_t*>(mem) + cap;
		y2x   = x2y + m;
		indeg = reinterpret_cast<uint32_t*>(mem + sz_x2y);

		// see note [topological ordering of copy commands]
		memset(indeg, 0, sz_indeg);
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

/* note [kernel normal form]
 *
 * 'Normal form' of the version matrix of the given kernel: versions are
 * renumbered to have consequent natural numbers starting from one; exceptions
 * are 'cursor' and 'bottom' versions which are not normalized (they must
 * coinside for mappable kernels). Order of versions is preserved.
 *
 * The normalized matrix is cut into rows: rows fit nicely into tagpool
 * and we need to index the normal form anyway to perform fast comparison of
 * two normal forms.
 */
void kernels_t::normal_form()
{
	kernel_t *kernel = buffer;
	size_t ntag = tagpool.ntags;
	std::set<tagver_t> used;
	std::set<tagver_t>::const_iterator u;

	for (size_t t = 0; t < ntag; ++t) {
		used.clear();
		for (size_t i = 0; i < kernel->size; ++i) {
			// see note [mapping ignores items with lookahead tags]
			const tagver_t v = tagpool[kernel->tvers[i]][t];
			if (v != TAGVER_CURSOR && v != TAGVER_BOTTOM) {
				used.insert(v);
			}
		}
		tagver_t maxv = 0;
		for (u = used.begin(); u != used.end(); ++u) {
			x2y[*u] = ++maxv;
		}
		for (size_t i = 0; i < kernel->size; ++i) {
			const tagver_t v = tagpool[kernel->tvers[i]][t];
			nform[ntag * i + t] = v == TAGVER_CURSOR || v == TAGVER_BOTTOM
				? v : x2y[v];
		}
	}
	for (size_t i = 0; i < kernel->size; ++i) {
		kernel->tnorm[i] = tagpool.insert(nform + ntag * i);
	}
}

/* note [bijective mappings]
 *
 * Suppose we have just constructed a new DFA state Y and want to map it
 * to an existing DFA state X. States must have identical sets of NFA
 * substates and identical sets of lookahead tags for each substate.
 * Furtermore, there must be bijective mapping between versions of X and Y
 * and this mapping must preserve version order (respect priorities).
 *
 * Bijective mappings have a nice property: there is only one possible state
 * X to which Y can be mapped. Indeed, if there was another state Z that
 * can be bijectively mapped to Y preserving priorities, then Z itself can
 * be mapped to X: both (1) and (2) are symmetrical in case of bijection
 * and the relation is transitive. So the existence of Z is a contradiction.
 *
 * In principle, non-bijective mappings are also possible if the new state
 * is less versatile than the old one (surjection from X to Y). However,
 * non-bijective mappings lack the 'unique counterpart' property and need
 * more complex analysis (and are not so useful after all), so we drop them.
 */

kernels_t::result_t kernels_t::insert(const closure_t &clos, tagver_t maxver)
{
	const size_t nkern = clos.size();
	size_t x = dfa_t::NIL;

	// empty closure corresponds to default state
	if (nkern == 0) return result_t(x, tcmd_t(), false);

	// resize buffer if closure is too large
	init(maxver, nkern);

	// copy closure to buffer kernel and find its normal form
	buffer->size = nkern;
	for (size_t i = 0; i < nkern; ++i) {
		const clos_t &c = clos[i];
		buffer->state[i] = c.state;
		buffer->tvers[i] = c.tvers;
	}
	normal_form();

	// get kernel hash
	uint32_t hash = static_cast<uint32_t>(nkern); // seed
	hash = hash32(hash, buffer->state, nkern * sizeof(void*));
	hash = hash32(hash, buffer->tnorm, nkern * sizeof(size_t));

	// try to find identical kernel
	kernel_eq_t eq;
	x = lookup.find_with(hash, buffer, eq);
	if (x != index_t::NIL) return result_t(x, commands1(clos), false);

	// else try to find mappable kernel
	// see note [bijective mappings]
	kernel_map_t map;
	x = lookup.find_with(hash, buffer, map);
	if (x != index_t::NIL) return result_t(x, commands2(clos, x), false);

	// otherwise add new kernel
	x = lookup.push(hash, kernel_t::copy(*buffer));
	return result_t(x, commands1(clos), true);
}

tcmd_t kernels_t::commands1(const closure_t &closure)
{
	tagsave_t *save = NULL;
	cclositer_t c1 = closure.begin(), c2 = closure.end(), c;
	tagver_t v;

	// at most one new cursor and one new bottom version per tag
	// no mapping => only save commands, no copy commands
	for (size_t t = 0; t < tagpool.ntags; ++t) {
		for (c = c1; c != c2 && (v = tagpool[c->ttran][t]) <= TAGVER_ZERO; ++c);
		if (c != c2) save = tcpool.make_save(save, v, false);

		for (c = c1; c != c2 && (v = tagpool[c->ttran][t]) >= TAGVER_ZERO; ++c);
		if (c != c2) save = tcpool.make_save(save, -v, true);
	}
	return tcmd_t(save, NULL);
}

/* note [mapping ignores items with lookahead tags]
 *
 * Consider two items X and Y being mapped.
 *
 * If tag T belongs to lookahead tags of item X, then all
 * outgoing transitions from item X update T. Which means
 * that it doesn't matter what particular version T has in X:
 * whatever version it has, it will be overwritten by any
 * outgoing transition.
 *
 * Note that lookahead tags are identical for both items
 * X and Y, because we only try to map DFA states with
 * identical lookahead tags.
 */

/* note [save(X), copy(Y,X) optimization]
 *
 * save(X) command followed by a copy(Y,X) command can be optimized to
 * save(Y). This helps reduce the number commands and versions (new version
 * X is gone), but what is more important, it allows to put copy commands
 * in front of save commands. This order is necessary when it comes to
 * fallback commands.
 *
 * Note that in case of injective mapping there may be more than one copy
 * command matching the same save command: save(X), copy(Y,X), copy(Z,X).
 * In this case save command must be replicated for each copy command:
 * save(Y), save(Z).
 *
 * For each save(X) command there must be at least one copy(Y,X) command
 * (exactly one case of bijective mapping). This is because X version in
 * save(X) command must be a new version which cannot occur in the older
 * DFA state. Thus all save commands are transformed (maybe replicated) by
 * copy commands, and some copy commands are erased by save commands.
 *
 * This optimization is applied after checking priority violation, so it
 * cannot affect the check.
*/

tcmd_t kernels_t::commands2(const closure_t &closure, size_t idx)
{
	// 'buffer' has the kernel corresponding to closure
	cclositer_t c = closure.begin();
	const kernel_t *k = (*this)[idx];
	const size_t ntag = tagpool.ntags;
	tagsave_t *save = NULL;
	tagcopy_t *copy = NULL;

	// map versions of the old kernel to versions of the new one
	std::fill(x2y - max, x2y + max, TAGVER_ZERO);
	std::fill(y2x - max, y2x + max, TAGVER_ZERO);
	for (size_t i = 0; i < k->size; ++i, ++c) {
		const tagver_t
			*xv = tagpool[k->tvers[i]],
			*yv = tagpool[c->tvers],
			*yt = tagpool[c->ttran];

		for (size_t t = 0; t < ntag; ++t) {
			const tagver_t x = xv[t], y = yv[t];

			// see note [mapping ignores items with lookahead tags]
			if (x == TAGVER_CURSOR || x == TAGVER_BOTTOM) continue;

			tagver_t &x0 = y2x[y], &y0 = x2y[x];

			// paranoid checks; normal form should take care of that
			// see note [kernel normal form]
			if (y0 != TAGVER_ZERO || x0 != TAGVER_ZERO) {
				assert(y == y0 && x == x0);
				continue;
			}

			y0 = y; x0 = x;

			const tagver_t z = yt[t],
				ax = abs(x), ay = abs(y);
			// see note [save(X), copy(Y,X) optimization]
			if (z == y) {
				save = tcpool.make_save(save, ax, z < 0);
			} else if (x != y) {
				assert(ax != ay); // stay paranoid
				copy = tcpool.make_copy(copy, ax, ay);
			}
		}
	}

	// see note [topological ordering of copy commands]
	tagcopy_t::topsort(&copy, indeg);

	return tcmd_t(save, copy);
}

static tcmd_t finalizer(const clos_t &clos, size_t ridx,
	dfa_t &dfa, const Tagpool &tagpool)
{
	tcpool_t &tcpool = dfa.tcpool;
	const Rule &rule = dfa.rules[ridx];
	const tagver_t *vers = tagpool[clos.tvers];
	tagsave_t *save = NULL;
	tagcopy_t *copy = NULL;

	for (size_t t = rule.lvar; t < rule.hvar; ++t) {
		const tagver_t v = vers[t];
		tagver_t &f = dfa.finvers[t];

		// pick a fresh version: final version is also used as fallback one
		if (f == TAGVER_ZERO) {
			f = ++dfa.maxtagver;
		}

		if (v == TAGVER_CURSOR) {
			save = tcpool.make_save(save, f, false);
		} else if (v == TAGVER_BOTTOM) {
			save = tcpool.make_save(save, f, true);
		} else {
			copy = tcpool.make_copy(copy, f, abs(v));
		}
	}

	return tcmd_t(save, copy);
}

void find_state(dfa_t &dfa, size_t state, size_t symbol,
	kernels_t &kernels, const closure_t &closure, dump_dfa_t &dump)
{
	const kernels_t::result_t
		result = kernels.insert(closure, dfa.maxtagver);

	if (result.isnew) {
		// create new DFA state
		dfa_state_t *t = new dfa_state_t(dfa.nchars);
		dfa.states.push_back(t);

		// check if the new state is final
		// see note [at most one final item per closure]
		cclositer_t c1 = closure.begin(), c2 = closure.end(),
			c = std::find_if(c1, c2, clos_t::fin);
		if (c != c2) {
			t->rule = c->state->rule;
			t->tcmd[dfa.nchars] = finalizer(*c, t->rule, dfa, kernels.tagpool);
			dump.final(result.state, c->state);
		}
	}

	if (state == dfa_t::NIL) { // initial state
		*dfa.tcmd0 = result.cmd;
		dump.state0(closure);
	} else {
		dfa_state_t *s = dfa.states[state];
		s->arcs[symbol] = result.state;
		s->tcmd[symbol] = result.cmd;
		dump.state(closure, state, symbol, result.isnew);
	}
}

} // namespace re2c
