#ifndef _RE2C_LIB_REGOFF_TRIE_
#define _RE2C_LIB_REGOFF_TRIE_

#include <algorithm>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "regex.h"
#include "src/util/check.h"
#include "src/util/forbid_copy.h"

namespace re2c {
namespace libre2c {

struct regoff_trie_t {
    struct node_t {
        regoff_t off;
        size_t pred;
    };

    size_t nlists;
    size_t* lists;
    size_t* count;

    size_t size;
    size_t capacity;
    node_t* storage;

    explicit regoff_trie_t(size_t nlists)
        : nlists(nlists),
          lists(new size_t[nlists]),
          count(new size_t[nlists]),
          size(0),
          capacity(nlists * 2),
          storage(new node_t[capacity]) {
        clear();
    }

    ~regoff_trie_t() {
        delete[] lists;
        delete[] count;
        delete[] storage;
    }

    inline void clear() {
        std::fill(lists, lists + nlists, ~0u);
        memset(count, 0, nlists * sizeof(size_t));
        size = 0;
    }

    inline void grow(size_t new_capacity) {
        DCHECK(new_capacity > capacity);
        node_t* new_storage = new node_t[new_capacity];
        memcpy(new_storage, storage, capacity * sizeof(node_t));
        delete[] storage;
        storage = new_storage;
        capacity = new_capacity;
    }

    inline void copy(size_t lhs, size_t rhs) {
        lists[lhs] = lists[rhs];
        count[lhs] = count[rhs];
    }

    inline void set(size_t lhs, regoff_t off) {
        if (count[lhs] == 0) {
            add(lhs, off);
        } else {
            // overwrite existing
            count[lhs] = 0;
            lists[lhs] = 0;
            add(lhs, off);
        }
    }

    inline void add(size_t lhs, regoff_t off) {
        if (size >= capacity) {
            grow(capacity * 2);
        }
        node_t node = {off, lists[lhs]};
        lists[lhs] = size;
        ++count[lhs];
        storage[size] = node;
        ++size;
    }

    FORBID_COPY(regoff_trie_t);
};

} // namespace libre2c
} // namespace re2c

#endif // _RE2C_LIB_REGOFF_TRIE_
