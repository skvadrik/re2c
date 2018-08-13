#ifndef _RE2C_AST_INPUT_
#define _RE2C_AST_INPUT_

#include <stdio.h>
#include <string>

#include "src/util/forbid_copy.h"

namespace re2c {

struct Input
{
    FILE * file;
    const std::string file_name;
    std::string escaped_file_name;

    explicit Input (const char * fn);
    ~Input ();
    bool open ();

    FORBID_COPY (Input);
};

} // namespace re2c

#endif // _RE2C_AST_INPUT_
