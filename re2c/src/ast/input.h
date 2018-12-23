#ifndef _RE2C_AST_INPUT_
#define _RE2C_AST_INPUT_

#include <stdio.h>
#include <string>
#include "src/util/forbid_copy.h"

namespace re2c {

struct Input
{
    FILE *file;
    std::string name;
    std::string escaped_name;

    Input();
    ~Input();
    bool open(const char *filename);

    FORBID_COPY(Input);
};

} // namespace re2c

#endif // _RE2C_AST_INPUT_
