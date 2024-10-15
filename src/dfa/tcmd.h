#ifndef _RE2C_DFA_TCMD_
#define _RE2C_DFA_TCMD_

#include <stddef.h>
#include <stdint.h>

#include "src/dfa/tag_history.h"
#include "src/regexp/tag.h"
#include "src/util/check.h"
#include "src/util/allocator.h"
#include "src/util/containers.h"

namespace re2c {

struct tcmd_t {
    tcmd_t* next;
    tagver_t lhs; // left hand side
    tagver_t rhs; // right hand side
    tagver_t history[1];

    static bool equal(const tcmd_t& x, const tcmd_t& y);
    static bool equal_history(const tagver_t* h, const tagver_t* g);
    static bool iscopy(const tcmd_t* x);
    static bool isset(const tcmd_t* x);
    static bool isadd(const tcmd_t* x);
    static tcmd_t** topsort(tcmd_t** phead, tcmd_t* end, uint32_t* indeg);
};

using tcid_t = uint32_t;

static constexpr tcid_t TCID0 = 0;
static constexpr tcid_t TCID_NONE = std::numeric_limits<tcid_t>::max();

class tcpool_t {
    using index_t = lookup_t<const tcmd_t*>;

    DfaAllocator& alc;
    index_t index;

  public:
    explicit tcpool_t(DfaAllocator& alc);
    tcmd_t* make_copy(tcmd_t* next, tagver_t lhs, tagver_t rhs);
    tcmd_t* make_set(tcmd_t* next, tagver_t lhs, tagver_t set);
    template<typename history_t> tcmd_t* make_add(tcmd_t* next,
                                                  tagver_t lhs,
                                                  tagver_t rhs,
                                                  const history_t& history,
                                                  hidx_t hidx,
                                                  size_t tag);
    tcmd_t* copy_add(tcmd_t* next, tagver_t lhs, tagver_t rhs, const tagver_t* history);
    tcid_t insert(const tcmd_t* tcmd);
    const tcmd_t* operator[](tcid_t id) const;
};

inline bool tcmd_t::iscopy(const tcmd_t* x) {
    return x->rhs != TAGVER_ZERO && x->history[0] == TAGVER_ZERO;
}

inline bool tcmd_t::isset(const tcmd_t* x) {
    if (x->rhs == TAGVER_ZERO) {
        DCHECK(x->history[0] != TAGVER_ZERO);
        return true;
    }
    return false;
}

inline bool tcmd_t::isadd(const tcmd_t* x) {
    return x->rhs != TAGVER_ZERO && x->history[0] != TAGVER_ZERO;
}

} // namespace re2c

#endif // _RE2C_DFA_TCMD_
