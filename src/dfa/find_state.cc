#include <string.h>
#include <algorithm>
#include <memory>
#include <vector>

#include "src/debug/debug.h"
#include "src/dfa/determinization.h"
#include "src/dfa/dfa.h"
#include "src/dfa/tag_history.h"
#include "src/dfa/tcmd.h"
#include "src/nfa/nfa.h"
#include "src/options/opt.h"
#include "src/regexp/tag.h"
#include "src/regexp/rule.h"
#include "src/util/check.h"
#include "src/util/hash32.h"

namespace re2c {

// note [mapping ignores items with lookahead tags]
//
// Consider two items X and Y being mapped. If tag T belongs to lookahead tags of item X, then all
// the outgoing transitions from item X update T. Which means that it doesn't matter which
// particular version T has in X: any version will be overwritten by any outgoing transition.
//
// Note that lookahead tags are identical for both items X and Y, because we only try to map TDFA
// states with identical lookahead tags.

// note [save(X), copy(Y,X) optimization]
//
// save(X) command followed by a copy(Y,X) command can be optimized to save(Y). This helps to reduce
// the number commands and versions (new version X is gone), but what is more important, it allows
// one to put copy commands in front of save commands. This order is necessary when it comes to the
// fallback commands.
//
// Note that in case of injective mapping there may be more than one copy command matching the same
// save command: save(X), copy(Y,X), copy(Z,X). In this case save command must be replicated for
// each copy command: save(Y), save(Z).
//
// For each save(X) command there must be at least one copy(Y,X) command (exactly one case of
// a bijective mapping). This is because X version in save(X) command must be a new version which
// cannot occur in the older TDFA state. Thus all save commands are transformed (maybe replicated)
// by copy commands, and some copy commands are erased by save commands.
//
// This optimization is applied after checking priority violation, so it cannot affect the check.

// note [bijective mappings]
//
// Suppose we have just constructed a new TDFA state Y and want to map it to an existing TDFA state
// X. States must have identical sets of TNFA substates and identical sets of lookahead tags for
// each substate. Furthermore, there must be bijective mapping between versions of X and Y and this
// mapping must preserve version order (respect priorities).
//
// Bijective mappings have a nice property: there is only one possible state X to which Y can be
// mapped. Indeed, if there was another state Z that can be bijectively mapped to Y preserving
// priorities, then Z itself can be mapped to X: both (1) and (2) are symmetrical in case of a
// bijection, and the relation is transitive. So the existence of Z is a contradiction.
//
// In principle, non-bijective mappings are also possible if the new state is less versatile than
// the old one (surjection from X to Y). However, non-bijective mappings lack the 'unique
// counterpart' property and need more complex analysis (and are not so useful after all), so we
// drop them.

template<typename ctx_t>
struct kernel_eq_t {
    ctx_t& ctx;
    bool operator()(const kernel_t* x, const kernel_t* y) const;
};

template<typename ctx_t, bool regless>
struct kernel_map_t {
    ctx_t& ctx;
    bool operator()(const kernel_t* x, const kernel_t* y);
};

template<typename ctx_t> static tcmd_t* final_actions(ctx_t&, const clos_t&);
template<typename ctx_t> static void reserve_buffers(ctx_t&);
template<typename ctx_t> static bool equal_lookahead_tags(ctx_t&, const kernel_t*, const kernel_t*);
template<typename ctx_t> static void unwind(const typename ctx_t::history_t&, tag_path_t&, hidx_t);
static kernel_t* make_new_kernel(size_t, IrAllocator&);
static kernel_t* make_kernel_copy(const kernel_t*, IrAllocator&);
static void copy_to_buffer(const closure_t&, const prectable_t*, kernel_t*);
static void group_by_tag(tag_path_t&, tag_path_t&, std::vector<uint32_t>&);
static uint32_t hash_kernel(const kernel_t*);

// explicit instantiation for context types
template void find_state<pdetctx_t>(pdetctx_t& ctx);
template void find_state<ldetctx_t>(ldetctx_t& ctx);
// explicit instantiation for registerless TDFA (in libre2c)
template bool do_find_state<pdetctx_t, true>(pdetctx_t&);
template bool do_find_state<ldetctx_t, true>(ldetctx_t&);

template<typename ctx_t>
void find_state(ctx_t& ctx) {
    Tdfa& dfa = ctx.dfa;

    // find or add the new state in the existing set of states
    const bool is_new = do_find_state<ctx_t, false>(ctx);

    if (is_new) {
        // create new DFA state
        TdfaState* t = new TdfaState(dfa.nchars);
        dfa.states.push_back(t);

        // check if the new state is final (see note [at most one final item per closure])
        cclositer_t f = std::find_if(ctx.state.begin(), ctx.state.end(), clos_t::fin);
        if (f != ctx.state.end()) {
            t->rule = f->state->rule;
            t->tcmd[dfa.nchars] = final_actions(ctx, *f);
        }
    }

    if (ctx.origin != Tdfa::NIL) {
        TdfaState* s = dfa.states[ctx.origin];
        s->arcs[ctx.symbol] = ctx.target;
        s->tcmd[ctx.symbol] = ctx.actions;
    }

    DDUMP_DFA_RAW(ctx, is_new);
    DDUMP_DFA_TREE(is_new);
}

template<typename ctx_t, bool regless>
bool do_find_state(ctx_t& ctx) {
    kernels_t& kernels = ctx.kernels;
    const closure_t& closure = ctx.state;

    // empty closure corresponds to default state
    if (closure.size() == 0) {
        ctx.target = Tdfa::NIL;
        ctx.actions = nullptr;
        return false;
    }

    // resize buffer if closure is too large
    reserve_buffers(ctx);
    kernel_t* k = ctx.buffers.kernel;

    // copy closure to buffer kernel
    copy_to_buffer(closure, ctx.newprectbl, k);

    // hash "static" part of the kernel
    const uint32_t hash = hash_kernel(k);

    // try to find identical kernel
    kernel_eq_t<ctx_t> cmp_eq = {ctx};
    ctx.target = kernels.find_with(hash, k, cmp_eq);
    if (ctx.target != kernels_t::NIL) return false;

    // else try to find mappable kernel (see note [bijective mappings])
    kernel_map_t<ctx_t, regless> cmp_map = {ctx};
    ctx.target = kernels.find_with(hash, k, cmp_map);
    if (ctx.target != kernels_t::NIL) return false;

    // otherwise add new kernel
    kernel_t* kcopy = make_kernel_copy(k, ctx.ir_alc);
    ctx.target = kernels.push(hash, kcopy);
    ctx.kernels_total += k->size;
    return true;
}

template<typename ctx_t>
tcmd_t* final_actions(ctx_t& ctx, const clos_t& fin) {
    const Rule& rule = ctx.rules[fin.state->rule];
    const tagver_t* vers = ctx.tagvertbl[fin.tvers];
    const hidx_t look = fin.thist;
    const typename ctx_t::history_t& thist = ctx.history;
    tcpool_t& tcpool = ctx.dfa.tcpool;
    tcmd_t* copy = nullptr, *save = nullptr, **p;

    for (size_t t = rule.ltag; t < rule.htag; ++t) {
        const Tag& tag = ctx.tags[t];
        if (fixed(tag)) continue;

        const tagver_t v = abs(vers[t]), l = last(thist, look, t);
        tagver_t& f = ctx.dfa.finvers[t];
        if (l == TAGVER_ZERO) {
            copy = tcpool.make_copy(copy, f, v);
        } else if (history(tag)) {
            save = tcpool.make_add(save, f, v, thist, look, t);
        } else {
            save = tcpool.make_set(save, f, l);
        }
    }

    // join 'copy' and 'save' commands
    for (p = &copy; *p; p = &(*p)->next);
    *p = save;

    return copy;
}

kernel_buffers_t::kernel_buffers_t()
    : maxsize(0),
      kernel(nullptr),
      cap(0),
      max(0),
      memory(nullptr),
      x2y(nullptr),
      y2x(nullptr),
      x2t(nullptr),
      indegree(nullptr),
      backup_actions(nullptr) {}

kernel_t* make_new_kernel(size_t size, IrAllocator& alc) {
    kernel_t* k = alc.alloct<kernel_t>(1);
    k->size = size;
    k->state = alc.alloct<TnfaState*>(size);
    k->thist = alc.alloct<hidx_t>(size);
    k->prectbl = nullptr;
    k->tvers = alc.alloct<uint32_t>(size);
    return k;
}

kernel_t* make_kernel_copy(const kernel_t* kernel, IrAllocator& alc) {
    const size_t n = kernel->size;

    kernel_t* k = make_new_kernel(n, alc);

    memcpy(k->state, kernel->state, n * sizeof(void*));
    memcpy(k->thist, kernel->thist, n * sizeof(hidx_t));

    prectable_t* ptbl = nullptr;
    if (kernel->prectbl) {
        ptbl = alc.alloct<prectable_t>(n * n);
        memcpy(ptbl, kernel->prectbl, n * n * sizeof(prectable_t));
    }
    k->prectbl = ptbl;

    memcpy(k->tvers, kernel->tvers, n * sizeof(uint32_t));

    return k;
}

uint32_t hash_kernel(const kernel_t* kernel) {
    const size_t n = kernel->size;

    // seed
    uint32_t h = static_cast<uint32_t>(n);

    // TNFA states
    h = hash32(h, kernel->state, n * sizeof(void*));

    // precedence table
    if (kernel->prectbl) {
        h = hash32(h, kernel->prectbl, n * n * sizeof(prectable_t));
    }

    return h;
}

void copy_to_buffer(const closure_t& closure, const prectable_t* prectbl, kernel_t* buffer) {
    const size_t n = closure.size();
    buffer->size = n;
    buffer->prectbl = prectbl;
    for (size_t i = 0; i < n; ++i) {
        const clos_t& c = closure[i];
        buffer->state[i] = c.state;
        buffer->tvers[i] = c.tvers;
        buffer->thist[i] = c.thist;
    }
}

template<typename ctx_t>
void reserve_buffers(ctx_t& ctx) {
    kernel_buffers_t& kbufs = ctx.buffers;
    IrAllocator& alc = ctx.ir_alc;
    const tagver_t maxver = ctx.dfa.maxtagver;
    const size_t nkern = ctx.state.size();

    if (kbufs.maxsize < nkern) {
        kbufs.maxsize = nkern * 2; // in advance
        kbufs.kernel = make_new_kernel(kbufs.maxsize, alc);
    }

    // +1 to ensure max tag version is not forgotten in loops
    kbufs.max = maxver + 1;
    if (kbufs.cap < kbufs.max) {
        kbufs.cap = kbufs.max * 2; // in advance

        const size_t n = static_cast<size_t>(kbufs.cap);
        kbufs.indegree = alc.alloct<uint32_t>(n);

        kbufs.x2y = alc.alloct<tagver_t>(n);
        kbufs.y2x = alc.alloct<tagver_t>(n);
        kbufs.x2t = alc.alloct<size_t>(n);
        kbufs.backup_actions = alc.alloct<tcmd_t>(n);
    }
}

template<typename ctx_t>
bool equal_lookahead_tags(ctx_t& ctx, const kernel_t* x, const kernel_t* y) {
    DCHECK(x->size == y->size);

    if (memcmp(x->thist, y->thist, x->size * sizeof(hidx_t)) == 0) {
        return true;
    }

    typename ctx_t::history_t& thist = ctx.history;
    tag_path_t& p1 = ctx.path1, &p2 = ctx.path2, &p3 = ctx.path3;
    std::vector<uint32_t>& count = ctx.tagcount;

    for (size_t i = 0; i < x->size; ++i) {
        const hidx_t xl = x->thist[i], yl = y->thist[i];

        if (xl == yl) continue;

        unwind<ctx_t>(thist, p1, xl);
        unwind<ctx_t>(thist, p2, yl);

        if (p1.size() != p2.size()) return false;

        group_by_tag(p1, p3, count);
        group_by_tag(p2, p3, count);

        if (p1 != p2) return false;
    }

    return true;
}

void group_by_tag(tag_path_t& path, tag_path_t& buf, std::vector<uint32_t>& count) {
    // Counting sort with tag index as the key (it should preserve relative order of elements with
    // the same tag).

    const size_t clen = count.size(), plen = path.size();
    std::fill(count.begin(), count.end(), 0);
    buf.resize(plen);

    for (size_t i = 0; i < plen; ++i) {
        ++count[path[i].idx];
    }

    for (size_t i = 1; i < clen; ++i) {
        count[i] += count[i - 1];
    }

    for (size_t i = plen; i --> 0; ) {
        buf[--count[path[i].idx]] = path[i];
    }

    path.swap(buf);
}

template<typename ctx_t>
void unwind(const typename ctx_t::history_t& hist, tag_path_t& path, hidx_t idx) {
    // Simple tags need only the last value, so in principle we could increase the chance of mapping
    // by recording only the last value. But this would complicate unwind procedure quite a bit, and
    // the cases when it makes any difference are rare.
    path.clear();
    for (; idx != HROOT; ) {
        const typename ctx_t::history_t::node_t& n = hist.node(idx);
        path.push_back(n.info);
        idx = n.pred;
    }
}

template<typename ctx_t>
bool kernel_eq_t<ctx_t>::operator()(const kernel_t* x, const kernel_t* y) const {
    // Check that the kernel sizes, TNFA states, tags versions, lookahead tags and precedence table
    // coincide.
    const size_t n = x->size;
    return n == y->size
            && memcmp(x->state, y->state, n * sizeof(void*)) == 0
            && (!x->prectbl || memcmp(x->prectbl, y->prectbl, n * n * sizeof(prectable_t)) == 0)
            && memcmp(x->tvers, y->tvers, n * sizeof(uint32_t)) == 0
            && equal_lookahead_tags(ctx, x, y);
}

template<typename ctx_t, bool regless>
bool kernel_map_t<ctx_t, regless>::operator()(const kernel_t* x, const kernel_t* y) {
    // Check that the kernel sizes, NFA states lookahead tags and precedence table coincide
    // (versions might differ).
    const size_t n = x->size;
    const bool compatible = n == y->size
            && memcmp(x->state, y->state, n * sizeof(void*)) == 0
            && (!x->prectbl || memcmp(x->prectbl, y->prectbl, n * n * sizeof(prectable_t)) == 0)
            && equal_lookahead_tags(ctx, x, y);

    if (!compatible) return false;

    const std::vector<Tag>& tags = ctx.tags;
    const size_t ntag = tags.size();
    kernel_buffers_t& bufs = ctx.buffers;
    tagver_t* x2y = bufs.x2y, *y2x = bufs.y2x, max = bufs.max;
    size_t* x2t = bufs.x2t;

    // Map tag versions of one kernel to that of another and check that lookahead tags coincide.
    std::fill(x2y, x2y + max, TAGVER_ZERO);
    std::fill(y2x, y2x + max, TAGVER_ZERO);
    for (size_t i = 0; i < n; ++i) {
        const tagver_t *xvs = ctx.tagvertbl[x->tvers[i]];
        const tagver_t *yvs = ctx.tagvertbl[y->tvers[i]];
        const hidx_t xl = x->thist[i];

        for (size_t t = 0; t < ntag; ++t) {
            // see note [mapping ignores items with lookahead tags]
            if (!history(tags[t]) && last(ctx.history, xl, t) != TAGVER_ZERO) continue;

            const tagver_t xv = xvs[t], yv = yvs[t];
            tagver_t& xv0 = y2x[yv], &yv0 = x2y[xv];

            if (yv0 == TAGVER_ZERO && xv0 == TAGVER_ZERO) {
                xv0 = xv;
                yv0 = yv;
                x2t[xv] = t;
            } else if (yv != yv0 || xv != xv0) {
                return false;
            }
        }
    }

    // Registerless automaton does not need register operations (actions).
    if (regless) return true;

    // We have a bijective mapping; now try to create list of commands.
    tcmd_t** pacts = &ctx.actions, *a, **pa, *copy = nullptr;
    tcmd_t* b1 = bufs.backup_actions, *b2 = b1;

    // Backup 'save' commands: if topsort finds cycles, this mapping will be rejected and we'll have
    // to revert all  changes.
    for (b2->next = a = *pacts; a; a = a->next) {
        *++b2 = *a;
    }

    // Fix LHS of 'save' commands to reuse old version (see note [save(X), copy(Y,X) optimization]).
    for (a = *pacts; a; a = a->next) {
        const tagver_t yv = a->lhs, xv = y2x[yv];
        a->lhs = abs(xv);
        y2x[yv] = x2y[xv] = TAGVER_ZERO;
    }

    // Create 'copy' commands.
    for (tagver_t xv = 0; xv < max; ++xv) {
        const tagver_t yv = x2y[xv], axv = abs(xv), ayv = abs(yv);
        if (yv != TAGVER_ZERO && xv != yv && !fixed(tags[x2t[xv]])) {
            DCHECK(axv != ayv);
            copy = ctx.dfa.tcpool.make_copy(copy, axv, ayv);
        }
    }

    // Join 'copy' and 'save' commands.
    for (pa = &copy; (a = *pa); pa = &a->next);
    *pa = *pacts;
    *pacts = copy;

    // See note [topological ordering of copy commands].
    tcmd_t** cycle = tcmd_t::topsort(pacts, nullptr, bufs.indegree);

    // In the case of cycles restore 'save' commands and fail.
    if (cycle) {
        for (*pacts = a = b1->next; a; a = a->next) {
            *a = *++b1;
        }
    }

    return cycle == nullptr;
}

} // namespace re2c
