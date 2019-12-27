#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <memory>
#include <valarray>
#include <vector>

#include "src/debug/debug.h"
#include "src/dfa/determinization.h"
#include "src/dfa/dfa.h"
#include "src/dfa/tag_history.h"
#include "src/dfa/tcmd.h"
#include "src/nfa/nfa.h"
#include "src/regexp/tag.h"
#include "src/regexp/rule.h"
#include "src/util/hash32.h"


namespace re2c {

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


/* note [bijective mappings]
 *
 * Suppose we have just constructed a new DFA state Y and want to map it
 * to an existing DFA state X. States must have identical sets of NFA
 * substates and identical sets of lookahead tags for each substate.
 * Furthermore, there must be bijective mapping between versions of X and Y
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

template<typename ctx_t, bool stadfa>
struct kernel_eq_t
{
    ctx_t &ctx;
    bool operator()(const kernel_t *x, const kernel_t *y) const;
};

template<typename ctx_t>
struct kernel_map_t
{
    ctx_t &ctx;
    bool operator()(const kernel_t *x, const kernel_t *y);
};

template<typename ctx_t, bool stadfa>
    static void find_state_specialized(ctx_t &);
template<typename ctx_t, bool stadfa>
    static bool do_find_state(ctx_t &);
template<typename ctx_t>
    static tcmd_t *final_actions(ctx_t &, const clos_t &);
template<typename ctx_t>
    static void stadfa_to_tdfa_actions(ctx_t &, tcmd_t **, tcmd_t **);
template<typename ctx_t>
    static tagver_t map_stadfa_ver(ctx_t &, size_t, int32_t);
template<typename ctx_t, bool stadfa>
    static void reserve_buffers(ctx_t &);
template<typename ctx_t>
    static bool equal_lookahead_tags(ctx_t &, const kernel_t *, const kernel_t *);
template<typename ctx_t>
    static bool equal_stacmd(ctx_t &, const kernel_t *, const kernel_t *);
template<typename ctx_t>
    static void unwind(const typename ctx_t::history_t &, tag_path_t &, hidx_t);
template<typename ctx_t>
    static void unwind_tag(const typename ctx_t::history_t &, tag_path_t &,
        hidx_t, size_t);
template<bool stadfa>
    static kernel_t *make_new_kernel(size_t, allocator_t &);
template<bool stadfa>
    static kernel_t *make_kernel_copy(const kernel_t *, allocator_t &);
template<bool stadfa>
    static void copy_to_buffer(const closure_t &, const prectable_t *,
        stacmd_t *, kernel_t *);
static void group_by_tag(tag_path_t &, tag_path_t &, std::vector<uint32_t> &);
static uint32_t hash_kernel(const kernel_t *);

// explicit specialization for context types
template void find_state<pdetctx_t>(pdetctx_t &ctx);
template void find_state<ldetctx_t>(ldetctx_t &ctx);

template<typename ctx_t>
void find_state(ctx_t &ctx)
{
    return ctx.dc_opts->stadfa
        ? find_state_specialized<ctx_t, true>(ctx)
        : find_state_specialized<ctx_t, false>(ctx);
}

template<typename ctx_t, bool stadfa>
void find_state_specialized(ctx_t &ctx)
{
    dfa_t &dfa = ctx.dfa;

    // find or add the new state in the existing set of states
    const bool is_new = do_find_state<ctx_t, stadfa>(ctx);

    if (is_new) {
        // create new DFA state
        dfa_state_t *t = new dfa_state_t(dfa.nchars);
        dfa.states.push_back(t);

        // check if the new state is final
        // see note [at most one final item per closure]
        cclositer_t
            b = ctx.state.begin(),
            e = ctx.state.end(),
            f = std::find_if(b, e, clos_t::fin);
        if (f != e) {
            t->rule = f->state->rule;
        }

        if (stadfa) {
            stadfa_to_tdfa_actions(ctx, &t->stacmd, &t->tcmd[dfa.nchars]);
        }
        else if (f != e) {
            t->tcmd[dfa.nchars] = final_actions(ctx, *f);
        }
    }

    if (ctx.dc_origin == dfa_t::NIL) {
        // initial state
        dfa.tcmd0 = ctx.dc_actions;
    }
    else {
        dfa_state_t *s = dfa.states[ctx.dc_origin];
        s->arcs[ctx.dc_symbol] = ctx.dc_target;
        s->tcmd[ctx.dc_symbol] = ctx.dc_actions;
    }

    DDUMP_DFA_RAW(ctx, is_new);
    DDUMP_DFA_TREE(is_new);
}

template<typename ctx_t, bool stadfa>
bool do_find_state(ctx_t &ctx)
{
    kernels_t &kernels = ctx.dc_kernels;
    const closure_t &closure = ctx.state;

    // empty closure corresponds to default state
    if (closure.size() == 0) {
        ctx.dc_target = dfa_t::NIL;
        ctx.dc_actions = NULL;
        return false;
    }

    // resize buffer if closure is too large
    reserve_buffers<ctx_t, stadfa>(ctx);
    kernel_t *k = ctx.dc_buffers.kernel;

    // copy closure to buffer kernel
    copy_to_buffer<stadfa>(closure, ctx.newprectbl, ctx.stadfa_actions, k);

    // hash "static" part of the kernel
    const uint32_t hash = hash_kernel(k);

    // try to find identical kernel
    kernel_eq_t<ctx_t, stadfa> cmp_eq = {ctx};
    ctx.dc_target = kernels.find_with(hash, k, cmp_eq);
    if (ctx.dc_target != kernels_t::NIL) return false;

    // else if not staDFA try to find mappable kernel
    // see note [bijective mappings]
    if (!stadfa) {
        kernel_map_t<ctx_t> cmp_map = {ctx};
        ctx.dc_target = kernels.find_with(hash, k, cmp_map);
        if (ctx.dc_target != kernels_t::NIL) return false;
    }

    // otherwise add new kernel
    kernel_t *kcopy = make_kernel_copy<stadfa>(k, ctx.dc_allocator);
    ctx.dc_target = kernels.push(hash, kcopy);
    return true;
}

template<typename ctx_t>
tcmd_t *final_actions(ctx_t &ctx, const clos_t &fin)
{
    dfa_t &dfa = ctx.dfa;
    const Rule &rule = dfa.rules[fin.state->rule];
    const tagver_t *vers = ctx.dc_tagvertbl[fin.tvers];
    const hidx_t look = fin.thist;
    const typename ctx_t::history_t &thist = ctx.history;
    tcpool_t &tcpool = dfa.tcpool;
    tcmd_t *copy = NULL, *save = NULL, **p;

    for (size_t t = rule.ltag; t < rule.htag; ++t) {

        const Tag &tag = dfa.tags[t];
        if (fixed(tag)) continue;

        const tagver_t v = abs(vers[t]), l = last(thist, look, t);
        tagver_t &f = dfa.finvers[t];
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

template<typename ctx_t>
void stadfa_to_tdfa_actions(ctx_t &ctx, tcmd_t **state_cmd, tcmd_t **final_cmd)
{
    tcpool_t &pool = ctx.dfa.tcpool;

    // Convert staDFA store/transfer/accept actions to tag commands:
    // map each (tag, index) pair to a unique tag version.
    tcmd_t *s = NULL, *f = NULL;
    tagver_t l, r;
    for (const stacmd_t *p = ctx.stadfa_actions; p; p = p->next) {
        switch (p->kind) {
        case stacmd_t::STORE:
            l = map_stadfa_ver(ctx, p->tag, p->lhs);
            if (history(ctx.dfa.tags[p->tag])) {
                r = map_stadfa_ver(ctx, p->tag, p->rhs);
                s = pool.make_add(s, l, r, ctx.history, p->hist, p->tag);
            }
            else {
                r = last(ctx.history, p->hist, p->tag);
                s = pool.make_set(s, l, r);
            }
            break;
        case stacmd_t::TRANSFER:
            if (p->lhs != p->rhs) {
                l = map_stadfa_ver(ctx, p->tag, p->lhs);
                r = map_stadfa_ver(ctx, p->tag, p->rhs);
                s = pool.make_copy(s, l, r);
            }
            break;
        case stacmd_t::ACCEPT:
            l = ctx.dfa.finvers[p->tag];
            if (p->hist == HROOT) {
                r = map_stadfa_ver(ctx, p->tag, p->rhs);
                f = pool.make_copy(f, l, r);
            }
            else if (history(ctx.dfa.tags[p->tag])) {
                r = map_stadfa_ver(ctx, p->tag, p->rhs);
                f = pool.make_add(f, l, r, ctx.history, p->hist, p->tag);
            }
            else {
                r = last(ctx.history, p->hist, p->tag);
                f = pool.make_set(f, l, r);
            }
            break;
        }
    }
    *state_cmd = s;
    *final_cmd = f;

    // Topologically sort tag commands. This may not be possible due to cycles
    // (in staDFA they are unavoidable because indices are determined by TNFA
    // substates, which may be flipped in the origin and target staDFA states).
    // Break each cycle by introducing a temporary tag version: e.g. 'x=y; y=x;'
    // is rewritten as 'z=x; x=y; y=z;'. Topsort gathers cycles at the end of
    // command list and returns a pointer to the first command of the cycle.
    // There can be multiple cycles, therefore the process is repeated until
    // topsort finds no more cycles.
    reserve_buffers<ctx_t, true>(ctx);
    tcmd_t **cycle = tcmd_t::topsort(state_cmd, NULL, ctx.dc_buffers.indegree);
    for (; cycle; ) {
        tcmd_t *c0 = *cycle;
        DASSERT(c0);

        const tagver_t tmp = ++ctx.dfa.maxtagver, lhs = c0->lhs;
        if (ctx.dfa.mtagvers.find(lhs) != ctx.dfa.mtagvers.end()) {
            ctx.dfa.mtagvers.insert(tmp);
        }

        *cycle = pool.make_copy(c0, tmp, lhs);

        for (tcmd_t *c = c0->next; c; c = c->next) {
            DASSERT(tcmd_t::iscopy(c) || tcmd_t::isadd(c));
            if (lhs == c->rhs) {
                c->rhs = tmp;
            }
        }

        reserve_buffers<ctx_t, true>(ctx);
        cycle = tcmd_t::topsort(&c0->next, NULL, ctx.dc_buffers.indegree);
    }
}

template<typename ctx_t>
tagver_t map_stadfa_ver(ctx_t &ctx, size_t tag, int32_t ver)
{
    const stadfa_tagvers_t::key_type k(tag, ver);
    stadfa_tagvers_t::iterator i = ctx.stadfa_tagvers.find(k);

    tagver_t m;
    if (i == ctx.stadfa_tagvers.end()) {
        m = ++ctx.dfa.maxtagver;

        ctx.stadfa_tagvers.insert(std::make_pair(k, m));

        if (history(ctx.dfa.tags[tag])) {
            ctx.dfa.mtagvers.insert(m);
        }
    }
    else {
        m = i->second;
    }
    return m;
}

kernel_buffers_t::kernel_buffers_t()
    : maxsize(0)
    , kernel(NULL)
    , cap(0)
    , max(0)
    , memory(NULL)
    , x2y(NULL)
    , y2x(NULL)
    , x2t(NULL)
    , indegree(NULL)
    , backup_actions(NULL)
{}

template<bool stadfa>
kernel_t *make_new_kernel(size_t size, allocator_t &alc)
{
    kernel_t *k = alc.alloct<kernel_t>(1);
    k->size = size;
    k->state = alc.alloct<nfa_state_t*>(size);
    k->thist = alc.alloct<hidx_t>(size);
    k->prectbl = NULL;
    if (!stadfa) {
        k->tvers = alc.alloct<uint32_t>(size);
    }
    else {
        k->stacmd = NULL;
    }
    return k;
}

template<bool stadfa>
kernel_t *make_kernel_copy(const kernel_t *kernel, allocator_t &alc)
{
    const size_t n = kernel->size;

    kernel_t *k = make_new_kernel<stadfa>(n, alc);

    memcpy(k->state, kernel->state, n * sizeof(void*));
    memcpy(k->thist, kernel->thist, n * sizeof(hidx_t));

    prectable_t *ptbl = NULL;
    if (kernel->prectbl) {
        ptbl = alc.alloct<prectable_t>(n * n);
        memcpy(ptbl, kernel->prectbl, n * n * sizeof(prectable_t));
    }
    k->prectbl = ptbl;

    if (!stadfa) {
        memcpy(k->tvers, kernel->tvers, n * sizeof(uint32_t));
    }
    else {
        // new staDFA commands are allocated for every closure, don't copy
        k->stacmd = kernel->stacmd;
    }

    return k;
}

uint32_t hash_kernel(const kernel_t *kernel)
{
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

template <bool stadfa>
void copy_to_buffer(const closure_t &closure, const prectable_t *prectbl,
    stacmd_t *stacmd, kernel_t *buffer)
{
    const size_t n = closure.size();
    buffer->size = n;
    buffer->prectbl = prectbl;
    if (!stadfa) {
        for (size_t i = 0; i < n; ++i) {
            const clos_t &c = closure[i];
            buffer->state[i] = c.state;
            buffer->tvers[i] = c.tvers;
            buffer->thist[i] = c.thist;
        }
    }
    else {
        for (size_t i = 0; i < n; ++i) {
            const clos_t &c = closure[i];
            buffer->state[i] = c.state;
            buffer->thist[i] = c.thist;
        }
        buffer->stacmd = stacmd;
    }
}

template<typename ctx_t, bool stadfa>
void reserve_buffers(ctx_t &ctx)
{
    kernel_buffers_t &kbufs = ctx.dc_buffers;
    allocator_t &alc = ctx.dc_allocator;
    const tagver_t maxver = ctx.dfa.maxtagver;
    const size_t nkern = ctx.state.size();

    if (kbufs.maxsize < nkern) {
        kbufs.maxsize = nkern * 2; // in advance
        kbufs.kernel = make_new_kernel<stadfa>(kbufs.maxsize, alc);
    }

    // +1 to ensure max tag version is not forgotten in loops
    kbufs.max = maxver + 1;
    if (kbufs.cap < kbufs.max) {
        kbufs.cap = kbufs.max * 2; // in advance

        const size_t n = static_cast<size_t>(kbufs.cap);
        kbufs.indegree = alc.alloct<uint32_t>(n);

        if (!stadfa) {
            const size_t m = 2 * n + 1;

            // point to the center (zero index) of each buffer
            // indexes in range [-N .. N] must be valid, where N is capacity
            kbufs.x2y = alc.alloct<tagver_t>(m) + n;
            kbufs.y2x = alc.alloct<tagver_t>(m) + n;
            kbufs.x2t = alc.alloct<size_t>(m) + n;

            kbufs.backup_actions = alc.alloct<tcmd_t>(n);
        }
    }
}

template<typename ctx_t>
bool equal_lookahead_tags(ctx_t &ctx, const kernel_t *x, const kernel_t *y)
{
    DASSERT(x->size == y->size);

    if (memcmp(x->thist, y->thist, x->size * sizeof(hidx_t)) == 0) {
        return true;
    }

    typename ctx_t::history_t &thist = ctx.history;
    tag_path_t &p1 = ctx.dc_path1, &p2 = ctx.dc_path2, &p3 = ctx.dc_path3;
    std::vector<uint32_t> &count = ctx.dc_tagcount;

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

void group_by_tag(tag_path_t &path, tag_path_t &buf, std::vector<uint32_t> &count)
{
    // counting sort with tag index as key
    // must preserve relative order of elements with the same tag

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
void unwind(const typename ctx_t::history_t &hist, tag_path_t &path, hidx_t idx)
{
    // Simple tags need only the last value, so in principle we could
    // increase the chance of mapping by recording only the last value.
    // But this would complicate unwind procedure quite a bit, and the
    // cases when it makes any difference are rare.
    path.clear();
    for (; idx != HROOT; ) {
        const typename ctx_t::history_t::node_t &n = hist.node(idx);
        path.push_back(n.info);
        idx = n.pred;
    }
}

template<typename ctx_t>
void unwind_tag(const typename ctx_t::history_t &hist, tag_path_t &path,
    hidx_t idx, size_t tag)
{
    path.clear();
    for (; idx != HROOT; ) {
        const typename ctx_t::history_t::node_t &n = hist.node(idx);
        if (n.info.idx == tag) {
            path.push_back(n.info);
        }
        idx = n.pred;
    }
}

template<typename ctx_t>
bool equal_stacmd(ctx_t &ctx, const kernel_t *x, const kernel_t *y)
{
    DASSERT(x->size == y->size);

    const stacmd_t *p = x->stacmd, *q = y->stacmd;
    for (; p && q; p = p->next, q = q->next) {
        const size_t t = p->tag;

        if (t != q->tag
            || p->kind != q->kind
            || p->lhs != q->lhs
            || p->rhs != q->rhs) return false;

        hidx_t i = p->hist, j = q->hist;
        if (i != j) {
            if (history(ctx.dfa.tags[t])) {
                tag_path_t &p1 = ctx.dc_path1, &p2 = ctx.dc_path2;
                unwind_tag<ctx_t>(ctx.history, p1, i, t);
                unwind_tag<ctx_t>(ctx.history, p2, j, t);
                if (p1 != p2) return false;
            }
            else if (last(ctx.history, i, t) != last(ctx.history, j, t)) {
                return false;
            }
        }
    }
    return !p && !q;
}

template<typename ctx_t, bool stadfa>
bool kernel_eq_t<ctx_t, stadfa>::operator()(const kernel_t *x, const kernel_t *y) const
{
    // check that kernel sizes, NFA states, tags versions,
    // lookahead tags and precedence table coincide
    const size_t n = x->size;
    return n == y->size
        && memcmp(x->state, y->state, n * sizeof(void*)) == 0
        && (!x->prectbl
            || memcmp(x->prectbl, y->prectbl, n * n * sizeof(prectable_t)) == 0)
        && (stadfa
            ? equal_stacmd(ctx, x, y)
            : memcmp(x->tvers, y->tvers, n * sizeof(uint32_t)) == 0)
        && equal_lookahead_tags(ctx, x, y);
}

template<typename ctx_t>
bool kernel_map_t<ctx_t>::operator()(const kernel_t *x, const kernel_t *y)
{
    // check that kernel sizes, NFA states lookahead tags
    // and precedence table coincide (versions might differ)
    const size_t n = x->size;
    const bool compatible = n == y->size
        && memcmp(x->state, y->state, n * sizeof(void*)) == 0
        && (!x->prectbl || memcmp(x->prectbl, y->prectbl, n * n * sizeof(prectable_t)) == 0)
        && equal_lookahead_tags(ctx, x, y);
    if (!compatible) return false;

    const std::vector<Tag> &tags = ctx.dfa.tags;
    const size_t ntag = tags.size();
    kernel_buffers_t &bufs = ctx.dc_buffers;
    tagver_t *x2y = bufs.x2y, *y2x = bufs.y2x, max = bufs.max;
    size_t *x2t = bufs.x2t;

    // map tag versions of one kernel to that of another
    // and check that lookahead versions (if any) coincide
    std::fill(x2y - max, x2y + max, TAGVER_ZERO);
    std::fill(y2x - max, y2x + max, TAGVER_ZERO);
    for (size_t i = 0; i < n; ++i) {
        const tagver_t
            *xvs = ctx.dc_tagvertbl[x->tvers[i]],
            *yvs = ctx.dc_tagvertbl[y->tvers[i]];
        const hidx_t xl = x->thist[i];

        for (size_t t = 0; t < ntag; ++t) {
            // see note [mapping ignores items with lookahead tags]
            if (!history(tags[t])
                && last(ctx.history, xl, t) != TAGVER_ZERO) continue;

            const tagver_t xv = xvs[t], yv = yvs[t];
            tagver_t &xv0 = y2x[yv], &yv0 = x2y[xv];

            if (yv0 == TAGVER_ZERO && xv0 == TAGVER_ZERO) {
                xv0 = xv;
                yv0 = yv;
                x2t[xv] = t;
            } else if (yv != yv0 || xv != xv0) {
                return false;
            }
        }
    }

    // we have bijective mapping; now try to create list of commands
    tcmd_t **pacts = &ctx.dc_actions, *a, **pa, *copy = NULL;
    tcmd_t *b1 = bufs.backup_actions, *b2 = b1;

    // backup 'save' commands: if topsort finds cycles, this mapping
    // will be rejected and we'll have to revert all changes
    for (b2->next = a = *pacts; a; a = a->next) {
        *++b2 = *a;
    }

    // fix LHS of 'save' commands to reuse old version
    // see note [save(X), copy(Y,X) optimization]
    for (a = *pacts; a; a = a->next) {
        const tagver_t
            yv = a->lhs * (a->history[0] == TAGVER_BOTTOM ? -1 : 1),
            xv = y2x[yv];
        a->lhs = abs(xv);
        y2x[yv] = x2y[xv] = TAGVER_ZERO;
    }

    // create 'copy' commands
    for (tagver_t xv = -max; xv < max; ++xv) {
        const tagver_t yv = x2y[xv], axv = abs(xv), ayv = abs(yv);
        if (yv != TAGVER_ZERO && xv != yv && !fixed(tags[x2t[xv]])) {
            DASSERT(axv != ayv);
            copy = ctx.dfa.tcpool.make_copy(copy, axv, ayv);
        }
    }

    // join 'copy' and 'save' commands
    for (pa = &copy; (a = *pa); pa = &a->next);
    *pa = *pacts;
    *pacts = copy;

    // see note [topological ordering of copy commands]
    tcmd_t **cycle = tcmd_t::topsort(pacts, NULL, bufs.indegree);

    // in case of cycles restore 'save' commands and fail
    if (cycle) {
        for (*pacts = a = b1->next; a; a = a->next) {
            *a = *++b1;
        }
    }

    return cycle == NULL;
}

} // namespace re2c
