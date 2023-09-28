#include <stdio.h>

#include "src/codegen/syntax.h"
#include "src/msg/msg.h"

namespace re2c {

Ret parse_syntax_file(const char* filepath) {
    FILE *file = fopen(filepath, "rb");
    if (!file) RET_FAIL(error("cannot open syntax file '%s'", filepath));

    fclose(file);
    return Ret::OK;
}

} // namespace re2c
