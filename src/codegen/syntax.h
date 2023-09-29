#ifndef _RE2C_CODEGEN_SYNTAX_
#define _RE2C_CODEGEN_SYNTAX_

#include <stdint.h>

#include "src/constants.h"

namespace re2c {

Ret parse_syntax_file(const char* filepath);
Ret lex_syntax_file(const uint8_t* text);

} // namespace re2c

#endif // _RE2C_CODEGEN_SYNTAX_
