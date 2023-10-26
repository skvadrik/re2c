#include <stdio.h>

#include "src/codegen/syntax.h"
#include "src/msg/msg.h"

namespace re2c {

StxFile::StxFile(const std::string& fname, Msg& msg, OutAllocator& alc)
    : alc(alc)
    , fname(fname)
    , file(nullptr)
    , flen(0)
    , buf(nullptr)
    , cur(nullptr)
    , tok(nullptr)
    , pos(nullptr)
    , loc({1, 0, 0}) // file index 0 is reserved for syntax file
    , msg(msg)
{}

StxFile::~StxFile() {
    delete[] buf;
    if (file) fclose(file);
}

Ret StxFile::read() {
    msg.filenames.push_back(fname);

    file = fopen(fname.c_str(), "rb");
    if (!file) RET_FAIL(error("cannot open syntax file '%s'", fname.c_str()));

    // get file size
    fseek(file, 0, SEEK_END);
    flen = static_cast<size_t>(ftell(file));
    fseek(file, 0, SEEK_SET);

    // allocate buffer
    buf = new uint8_t[flen + 1];

    // read file contents into buffer and append terminating zero at the end
    if (fread(buf, 1, flen, file) != flen) {
        RET_FAIL(error("cannot read syntax file '%s'", fname.c_str()));
    }
    buf[flen] = 0;

    cur = tok = pos = buf;
    return Ret::OK;
}

Ret load_syntax_config(const std::string& fname, Msg& msg, OutAllocator& alc, Stx& stx) {
    StxFile sf(fname, msg, alc);
    CHECK_RET(sf.read());
    CHECK_RET(sf.parse(stx));
    return Ret::OK;
}

} // namespace re2c
