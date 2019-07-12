#include <stddef.h>

#include "src/util/get_dir.h"


namespace re2c {

void get_dir(std::string &path)
{
    // scan the path backwards until the first slash (if any) and clip
    size_t i = path.length();
    for (; i > 0; --i) {
        const char c = path[i - 1];
        if (c == '/' || c == '\\') break;
    }
    path.resize(i);
}

} // namespace re2c
