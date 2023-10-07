#ifndef _RE2C_CODEGEN_SYNTAX_
#define _RE2C_CODEGEN_SYNTAX_

#include <stdint.h>
#include <string>

#include "src/codegen/syntax_parser.h"
#include "src/constants.h"
#include "src/msg/location.h"
#include "src/msg/msg.h"
#include "src/util/allocator.h"
#include "src/util/check.h"
#include "src/util/forbid_copy.h"

namespace re2c {

class SyntaxConfig {
    OutAllocator& alc;
    const std::string& fname;
    FILE* file;
    size_t flen;
    uint8_t* buf;
    const uint8_t* cur; // current lexer position
    const uint8_t* tok; // token start
    const uint8_t* pos; // line start (used for error reporting)
    loc_t loc;

  public:
    Msg& msg;

  public:
    SyntaxConfig(const std::string& fname, Msg& msg, OutAllocator& alc);
    ~SyntaxConfig();
    Ret read();
    Ret parse();
    int lex_token(YYSTYPE* yylval);
    inline loc_t tok_loc() const;

    FORBID_COPY(SyntaxConfig);
};

Ret load_syntax_config(const std::string& fname, Msg& msg, OutAllocator& alc);

loc_t SyntaxConfig::tok_loc() const {
    DCHECK(pos <= tok);
    return {loc.line, static_cast<uint32_t>(tok - pos), loc.file};
}

} // namespace re2c

#endif // _RE2C_CODEGEN_SYNTAX_
