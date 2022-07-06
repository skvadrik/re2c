#ifndef _RE2C_AST_INPUT_
#define _RE2C_AST_INPUT_

#include <stdio.h>
#include <string>
#include <vector>
#include <stdint.h>

#include "src/constants.h"
#include "src/util/attribute.h"
#include "src/util/forbid_copy.h"

namespace re2c {

struct Input {
    FILE* file;
    std::string name;
    std::string path;
    std::string escaped_name;
    const uint8_t* so; // start offset in buffer
    const uint8_t* eo; // end offset in buffer
    uint32_t line;
    uint32_t fidx;

    explicit Input(size_t fidx);
    ~Input();
    Ret open(const std::string& filename,
             const std::string* parent,
             const std::vector<std::string>& incpaths) NODISCARD;

    FORBID_COPY(Input);
};

} // namespace re2c

#endif // _RE2C_AST_INPUT_
