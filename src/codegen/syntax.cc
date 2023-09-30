#include <stdio.h>

#include "src/codegen/syntax.h"
#include "src/msg/msg.h"

namespace re2c {

Ret process_syntax_file(const std::string& filepath) {
    FILE *file = fopen(filepath.c_str(), "rb");
    if (!file) RET_FAIL(error("cannot open syntax file '%s'", filepath.c_str()));

    fclose(file);
    return Ret::OK;
}

} // namespace re2c
