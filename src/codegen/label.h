#ifndef _RE2C_CODE_LABEL_
#define _RE2C_CODE_LABEL_

#include "src/util/c99_stdint.h"


namespace re2c {

struct Label {
    uint32_t index;
    bool     used;
};

static const Label NO_LABEL = {~0u, false};

} // namespace re2c

#endif // _RE2C_CODE_LABEL_
