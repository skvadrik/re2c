#include <stdlib.h>

#include "src/debug/debug.h"
#include "src/dfa/determinization.h"
#include "src/dfa/tag_history.h"


namespace re2c
{

static void reconstruct_history(const tag_history_t &, tag_path_t &, hidx_t);

// maximum 29-bit (we have 30 bits, but highest must be non-negative)
static const int32_t MAX_RHO = 0x1fffFFFF;

int32_t precedence(determ_context_t &ctx,
    const clos_t &x, const clos_t &y, int32_t &rhox, int32_t &rhoy)
{
    const hidx_t xl = x.tlook, yl = y.tlook;
    const uint32_t xo = x.origin, yo = y.origin;
    const std::vector<Tag> &tags = ctx.dc_dfa.tags;
    const kernel_t *k = NULL;

    if (xl == yl && xo == yo) {
        rhox = rhoy = MAX_RHO;
        return 0;
    }

    tag_history_t &thist = ctx.dc_taghistory;
    tag_path_t &p1 = thist.path1, &p2 = thist.path2;
    reconstruct_history(thist, p1, xl);
    reconstruct_history(thist, p2, yl);
    tag_path_t::const_reverse_iterator
        i1 = p1.rbegin(), e1 = p1.rend(), j1 = i1, g1,
        i2 = p2.rbegin(), e2 = p2.rend(), j2 = i2, g2;

    DINCCOUNT_CLPREC(ctx);
    DINCCOUNT_CLLENGTH(ctx, p1.size() + p2.size());

    const bool fork_frame = xo == yo;

    // longest precedence
    if (fork_frame) {
        // find fork
        for (; j1 != e1 && j2 != e2 && *j1 == *j2; ++j1, ++j2);
        rhox = rhoy = j1 > i1
            ? tags[(j1 - 1)->idx].height : MAX_RHO;
    }
    else {
        // get precedence table and size of the origin state
        k = ctx.dc_kernels[ctx.dc_origin];
        rhox = unpack_longest(k->prectbl[xo * k->size + yo]);
        rhoy = unpack_longest(k->prectbl[yo * k->size + xo]);
    }
    for (g1 = j1; g1 != e1; ++g1) {
        rhox = std::min(rhox, tags[g1->idx].height);
    }
    for (g2 = j2; g2 != e2; ++g2) {
        rhoy = std::min(rhoy, tags[g2->idx].height);
    }
    if (rhox > rhoy) return -1;
    if (rhox < rhoy) return 1;

    // leftmost precedence
    if (fork_frame) {
        // equal => not less
        if (j1 == e1 && j2 == e2) return 0;

        // shorter => less
        if (j1 == e1) return -1;
        if (j2 == e2) return 1;

        const uint32_t idx1 = j1->idx, idx2 = j2->idx;
        const bool neg1 = j1->neg, neg2 = j2->neg;

        // can't be both closing
        DASSERT(!(idx1 % 2 == 1 && idx2 % 2 == 1));

        // closing vs opening: closing wins
        if (idx1 % 2 == 1) return -1;
        if (idx2 % 2 == 1) return 1;

        // can't be both negative
        DASSERT(!(neg1 && neg2));

        // positive vs negative: positive wins
        if (neg1) return 1;
        if (neg2) return -1;

        // positive vs positive: smaller wins
        // (this case is only possible because multiple
        // top-level RE don't have proper negative tags)
        if (idx1 < idx2) return -1;
        if (idx1 > idx2) return 1;
    }
    else {
        return unpack_leftmost(k->prectbl[xo * k->size + yo]);
    }

    // unreachable
    DASSERT(false);
    return 0;
}

void reconstruct_history(const tag_history_t &history,
    tag_path_t &path, hidx_t idx)
{
    path.clear();
    for (; idx != HROOT; idx = history.pred(idx)) {
        path.push_back(history.info(idx));
    }
}

int32_t unpack_longest(int32_t packed)
{
    // take lower 30 bits and sign-extend
    return static_cast<int32_t>(static_cast<uint32_t>(packed) << 2u) >> 2u;
}

int32_t unpack_leftmost(int32_t packed)
{
    // take higher 2 bits and sign-extend
    return packed >> 30u;
}

int32_t pack(int32_t longest, int32_t leftmost)
{
    // avoid signed overflows by using unsigned arithmetics
    uint32_t u_longest = static_cast<uint32_t>(longest);
    uint32_t u_leftmost = static_cast<uint32_t>(leftmost);

    // leftmost: higher 2 bits, longest: lower 30 bits
    uint32_t u_packed = (u_longest & 0x3fffFFFF) | (u_leftmost << 30u);
    int32_t packed = static_cast<int32_t>(u_packed);

    DASSERT(unpack_longest(packed) == longest
        && unpack_leftmost(packed) == leftmost);

    return packed;
}

} // namespace re2c
