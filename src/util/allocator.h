#ifndef _RE2C_UTIL_ALLOCATOR_
#define _RE2C_UTIL_ALLOCATOR_

#include <stdint.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>

#include "src/util/forbid_copy.h"

namespace re2c {

// Different allocator types for data with different life spans.
enum class AllocatorKind: uint32_t {
    AST, // abstract syntax tree is shared between blocks and lives when processing the entire file
    IR,  // intermediate represenations are only alive when processing a single DFA
    DFA, // a DFA is alive when processing all DFA in a block and doing codegen for a block
    OUT  // output is always alive (parts of it are constructed as early as in the parser)
};

// Works nice for tiny POD objects (~30 bytes and lower)
// WARNING: Does not free memory for distinct objects!
//
// Works ~20 times faster, than linux's glibc allocator :]
//
template<AllocatorKind kind, uint32_t SLAB_SIZE = 1024 * 1024, size_t ALIGN = 1>
class slab_allocator_t {
    using slabs_t = std::vector<char*>;

    slabs_t slabs_; // quasilist of allocated slabs of `SLAB_SIZE` bytes
    char* current_slab_;
    char* current_slab_end_;

  public:
    slab_allocator_t(): slabs_(), current_slab_(nullptr), current_slab_end_(nullptr) {}
    ~slab_allocator_t() { clear(); }

    void clear() {
        std::for_each(slabs_.rbegin(), slabs_.rend(), free);
        slabs_.clear();
        current_slab_ = current_slab_end_ = nullptr;
    }

    void* alloc(size_t size) {
        char* result;

        // next aligned address (we assume that malloc aligns depending on size)
        size = (size + ALIGN - 1) & ~(ALIGN - 1);

        if (size <= static_cast<size_t>(current_slab_end_ - current_slab_)) {
            // enough space in slab
            result = current_slab_;
            current_slab_ += size;
        } else if (size <= SLAB_SIZE / 4) {
            // start new slab
            current_slab_ = static_cast<char*>(malloc(SLAB_SIZE));
            current_slab_end_ = current_slab_ + SLAB_SIZE;
            slabs_.push_back(current_slab_);
            result = current_slab_;
            current_slab_ += size;
        } else {
            // large size; allocate standalone piece of memory
            result = static_cast<char*>(malloc(size));
            slabs_.push_back(result);
        }

        return result;
    }

    template<typename data_t>
    inline data_t* alloct(size_t n) {
        return static_cast<data_t*>(alloc(n * sizeof(data_t)));
    }

    slab_allocator_t(slab_allocator_t&&) = default;
    slab_allocator_t& operator=(slab_allocator_t&&) = default;
    FORBID_COPY(slab_allocator_t);
};

// Use maximum alignment.
// Use different types to prevent accidentally mixing allocators for data with different life spans.
using AstAllocator = slab_allocator_t<AllocatorKind::AST, 16 * 4096, sizeof(void*)>;
using IrAllocator = slab_allocator_t<AllocatorKind::IR, 16 * 4096, sizeof(void*)>;
using DfaAllocator = slab_allocator_t<AllocatorKind::DFA, 16 * 4096, sizeof(void*)>;
using OutAllocator = slab_allocator_t<AllocatorKind::OUT, 16 * 4096, sizeof(void*)>;

} // namespace re2c

#endif // _RE2C_UTIL_ALLOCATOR_
