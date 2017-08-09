#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <valarray>

#include "src/dfa/dfa.h"
#include "src/dfa/dump.h"
#include "src/dfa/find_state.h"
#include "src/dfa/tagpool.h"
#include "src/dfa/tcmd.h"
#include "src/nfa/nfa.h"
#include "src/re/rule.h"
#include "src/util/hash32.h"

namespace re2c
{

kernel_t::kernel_t(size_t n)
	: size(n)
	, state(new nfa_state_t*[size])
	, tvers(new size_t[size])
	, tlook(new hidx_t[size])
	, order(new size_t[size])
{}

kernel_t *kernel_t::copy(const kernel_t &k)
{
	const size_t n = k.size;
	kernel_t *kcopy = new kernel_t(n);
	memcpy(kcopy->state, k.state, n * sizeof(void*));
	memcpy(kcopy->tvers, k.tvers, n * sizeof(size_t));
	memcpy(kcopy->tlook, k.tlook, n * sizeof(hidx_t));
	memcpy(kcopy->order, k.order, n * sizeof(size_t));
	return kcopy;
}

kernel_t::~kernel_t()
{
	delete[] state;
	delete[] tvers;
	delete[] tlook;
	delete[] order;
}

static bool equal_lookahead_tags(const kernel_t *x, const kernel_t *y,
	Tagpool &tagpool, const std::vector<Tag> &tags)
{
	if (memcmp(x->tlook, y->tlook, x->size * sizeof(hidx_t)) == 0) {
		return true;
	}
	tagtree_t &h = tagpool.history;
	for (size_t i = 0; i < x->size; ++i) {
		const hidx_t xl = x->tlook[i], yl = y->tlook[i];
		for (size_t t = 0; t < tagpool.ntags; ++t) {
			if (history(tags[t])) {
				// compare subhistories
				if (h.compare_plain(xl, yl, t) != 0) return false;
			} else {
				// compare only the last tags
				if (h.last(xl, t) != h.last(yl, t)) return false;
			}
		}
	}
	return true;
}

struct kernel_eq_t
{
	Tagpool &tagpool;
	const std::vector<Tag> &tags;
	bool operator()(const kernel_t *x, const kernel_t *y) const
	{
		return x->size == y->size
			&& memcmp(x->state, y->state, x->size * sizeof(void*)) == 0
			&& memcmp(x->tvers, y->tvers, x->size * sizeof(size_t)) == 0
			&& memcmp(x->order, y->order, x->size * sizeof(size_t)) == 0
			&& equal_lookahead_tags(x, y, tagpool, tags);
	}
};

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

bool kernels_t::operator()(const kernel_t *k1, const kernel_t *k2)
{
	// check that kernel sizes, NFA states and orders coincide
	const bool compatible = k1->size == k2->size
		&& memcmp(k1->state, k2->state, k1->size * sizeof(void*)) == 0
		&& memcmp(k1->order, k2->order, k1->size * sizeof(size_t)) == 0
		&& equal_lookahead_tags(k1, k2, tagpool, tags);
	if (!compatible) return false;

	// map tag versions of one kernel to that of another
	// and check that lookahead versions (if any) coincide
	const size_t ntag = tagpool.ntags;
	std::fill(x2y - max, x2y + max, TAGVER_ZERO);
	std::fill(y2x - max, y2x + max, TAGVER_ZERO);
	for (size_t i = 0; i < k1->size; ++i) {
		const tagver_t
			*xv = tagpool[k1->tvers[i]],
			*yv = tagpool[k2->tvers[i]];
		const hidx_t xl = k1->tlook[i];

		for (size_t t = 0; t < ntag; ++t) {
			// see note [mapping ignores items with lookahead tags]
			if (tagpool.history.last(xl, t) != TAGVER_ZERO
				&& !history(tags[t])) continue;

			const tagver_t x = xv[t], y = yv[t];
			tagver_t &x0 = y2x[y], &y0 = x2y[x];

			if (y0 == TAGVER_ZERO && x0 == TAGVER_ZERO) {
				x0 = x;
				y0 = y;
				x2t[x] = t;
			} else if (y != y0 || x != x0) {
				return false;
			}
		}
	}

	// we have bijective mapping; now try to create list of commands
	tcmd_t *a, **pa, *copy = NULL;

	// backup 'save' commands: if topsort finds cycles, this mapping
	// will be rejected and we'll have to revert all changes
	size_t nact = 0;
	for (a = *pacts; a; a = a->next) {
		actnext[nact] = a;
		actlhs[nact] = a->lhs;
		++nact;
	}

	// fix LHS of 'save' commands to reuse old version
	// see note [save(X), copy(Y,X) optimization]
	for (a = *pacts; a; a = a->next) {
		const tagver_t
			y = a->lhs * (a->history[0] == TAGVER_BOTTOM ? -1 : 1),
			x = y2x[y];
		a->lhs = abs(x);
		y2x[y] = x2y[x] = TAGVER_ZERO;
	}

	// create 'copy' commands
	for (tagver_t x = -max; x < max; ++x) {
		const tagver_t y = x2y[x], ax = abs(x), ay = abs(y);
		if (y != TAGVER_ZERO && x != y && !fixed(tags[x2t[x]])) {
			assert(ax != ay);
			copy = tcpool.make_copy(copy, ax, ay);
		}
	}

	// join 'copy' and 'save' commands
	for (pa = &copy; (a = *pa); pa = &a->next);
	*pa = *pacts;
	*pacts = copy;

	// see note [topological ordering of copy commands]
	const bool nontrivial_cycles = tcmd_t::topsort(pacts, indeg);

	// in case of cycles restore 'save' commands and fail
	if (nontrivial_cycles) {
		pa = pacts;
		for (size_t i = 0; i < nact; ++i) {
			*pa = a = actnext[i];
			a->lhs = actlhs[i];
			pa = &a->next;
		}
		*pa = NULL;
	}

	return !nontrivial_cycles;
}

kernels_t::kernels_t(Tagpool &tagp, tcpool_t &tcp, const std::vector<Tag> &ts)
	: lookup()
	, tagpool(tagp)
	, tcpool(tcp)
	, tags(ts)

	, maxsize(0) // usually ranges from one to some twenty
	, buffer(new kernel_t(maxsize))

	, cap(0)
	, max(0)
	, mem(NULL)
	, x2y(NULL)
	, y2x(NULL)
	, x2t(NULL)
	, indeg(NULL)

	, pacts(NULL)
	, actnext(NULL)
	, actlhs(NULL)
{}

kernels_t::~kernels_t()
{
	delete buffer;
	delete[] mem;

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
		buffer = new kernel_t(maxsize);
	}

	// +1 to ensure max tag version is not forgotten in loops
	max = v + 1;
	if (cap < max) {
		cap = max * 2; // in advance

		const size_t
			n = static_cast<size_t>(cap),
			m = 2 * n + 1,
			sz_x2y = 2 * m * sizeof(tagver_t),
			sz_x2t = m * sizeof(size_t),
			sz_actnext = n * sizeof(tcmd_t*),
			sz_actlhs = n * sizeof(tagver_t),
			sz_indeg = n * sizeof(uint32_t);
		delete[] mem;
		mem = new char[sz_x2y + sz_x2t + sz_actnext + sz_actlhs + sz_indeg];

		// point to the center (zero index) of each buffer
		// indexes in range [-N .. N] must be valid, where N is capacity
		x2y     = reinterpret_cast<tagver_t*>(mem) + cap;
		y2x     = x2y + m;
		x2t     = reinterpret_cast<size_t*>(mem + sz_x2y) + cap;
		actnext = reinterpret_cast<tcmd_t**>(mem + sz_x2y + sz_x2t);
		actlhs  = reinterpret_cast<tagver_t*>(mem + sz_x2y + sz_x2t + sz_actnext);
		indeg   = reinterpret_cast<uint32_t*>(mem + sz_x2y + sz_x2t + sz_actnext + sz_actlhs);
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

kernels_t::result_t kernels_t::insert(const closure_t &clos,
	tcmd_t *acts, tagver_t maxver)
{
	const size_t nkern = clos.size();
	size_t x = dfa_t::NIL;

	// empty closure corresponds to default state
	if (nkern == 0) return result_t(x, NULL, false);

	// resize buffer if closure is too large
	init(maxver, nkern);

	// copy closure to buffer kernel and find its normal form
	buffer->size = nkern;
	for (size_t i = 0; i < nkern; ++i) {
		const clos_t &c = clos[i];
		buffer->state[i] = c.state;
		buffer->tvers[i] = c.tvers;
		buffer->tlook[i] = c.tlook;
		buffer->order[i] = c.order;
	}

	// get kernel hash
	uint32_t hash = static_cast<uint32_t>(nkern); // seed
	hash = hash32(hash, buffer->state, nkern * sizeof(void*));
	hash = hash32(hash, buffer->order, nkern * sizeof(size_t));

	// try to find identical kernel
	kernel_eq_t eq = {tagpool, tags};
	x = lookup.find_with(hash, buffer, eq);
	if (x != index_t::NIL) return result_t(x, acts, false);

	// else try to find mappable kernel
	// see note [bijective mappings]
	this->pacts = &acts;
	x = lookup.find_with(hash, buffer, *this);
	if (x != index_t::NIL) return result_t(x, acts, false);

	// otherwise add new kernel
	x = lookup.push(hash, kernel_t::copy(*buffer));
	return result_t(x, acts, true);
}

static tcmd_t *finalizer(const clos_t &clos, size_t ridx,
	dfa_t &dfa, const Tagpool &tagpool, const std::vector<Tag> &tags)
{
	tcpool_t &tcpool = dfa.tcpool;
	const Rule &rule = dfa.rules[ridx];
	const tagver_t *vers = tagpool[clos.tvers];
	const tagtree_t &hist = tagpool.history;
	const hidx_t look = clos.tlook;
	tcmd_t *copy = NULL, *save = NULL, **p;

	for (size_t t = rule.ltag; t < rule.htag; ++t) {
		const Tag &tag = tags[t];
		if (fixed(tag)) continue;

		const tagver_t v = abs(vers[t]), l = hist.last(look, t);
		tagver_t &f = dfa.finvers[t];
		if (l == TAGVER_ZERO) {
			copy = tcpool.make_copy(copy, f, v);
		} else if (history(tag)) {
			save = tcpool.make_add(save, f, v, hist, look, t);
		} else {
			save = tcpool.make_set(save, f, l);
		}
	}

	// join 'copy' and 'save' commands
	for (p = &copy; *p; p = &(*p)->next);
	*p = save;

	return copy;
}

void find_state(dfa_t &dfa, size_t state, size_t symbol, kernels_t &kernels,
	const closure_t &closure, tcmd_t *acts, dump_dfa_t &dump)
{
	const kernels_t::result_t
		result = kernels.insert(closure, acts, dfa.maxtagver);

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
			t->tcmd[dfa.nchars] = finalizer(*c, t->rule, dfa,
				kernels.tagpool, kernels.tags);
			dump.final(result.state, c->state);
		}
	}

	if (state == dfa_t::NIL) { // initial state
		dfa.tcmd0 = result.cmd;
		dump.state0(closure);
	} else {
		dfa_state_t *s = dfa.states[state];
		s->arcs[symbol] = result.state;
		s->tcmd[symbol] = result.cmd;
		dump.state(closure, state, symbol, result.isnew);
	}
}

} // namespace re2c
