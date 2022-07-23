#include <string.h>
#include <algorithm>
#include <new>
#include <vector>

#include "src/cfg/cfg.h"
#include "src/dfa/dfa.h"
#include "src/regexp/rule.h"
#include "src/util/check.h"
#include "src/util/containers.h"

namespace re2c {

struct tcmd_t;

cfg_context_t::cfg_context_t(Tdfa& dfa)
    : dfa(dfa),
      nstate(dfa.states.size()),
      nsym(dfa.nchars),
      trans2bb(new cfg_ix_t[nstate * (nsym + 2)]),
      final2bb(trans2bb + nstate * nsym),
      fback2bb(final2bb + nstate),
      state_mark(new uint32_t[nstate * (nsym + 2)]),
      trans_mark(state_mark + nstate),
      final_mark(trans_mark + nstate * nsym),
      mark(0),
      succb(nullptr),
      succe(nullptr),
      worklist() {
    memset(state_mark, 0, nstate * (nsym + 2) * sizeof(uint32_t));
    worklist.reserve(nstate);
}

cfg_context_t::~cfg_context_t() {
    delete[] trans2bb;
    delete[] state_mark;
    delete[] succb;
}

static void successors(cfg_context_t& ctx, size_t x, bool self);
static void fallback(cfg_context_t& ctx, size_t x);

cfg_t::cfg_t(Tdfa& a)
    : dfa(a),
      bblocks(nullptr),
      nbbarc(0),
      nbbfin(0),
      nbbfall(0),
      tcmd0(nullptr) {
    cfg_context_t ctx(dfa);
    map_actions_to_bblocks(ctx);
    create_bblocks(ctx);
}

void cfg_t::map_actions_to_bblocks(cfg_context_t& ctx) {
    // root bblock for initial tagged epsilon-transition
    cfg_ix_t nbb = 1;

    // bblocks for tagged transitions
    for (size_t i = 0; i < ctx.nstate; ++i) {
        cfg_ix_t* trans2bb = &ctx.trans2bb[i * ctx.nsym];
        tcmd_t** cmd = dfa.states[i]->tcmd;
        for (size_t c = 0; c < ctx.nsym; ++c) {
            trans2bb[c] = cmd[c] == nullptr ? 0 : nbb++;
        }
    }
    nbbarc = nbb;

    // bblock for final tagged epsilon-transition
    for (size_t i = 0; i < ctx.nstate; ++i) {
        TdfaState* s = dfa.states[i];
        ctx.final2bb[i] = (s->rule != Rule::NONE && s->tcmd[ctx.nsym]) ? nbb++ : 0;
    }
    nbbfin = nbb;

    // bblock for fallback tagged epsilon-transition
    for (size_t i = 0; i < ctx.nstate; ++i) {
        const TdfaState* s = dfa.states[i];
        // (check final tags: fallback tags may be empty)
        ctx.fback2bb[i] = s->fallback && s->tcmd[ctx.nsym] ? nbb++ : 0;
    }
    nbbfall = nbb;
}

void cfg_t::create_bblocks(cfg_context_t& ctx) {
    ctx.succb = new cfg_ix_t[nbbfin];
    bblocks = allocate<cfg_bb_t>(nbbfall);
    cfg_bb_t* b = bblocks;

    // root bblock
    successors(ctx, 0, true /*self*/);
    new(b++) cfg_bb_t(ctx.succb, ctx.succe, tcmd0, nullptr);

    // transition bblocks
    for (size_t i = 0; i < ctx.nstate; ++i) {
        const TdfaState* s = dfa.states[i];
        const cfg_ix_t* trans2bb = &ctx.trans2bb[i * ctx.nsym];
        for (size_t c = 0; c < ctx.nsym; ++c) {
            if (trans2bb[c]) {
                successors(ctx, s->arcs[c], true /*self*/);
                new(b++) cfg_bb_t(ctx.succb, ctx.succe, s->tcmd[c], nullptr);
            }
        }
    }

    // final bblocks
    for (size_t i = 0; i < ctx.nstate; ++i) {
        if (ctx.final2bb[i]) {
            const TdfaState* s = dfa.states[i];
            new(b++) cfg_bb_t(nullptr, nullptr, s->tcmd[ctx.nsym], &dfa.rules[s->rule]);
        }
    }

    // fallback bblocks
    for (size_t i = 0; i < ctx.nstate; ++i) {
        if (ctx.fback2bb[i]) {
            fallback(ctx, i);
            const TdfaState* s = dfa.states[i];
            new(b++) cfg_bb_t(ctx.succb, ctx.succe, s->tcmd[ctx.nsym + 1], &dfa.rules[s->rule]);
        }
    }
}

cfg_bb_t::cfg_bb_t(const cfg_ix_t* sb, const cfg_ix_t* se, tcmd_t*& c, const Rule* r)
    : succb(nullptr),
      succe(nullptr),
      cmd(c),
      rule(r) {
    const size_t n = static_cast<size_t>(se - sb);
    succb = new cfg_ix_t[n];
    if (n > 0) memcpy(succb, sb, n * sizeof(cfg_ix_t));
    succe = succb + n;
}

// find immediate successors of the given bblock
void successors(cfg_context_t& ctx, size_t x0, bool self) {
    DCHECK(x0 != Tdfa::NIL);
    DCHECK(ctx.mark < cfg_context_t::MAX_MARK);
    ++ctx.mark;
    ctx.succe = ctx.succb;

    // if we start from an incoming transition, process the state itself
    if (self) {
        ctx.state_mark[x0] = ctx.mark;
    }

    ctx.worklist.push_back(x0);

    // DFS on the graph induced by tagged DFA states and transitions
    while (!ctx.worklist.empty()) {
        const size_t x = ctx.worklist.back();
        ctx.worklist.pop_back();

        const size_t* a = ctx.dfa.states[x]->arcs;
        const cfg_ix_t* trans2bb = &ctx.trans2bb[ctx.nsym * x];
        uint32_t* trans_mark = &ctx.trans_mark[ctx.nsym * x];

        for (size_t c = 0; c < ctx.nsym; ++c) {
            const size_t y = a[c];

            // if already visited this transition, stop
            if (trans_mark[c] >= ctx.mark) {
                continue;
            }
            trans_mark[c] = ctx.mark;

            // if reached a tagged transition, record and stop
            if (trans2bb[c]) {
                *ctx.succe++ = trans2bb[c];
                continue;
            }

            // if already visited the to-state, stop
            if (y == Tdfa::NIL || ctx.state_mark[y] >= ctx.mark) {
                continue;
            }
            ctx.state_mark[y] = ctx.mark;

            // else continue search for successors
            ctx.worklist.push_back(y);
        }

        // if reached a non-visited final state, record
        if (ctx.final_mark[x] < ctx.mark) {
            ctx.final_mark[x] = ctx.mark;

            if (ctx.final2bb[x]) {
                *ctx.succe++ = ctx.final2bb[x];
            }
        }
    }
}

// find all bblocks reachable from this one by following non-accepting DFA
// paths: this is the set of bblocks affected by liveness of fallback tags
void fallback(cfg_context_t& ctx, size_t x0) {
    DCHECK(x0 != Tdfa::NIL);
    DCHECK(ctx.mark < cfg_context_t::MAX_MARK);
    ++ctx.mark;
    ctx.succe = ctx.succb;

    ctx.worklist.push_back(x0);

    // DFS on the graph induced by tagged DFA states and transitions
    while (!ctx.worklist.empty()) {
        const size_t x = ctx.worklist.back();
        ctx.worklist.pop_back();

        const size_t* a = ctx.dfa.states[x]->arcs;
        const cfg_ix_t* trans2bb = &ctx.trans2bb[ctx.nsym * x];
        uint32_t* trans_mark = &ctx.trans_mark[ctx.nsym * x];

        for (size_t c = 0; c < ctx.nsym; ++c) {
            const size_t y = a[c];

            // if the next state is not fallthrough, stop
            if (y == Tdfa::NIL || !ctx.dfa.states[y]->fallthru) {
                continue;
            }

            // if already visited this transition, stop
            if (trans_mark[c] >= ctx.mark) {
                continue;
            }
            trans_mark[c] = ctx.mark;

            // if reached a tagged transition, record
            if (trans2bb[c]) {
                *ctx.succe++ = trans2bb[c];
            }

            // if already visited the to-state, stop
            if (ctx.state_mark[y] >= ctx.mark) {
                continue;
            }
            ctx.state_mark[y] = ctx.mark;

            // continue propagating fallback states
            ctx.worklist.push_back(y);
        }
    }
}

cfg_t::~cfg_t() {
    cfg_bb_t* b = bblocks, *e = b + nbbfall;
    for (; b < e; ++b) {
        delete[] b->succb;
    }

    operator delete(bblocks);
}

// C++11 requres outer decl for ODR-used static constexpr data members (not needed in C++17).
constexpr uint32_t cfg_context_t::MAX_MARK;

} // namespace re2c

