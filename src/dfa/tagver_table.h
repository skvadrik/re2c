#ifndef _RE2C_DFA_TAGVER_TABLE_
#define _RE2C_DFA_TAGVER_TABLE_

#include <stddef.h>
#include <stdint.h>

#include "src/regexp/tag.h"
#include "src/util/containers.h"
#include "src/util/forbid_copy.h"

namespace re2c {

static constexpr size_t ZERO_TAGS = 0;

struct tagver_table_t {
  private:
    using taglookup_t = lookup_t<const tagver_t*>;
    taglookup_t lookup;

  public:
    const size_t ntags;
    tagver_t* buffer;

    explicit tagver_table_t(size_t n);
    ~tagver_table_t();
    uint32_t insert_const(tagver_t ver);
    uint32_t insert_succ(tagver_t fst);
    uint32_t insert(const tagver_t* tags);
    const tagver_t* operator[](uint32_t idx) const;
    FORBID_COPY(tagver_table_t);
};

} // namespace re2c

#endif // _RE2C_DFA_TAGVER_TABLE_
