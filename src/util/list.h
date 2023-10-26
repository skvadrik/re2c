#ifndef _RE2C_UTIL_LIST_
#define _RE2C_UTIL_LIST_

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
        for (; *(list1->ptail); list1->ptail = &(*list1->ptail)->next);
    }
}

#endif // _RE2C_UTIL_LIST_
