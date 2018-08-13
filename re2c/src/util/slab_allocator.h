#ifndef _RE2C_UTIL_SLAB_ALLOCATOR_
#define _RE2C_UTIL_SLAB_ALLOCATOR_

#include "src/util/c99_stdint.h"
#include <algorithm> // std::for_each
#include <stdlib.h> // malloc, free
#include <vector> // slab queue

#include "src/util/forbid_copy.h"

/*
 * Works nice for tiny POD objects (~30 bytes and lower)
 * WARNING: Does not free memory for distinct objects!
 *
 * Works ~20 times faster, than linux's glibc allocator :]
 */
template<uint32_t MAXIMUM_INLINE = 4 * 1024,
    uint32_t SLAB_SIZE = 1024 * 1024,
    size_t ALIGN = 1>
class slab_allocator_t
{
    typedef std::vector<char*> slabs_t;

    slabs_t slabs_; /* quasilist of allocated slabs of 'SLAB_SIZE' bytes */
    char *current_slab_;
    char *current_slab_end_;

public:
    slab_allocator_t(): slabs_(), current_slab_(0), current_slab_end_(0) {}

    ~slab_allocator_t() { std::for_each(slabs_.rbegin(), slabs_.rend(), free); }

    void *alloc(size_t size)
    {
        char *result;

        /* alignment */
        size += ALIGN - size % ALIGN;

        /* very large objects */
        if (size > MAXIMUM_INLINE) {
            result = static_cast<char*>(malloc(size));
            slabs_.push_back(result);
            return result;
        }

        /* no space in slab */
        const size_t yet_in_slab = static_cast<size_t>(current_slab_end_ - current_slab_);
        if (yet_in_slab < size) {
            current_slab_ = static_cast<char*>(malloc(SLAB_SIZE));
            current_slab_end_ = current_slab_ + SLAB_SIZE;
            slabs_.push_back(current_slab_);
        }

        result = current_slab_;
        current_slab_ += size;

        return result;
    }

    template<typename data_t>
    inline data_t *alloct(size_t n)
    {
        return static_cast<data_t*>(alloc(n * sizeof(data_t)));
    }

    FORBID_COPY(slab_allocator_t);
};

#endif // _RE2C_UTIL_SLAB_ALLOCATOR_
