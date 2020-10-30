#ifndef _RE2C_UTIL_ALLOCATE_
#define _RE2C_UTIL_ALLOCATE_

#include <stddef.h> // size_t


namespace re2c {

// useful fof allocation of arrays of POD objects
// 'new []' invokes default constructor for each object
// this can be unacceptable for performance reasons
template<typename T>
T *allocate(size_t n)
{
    void *p = operator new(n * sizeof(T));
    return static_cast<T*>(p);
}

// Simple memory buffer with size. Suitable for allocating
// (and possibly growing) uninitialized storage.
template<typename T>
struct membuf_t {
    T *ptr;
    size_t size;
};

template<typename T>
void init_membuf(membuf_t<T> &buf, size_t size)
{
    buf.ptr = allocate<T>(size);
    buf.size = size;
}

template<typename T>
void free_membuf(membuf_t<T> &buf)
{
    operator delete(buf.ptr);
    buf.ptr = 0;
    buf.size = 0;
}

template<typename T>
void grow_membuf(membuf_t<T> &buf, size_t size)
{
    if (size > buf.size) {
        buf.size = size * 2;
        operator delete(buf.ptr);
        buf.ptr = allocate<T>(buf.size);
    }
}

} // namespace re2c

#endif // _RE2C_UTIL_ALLOCATE_
