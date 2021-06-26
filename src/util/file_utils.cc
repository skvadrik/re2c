#include <stddef.h>

#include "src/util/file_utils.h"


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

std::string escape_backslashes(const std::string &str)
{
    const size_t len = str.length();
    std::string escaped;
    escaped.reserve(len * 2);

    for (size_t i = 0; i < len;) {
        char c = str[i++];
        escaped += c;
        if (c == '\\') {
            // escape backslash
            escaped += '\\';
            // if already escaped, skip next character
            if (i < len && str[i] == '\\') ++i;
        }
    }

    return escaped;
}

} // namespace re2c
