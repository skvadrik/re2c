#ifndef _RE2C_CODEGEN_SYNTAX_
#define _RE2C_CODEGEN_SYNTAX_

#include <stdint.h>
#include <string>

#include "src/codegen/syntax_parser.h"
#include "src/constants.h"

namespace re2c {

Ret process_syntax_file(const std::string& fname);
int lex_syntax_file(YYSTYPE* yylval, const uint8_t** cursor);
Ret parse_syntax_file(const uint8_t** cursor);

} // namespace re2c

#endif // _RE2C_CODEGEN_SYNTAX_
