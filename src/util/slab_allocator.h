#ifndef _RE2C_UTIL_SLAB_ALLOCATOR_
#define _RE2C_UTIL_SLAB_ALLOCATOR_

#include "src/util/c99_stdint.h"
#include <algorithm> // std::for_each
#include <stdlib.h> // malloc, free
#include <vector> // slab queue

#include "src/util/forbid_copy.h"


namespace re2c {

/*
 * Works nice for tiny POD objects (~30 bytes and lower)
 * WARNING: Does not free memory for distinct objects!
 *
 * Works ~20 times faster, than linux's glibc allocator :]
 */
template<uint32_t SLAB_SIZE = 1024 * 1024, size_t ALIGN = 1>
class slab_allocator_t
{
    typedef std::vector<char*> slabs_t;

    slabs_t slabs_; /* quasilist of allocated slabs of 'SLAB_SIZE' bytes */
    char *current_slab_;
    char *current_slab_end_;

public:
    slab_allocator_t(): slabs_(), current_slab_(0), current_slab_end_(0) {}

    ~slab_allocator_t() { clear(); }

    void clear()
    {
        std::for_each(slabs_.rbegin(), slabs_.rend(), free);
        slabs_.clear();
        current_slab_ = current_slab_end_ = 0;
    }

    void *alloc(size_t size)
    {
        char *result;

        // next aligned address (we assume that malloc aligns depending on size)
        size = (size + ALIGN - 1) & ~(ALIGN - 1);

        if (size <= static_cast<size_t>(current_slab_end_ - current_slab_)) {
            // enough space in slab
            result = current_slab_;
            current_slab_ += size;
        }
        else if (size <= SLAB_SIZE / 4) {
            // start new slab
            current_slab_ = static_cast<char*>(malloc(SLAB_SIZE));
            current_slab_end_ = current_slab_ + SLAB_SIZE;
            slabs_.push_back(current_slab_);
            result = current_slab_;
            current_slab_ += size;
        }
        else {
            // large size; allocate standalone piece of memory
            result = static_cast<char*>(malloc(size));
            slabs_.push_back(result);
        }

        return result;
    }

    template<typename data_t>
    inline data_t *alloct(size_t n)
    {
        return static_cast<data_t*>(alloc(n * sizeof(data_t)));
    }

    FORBID_COPY(slab_allocator_t);
};

} // namespace re2c

#endif // _RE2C_UTIL_SLAB_ALLOCATOR_
