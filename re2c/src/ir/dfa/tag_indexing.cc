#include "src/ir/dfa/tag_optimize.h"
#include "src/util/hash32.h"
#include "src/util/lookup.h"

namespace re2c
{

template<typename cmd_t> struct cmp_t;
template<typename cmd_t> void doindex(cmd_t **pcmd, lookup_t<cmd_t*> &index);

void tag_indexing(dfa_t &dfa)
{
	const size_t
		nstate = dfa.states.size(),
		nsym = dfa.nchars;
	lookup_t<tagsave_t*> saveindex;
	lookup_t<tagcopy_t*> copyindex;

	for (size_t i = 0; i < nstate; ++i) {
		dfa_state_t *s = dfa.states[i];

		for (size_t c = 0; c < nsym; ++c) {
			tagcmd_t &cmd = s->tags[c];
			doindex(&cmd.save, saveindex);
			doindex(&cmd.copy, copyindex);
		}

		tagcmd_t &cmd = s->rule_tags;
		doindex(&cmd.save, saveindex);
		doindex(&cmd.copy, copyindex);
	}
}

// After renaming different tags may map to the same version,
// thus one set of versions may have different representations.
// Transition tags are treated as sets and should be unified.

// After renaming different lists may become identical
// up to reordering and deleting duplicates.

template<typename cmd_t>
void doindex(cmd_t **pcmd, lookup_t<cmd_t*> &index)
{
	cmd_t *cmd = *pcmd;
	if (!cmd) return;

	// sort lexicographically
	for (cmd_t *p = cmd; p; p = p->next) {
		for (cmd_t *q = p->next; q; q = q->next) {
			if (cmd_t::less(*q, *p)) {
				cmd_t::swap(*p, *q);
			}
		}
	}

	// delete duplicates
	for (cmd_t *p = cmd; p; p = p->next) {
		cmd_t *q = p->next;
		if (q && cmd_t::equal(*p, *q)) {
			p->next = q->next;
		}
	}

	// find in or add to index
	const uint32_t hash = cmd_t::hash(cmd);
	size_t idx = index.find_with(hash, cmd, cmp_t<cmd_t>());
	if (idx == lookup_t<cmd_t*>::NIL) {
		idx = index.push(hash, cmd);
	}

	*pcmd = index[idx];
}

void tagsave_t::swap(tagsave_t &x, tagsave_t &y)
{
	std::swap(x.ver, y.ver);
}

void tagcopy_t::swap(tagcopy_t &x, tagcopy_t &y)
{
	std::swap(x.lhs, y.lhs);
	std::swap(x.rhs, y.rhs);
}

bool tagsave_t::less(const tagsave_t &x, const tagsave_t &y)
{
	return x.ver < y.ver;
}

bool tagcopy_t::less(const tagcopy_t &x, const tagcopy_t &y)
{
	const tagver_t
		lx = x.lhs, ly = y.lhs,
		rx = x.rhs, ry = y.rhs;
	return (lx < ly) || (lx == ly && rx < ry);
}

bool tagsave_t::equal(const tagsave_t &x, const tagsave_t &y)
{
	return x.ver == y.ver;
}

bool tagcopy_t::equal(const tagcopy_t &x, const tagcopy_t &y)
{
	return x.lhs == y.lhs && x.rhs == y.rhs;
}

template<typename cmd_t> struct cmp_t
{
	bool operator()(const cmd_t *x, const cmd_t *y) const
	{
		for (;;) {
			if (!x && !y) return true;
			if (!x || !y) return false;
			if (!cmd_t::equal(*x, *y)) return false;
			x = x->next;
			y = y->next;
		}
	}
};

uint32_t tagsave_t::hash(const tagsave_t *p)
{
	uint32_t h = 0;
	for (; p; p = p->next) {
		h = hash32(h, &p->ver, sizeof(p->ver));
	}
	return h;
}

uint32_t tagcopy_t::hash(const tagcopy_t *p)
{
	uint32_t h = 0;
	for (; p; p = p->next) {
		h = hash32(h, &p->lhs, sizeof(p->lhs));
		h = hash32(h, &p->rhs, sizeof(p->rhs));
	}
	return h;
}

} // namespace re2c
