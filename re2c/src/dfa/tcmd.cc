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
	std::swap(x.pred, y.pred);
}

bool tcmd_t::less(const tcmd_t &x, const tcmd_t &y)
{
	if (x.lhs < y.lhs) return true;
	if (x.lhs > y.lhs) return false;

	if (x.rhs < y.rhs) return true;
	if (x.rhs > y.rhs) return false;

	if (x.pred < y.pred) return true;
	if (x.pred > y.pred) return false;

	return false;
}

bool tcmd_t::equal(const tcmd_t &x, const tcmd_t &y)
{
	return x.lhs == y.lhs && x.rhs == y.rhs && x.pred == y.pred;
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

bool tcmd_t::isset(const tcmd_t *cmd)
{
	return !tcmd_t::iscopy(cmd->rhs) && cmd->pred == TAGVER_ZERO;
}

bool tcmd_t::isadd(const tcmd_t *cmd)
{
	return !tcmd_t::iscopy(cmd->rhs) && cmd->pred != TAGVER_ZERO;
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

static tagver_t depend(const tcmd_t *x)
{
	const tagver_t r = x->rhs, h = x->pred;
	return tcmd_t::iscopy(r) ? r : h;
}

void tcmd_t::topsort1(tcmd_t **phead, uint32_t *indeg)
{
	tcmd_t
		*x0 = *phead, **px, *x,
		*y0 = NULL, **py, **py1;

	// initialize in-degree
	for (x = x0; x; x = x->next) {
		++indeg[depend(x)];
	}

	for (py = &y0;;) {
		// reached end of list
		if (!x0) break;

		px = &x0;
		py1 = py;
		for (x = x0; x; x = x->next) {
			if (indeg[x->lhs] == 0) {
				--indeg[depend(x)];
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
}

tcpool_t::tcpool_t()
	: alc()
	, index()
{
	// empty command must have static number zero
	assert(TCID0 == insert(NULL));
}

tcmd_t *tcpool_t::make_tcmd(tcmd_t *next, tagver_t lhs, tagver_t rhs, tagver_t pred)
{
	tcmd_t *p = alc.alloct<tcmd_t>(1);
	p->next = next;
	p->lhs = lhs;
	p->rhs = rhs;
	p->pred = pred;
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
