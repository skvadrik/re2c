#include <string.h>
#include <algorithm>
#include <new>
#include <valarray>
#include <vector>

#include "src/cfg/cfg.h"
#include "src/dfa/dfa.h"
#include "src/util/allocate.h"

namespace re2c
{

struct Rule;
struct tcmd_t;

static void map_arcs_to_bblocks(const dfa_t &dfa, cfg_ix_t *arc2bb, cfg_ix_t &nbbarc, cfg_ix_t &nbbfin, cfg_ix_t &nbbfall);
static cfg_bb_t *create_bblocks(dfa_t &dfa, const cfg_ix_t *arc2bb, cfg_ix_t nbbfin, cfg_ix_t nbbfall);
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
        tcmd_t **c = dfa.states[i]->tcmd, **f = c + nsym;
        for (; c < f; ++c) {
            *arc2bb++ = *c == NULL ? 0 : nbb++;
        }
    }
    nbbarc = nbb;

    // bblock for final tagged epsilon-transition
    for (size_t i = 0; i < nstate; ++i) {
        tcmd_t *f = dfa.states[i]->tcmd[nsym];
        *arc2bb++ = f == NULL ? 0 : nbb++;
    }
    nbbfin = nbb;

    // bblock for fallback tagged epsilon-transition
    for (size_t i = 0; i < nstate; ++i) {
        const dfa_state_t *s = dfa.states[i];
        // (check final tags: fallback tags may be empty)
        *arc2bb++ = s->fallback && s->tcmd[nsym] ? nbb++ : 0;
    }
    nbbfall = nbb;
}

cfg_bb_t *create_bblocks(dfa_t &dfa, const cfg_ix_t *arc2bb,
    cfg_ix_t nbbfin, cfg_ix_t nbbfall)
{
    const size_t
        nstate = dfa.states.size(),
        nsym = dfa.nchars;
    const cfg_ix_t *a2b = arc2bb;
    cfg_ix_t *succb = new cfg_ix_t[nbbfin], *succe;
    bool *been = new bool[nstate];

    cfg_bb_t *bblocks = allocate<cfg_bb_t>(nbbfall), *b = bblocks;

    // root bblock
    std::fill(been, been + nstate, false);
    successors(dfa, arc2bb, been, succe = succb, 0);
    new(b++) cfg_bb_t(succb, succe, dfa.tcmd0, NULL);

    // transition bblocks
    for (size_t i = 0; i < nstate; ++i) {
        const dfa_state_t *s = dfa.states[i];
        for (size_t c = 0; c < nsym; ++c) {
            if (*a2b++ != 0) {
                std::fill(been, been + nstate, false);
                successors(dfa, arc2bb, been, succe = succb, s->arcs[c]);
                new(b++) cfg_bb_t(succb, succe, s->tcmd[c], NULL);
            }
        }
    }

    // final bblocks
    for (size_t i = 0; i < nstate; ++i) {
        if (*a2b++ != 0) {
            const dfa_state_t *s = dfa.states[i];
            new(b++) cfg_bb_t(NULL, NULL, s->tcmd[nsym], &dfa.rules[s->rule]);
        }
    }

    // fallback bblocks
    for (size_t i = 0; i < nstate; ++i) {
        if (*a2b++ != 0) {
            const dfa_state_t *s = dfa.states[i];
            std::fill(been, been + nstate, false);
            fallback(dfa, arc2bb, been, succe = succb, i);
            new(b++) cfg_bb_t(succb, succe, s->tcmd[nsym + 1], &dfa.rules[s->rule]);
        }
    }

    delete[] succb;
    delete[] been;
    return bblocks;
}

cfg_bb_t::cfg_bb_t(const cfg_ix_t *sb, const cfg_ix_t *se,
    tcmd_t *&c, const Rule *r)
    : succb(NULL)
    , succe(NULL)
    , cmd(c)
    , rule(r)
{
    const size_t n = static_cast<size_t>(se - sb);
    succb = new cfg_ix_t[n];
    if (n > 0) memcpy(succb, sb, n * sizeof(cfg_ix_t));
    succe = succb + n;
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

    operator delete(bblocks);
}

} // namespace re2c

