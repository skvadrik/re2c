#ifndef _RE2C_CODEGEN_SYNTAX_
#define _RE2C_CODEGEN_SYNTAX_

#include <stdint.h>
#include <string>

#include "src/codegen/syntax_parser.h"
#include "src/constants.h"
#include "src/util/forbid_copy.h"

namespace re2c {

class SyntaxConfig {
    const std::string& fname;
    FILE* file;
    size_t flen;
    uint8_t* buffer;
    const uint8_t* cursor;

  public:
    SyntaxConfig(const std::string& fname);
    ~SyntaxConfig();
    Ret read();
    Ret parse();
    int lex_token(YYSTYPE* yylval);

    FORBID_COPY(SyntaxConfig);
};

Ret load_syntax_config(const std::string& fname);

} // namespace re2c

#endif // _RE2C_CODEGEN_SYNTAX_
