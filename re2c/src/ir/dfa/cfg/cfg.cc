#include <string.h>

#include "src/ir/dfa/cfg/cfg.h"

namespace re2c
{

static void map_arcs_to_bblocks(const dfa_t &dfa, cfg_ix_t *arc2bb, cfg_ix_t &nbbarc, cfg_ix_t &nbbfin, cfg_ix_t &nbbfall);
static cfg_bb_t *create_bblocks(const dfa_t &dfa, const cfg_ix_t *arc2bb, cfg_ix_t nbbfin, cfg_ix_t nbbfall);
static void basic_block(cfg_bb_t *bb, const cfg_ix_t *succb, const cfg_ix_t *succe, tcmd_t *cmd, const Rule *rule);
static void successors(const dfa_t &dfa, const cfg_ix_t *arc2bb, bool *been, cfg_ix_t *&succ, size_t x);
static void fallback(const dfa_t &dfa, const cfg_ix_t *arc2bb, bool *been, cfg_ix_t *&succ, size_t x);

cfg_t::cfg_t(dfa_t &a)
	: dfa(a)
	, bblocks(NULL)
	, nbbarc(0)
	, nbbfin(0)
	, nbbfall(0)
{
	const size_t
		nstate = dfa.states.size(),
		nsym = dfa.nchars;
	cfg_ix_t *arc2bb = new cfg_ix_t[nstate * (nsym + 2)];

	map_arcs_to_bblocks(dfa, arc2bb, nbbarc, nbbfin, nbbfall);
	bblocks = create_bblocks(dfa, arc2bb, nbbfin, nbbfall);

	delete[] arc2bb;
}

void map_arcs_to_bblocks(const dfa_t &dfa, cfg_ix_t *arc2bb,
	cfg_ix_t &nbbarc, cfg_ix_t &nbbfin, cfg_ix_t &nbbfall)
{
	const size_t
		nstate = dfa.states.size(),
		nsym = dfa.nchars;

	// root bblock for initial tagged epsilon-transition
	cfg_ix_t nbb = 1;

	// bblocks for tagged transitions
	for (size_t i = 0; i < nstate; ++i) {
		const tcmd_t *c = dfa.states[i]->tcmd, *f = c + nsym;
		for (; c < f; ++c) {
			*arc2bb++ = c->empty() ? 0 : nbb++;
		}
	}
	nbbarc = nbb;

	// bblock for final tagged epsilon-transition
	for (size_t i = 0; i < nstate; ++i) {
		const tcmd_t &f = dfa.states[i]->tcmd[nsym];
		*arc2bb++ = f.empty() ? 0 : nbb++;
	}
	nbbfin = nbb;

	// bblock for fallback tagged epsilon-transition
	for (size_t i = 0; i < nstate; ++i) {
		const dfa_state_t *s = dfa.states[i];
		// (check final tags: fallback tags may be empty)
		*arc2bb++ = s->fallback && !s->tcmd[nsym].empty() ? nbb++ : 0;
	}
	nbbfall = nbb;
}

cfg_bb_t *create_bblocks(const dfa_t &dfa, const cfg_ix_t *arc2bb,
	cfg_ix_t nbbfin, cfg_ix_t nbbfall)
{
	const size_t
		nstate = dfa.states.size(),
		nsym = dfa.nchars;
	const cfg_ix_t *a2b = arc2bb;
	cfg_ix_t *succb = new cfg_ix_t[nbbfin], *succe;
	bool *been = new bool[nstate];

	cfg_bb_t *bblocks = new cfg_bb_t[nbbfall], *b = bblocks;

	// root bblock
	std::fill(been, been + nstate, false);
	successors(dfa, arc2bb, been, succe = succb, 0);
	basic_block(b++, succb, succe, dfa.tcmd0, NULL);

	// transition bblocks
	for (size_t i = 0; i < nstate; ++i) {
		const dfa_state_t *s = dfa.states[i];
		for (size_t c = 0; c < nsym; ++c) {
			if (*a2b++ != 0) {
				std::fill(been, been + nstate, false);
				successors(dfa, arc2bb, been, succe = succb, s->arcs[c]);
				basic_block(b++, succb, succe, &s->tcmd[c], NULL);
			}
		}
	}

	// final bblocks
	for (size_t i = 0; i < nstate; ++i) {
		if (*a2b++ != 0) {
			const dfa_state_t *s = dfa.states[i];
			basic_block(b++, NULL, NULL, &s->tcmd[nsym], &dfa.rules[s->rule]);
		}
	}

	// fallback bblocks
	for (size_t i = 0; i < nstate; ++i) {
		if (*a2b++ != 0) {
			const dfa_state_t *s = dfa.states[i];
			std::fill(been, been + nstate, false);
			fallback(dfa, arc2bb, been, succe = succb, i);
			basic_block(b++, succb, succe, &s->tcmd[nsym + 1], &dfa.rules[s->rule]);
		}
	}

	delete[] succb;
	delete[] been;
	return bblocks;
}

void basic_block(cfg_bb_t *bb, const cfg_ix_t *succb,
	const cfg_ix_t *succe, tcmd_t *cmd, const Rule *rule)
{
	const size_t n = static_cast<size_t>(succe - succb);
	cfg_ix_t *s = new cfg_ix_t[n];
	memcpy(s, succb, n * sizeof(cfg_ix_t));

	bb->succb = s;
	bb->succe = s + n;
	bb->cmd = cmd;
	bb->rule = rule;
}

// find immediate successors of the given bblock
void successors(const dfa_t &dfa, const cfg_ix_t *arc2bb, bool *been,
	cfg_ix_t *&succ, size_t x)
{
	if (x == dfa_t::NIL || been[x]) return;
	been[x] = true;

	const size_t
		nstate = dfa.states.size(),
		nsym = dfa.nchars,
		*a = dfa.states[x]->arcs;
	const cfg_ix_t *a2b = &arc2bb[x * nsym];

	for (size_t c = 0; c < nsym; ++c) {
		const cfg_ix_t b = a2b[c];
		if (b != 0) {
			*succ++ = b;
		} else {
			successors(dfa, arc2bb, been, succ, a[c]);
		}
	}

	const cfg_ix_t f = arc2bb[nstate * nsym + x];
	if (f != 0) {
		*succ++ = f;
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
	const cfg_ix_t *a2b = &arc2bb[x * nsym];

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
	cfg_bb_t *b = bblocks, *e = b + nbbfall;
	for (; b < e; ++b) {
		delete[] b->succb;
	}

	delete[] bblocks;
}

} // namespace re2c

