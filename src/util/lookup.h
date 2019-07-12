#ifndef _RE2C_UTIL_LOOKUP_
#define _RE2C_UTIL_LOOKUP_

#include "src/util/c99_stdint.h"
#include <limits>
#include <map>
#include <vector>
#include <stddef.h>

#include "src/debug/debug.h"


namespace re2c {

/*
 * O(1) random access
 * O(log(n)) insertion
 */
template<typename data_t, typename hash_t = uint32_t>
struct lookup_t
{
    static const uint32_t NIL;

private:
    struct elem_t
    {
        uint32_t next;
        data_t data;

        elem_t(uint32_t n, const data_t &d)
            : next(n), data(d) {}
    };

    std::vector<elem_t> elems;
    std::map<hash_t, uint32_t> lookup;

public:
    lookup_t();
    uint32_t size() const;
    data_t& operator[](uint32_t idx);
    const data_t& operator[](uint32_t idx) const;
    uint32_t push(hash_t hash, const data_t &data);
    template<typename pred_t> uint32_t find_with(hash_t hash, const data_t &data, pred_t &pred) const;
    template<typename pred_t> uint32_t find_next_with(uint32_t prev, const data_t &data, pred_t &pred) const;

private:
    uint32_t head(hash_t) const;
    template<typename pred_t> uint32_t find(uint32_t next, const data_t &data, pred_t &pred) const;
};

template<typename data_t, typename hash_t>
const uint32_t lookup_t<data_t, hash_t>::NIL = ~0u;

template<typename data_t, typename hash_t>
lookup_t<data_t, hash_t>::lookup_t()
    : elems()
    , lookup()
{}

template<typename data_t, typename hash_t>
uint32_t lookup_t<data_t, hash_t>::size() const
{
    return static_cast<uint32_t>(elems.size());
}

template<typename data_t, typename hash_t>
data_t& lookup_t<data_t, hash_t>::operator[](uint32_t idx)
{
    DASSERT(idx < elems.size());
    return elems[idx].data;
}

template<typename data_t, typename hash_t>
const data_t& lookup_t<data_t, hash_t>::operator[](uint32_t idx) const
{
    DASSERT(idx < elems.size());
    return elems[idx].data;
}

template<typename data_t, typename hash_t>
uint32_t lookup_t<data_t, hash_t>::head(hash_t h) const
{
    typename std::map<hash_t, uint32_t>::const_iterator x = lookup.find(h);
    return x == lookup.end() ? NIL : x->second;
}

template<typename data_t, typename hash_t>
uint32_t lookup_t<data_t, hash_t>::push(hash_t hash, const data_t &data)
{
    DASSERT(elems.size() < NIL);
    const uint32_t idx = static_cast<uint32_t>(elems.size());
    elems.push_back(elem_t(head(hash), data));
    lookup[hash] = idx;
    return idx;
}

template<typename data_t, typename hash_t>
template<typename pred_t>
uint32_t lookup_t<data_t, hash_t>::find(uint32_t next, const data_t &data, pred_t &pred) const
{
    for (uint32_t i = next; i != NIL;) {
        const elem_t &e = elems[i];
        if (pred(e.data, data)) {
            return i;
        }
        i = e.next;
    }
    return NIL;
}

template<typename data_t, typename hash_t>
template<typename pred_t>
uint32_t lookup_t<data_t, hash_t>::find_with(hash_t hash, const data_t &data, pred_t &pred) const
{
    return find(head(hash), data, pred);
}

template<typename data_t, typename hash_t>
template<typename pred_t>
uint32_t lookup_t<data_t, hash_t>::find_next_with(uint32_t prev, const data_t &data, pred_t &pred) const
{
    return find(elems[prev].next, data, pred);
}

} // namespace re2c

#endif // _RE2C_UTIL_LOOKUP_
