#ifndef _RE2C_CODEGEN_SYNTAX_
#define _RE2C_CODEGEN_SYNTAX_

#include <stdint.h>
#include <string>

#include "src/constants.h"

namespace re2c {

Ret process_syntax_file(const std::string& filepath);
Ret lex_syntax_file(const uint8_t* text);
Ret parse_syntax_file();

} // namespace re2c

#endif // _RE2C_CODEGEN_SYNTAX_
