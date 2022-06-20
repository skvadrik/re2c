#ifndef _RE2C_UTIL_CONTAINERS_
#define _RE2C_UTIL_CONTAINERS_

#include <assert.h>
#include <string.h>

namespace re2c {

template<typename T>
class array_t {
    T* data_;
    uint32_t size_;

  public:
    template<typename Allocator>
    void init(const T* data, size_t size, Allocator& alc) {
        if (size > 0) {
            assert(size < UINT32_MAX);
            size_ = static_cast<uint32_t>(size);
            data_ = alc.template alloct<T>(size);
            memcpy(data_, data, size * sizeof(T));
        } else {
            data_ = nullptr;
            size_ = 0;
        }
    }

    bool empty() const { return size_ == 0; }
    size_t size() const { return size_; }

    T& operator[](size_t at) { return data_[at]; }
    const T& operator[](size_t at) const { return data_[at]; }

    T* begin() { return data_; }
    T* end() { return data_ + size_; }
    const T* begin() const { return data_; }
    const T* end() const { return data_ + size_; }

    T& front() { return data_[0]; }
    T& back() { return data_[size_ - 1]; }
    const T& front() const { return data_[0]; }
    const T& back() const { return data_[size_ - 1]; }
};

// Useful for allocation of arrays of POD objects without invoking a constructor (`new []` invokes
// default constructor for each object, and this can be unacceptable for performance reasons).
template<typename T>
T* allocate(size_t n) {
    void* p = operator new(n * sizeof(T));
    return static_cast<T*>(p);
}

// Simple memory buffer with size. Suitable for allocating (and growing) uninitialized storage.
template<typename T>
struct membuf_t {
    T* ptr_;
    size_t size_;

    void init(size_t size) {
        ptr_ = allocate<T>(size);
        size_ = size;
    }

    void free() {
        operator delete(ptr_);
        ptr_ = nullptr;
        size_ = 0;
    }

    void grow(size_t size) {
        if (size > size_) {
            size_ = size * 2;
            operator delete(ptr_);
            ptr_ = allocate<T>(size_);
        }
    }
};

} // namespace re2c

#endif // _RE2C_UTIL_CONTAINERS_
