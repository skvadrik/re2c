#include <stdint.h>

#include "src/codegen/syntax.h"
#include "src/msg/msg.h"
#include "syntax_parser.h"

namespace re2c {

Ret lex_syntax_file(const uint8_t* text) {
    const uint8_t* YYCURSOR = text;
    const uint8_t* YYMARKER;

/*!local:re2c
    re2c:yyfill:enable = 0;
    re2c:define:YYCTYPE = uint8_t;

    * { RET_FAIL(error("syntax error in syntax file")); }
*/
    return Ret::OK;
}

} // namespace re2c
