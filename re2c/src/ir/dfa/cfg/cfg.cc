#include <string.h>

#include "src/ir/dfa/cfg/cfg.h"

namespace re2c
{

static cfg_ix_t map_arcs_to_bblocks(const dfa_t &dfa, cfg_ix_t *arc2bb);
static cfg_bb_t *create_bblocks(const dfa_t &dfa, const cfg_ix_t *arc2bb, cfg_ix_t nbblock);
static void basic_block(cfg_bb_t *bb, const cfg_ix_t *succb, const cfg_ix_t *succe, tcmd_t *cmd, tagver_t *use);
static void successors(const dfa_t &dfa, const cfg_ix_t *arc2bb, bool *been, cfg_ix_t *&succ, size_t x);
static void fallback(const dfa_t &dfa, const cfg_ix_t *arc2bb, bool *been, cfg_ix_t *&succ, size_t x);

cfg_t::cfg_t(dfa_t &a)
	: dfa(a)
	, bblocks(NULL)
	, nbblock(0)
{
	const size_t
		nstate = dfa.states.size(),
		narc = nstate * dfa.nchars;
	cfg_ix_t *arc2bb = new cfg_ix_t[narc + nstate];

	nbblock = map_arcs_to_bblocks(dfa, arc2bb);
	bblocks = create_bblocks(dfa, arc2bb, nbblock);

	delete[] arc2bb;
}

cfg_ix_t map_arcs_to_bblocks(const dfa_t &dfa, cfg_ix_t *arc2bb)
{
	const size_t
		nstate = dfa.states.size(),
		nsym = dfa.nchars;

	// first bblock is CFG root: it has no counterpart in DFA
	cfg_ix_t nbblock = 1;

	for (size_t i = 0; i < nstate; ++i) {
		const dfa_state_t *s = dfa.states[i];

		// bblocks for tagged transitions in DFA
		for (size_t c = 0; c < nsym; ++c) {
			const tcmd_t &cmd = s->tcmd[c];
			*arc2bb++ = cmd.save || cmd.copy ? nbblock++ : 0;
		}

		// bblocks for final DFA states with rules that have tags
		*arc2bb++ = s->rule != Rule::NONE
			&& dfa.rules[s->rule].tags != ZERO_TAGS
			? nbblock++ : 0;
	}

	return nbblock;
}

cfg_bb_t *create_bblocks(const dfa_t &dfa, const cfg_ix_t *arc2bb, cfg_ix_t nbblock)
{
	const size_t
		nstate = dfa.states.size(),
		nsym = dfa.nchars;
	const cfg_ix_t *a2b = arc2bb;
	cfg_ix_t *succb = new cfg_ix_t[nbblock], *succe;
	bool *been = new bool[nstate];

	cfg_bb_t *bblocks = new cfg_bb_t[nbblock], *b = bblocks;

	// root bblock
	std::fill(been, been + nstate, false);
	successors(dfa, arc2bb, been, succe = succb, 0);
	basic_block(b++, succb, succe, new tcmd_t, TAGVER_ZERO);

	for (size_t i = 0; i < nstate; ++i) {
		const dfa_state_t *s = dfa.states[i];

		// transition bblocks
		for (size_t c = 0; c < nsym; ++c) {
			if (*a2b++ != 0) {
				std::fill(been, been + nstate, false);
				successors(dfa, arc2bb, been, succe = succb, s->arcs[c]);
				basic_block(b++, succb, succe, &s->tcmd[c], TAGVER_ZERO);
			}
		}

		// final bblocks
		if (*a2b++ != 0) {
			std::fill(been, been + nstate, false);
			fallback(dfa, arc2bb, been, succe = succb, i);
			basic_block(b++, succb, succe, &s->tcmd[nsym], dfa.rules[s->rule].tags);
		}
	}

	delete[] succb;
	delete[] been;
	return bblocks;
}

void basic_block(cfg_bb_t *bb, const cfg_ix_t *succb,
	const cfg_ix_t *succe, tcmd_t *cmd, tagver_t *use)
{
	const size_t n = static_cast<size_t>(succe - succb);
	cfg_ix_t *s = new cfg_ix_t[n];
	memcpy(s, succb, n * sizeof(cfg_ix_t));

	bb->succb = s;
	bb->succe = s + n;
	bb->cmd = cmd;
	bb->use = use;
}

// find immediate successors of the given bblock
void successors(const dfa_t &dfa, const cfg_ix_t *arc2bb, bool *been,
	cfg_ix_t *&succ, size_t x)
{
	if (x == dfa_t::NIL || been[x]) return;
	been[x] = true;

	const size_t
		nsym = dfa.nchars,
		*a = dfa.states[x]->arcs;
	const cfg_ix_t *a2b = &arc2bb[x * (nsym + 1)];

	for (size_t c = 0; c < nsym; ++c) {
		const cfg_ix_t b = a2b[c];
		if (b != 0) {
			*succ++ = b;
		} else {
			successors(dfa, arc2bb, been, succ, a[c]);
		}
	}

	const cfg_ix_t b = a2b[nsym];
	if (b != 0) {
		*succ++ = b;
	}
}

// find all bblocks reachable from this one by following
// non-accepting DFA paths: this is the set of bblocks affected
// by liveness of fallback tags
void fallback(const dfa_t &dfa, const cfg_ix_t *arc2bb, bool *been,
	cfg_ix_t *&succ, size_t x)
{
	if (x == dfa_t::NIL || been[x]) return;
	been[x] = true;

	const size_t
		nsym = dfa.nchars,
		*a = dfa.states[x]->arcs;
	const cfg_ix_t *a2b = &arc2bb[x * (nsym + 1)];

	for (size_t c = 0; c < nsym; ++c) {
		const size_t y = a[c];
		if (y != dfa_t::NIL && dfa.states[y]->fallthru) {
			const cfg_ix_t b = a2b[c];
			if (b != 0) {
				*succ++ = b;
			}
			fallback(dfa, arc2bb, been, succ, y);
		}
	}
}

cfg_t::~cfg_t()
{
	cfg_bb_t *b = bblocks, *e = b + nbblock;

	delete b->cmd;

	for (; b < e; ++b) {
		delete[] b->succb;
	}

	delete[] bblocks;
}

} // namespace re2c

