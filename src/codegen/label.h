#ifndef _RE2C_CODE_LABEL_
#define _RE2C_CODE_LABEL_

#include "src/util/c99_stdint.h"


namespace re2c {

struct Label {
    uint32_t index;
    bool     used;
};

template<typename Allocator>
Label *new_label(Allocator &alc, uint32_t index)
{
    Label *l = alc.template alloct<Label>(1);
    l->index = index;
    l->used = false;
    return l;
}

} // namespace re2c

#endif // _RE2C_CODE_LABEL_
