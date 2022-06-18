#include <stdlib.h>
#include <string.h>
#include <algorithm>

#include "src/dfa/tagver_table.h"
#include "src/util/hash32.h"

namespace re2c {

struct eqtag_t {
    size_t ntags;

    explicit eqtag_t(size_t n): ntags(n) {}
    inline tagver_t operator()(const tagver_t* x, const tagver_t* y) const {
        return memcmp(x, y, ntags * sizeof(tagver_t)) == 0;
    }
};

tagver_table_t::tagver_table_t(size_t n): lookup(), ntags(n), buffer(new tagver_t[n]) {}

tagver_table_t::~tagver_table_t() {
    delete[] buffer;
    const size_t n = lookup.size();
    for (uint32_t i = 0; i < n; ++i) {
        free(const_cast<tagver_t*>(lookup[i]));
    }
}

uint32_t tagver_table_t::insert_const(tagver_t ver) {
    std::fill(buffer, buffer + ntags, ver);
    return insert(buffer);
}

uint32_t tagver_table_t::insert_succ(tagver_t fst) {
    for (uint32_t i = 0; i < ntags; ++i) {
        buffer[i] = fst++;
    }
    return insert(buffer);
}

uint32_t tagver_table_t::insert(const tagver_t* tags) {
    const size_t size = ntags * sizeof(tagver_t);
    const uint32_t hash = hash32(0, tags, size);

    eqtag_t eq(ntags);
    const uint32_t idx = lookup.find_with(hash, tags, eq);
    if (idx != taglookup_t::NIL) {
        return idx;
    }

    tagver_t* copy = static_cast<tagver_t*>(malloc(size));
    memcpy(copy, tags, size);
    return lookup.push(hash, copy);
}

const tagver_t* tagver_table_t::operator[](uint32_t idx) const {
    return lookup[idx];
}

} // namespace re2c
