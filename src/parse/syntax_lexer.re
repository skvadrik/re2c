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
    word = [a-zA-Z_][a-zA-Z_0-9.-]*;
    number = [-]? [0-9]+;
    comment = "//" [^\x00\n]* eol;

    re2c:define:YYCTYPE = uint8_t;
    re2c:define:YYCURSOR = cur;
    re2c:define:YYMARKER = mar;
    re2c:define:YYLIMIT = lim;
*/

namespace re2c {

/*!max:re2c format = "size_t LexerState::maxfill_syntax() { return @@; }"; */

#define RET_TOK(t) do { token = t; return Ret::OK; } while(0)

#define RET_CONF_ID(id) do { token = STX_CONF_ID; yylval->conf_id = id; return Ret::OK; } while(0)
#define RET_VAR_ID(id)  do { token = STX_VAR_ID; yylval->var_id = id; return Ret::OK; } while(0)

#define RET_GOPT(b) do { token = STX_GOPT; yylval->gopt = b; return Ret::OK; } while(0)
#define RET_LOPT(b) do { token = STX_LOPT; yylval->lopt = b; return Ret::OK; } while(0)

Ret Input::lex_syntax_token(STX_STYPE* yylval, Opt& opts, int& token) {
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

    "code:" { goto code; }

    // list configurations
    "api"        { RET_CONF_ID(StxConfId::API); }
    "api_style"  { RET_CONF_ID(StxConfId::API_STYLE); }
    "code_model" { RET_CONF_ID(StxConfId::CODE_MODEL); }
    "target"     { RET_CONF_ID(StxConfId::TARGET); }

    // word configurations
    "computed_goto"            { RET_CONF_ID(StxConfId::COMPUTED_GOTO); }
    "case_ranges"              { RET_CONF_ID(StxConfId::CASE_RANGES); }
    "semicolons"               { RET_CONF_ID(StxConfId::SEMICOLONS); }
    "implicit_bool_conversion" { RET_CONF_ID(StxConfId::IMPLICIT_BOOL_CONVERSION); }
    "backtick_quoted_strings"  { RET_CONF_ID(StxConfId::BACKTICK_QUOTED_STRINGS); }
    "standalone_single_quotes" { RET_CONF_ID(StxConfId::STANDALONE_SINGLE_QUOTES); }

    // local variables
    "arg"       { RET_VAR_ID(StxVarId::ARG); }
    "argmods"   { RET_VAR_ID(StxVarId::ARGMODS); }
    "argname"   { RET_VAR_ID(StxVarId::ARGNAME); }
    "argtype"   { RET_VAR_ID(StxVarId::ARGTYPE); }
    "array"     { RET_VAR_ID(StxVarId::ARRAY); }
    "backup"    { RET_VAR_ID(StxVarId::BACKUP); }
    "branch"    { RET_VAR_ID(StxVarId::BRANCH); }
    "case"      { RET_VAR_ID(StxVarId::CASE); }
    "char"      { RET_VAR_ID(StxVarId::CHAR); }
    "cond"      { RET_VAR_ID(StxVarId::COND); }
    "ctype"     { RET_VAR_ID(StxVarId::CTYPE); }
    "cursor"    { RET_VAR_ID(StxVarId::CURSOR); }
    "date"      { RET_VAR_ID(StxVarId::DATE); }
    "debug"     { RET_VAR_ID(StxVarId::DEBUG); }
    "elem"      { RET_VAR_ID(StxVarId::ELEM); }
    "expr"      { RET_VAR_ID(StxVarId::EXPR); }
    "fn"        { RET_VAR_ID(StxVarId::FN); }
    "file"      { RET_VAR_ID(StxVarId::FILE); }
    "fndecl"    { RET_VAR_ID(StxVarId::FNDECL); }
    "fndef"     { RET_VAR_ID(StxVarId::FNDEF); }
    "index"     { RET_VAR_ID(StxVarId::INDEX); }
    "init"      { RET_VAR_ID(StxVarId::INIT); }
    "label"     { RET_VAR_ID(StxVarId::LABEL); }
    "lhs"       { RET_VAR_ID(StxVarId::LHS); }
    "line"      { RET_VAR_ID(StxVarId::LINE); }
    "marker"    { RET_VAR_ID(StxVarId::MARKER); }
    "name"      { RET_VAR_ID(StxVarId::NAME); }
    "num"       { RET_VAR_ID(StxVarId::NUM); }
    "op"        { RET_VAR_ID(StxVarId::OP); }
    "peek"      { RET_VAR_ID(StxVarId::PEEK); }
    "retval"    { RET_VAR_ID(StxVarId::RETVAL); }
    "rhs"       { RET_VAR_ID(StxVarId::RHS); }
    "row"       { RET_VAR_ID(StxVarId::ROW); }
    "size"      { RET_VAR_ID(StxVarId::SIZE); }
    "skip"      { RET_VAR_ID(StxVarId::SKIP); }
    "state"     { RET_VAR_ID(StxVarId::STATE); }
    "stmt"      { RET_VAR_ID(StxVarId::STMT); }
    "type"      { RET_VAR_ID(StxVarId::TYPE); }
    "typecast"  { RET_VAR_ID(StxVarId::TYPECAST); }
    "val"       { RET_VAR_ID(StxVarId::VAL); }
    "var"       { RET_VAR_ID(StxVarId::VAR); }
    "version"   { RET_VAR_ID(StxVarId::VER); }

    // global variables
    "nl"        { RET_VAR_ID(StxVarId::NEWLINE); }
    "indent"    { RET_VAR_ID(StxVarId::INDENT); }
    "dedent"    { RET_VAR_ID(StxVarId::DEDENT); }
    "topindent" { RET_VAR_ID(StxVarId::TOPINDENT); }

    word {
        yylval->str = newcstr(tok, cur, alc);
        RET_TOK(STX_WORD);
    }

    number {
        if (s_to_i32_unsafe(tok, cur, yylval->num)) {
            RET_TOK(STX_NUMBER);
        }
        RET_FAIL(error_at_tok("configuration value overflow"));
    }

    ["] { tmp_str.clear(); goto str; }

    [(] space* { goto opt; }

    [=?:;,){}[\]] { RET_TOK(cur[-1]); }

    * { RET_FAIL(error_at_tok("unexpected character: '%c'", cur[-1])); }
*/

code: /*!local:re2c
    "var_local"            { RET_CONF_ID(StxConfId::VAR_LOCAL); }
    "var_global"           { RET_CONF_ID(StxConfId::VAR_GLOBAL); }
    "const_local"          { RET_CONF_ID(StxConfId::CONST_LOCAL); }
    "const_global"         { RET_CONF_ID(StxConfId::CONST_GLOBAL); }
    "array_local"          { RET_CONF_ID(StxConfId::ARRAY_LOCAL); }
    "array_global"         { RET_CONF_ID(StxConfId::ARRAY_GLOBAL); }
    "array_elem"           { RET_CONF_ID(StxConfId::ARRAY_ELEM); }
    "type_int"             { RET_CONF_ID(StxConfId::TYPE_INT); }
    "type_uint"            { RET_CONF_ID(StxConfId::TYPE_UINT); }
    "type_cond_enum"       { RET_CONF_ID(StxConfId::TYPE_COND_ENUM); }
    "type_yybm"            { RET_CONF_ID(StxConfId::TYPE_YYBM); }
    "type_yytarget"        { RET_CONF_ID(StxConfId::TYPE_YYTARGET); }
    "assign"               { RET_CONF_ID(StxConfId::ASSIGN); }
    "assign_op"            { RET_CONF_ID(StxConfId::ASSIGN_OP); }
    "if_then_else"         { RET_CONF_ID(StxConfId::IF_THEN_ELSE); }
    "if_then_else_oneline" { RET_CONF_ID(StxConfId::IF_THEN_ELSE_ONELINE); }
    "switch"               { RET_CONF_ID(StxConfId::SWITCH); }
    "switch_cases"         { RET_CONF_ID(StxConfId::SWITCH_CASES); }
    "switch_cases_oneline" { RET_CONF_ID(StxConfId::SWITCH_CASES_ONELINE); }
    "switch_case_range"    { RET_CONF_ID(StxConfId::SWITCH_CASE_RANGE); }
    "switch_case_default"  { RET_CONF_ID(StxConfId::SWITCH_CASE_DEFAULT); }
    "loop"                 { RET_CONF_ID(StxConfId::LOOP); }
    "enum"                 { RET_CONF_ID(StxConfId::ENUM); }
    "enum_elem"            { RET_CONF_ID(StxConfId::ENUM_ELEM); }
    "fndecl"               { RET_CONF_ID(StxConfId::FNDECL); }
    "fndef"                { RET_CONF_ID(StxConfId::FNDEF); }
    "fncall"               { RET_CONF_ID(StxConfId::FNCALL); }
    "tailcall"             { RET_CONF_ID(StxConfId::TAILCALL); }
    "recursive_functions"  { RET_CONF_ID(StxConfId::RECURSIVE_FUNCTIONS); }
    "fingerprint"          { RET_CONF_ID(StxConfId::FINGERPRINT); }
    "line_info"            { RET_CONF_ID(StxConfId::LINE_INFO); }
    "abort"                { RET_CONF_ID(StxConfId::ABORT); }
    "yyaccept"             { RET_CONF_ID(StxConfId::ACCEPT); }
    "yydebug"              { RET_CONF_ID(StxConfId::DEBUG); }
    "yypeek"               { RET_CONF_ID(StxConfId::PEEK); }
    "yyskip"               { RET_CONF_ID(StxConfId::SKIP); }
    "yybackup"             { RET_CONF_ID(StxConfId::BACKUP); }
    "yyskip_peek"          { RET_CONF_ID(StxConfId::SKIP_PEEK); }
    "yypeek_skip"          { RET_CONF_ID(StxConfId::PEEK_SKIP); }
    "yyskip_backup"        { RET_CONF_ID(StxConfId::SKIP_BACKUP); }
    "yybackup_skip"        { RET_CONF_ID(StxConfId::BACKUP_SKIP); }
    "yybackup_peek"        { RET_CONF_ID(StxConfId::BACKUP_PEEK); }
    "yyskip_backup_peek"   { RET_CONF_ID(StxConfId::SKIP_BACKUP_PEEK); }
    "yybackup_peek_skip"   { RET_CONF_ID(StxConfId::BACKUP_PEEK_SKIP); }

    [a-z0-9_]* { RET_FAIL(error_at_tok("unknown configuration '%.*s'", int(cur - tok), tok)); }
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

    "have_init"     { RET_LOPT(StxLOpt::HAVE_INIT); }
    "have_cond"     { RET_LOPT(StxLOpt::HAVE_COND); }
    "have_type"     { RET_LOPT(StxLOpt::HAVE_TYPE); }
    "have_args"     { RET_LOPT(StxLOpt::HAVE_ARGS); }
    "have_argmods"  { RET_LOPT(StxLOpt::HAVE_ARGMODS); }
    "have_retval"   { RET_LOPT(StxLOpt::HAVE_RETVAL); }
    "multival"      { RET_LOPT(StxLOpt::MULTIVAL); }
    "char_literals" { RET_LOPT(StxLOpt::CHAR_LITERALS); }

    * { RET_FAIL(error_at_cur("unknown option")); }
*/

    UNREACHABLE();
    return Ret::FAIL; // unreachable
}

#undef RET_TOK
#undef RET_GOPT
#undef RET_LOPT

} // namespace re2c
