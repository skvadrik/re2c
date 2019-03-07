#ifndef _RE2C_MSG_LOCATION_
#define _RE2C_MSG_LOCATION_

#include "src/util/c99_stdint.h"


namespace re2c {

struct loc_t
{
    uint32_t line;
    uint32_t coln;
    uint32_t file;
};

static const loc_t ATSTART = {1, 0, 0};
static const loc_t NOWHERE = {~0u, ~0u, ~0u};

enum locfmt_t
    { LOCFMT_GNU
    , LOCFMT_MSVC
    };

} // namespace re2c

#endif // _RE2C_MSG_LOCATION_

