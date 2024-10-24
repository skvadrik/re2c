#ifndef _RE2C_SKELETON_MTAG_TRIE_
#define _RE2C_SKELETON_MTAG_TRIE_

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "src/util/check.h"

namespace re2c {

static constexpr uint32_t MTAG_TRIE_ROOT = ~0u;

struct mtag_t {
    uint32_t pred;
    uint32_t dist;
};

struct mtag_trie_t {
    mtag_t* head;
    uint32_t size;
    uint32_t next;
};

inline void mtag_trie_clear(mtag_trie_t& trie) {
    trie.next = 0;
}

inline void mtag_trie_init(mtag_trie_t& trie) {
    static constexpr uint32_t SIZE = 1024;
    trie.head = new mtag_t[SIZE];
    trie.size = SIZE;
    trie.next = 0;
}

inline void mtag_trie_free(mtag_trie_t& trie) {
    delete[] trie.head;
    trie.head = nullptr;
    trie.size = 0;
}

inline uint32_t mtag_trie_next(mtag_trie_t& trie) {
    DCHECK(trie.next <= trie.size);
    if (trie.next == trie.size) {
        mtag_t* head = new mtag_t[2 * trie.size];
        memcpy(head, trie.head, trie.size * sizeof(mtag_t));
        free(trie.head);
        trie.head = head;
        trie.size *= 2;
    }

    return trie.next++;
}

inline uint32_t mtag(mtag_trie_t& trie, uint32_t pred, uint32_t dist) {
    uint32_t next = mtag_trie_next(trie);
    mtag_t& t = trie.head[next];
    t.pred = pred;
    t.dist = dist;
    return next;
}

inline uint32_t mtag_length(mtag_trie_t& trie, uint32_t mtag) {
    uint32_t len = 0;
    for (; mtag != MTAG_TRIE_ROOT; ) {
        ++len;
        mtag = trie.head[mtag].pred;
    }
    return len;
}

} // namespace re2c

#endif // _RE2C_SKELETON_MTAG_TRIE_
