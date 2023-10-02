#include <stdint.h>

#include "src/codegen/syntax.h"
#include "src/codegen/syntax_parser.h"
#include "src/msg/msg.h"

/*!re2c
    eof = [\x00];
    eol = "\n";
    space = [ \t];
    name = [a-zA-Z_][a-zA-Z_0-9-]*;
    number = [-]? [0-9]+;
    comment = "//" [^\x00\n]* eol;

    re2c:yyfill:enable = 0;
    re2c:define:YYCTYPE = uint8_t;
*/

namespace re2c {

#define RET_TOK(token) do { \
    *cursor = YYCURSOR; \
    return token; \
} while (0)

int lex_syntax_file(YYSTYPE* yylval, const uint8_t** cursor) {
    const uint8_t* YYCURSOR = *cursor;
    const uint8_t* YYMARKER;

start: /*!local:re2c
    eof {
        RET_TOK(YYEOF);
    }
    eol | comment {
        goto start;
    }
    space+ {
        goto start;
    }
    name space* "=" {
        yylval->str = "<config>";
        RET_TOK(TOKEN_CONFIG);
    }
    name {
        yylval->str = "<name>";
        RET_TOK(TOKEN_NAME);
    }
    number {
        yylval->num = 123;
        RET_TOK(TOKEN_NUMBER);
    }
    ["] ([^"\x00\n] | [\\]["])* ["] {
        yylval->str = "<string>";
        RET_TOK(TOKEN_STRING);
    }
    [=?:;(){}[\]] {
        RET_TOK(YYCURSOR[-1]);
    }
    * {
        error("syntax error in syntax file");
        RET_TOK(TOKEN_ERROR);
    }
*/

    RET_TOK(TOKEN_ERROR); // unreachable
}

#undef RET_TOK

} // namespace re2c
