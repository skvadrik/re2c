#include <stdint.h>

#include "src/msg/msg.h"
#include "src/options/opt.h"
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

/*!max:re2c format = "size_t LexerState::maxfill_syntax() { return @@; }"; */

#define RET_TOK(t) do { token = t; return Ret::OK; } while(0)

#define RET_GOPT(b) do { token = STX_GOPT; yylval->gopt = b; return Ret::OK; } while(0)
#define RET_LOPT(b) do { token = STX_LOPT; yylval->lopt = b; return Ret::OK; } while(0)

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
    ["] { tmp_str.clear(); goto str; }
    [(] space* { goto opt; }
    [?:;,){}[\]] { RET_TOK(cur[-1]); }
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

opt:
    tok = cur;
/*!local:re2c
    // Global conditionals.
    //
    // A subset of options is exported for use in `code:*` configurations in syntax files.
    // Both constant and mutable options are allowed here, as they are used during codegen,
    // when block-level options are already known.
    //
    // These options are part of the syntax file API and should not be removed or changed.

    "api.pointers"                   { RET_GOPT(StxGOpt::API_DEFAULT); }
    "api.generic"                    { RET_GOPT(StxGOpt::API_CUSTOM); }
    "api_style.functions"            { RET_GOPT(StxGOpt::API_STYLE_FUNCTIONS); }
    "api_style.freeform"             { RET_GOPT(StxGOpt::API_STYLE_FREEFORM); }
    "code_model.goto_label"          { RET_GOPT(StxGOpt::CODE_MODEL_GOTO_LABEL); }
    "code_model.loop_switch"         { RET_GOPT(StxGOpt::CODE_MODEL_LOOP_SWITCH); }
    "code_model.recursive_functions" { RET_GOPT(StxGOpt::CODE_MODEL_REC_FUNC); }
    "start_conditions"               { RET_GOPT(StxGOpt::START_CONDITIONS); }
    "storable_state"                 { RET_GOPT(StxGOpt::STORABLE_STATE); }
    "date"                           { RET_GOPT(StxGOpt::DATE); }
    "version"                        { RET_GOPT(StxGOpt::VER); }
    "case_ranges"                    { RET_GOPT(StxGOpt::CASE_RANGES); }
    "unsafe"                         { RET_GOPT(StxGOpt::UNSAFE); }
    "loop_label"                     { RET_GOPT(StxGOpt::LOOP_LABEL); }

    // Local conditionals.

    "have_init"    { RET_LOPT(StxLOpt::HAVE_INIT); }
    "have_cond"    { RET_LOPT(StxLOpt::HAVE_COND); }
    "have_type"    { RET_LOPT(StxLOpt::HAVE_TYPE); }
    "have_args"    { RET_LOPT(StxLOpt::HAVE_ARGS); }
    "have_argmods" { RET_LOPT(StxLOpt::HAVE_ARGMODS); }
    "multival"     { RET_LOPT(StxLOpt::MULTIVAL); }

    * { RET_FAIL(error_at_cur("unknown option")); }
*/

    UNREACHABLE();
    return Ret::FAIL; // unreachable
}

#undef RET_TOK
#undef RET_GOPT
#undef RET_LOPT

} // namespace re2c
