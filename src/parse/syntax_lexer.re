#include <stdint.h>

#include "src/msg/msg.h"
#include "src/parse/input.h"
#include "src/parse/syntax_parser.h"
#include "src/util/string_utils.h"

#define YYFILL(n) do { \
    if (!fill(n)) RET_FAIL(error_at_cur("unexpected end of input in configuration")); \
} while(0)

/*!re2c
    eof = [\x00];
    eol = "\n";
    esc = "\\";
    space = [ \t];
    name = [a-zA-Z_][a-zA-Z_0-9.-]*;
    number = [-]? [0-9]+;
    comment = "//" [^\x00\n]* eol;

    re2c:define:YYCTYPE = uint8_t;
    re2c:define:YYCURSOR = cur;
    re2c:define:YYMARKER = mar;
    re2c:define:YYLIMIT = lim;
    re2c:tags = 1;
*/

namespace re2c {

#define RET_TOK(t) do { token = t; return Ret::OK; } while(0)

Ret Input::lex_syntax_token(STX_STYPE* yylval, Opt& opts, int& token) {
    const uint8_t* p;
    /*!stags:re2c format = "const uint8_t* @@;"; */

start:
    tok = cur;
    location = cur_loc();
/*!local:re2c
    eof { RET_TOK(STX_EOF); }
    eol | comment {
        next_line();
        goto start;
    }
    space+ { goto start; }
    "conf:" {
        CHECK_RET(lex_conf(opts));
        goto start;
    }
    "code:" name @p space* "=" {
        yylval->str = newcstr(tok, p, alc);
        RET_TOK(STX_CONF_CODE);
    }
    name @p space* "=" {
        yylval->str = newcstr(tok, p, alc);
        RET_TOK(STX_CONF);
    }
    name {
        yylval->str = newcstr(tok, cur, alc);
        RET_TOK(STX_NAME);
    }
    number {
        if (s_to_i32_unsafe(tok, cur, yylval->num)) {
            RET_TOK(STX_NUMBER);
        }
        RET_FAIL(error_at_tok("configuration value overflow"));
    }
    ["] { goto str; }
    [?:;,(){}[\]] { RET_TOK(cur[-1]); }
    * { RET_FAIL(error_at_tok("unexpected character: '%c'", cur[-1])); }
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
        RET_TOK(STX_STRING);
    }
    * {
        tok = cur - 1;
        RET_FAIL(error_at_tok("syntax error in string literal"));
    }
*/
    UNREACHABLE();
    return Ret::FAIL; // unreachable
}

#undef RET_TOK

} // namespace re2c
