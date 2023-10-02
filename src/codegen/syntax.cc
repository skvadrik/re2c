#include <stdio.h>

#include "src/codegen/syntax.h"
#include "src/msg/msg.h"

namespace re2c {

Ret process_syntax_file(const std::string& fname) {
    FILE *file = fopen(fname.c_str(), "rb");
    if (!file) RET_FAIL(error("cannot open syntax file '%s'", fname.c_str()));

    // get file size
    fseek(file, 0, SEEK_END);
    size_t flen = static_cast<size_t>(ftell(file));
    fseek(file, 0, SEEK_SET);

    // allocate buffer
    uint8_t* buf = new uint8_t[flen + 1];

    // read file contents into buffer and append terminating zero at the end
    if (fread(buf, 1, flen, file) != flen) {
        RET_FAIL(error("cannot read syntax file '%s'", fname.c_str()));
    }
    buf[flen] = 0;

    const uint8_t* cursor = buf;
    CHECK_RET(parse_syntax_file(&cursor));

    delete[] buf;
    fclose(file);
    return Ret::OK;
}

} // namespace re2c
