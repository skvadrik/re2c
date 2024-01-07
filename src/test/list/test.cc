#include <assert.h>
#include <vector>

#include "src/util/allocator.h"
#include "src/util/containers.h"

using namespace re2c;

namespace {

struct Int {
    int elem;
    Int* next;
};

using List = list_t<Int>;

Int* new_int(OutAllocator& alc, int elem){
    Int* x = alc.alloct<Int>(1);
    x->elem = elem;
    x->next = nullptr;
    return x;
}

List* new_list_int(OutAllocator& alc) {
    return new_list<Int>(alc);
}

void check_list(const List* l, const std::vector<int>& v) {
    size_t j = 0;
    for (const Int* i = l->head; i; i = i->next, ++j) {
        assert(j < v.size());
        assert(i->elem == v[j]);
        if (!i->next) assert(l->ptail == &i->next);
    }
    assert(j == v.size());
    if (j == 0) assert(l->ptail == &l->head);
}

} // anonymous namespace;

int main() {
    OutAllocator alc;
    List* l1 = new_list_int(alc);
    List* l2 = new_list_int(alc);
    List* l3 = new_list_int(alc);

    append(l1, l2);
    check_list(l1, {});
    check_list(l2, {});

    prepend(l2, l3);
    check_list(l2, {});
    check_list(l3, {});

    append(l1, new_int(alc, 1));
    append(l1, new_int(alc, 2));
    prepend(l1, new_int(alc, 3));
    prepend(l1, new_int(alc, 4));
    check_list(l1, {4, 3, 1, 2});

    append(l1, l2);
    check_list(l1, {4, 3, 1, 2});
    check_list(l2, {});

    prepend(l1, l2);
    check_list(l1, {4, 3, 1, 2});
    check_list(l2, {});

    append(l2, l1);
    check_list(l1, {});
    check_list(l2, {4, 3, 1, 2});

    prepend(l1, l2);
    check_list(l1, {4, 3, 1, 2});
    check_list(l2, {});

    prepend(l2, new_int(alc, 5));
    append(l2, new_int(alc, 6));
    prepend(l2, new_int(alc, 7));
    append(l2, new_int(alc, 8));
    check_list(l2, {7, 5, 6, 8});

    append(l3, new_int(alc, 0));
    check_list(l3, {0});

    prepend(l2, l3);
    check_list(l2, {0, 7, 5, 6, 8});
    check_list(l3, {});

    check_list(l1, {4, 3, 1, 2});
    check_list(l2, {0, 7, 5, 6, 8});
    append(l1, l2);
    check_list(l1, {4, 3, 1, 2, 0, 7, 5, 6, 8});
    check_list(l2, {});

    return 0;
}
