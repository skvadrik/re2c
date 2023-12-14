#include <stdint.h>

#include "src/msg/msg.h"
#include "src/options/syntax_parser.h"
#include "src/util/string_utils.h"

/*!re2c
    eof = [\x00];
    eol = "\n";
    esc = "\\";
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

int StxFile::lex_token(STX_STYPE* yylval) {
    const uint8_t* YYMARKER, *p;
    /*!stags:re2c format = "const uint8_t* @@;"; */

start:
    tok = cur;
/*!local:re2c
    eof { return STX_EOF; }
    eol | comment {
        ++loc.line;
        pos = cur;
        goto start;
    }
    space+ { goto start; }
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
            return STX_error;
        }
    }
    ["] { goto str; }
    [?:;,(){}[\]] { return cur[-1]; }
    * {
        msg.error(tok_loc(), "unexpected character: '%c'", cur[-1]);
        return STX_error;
    }
*/

str: /*!local:re2c
    esc esc         { tmp_str += '\\'; goto str; }
    esc ["]         { tmp_str += '"'; goto str; }
    esc [a]         { tmp_str += '\a'; goto str; }
    esc [b]         { tmp_str += '\b'; goto str; }
    esc [f]         { tmp_str += '\f'; goto str; }
    esc [n]         { tmp_str += '\n'; goto str; }
    esc [r]         { tmp_str += '\r'; goto str; }
    esc [t]         { tmp_str += '\t'; goto str; }
    esc [v]         { tmp_str += '\v'; goto str; }
    esc [x][0-9]{2} { tmp_str += static_cast<char>(unesc_hex(cur - 4, cur)); goto str; }
    [^"\\\x00\n]    { tmp_str += static_cast<char>(cur[-1]); goto str; }
    ["] {
        yylval->str = copystr(tmp_str, alc);
        tmp_str.clear();
        return STX_STRING;
    }
    * {
        tok = cur - 1;
        msg.error(tok_loc(), "syntax error in string literal");
        return STX_error;
    }
*/
    UNREACHABLE();
    return STX_error; // unreachable
}

} // namespace re2c
