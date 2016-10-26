#include "src/ir/dfa/tag_optimize.h"
#include "src/util/hash32.h"

namespace re2c
{

typedef lookup_t<tagcopy_t*> tagcopy_index_t;

struct tagcopy_cmp_t
{
	bool operator()(const tagcopy_t *x, const tagcopy_t *y);
};

static void rename_set(Tagpool &tagpool, size_t &tags, const tagver_t *ver2new, bool unify);
static void rename_copy(tagcopy_t **phead, const tagver_t *ver2new, tagcopy_index_t &index);
static int less(const tagcopy_t *x, const tagcopy_t *y);
static int equal(const tagcopy_t *x, const tagcopy_t *y);
static tagcopy_t *indexate(tagcopy_index_t &index, tagcopy_t *head);

void tag_renaming(dfa_t &dfa, const tagver_t *ver2new, tagver_t maxver)
{
	if (maxver >= dfa.maxtagver) {
		assert(maxver == dfa.maxtagver);
		return;
	}

	Tagpool &tagpool = dfa.tagpool;
	const size_t
		nstates = dfa.states.size(),
		nrule = dfa.rules.size();
	tagcopy_index_t index;

	for (size_t i = 0; i < nstates; ++i) {
		dfa_state_t *s = dfa.states[i];
		for (size_t c = 0; c < dfa.nchars; ++c) {
			rename_set(tagpool, s->tags[c].set, ver2new, true);
			rename_copy(&s->tags[c].copy, ver2new, index);
		}
		rename_set(tagpool, s->rule_tags.set, ver2new, true);
		rename_copy(&s->rule_tags.copy, ver2new, index);
	}
	for (size_t i = 0; i < nrule; ++i) {
		rename_set(tagpool, dfa.rules[i].tags, ver2new, false);
	}
}

void rename_set(Tagpool &tagpool, size_t &tags, const tagver_t *ver2new,
	bool unify)
{
	if (tags == ZERO_TAGS) return;

	const tagver_t *oldver = tagpool[tags];
	tagver_t *newver = tagpool.buffer1;
	const size_t ntag = tagpool.ntags;

	for (size_t t = 0; t < ntag; ++t) {
		const tagver_t v = oldver[t];
		newver[t] = v != TAGVER_ZERO
			? ver2new[v]
			: v;
	}

	// After renaming different tags may map to the same version,
	// thus one set of versions may have different representations.
	// Transition tags are treated as sets and should be unified.
	// Rule tags are treated as mappings of tag to its final version.
	if (unify) {
		tagver_t *e = newver + ntag;
		std::sort(newver, e);
		std::fill(std::unique(newver, e), e, TAGVER_ZERO);
	}

	tags = tagpool.insert(newver);
}

void rename_copy(tagcopy_t **phead, const tagver_t *ver2new,
	tagcopy_index_t &index)
{
	for (tagcopy_t **pp = phead, *p = *pp; p; p = *pp) {
		p->lhs = ver2new[p->lhs];
		p->rhs = ver2new[p->rhs];
		if (p->lhs == p->rhs) {
			*pp = p->next;
		} else {
			pp = &p->next;
		}
	}

	// After renaming different lists may become identical
	// up to reordering and deleting duplicates.

	// sort lexicographically
	for (tagcopy_t *p = *phead; p; p = p->next) {
		for (tagcopy_t *q = p->next; q; q = q->next) {
			if (less(q, p)) {
				std::swap(p->lhs, q->lhs);
				std::swap(p->rhs, q->rhs);
			}
		}
	}
	// delete duplicates
	for (tagcopy_t *p = *phead; p; p = p->next) {
		tagcopy_t *q = p->next;
		if (q && equal(p, q)) {
			p->next = q->next;
		}
	}

	*phead = indexate(index, *phead);
}

int less(const tagcopy_t *x, const tagcopy_t *y)
{
	const tagver_t
		lx = x->lhs, ly = y->lhs,
		rx = x->rhs, ry = y->rhs;
	return (lx < ly) || (lx == ly && rx < ry);
}

int equal(const tagcopy_t *x, const tagcopy_t *y)
{
	return x->lhs == y->lhs && x->rhs == y->rhs;
}

bool tagcopy_cmp_t::operator()(const tagcopy_t *x, const tagcopy_t *y)
{
	for (;;) {
		if (!x && !y) return true;
		if (!x || !y) return false;
		if (x->lhs != y->lhs || x->rhs != y->rhs) return false;
		x = x->next;
		y = y->next;
	}
}

tagcopy_t *indexate(tagcopy_index_t &index, tagcopy_t *head)
{
	uint32_t hash = 0;
	for (const tagcopy_t *p = head; p; p = p->next) {
		hash = hash32(hash, &p->lhs, sizeof(p->lhs));
		hash = hash32(hash, &p->rhs, sizeof(p->rhs));
	}

	tagcopy_cmp_t eq;
	const size_t idx = index.find_with(hash, head, eq);
	if (idx != tagcopy_index_t::NIL) {
		return index[idx];
	}

	index.push(hash, head);
	return head;
}

} // namespace re2c

