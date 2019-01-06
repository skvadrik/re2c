#ifndef _RE2C_UTIL_FIXED_ALLOCATOR_
#define _RE2C_UTIL_FIXED_ALLOCATOR_

#include "src/util/c99_stdint.h"
#include <vector> // slab queue

#include "src/util/forbid_copy.h"


template<typename T, uint32_t SLAB_SIZE = 4096>
class fixed_allocator_t
{
    typedef std::vector<T*> slabs_t;

    slabs_t slabs;
    size_t index;

public:
    fixed_allocator_t(): slabs(), index(SLAB_SIZE) {}

    ~fixed_allocator_t() { clear(); }

    void clear()
    {
        typename slabs_t::reverse_iterator
            i = slabs.rbegin(), e = slabs.rend();
        for (; i != e; ++i) {
            operator delete(*i);
        }
        slabs.clear();
        index = SLAB_SIZE;
    }

    T *alloc()
    {
        if (index >= SLAB_SIZE) {
            slabs.push_back(new_slab());
            index = 0;
        }

        T * p = slabs.back() + index;
        ++index;
        return p;
    }

private:
    static T *new_slab()
    {
        return static_cast<T*>(operator new(SLAB_SIZE * sizeof(T)));
    }

    FORBID_COPY(fixed_allocator_t);
};

#endif // _RE2C_UTIL_FIXED_ALLOCATOR_
