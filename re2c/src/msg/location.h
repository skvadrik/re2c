#ifndef _RE2C_MSG_LOCATION_
#define _RE2C_MSG_LOCATION_

#include "src/util/c99_stdint.h"
#include <string.h>


namespace re2c {

struct loc_t
{
    uint32_t line;
    uint32_t coln;
    std::string fname;

    loc_t(uint32_t l, uint32_t c, const std::string &f)
        : line(l), coln(c), fname(f) {}
};

} // namespace re2c

#endif // _RE2C_MSG_LOCATION_

