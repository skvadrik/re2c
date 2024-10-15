#ifndef _RE2C_UTIL_CONTAINERS_
#define _RE2C_UTIL_CONTAINERS_

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <limits>
#include <map>
#include <vector>

#include "src/util/check.h"

namespace re2c {

template<typename T>
class array_t {
    T* data_;
    uint32_t size_;

  public:
    template<typename Allocator>
    void init(const T* data, size_t size, Allocator& alc) {
        if (size > 0) {
            CHECK(size < UINT32_MAX);
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

// Lookup table with O(1) random access and  O(log(n)) insertion (a vector paired with a map).
template<typename data_t, typename hash_t = uint32_t>
struct lookup_t {
    enum : uint32_t { NIL = ~0u };

  private:
    struct elem_t {
        uint32_t next;
        data_t data;

        elem_t(uint32_t n, const data_t& d): next(n), data(d) {}
    };

    std::vector<elem_t> elems;
    std::map<hash_t, uint32_t> lookup;

  public:
    lookup_t(): elems(), lookup() {}

    uint32_t size() const {
        return static_cast<uint32_t>(elems.size());
    }

    data_t& operator[](uint32_t idx) {
        DCHECK(idx < elems.size());
        return elems[idx].data;
    }

    const data_t& operator[](uint32_t idx) const {
        DCHECK(idx < elems.size());
        return elems[idx].data;
    }

    uint32_t push(hash_t hash, const data_t& data) {
        DCHECK(elems.size() < NIL);
        const uint32_t idx = static_cast<uint32_t>(elems.size());
        elems.push_back(elem_t(head(hash), data));
        lookup[hash] = idx;
        return idx;
    }

    template<typename pred_t>
    uint32_t find_with(hash_t hash, const data_t& data, pred_t& pred) const {
        return find(head(hash), data, pred);
    }

    template<typename pred_t>
    uint32_t find_next_with(uint32_t prev, const data_t& data, pred_t& pred) const {
        return find(elems[prev].next, data, pred);
    }

  private:
    uint32_t head(hash_t h) const {
        typename std::map<hash_t, uint32_t>::const_iterator x = lookup.find(h);
        return x == lookup.end() ? NIL : x->second;
    }

    template<typename pred_t>
    uint32_t find(uint32_t next, const data_t& data, pred_t& pred) const  {
        for (uint32_t i = next; i != NIL;) {
            const elem_t& e = elems[i];
            if (pred(e.data, data)) {
                return i;
            }
            i = e.next;
        }
        return NIL;
    }
};

// A wrapper over std::vector where all elements are unique (a simplistic replacement for a set).
// Insertion is O(n), as it loops over all elements to ensure they are different.
template<typename T>
class uniq_vector_t : public std::vector<T> {
    using base_t = std::vector<T>;

    void push_back(const T& v) = delete;
    template<class... Args> void emplace_back(Args&&... args) = delete;
    // Should also hide all `insert` methods...

  public:
    size_t find_or_add(const T& v) {
        const size_t size = base_t::size();
        for (size_t i = 0; i < size; ++i) {
            if (base_t::operator[](i) == v) {
                return i;
            }
        }
        base_t::push_back(v);
        return size;
    }
};

template<typename T>
struct list_t {
    T* head;
    T** ptail;
};

template<typename T, typename Allocator>
inline list_t<T>* new_list(Allocator& alc) {
    list_t<T>* x = alc.template alloct<list_t<T> >(1);
    x->head = nullptr;
    x->ptail = &x->head;
    return x;
}

template<typename T>
inline void append(list_t<T>* list, T* elem) {
    if (elem != nullptr) {
        *list->ptail = elem;
        list->ptail = &elem->next;
    }
}

template<typename T>
inline void prepend(list_t<T>* list, T* elem) {
    if (elem != nullptr) {
        if (!list->head) {
            list->ptail = &elem->next;
        }
        elem->next = list->head;
        list->head = elem;
    }
}

template<typename T>
inline void append(list_t<T>* list1, list_t<T>* list2) {
    if (list2 && list2->head) {
        *list1->ptail = list2->head;
        list1->ptail = list2->ptail;
        // for safety, clear the old list
        list2->head = nullptr;
        list2->ptail = &list2->head;
    }
}

template<typename T>
inline void prepend(list_t<T>* list1, list_t<T>* list2) {
    if (list2 && list2->head) {
        *list2->ptail = list1->head;
        if (!list1->head) list1->ptail = list2->ptail;
        list1->head = list2->head;
        // for safety, clear the old list
        list2->head = nullptr;
        list2->ptail = &list2->head;
    }
}

} // namespace re2c

#endif // _RE2C_UTIL_CONTAINERS_
