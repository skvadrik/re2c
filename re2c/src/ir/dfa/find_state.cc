#include <string.h>

#include "src/ir/dfa/find_state.h"
#include "src/util/hash32.h"

namespace re2c
{

kernel_t::kernel_t(size_t n)
	: size(n)
	, state(new nfa_state_t*[size])
	, tvers(new size_t[size])
	, tlook(new size_t[size])
{}

kernel_t *kernel_t::copy(const kernel_t &k)
{
	const size_t n = k.size;
	kernel_t *kcopy = new kernel_t(n);
	memcpy(kcopy->state, k.state, n * sizeof(void*));
	memcpy(kcopy->tvers, k.tvers, n * sizeof(size_t));
	memcpy(kcopy->tlook, k.tlook, n * sizeof(size_t));
	return kcopy;
}

kernel_t::~kernel_t()
{
	delete[] state;
	delete[] tvers;
	delete[] tlook;
}

struct kernel_eq_t
{
	bool operator()(const kernel_t *x, const kernel_t *y) const
	{
		return x->size == y->size
			&& memcmp(x->state, y->state, x->size * sizeof(void*)) == 0
			&& memcmp(x->tvers, y->tvers, x->size * sizeof(size_t)) == 0
			&& memcmp(x->tlook, y->tlook, x->size * sizeof(size_t)) == 0;
	}
};

mapping_t::mapping_t(Tagpool &pool)
	: tagpool(pool)
	, cap(0)
	, mem(NULL)
	, max(0)
	, x2t(NULL)
	, x2y(NULL)
	, y2x(NULL)
	, indeg(NULL)
{}

mapping_t::~mapping_t()
{
	delete[] mem;
}

void mapping_t::init(tagver_t v)
{
	// +1 to ensure max tag version is not forgotten in loops
	max = v + 1;

	if (cap < max) {
		cap = max * 2; // in advance

		const size_t
			n = static_cast<size_t>(cap),
			n2 = 2 * n + 1,
			sz_x2t = n2 * sizeof(size_t),
			sz_x2y = 2 * n2 * sizeof(tagver_t),
			sz_indeg = n * sizeof(uint32_t);
		delete[] mem;
		mem = new char[sz_x2t + sz_x2y + sz_indeg];

		// point to the center (zero index) of each buffer
		// indexes in range [-N .. N] must be valid, where N is capacity
		x2t        = reinterpret_cast<size_t*>(mem) + cap;
		x2y        = reinterpret_cast<tagver_t*>(mem + sz_x2t) + cap;
		y2x        = x2y + n2;
		indeg      = reinterpret_cast<uint32_t*>(mem + sz_x2t + sz_x2y);

		// see note [topological ordering of copy commands]
		memset(indeg, 0, sz_indeg);
	}
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

/* note [mapping should not violate tag priorities]
 *
 * If tag X1 is mapped to Y1, X2 to Y2 and X1 has lower priority
 * than X2, then Y1 must have lower priority than Y2.
 *
 * We represent mapping as array of Y-components indexed by
 * X-component; all tags are merged together. However, priorities
 * should be checked individually for each tag. Since mapping is
 * automatically sorted by X, it suffices to ensure that Y
 * subsequence for the given tag is monotonically non-decreasing.
 */

static bool compatible_kernels(const kernel_t *x, const kernel_t *y)
{
	return x->size == y->size
		&& memcmp(x->state, y->state, x->size * sizeof(void*)) == 0
		&& memcmp(x->tlook, y->tlook, x->size * sizeof(size_t)) == 0;
}

bool mapping_t::operator()(const kernel_t *k1, const kernel_t *k2)
{
	// check that kernel sizes, NFA states and lookahead tags coincide
	if (!compatible_kernels(k1, k2)) return false;

	const size_t ntag = tagpool.ntags;

	// map tag versions of one kenel to that of another
	std::fill(x2y - max, x2y + max, TAGVER_ZERO);
	std::fill(y2x - max, y2x + max, TAGVER_ZERO);
	for (size_t i = 0; i < k1->size; ++i) {
		const tagver_t
			*xl = tagpool[k1->tlook[i]],
			*xv = tagpool[k1->tvers[i]],
			*yv = tagpool[k2->tvers[i]];

		for (size_t t = 0; t < ntag; ++t) {
			// see note [mapping ignores items with lookahead tags]
			if (xl[t] != TAGVER_ZERO) continue;

			const tagver_t x = xv[t], y = yv[t],
				x0 = y2x[y], y0 = x2y[x];
			if (y0 == TAGVER_ZERO && x0 == TAGVER_ZERO) {
				x2t[x] = t;
				x2y[x] = y;
				y2x[y] = x;
			} else if (!(y == y0 && x == x0)) return false;
		}
	}

	// mapping is possible; check that it is correct
	// see note [mapping should not violate tag priorities]
	tagver_t *pred = tagpool.buffer1;
	std::fill(pred, pred + ntag, -max);
	for (tagver_t x = -max; x < max; ++x) {
		const tagver_t y = x2y[x];
		const size_t t = x2t[x];

		if (y == TAGVER_ZERO) continue;
		if (y < pred[t]) return false;
		pred[t] = y;
	}
	return true;
}

kernels_t::kernels_t(Tagpool &tagpool)
	: lookup()
	, mapping(tagpool)
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
	if (nkern == 0) return result_t(x, NULL, false);

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
		buffer->tvers[i] = c.tvers;
		buffer->tlook[i] = c.tlook;
	}

	// get kernel hash
	uint32_t hash = static_cast<uint32_t>(nkern); // seed
	hash = hash32(hash, buffer->state, nkern * sizeof(void*));
	hash = hash32(hash, buffer->tlook, nkern * sizeof(size_t));

	// try to find identical kernel
	kernel_eq_t eq;
	x = lookup.find_with(hash, buffer, eq);
	if (x != index_t::NIL) return result_t(x, NULL, false);

	// else try to find mappable kernel
	// see note [bijective mappings]
	mapping.init(maxver);
	x = lookup.find_with(hash, buffer, mapping);
	if (x != index_t::NIL) return result_t(x, &mapping, false);

	// otherwise add new kernel
	x = lookup.push(hash, kernel_t::copy(*buffer));
	return result_t(x, NULL, true);
}

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

static tcmd_t commands(const closure_t &closure, const Tagpool &tagpool,
	tcpool_t &tcpool, mapping_t *map)
{
	tagsave_t *save = NULL;
	tagcopy_t *copy = NULL;
	tagver_t *cur = tagpool.buffer1, *bot = tagpool.buffer2;
	cclositer_t c1 = closure.begin(), c2 = closure.end(), c;

	// at most one new cursor and one new bottom version per tag
	for (size_t t = 0; t < tagpool.ntags; ++t) {
		for (c = c1; c != c2 && tagpool[c->ttran][t] != TAGVER_CURSOR; ++c);
		cur[t] = c == c2 ? TAGVER_ZERO : tagpool[c->tvers][t];

		for (c = c1; c != c2 && tagpool[c->ttran][t] != TAGVER_BOTTOM; ++c);
		bot[t] = c == c2 ? TAGVER_ZERO : tagpool[c->tvers][t];
	}

	if (!map) {
		// no mapping => only save commands, no copy commands
		for (size_t t = 0; t < tagpool.ntags; ++t) {
			const tagver_t x = cur[t], y = bot[t];
			if (x != TAGVER_ZERO) save = tcpool.make_save(save, x, false);
			if (y != TAGVER_ZERO) save = tcpool.make_save(save, -y, true);
		}
	} else {
		// mapping: see note [save(X), copy(Y,X) optimization]
		for (tagver_t x = -map->max; x < map->max; ++x) {
			const tagver_t
				y = map->x2y[x],
				ax = abs(x),
				ay = abs(y);
			const size_t t = map->x2t[x];
			if (y == TAGVER_ZERO) {
				continue;
			} else if (cur[t] == y) {
				save = tcpool.make_save(save, ax, false);
			} else if (bot[t] == y) {
				save = tcpool.make_save(save, ax, true);
			} else if (x != y) {
				assert(ax != ay);
				copy = tcpool.make_copy(copy, ax, ay);
			}
		}
		// see note [topological ordering of copy commands]
		tagcopy_t::topsort(&copy, map->indeg);
	}

	return tcmd_t(save, copy);
}

static tcmd_t finalizer(const clos_t &clos, size_t ridx,
	dfa_t &dfa, const Tagpool &tagpool)
{
	tcpool_t &tcpool = dfa.tcpool;
	const Rule &rule = dfa.rules[ridx];
	const tagver_t
		*vers = tagpool[clos.tvers],
		*tran = tagpool[clos.tlook];
	tagsave_t *save = NULL;
	tagcopy_t *copy = NULL;

	for (size_t t = rule.lvar; t < rule.hvar; ++t) {
		const tagver_t u = tran[t], v = abs(vers[t]);
		tagver_t &f = dfa.finvers[t];

		// pick a fresh version: final version is also used as fallback one
		if (f == TAGVER_ZERO) {
			f = ++dfa.maxtagver;
		}

		if (u != TAGVER_ZERO) {
			save = tcpool.make_save(save, f, u == TAGVER_BOTTOM);
		} else {
			copy = tcpool.make_copy(copy, f, v);
		}
	}

	return tcmd_t(save, copy);
}

void find_state(dfa_t &dfa, size_t state, size_t symbol,
	const Tagpool &tagpool, kernels_t &kernels,
	const closure_t &closure, dump_dfa_t &dump)
{
	const kernels_t::result_t result = kernels.insert(closure, dfa.maxtagver);
	const tcmd_t cmd = commands(closure, tagpool, dfa.tcpool, result.mapping);

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
			t->tcmd[dfa.nchars] = finalizer(*c, t->rule, dfa, tagpool);
			dump.final(result.state, c->state);
		}
	}

	if (state == dfa_t::NIL) { // initial state
		*dfa.tcmd0 = cmd;
		dump.state0(closure);
	} else {
		dfa_state_t *s = dfa.states[state];
		s->arcs[symbol] = result.state;
		s->tcmd[symbol] = cmd;
		dump.state(closure, state, symbol, result.isnew);
	}
}

} // namespace re2c
