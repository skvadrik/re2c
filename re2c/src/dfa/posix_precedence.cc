#include <assert.h>
#include <stdlib.h>

#include "src/dfa/determinization.h"
#include "src/dfa/tag_history.h"


namespace re2c
{

static void reconstruct_history(const tag_history_t &, tag_path_t &, hidx_t);
static int32_t unpack_longest(int32_t);
static int32_t unpack_leftmost(int32_t);


int32_t precedence(determ_context_t &ctx,
    const clos_t &x, const clos_t &y, int32_t &rhox, int32_t &rhoy)
{
    const hidx_t xl = x.tlook, yl = y.tlook;
    const uint32_t xo = x.origin, yo = y.origin;

    if (xl == yl && xo == yo) {
        rhox = rhoy = -1;
        return 0;
    }

    tag_history_t &thist = ctx.dc_taghistory;
    tag_path_t &p1 = thist.path1, &p2 = thist.path2;

    reconstruct_history(thist, p1, xl);
    reconstruct_history(thist, p2, yl);

    tag_path_t::const_reverse_iterator
        i1 = p1.rbegin(), e1 = p1.rend(), j1 = i1, g1,
        i2 = p2.rbegin(), e2 = p2.rend(), j2 = i2, g2;

    const std::vector<Tag> &tags = ctx.dc_dfa.tags;
    size_t nclos = 0;
    const prectable_t *prectbl = NULL;
    const bool fork_frame = xo == yo;

    if (fork_frame) {
        // find fork
        for (; j1 != e1 && j2 != e2 && *j1 == *j2; ++j1, ++j2);
    }
    else {
        // get precedence table and size of the origin state
        const kernel_t *k = ctx.dc_kernels[ctx.dc_origin];
        nclos = k->size;
        prectbl = k->prectbl;
    }

    // longest precedence
    if (!fork_frame) {
        rhox = unpack_longest(prectbl[xo * nclos + yo]);
        rhoy = unpack_longest(prectbl[yo * nclos + xo]);
    }
    else {
        rhox = rhoy = std::numeric_limits<int>::max();
        if (j1 > i1) rhox = rhoy = tags[(j1 - 1)->idx].height;
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
    if (!fork_frame) {
        return unpack_leftmost(prectbl[xo * nclos + yo]);
    }
    else {
        // equal => not less
        if (j1 == e1 && j2 == e2) return 0;

        // shorter => less
        if (j1 == e1) return -1;
        if (j2 == e2) return 1;

        const uint32_t idx1 = j1->idx, idx2 = j2->idx;
        const bool neg1 = j1->neg, neg2 = j2->neg;

        // can't be both closing
        assert(!(idx1 % 2 == 1 && idx2 % 2 == 1));

        // closing vs opening: closing wins
        if (idx1 % 2 == 1) return -1;
        if (idx2 % 2 == 1) return 1;

        // can't be both negative
        assert(!(neg1 && neg2));

        // positive vs negative: positive wins
        if (neg1) return 1;
        if (neg2) return -1;

        // positive vs positive: smaller wins
        // (this case is only possible because multiple
        // top-level RE don't have proper negative tags)
        if (idx1 < idx2) return -1;
        if (idx1 > idx2) return 1;
    }

    // unreachable
    assert(false);
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


int32_t unpack_longest(int32_t value)
{
    // lower 30 bits
    return value & 0x3fffFFFF;
}


int32_t unpack_leftmost(int32_t value)
{
    // higher 2 bits
    return value >> 30u;
}

} // namespace re2c
