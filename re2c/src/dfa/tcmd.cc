#include <assert.h>

#include "src/dfa/tcmd.h"
#include "src/util/hash32.h"

namespace re2c
{

static uint32_t hash_tcmd(const tcmd_t *tcmd);

void tcmd_t::swap(tcmd_t &x, tcmd_t &y)
{
	std::swap(x.lhs, y.lhs);
	std::swap(x.rhs, y.rhs);
}

bool tcmd_t::less(const tcmd_t &x, const tcmd_t &y)
{
	const tagver_t
		lx = x.lhs, ly = y.lhs,
		rx = x.rhs, ry = y.rhs;
	return (lx < ly) || (lx == ly && rx < ry);
}

bool tcmd_t::equal(const tcmd_t &x, const tcmd_t &y)
{
	return x.lhs == y.lhs && x.rhs == y.rhs;
}

/* note [topological ordering of copy commands]
 *
 * The order in which copy commands are executed is important:
 * 'x = y; y = z;' is not the same as 'y = z; x = y;' (the latter
 * overwrites 'y' before its precious value is copied to 'x').
 *
 * To avoid overwrites, commands should be topologically sorted.
 * Cycles of length 2 are not allowed by construction; cycles of
 * length 3 or more are left as is.
 *
 * For the purpose of topsort, we treat commands as arcs of directed
 * acyclic graph: command 'x = y' yields arc X -> Y. Topsort works
 * by iteratively removing arcs X -> Y such that X has zero in-degree
 * (they correspond to commands with no dependencies).
 * Commands in the order of removal are topologically sorted.
 *
 * The algorithm iterates graph and removes arcs with zero in-degree
 * until either the graph is empty or all remaining arcs belong to
 * cycles.
 *
 * The algorithm starts and ends with all-zero in-degree buffer.
 */

bool tcmd_t::iscopy(tagver_t rhs)
{
	return rhs != TAGVER_BOTTOM && rhs != TAGVER_CURSOR;
}

static tcmd_t **topsort_(tcmd_t **phead, uint32_t *indeg);

void tcmd_t::topsort(tcmd_t **phead, uint32_t *indeg)
{
	tcmd_t *x = *phead, **py = phead, **py0;

	for (x = *phead; x;) {

		*py = x;
		for (; x && !tcmd_t::iscopy(x->rhs); x = x->next) {
			py = &x->next;
		}

		py0 = py;
		for (; x && tcmd_t::iscopy(x->rhs); x = x->next) {
			py = &x->next;
		}
		*py = NULL;

		py = topsort_(py0, indeg);
	}
}

tcmd_t **topsort_(tcmd_t **phead, uint32_t *indeg)
{
	tcmd_t
		*x0 = *phead, **px, *x,
		*y0 = NULL, **py, **py1;

	// initialize in-degree
	for (x = x0; x; x = x->next) {
		++indeg[x->rhs];
	}

	for (py = &y0;;) {
		// reached end of list
		if (!x0) break;

		px = &x0;
		py1 = py;
		for (x = x0; x; x = x->next) {
			if (indeg[x->lhs] == 0) {
				--indeg[x->rhs];
				*py = x;
				py = &x->next;
			} else {
				*px = x;
				px = &x->next;
			}
		}
		*px = NULL;

		// only cycles left
		if (py == py1) break;
	}
	*py = x0;

	*phead = y0;
	for (; *py; py = &(*py)->next);
	return py;
}

tcpool_t::tcpool_t()
	: alc()
	, index()
{
	// empty command must have static number zero
	assert(TCID0 == insert(NULL));
}

tcmd_t *tcpool_t::make_tcmd(tcmd_t *next, tagver_t lhs, tagver_t rhs)
{
	tcmd_t *p = alc.alloct<tcmd_t>(1);
	p->next = next;
	p->lhs = lhs;
	p->rhs = rhs;
	return p;
}

uint32_t hash_tcmd(const tcmd_t *tcmd)
{
	uint32_t h = 0;
	for (const tcmd_t *p = tcmd; p; p = p->next) {
		h = hash32(h, &p->lhs, sizeof(p->lhs));
		h = hash32(h, &p->rhs, sizeof(p->rhs));
	}
	return h;
}

struct tcmd_eq_t
{
	bool operator()(const tcmd_t *x, const tcmd_t *y) const
	{
		for (;;) {
			if (!x && !y) return true;
			if (!x || !y) return false;
			if (!tcmd_t::equal(*x, *y)) return false;
			x = x->next;
			y = y->next;
		}
	}
};

tcid_t tcpool_t::insert(const tcmd_t *tcmd)
{
	const uint32_t h = hash_tcmd(tcmd);

	tcmd_eq_t eq;
	size_t id = index.find_with(h, tcmd, eq);
	if (id == index_t::NIL) {
		id = index.push(h, tcmd);
	}

	return static_cast<tcid_t>(id);
}

const tcmd_t *tcpool_t::operator[](tcid_t id) const
{
	return index[id];
}

} // namespace re2c
