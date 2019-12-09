#ifndef _RE2C_DFA_TCMD_
#define _RE2C_DFA_TCMD_

#include <stddef.h>
#include "src/util/c99_stdint.h"

#include "src/dfa/tag_history.h"
#include "src/regexp/tag.h"
#include "src/util/lookup.h"
#include "src/util/slab_allocator.h"


namespace re2c {

struct tcmd_t
{
    tcmd_t *next;
    tagver_t lhs; // left hand side
    tagver_t rhs; // right hand side
    tagver_t history[1];

    static bool equal(const tcmd_t &x, const tcmd_t &y);
    static bool equal_history(const tagver_t *h, const tagver_t *g);
    static bool iscopy(const tcmd_t *x);
    static bool isset(const tcmd_t *x);
    static bool isadd(const tcmd_t *x);
    static tcmd_t **topsort(tcmd_t **phead, tcmd_t *end, uint32_t *indeg);
};

typedef uint32_t tcid_t;

static const tcid_t TCID0 = 0;

class tcpool_t
{
    typedef slab_allocator_t<4096, sizeof(void*)> alc_t;
    typedef lookup_t<const tcmd_t*> index_t;

    alc_t alc;
    index_t index;

public:
    tcpool_t();
    tcmd_t *make_copy(tcmd_t *next, tagver_t lhs, tagver_t rhs);
    tcmd_t *make_set(tcmd_t *next, tagver_t lhs, tagver_t set);
    template<typename history_t> tcmd_t *make_add(tcmd_t *next, tagver_t lhs, tagver_t rhs, const history_t &history, hidx_t hidx, size_t tag);
    tcmd_t *copy_add(tcmd_t *next, tagver_t lhs, tagver_t rhs, const tagver_t *history);
    tcid_t insert(const tcmd_t *tcmd);
    const tcmd_t *operator[](tcid_t id) const;
};

} // namespace re2c

#endif // _RE2C_DFA_TCMD_
