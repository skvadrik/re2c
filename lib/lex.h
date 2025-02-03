#ifndef _RE2C_LIB_LEX_
#define _RE2C_LIB_LEX_

#include "lib/parse.h"
#include "src/msg/location.h"
#include "src/regexp/regexp.h"
#include "src/parse/ast.h"

namespace re2c {

int lex(RE2C_LIB_STYPE* yylval, const uint8_t*& pattern, Ast& ast);
const AstNode* parse(const char* pattern, Ast& ast);
extern const AstNode* regexp;

} // namespace re2c

#endif // _RE2C_LIB_LEX_
