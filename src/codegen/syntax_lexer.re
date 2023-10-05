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
    re2c:define:YYCURSOR = cur;
*/

namespace re2c {

int SyntaxConfig::lex_token(YYSTYPE* yylval) {
    const uint8_t* YYMARKER;

start: /*!local:re2c
    eof {
        return YYEOF;
    }
    eol | comment {
        ++loc.line;
        pos = cur;
        goto start;
    }
    space+ {
        goto start;
    }
    name space* "=" {
        yylval->str = "<config>";
        return TOKEN_CONFIG;
    }
    name {
        yylval->str = "<name>";
        return TOKEN_NAME;
    }
    number {
        yylval->num = 123;
        return TOKEN_NUMBER;
    }
    ["] ([^"\x00\n] | [\\]["])* ["] {
        yylval->str = "<string>";
        return TOKEN_STRING;
    }
    [=?:;(){}[\]] {
        return cur[-1];
    }
    * {
        msg.error(cur_loc(), "unexpected character: '%c'", cur[-1]);
        return YYerror;
    }
*/

    return YYerror; // unreachable
}

} // namespace re2c
