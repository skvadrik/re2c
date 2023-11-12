#include <stdint.h>

#include "src/codegen/syntax.h"
#include "src/codegen/syntax_parser.h"
#include "src/msg/msg.h"
#include "src/util/string_utils.h"

/*!re2c
    eof = [\x00];
    eol = "\n";
    space = [ \t];
    name = [a-zA-Z_][a-zA-Z_0-9.-]*;
    number = [-]? [0-9]+;
    comment = "//" [^\x00\n]* eol;

    re2c:yyfill:enable = 0;
    re2c:define:YYCTYPE = uint8_t;
    re2c:define:YYCURSOR = cur;
    re2c:tags = 1;
*/

namespace re2c {

int StxFile::lex_token(YYSTYPE* yylval) {
    const uint8_t* YYMARKER, *p;
    /*!stags:re2c format = "const uint8_t* @@;"; */

start:
    tok = cur;
/*!local:re2c
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
    "code:" name @p space* "=" {
        yylval->str = newcstr(tok, p, alc);
        return STX_CONF_CODE;
    }
    name @p space* "=" {
        yylval->str = newcstr(tok, p, alc);
        return STX_CONF;
    }
    name {
        yylval->str = newcstr(tok, cur, alc);
        return STX_NAME;
    }
    number {
        if (s_to_i32_unsafe(tok, cur, yylval->num)) {
            return STX_NUMBER;
        } else {
            msg.error(tok_loc(), "configuration value overflow");
            return YYerror;
        }
    }
    ["] ([^"\x00\n] | [\\]["])* ["] {
        yylval->str = newcstr(tok + 1, cur - 1, alc);
        return STX_STRING;
    }
    [?:;,(){}[\]] {
        return cur[-1];
    }
    * {
        msg.error(tok_loc(), "unexpected character: '%c'", cur[-1]);
        return YYerror;
    }
*/

    return YYerror; // unreachable
}

} // namespace re2c
