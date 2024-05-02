#include <stdint.h>
#include <string>
#include <vector>

#include "src/encoding/enc.h"
#include "src/msg/msg.h"
#include "src/options/opt.h"
#include "src/parse/ast.h"
#include "src/parse/conf_parser.h"
#include "src/parse/input.h"
#include "src/util/file_utils.h"
#include "src/util/string_utils.h"

namespace re2c {

/*!max:re2c format = "size_t LexerState::maxfill_conf() { return @@; }"; */

#define YYFILL(n) do { \
    if (!fill(n)) { \
        RET_FAIL(error_at_cur("unexpected end of input in configuration")); \
    } \
} while(0)

// In syntax file mode do not overwrite user-defined options.
#define SETOPT(opt, val) do { \
    if (in_syntax_file) { \
        opts.init_##opt(val); \
    } else { \
        opts.set_##opt(val); \
    } \
} while (0)

#define RET_CONF_BOOL(conf) do { \
    CHECK_RET(lex_conf_bool(opts)); \
    SETOPT(conf, tmp_num != 0); \
    return Ret::OK; \
} while(0)

#define RET_CONF_FEATURE(conf) do { \
    CHECK_RET(lex_conf_bool(opts)); \
    if (tmp_num != 0 && !opts.glob.supported_features_contains(#conf)) { \
        RET_FAIL(error_at_cur("'%s' feature is not supported for this backend", #conf)); \
    } \
    SETOPT(conf, tmp_num != 0); \
    return Ret::OK; \
} while(0)

#define RET_CONF_STR(conf) do { \
    CHECK_RET(lex_conf_string(opts)); \
    SETOPT(conf, tmp_str); \
    return Ret::OK; \
} while(0)

#define RET_CONF_ENC(enc) do { \
    CHECK_RET(lex_conf_bool(opts)); \
    if (in_syntax_file) { \
        opts.init_encoding(enc, tmp_num != 0); \
    } else { \
        opts.set_encoding(enc, tmp_num != 0); \
    } \
    return Ret::OK; \
} while(0)

#define RET_CONF_NUM_NONNEG(conf) do { \
    CHECK_RET(lex_conf_number(opts)); \
    if (tmp_num < 0) RET_FAIL(error_at_cur("expected nonnegative value in configuration")); \
    SETOPT(conf, static_cast<uint32_t>(tmp_num)); \
    return Ret::OK; \
} while(0)

#define RET_CONF_EOF(conf) do { \
    CHECK_RET(lex_conf_number(opts)); \
    SETOPT(conf, tmp_num < 0 ? NOEOF : static_cast<uint32_t>(tmp_num)); \
    return Ret::OK; \
} while(0)

/*!re2c
    re2c:define:YYCTYPE     = uint8_t;
    re2c:define:YYCURSOR    = cur;
    re2c:define:YYLIMIT     = lim;
    re2c:define:YYMARKER    = mar;
    re2c:define:YYCTXMARKER = ctx;

    eof         = [\x00];
    eol         = [\n];
    space       = [ \t\r];
    semi        = [;];
    quotes      = ['"];
    naked_char  = [^] \ (eof | eol | space | semi);
    naked       = (naked_char \ quotes) naked_char*;
    conf_assign = space* "=" space*;
    number      = "0" | ("-"? [1-9] [0-9]*);
    comment     = "//" [^\x00\n]* eol;
*/

Ret Input::lex_conf(Opt& opts) {
/*!local:re2c
    "api" | "flags:input" { goto input; }
    "api:style"           { goto api_style; }
    "api:sigil"           { RET_CONF_STR(api_sigil); }

    // header filename in configuration is relative to the output file directory
    "header" | "flags:type-header" | "flags:t" {
        CHECK_RET(lex_conf_string(opts));
        if (!tmp_str.empty()) {
            std::string path(opts.glob.output_file);
            get_dir(path);
            SETOPT(header_file, path + tmp_str);
        }
        return Ret::OK;
    }

    "eof"      { RET_CONF_EOF(fill_eof); }
    "sentinel" { RET_CONF_EOF(fill_sentinel); }

    "yyfill:enable"    { RET_CONF_BOOL(fill_enable); }
    "yyfill:parameter" { RET_CONF_BOOL(fill_param_enable); }
    "yyfill:check"     { RET_CONF_BOOL(fill_check); }

    "yyfn:sep" { RET_CONF_STR(fn_sep); }

    "flags:"? "tags" | "flags:T"  { RET_CONF_BOOL(tags); }
    "flags:"? "leftmost-captures" { RET_CONF_BOOL(tags_posix_syntax); }
    "flags:"? "posix-captures" | "flags:P" {
        CHECK_RET(lex_conf_bool(opts));
        SETOPT(tags_posix_syntax, tmp_num != 0);
        SETOPT(tags_posix_semantics, tmp_num != 0);
        return Ret::OK;
    }
    "tags:prefix"     { RET_CONF_STR(tags_prefix); }
    "tags:expression" { RET_CONF_STR(tags_expression); }
    "invert-captures" { RET_CONF_BOOL(invert_captures); }

    "define:YYBACKUP"                    { RET_CONF_STR(api_backup); }
    "define:YYBACKUPCTX"                 { RET_CONF_STR(api_backup_ctx); }
    "define:YYCONDTYPE"                  { RET_CONF_STR(api_cond_type); }
    "define:YYCOPYMTAG"                  { RET_CONF_STR(api_mtag_copy); }
    "define:YYCOPYSTAG"                  { RET_CONF_STR(api_stag_copy); }
    "define:YYCTYPE"                     { RET_CONF_STR(api_char_type); }
    "define:YYCTXMARKER"                 { RET_CONF_STR(api_ctxmarker); }
    "define:YYCURSOR"                    { RET_CONF_STR(api_cursor); }
    "define:YYDEBUG"                     { RET_CONF_STR(api_debug); }
    "define:YYFILL"                      { RET_CONF_STR(api_fill); }
    "define:YYFILL@len"                  { RET_CONF_STR(fill_param); }
    "define:YYFILL:naked"                { RET_CONF_BOOL(fill_naked); }
    "define:YYGETCOND" "ITION"?          { RET_CONF_STR(api_cond_get); }
    "define:YYGETCOND" "ITION"? ":naked" { RET_CONF_BOOL(cond_get_naked); }
    "define:YYGETSTATE"                  { RET_CONF_STR(api_state_get); }
    "define:YYGETSTATE:naked"            { RET_CONF_BOOL(state_get_naked); }
    "define:YYLESSTHAN"                  { RET_CONF_STR(api_less_than); }
    "define:YYLIMIT"                     { RET_CONF_STR(api_limit); }
    "define:YYMARKER"                    { RET_CONF_STR(api_marker); }
    "define:YYMAXFILL"                   { RET_CONF_STR(api_maxfill); }
    "define:YYMAXNMATCH"                 { RET_CONF_STR(api_maxnmatch); }
    "define:YYMTAGN"                     { RET_CONF_STR(api_mtag_neg); }
    "define:YYMTAGP"                     { RET_CONF_STR(api_mtag_pos); }
    "define:YYPEEK"                      { RET_CONF_STR(api_peek); }
    "define:YYRESTORE"                   { RET_CONF_STR(api_restore); }
    "define:YYRESTORECTX"                { RET_CONF_STR(api_restore_ctx); }
    "define:YYRESTORETAG"                { RET_CONF_STR(api_restore_tag); }
    "define:YYSETCOND" "ITION"?          { RET_CONF_STR(api_cond_set); }
    "define:YYSETCOND" "ITION"? "@cond"  { RET_CONF_STR(cond_set_param); }
    "define:YYSETCOND" "ITION"? ":naked" { RET_CONF_BOOL(cond_set_naked); }
    "define:YYSETSTATE"                  { RET_CONF_STR(api_state_set); }
    "define:YYSETSTATE:naked"            { RET_CONF_BOOL(state_set_naked); }
    "define:YYSETSTATE@state"            { RET_CONF_STR(state_set_param); }
    "define:YYSHIFT"                     { RET_CONF_STR(api_shift); }
    "define:YYSHIFTSTAG"                 { RET_CONF_STR(api_stag_shift); }
    "define:YYSHIFTMTAG"                 { RET_CONF_STR(api_mtag_shift); }
    "define:YYSKIP"                      { RET_CONF_STR(api_skip); }
    "define:YYSTAGN"                     { RET_CONF_STR(api_stag_neg); }
    "define:YYSTAGP"                     { RET_CONF_STR(api_stag_pos); }
    "define:YYFN" {
        CHECK_RET(lex_conf_list(opts));
        if (tmp_list.size() < 1) {
            RET_FAIL(error_at_tok("`re2c:define:YYFN` value should be a nonempty list of strings"));
        }
        SETOPT(api_fn, tmp_list);
        return Ret::OK;
    }

    "variable:"  "yyctable"        { RET_CONF_STR(var_cond_table); }
    "variable:"  "yyaccept"        { RET_CONF_STR(var_accept); }
    "variable:"  "yytarget"        { RET_CONF_STR(var_computed_gotos_table); }
    "variable:"  "yystate"         { RET_CONF_STR(var_state); }
    "variable:"  "yych"            { RET_CONF_STR(var_char); }
    "variable:"? "yych:conversion" { RET_CONF_BOOL(char_conv); }
    "variable:"? "yych:literals"   { goto char_lit; }
    "variable:"? "yych:emit"       { RET_CONF_BOOL(char_emit); }
    "variable:"  "yybm"            { RET_CONF_STR(var_bitmaps); }
    "variable:"? "yybm:hex"        { RET_CONF_BOOL(bitmaps_hex); }
    "variable:"  "yyfill"          { RET_CONF_STR(var_fill); }
    "variable:"  "yystable"        { return lex_conf_string(opts); } // deprecated

    "cond:abort"                         { RET_CONF_BOOL(cond_abort); }
    "cond:prefix" | "condprefix"         { RET_CONF_STR(cond_label_prefix); }
    "cond:enumprefix" | "condenumprefix" { RET_CONF_STR(cond_enum_prefix); }
    "cond:divider"                       { RET_CONF_STR(cond_div); }
    "cond:divider@cond"                  { RET_CONF_STR(cond_div_param); }
    "cond:goto"                          { RET_CONF_STR(cond_goto); }
    "cond:goto@cond"                     { RET_CONF_STR(cond_goto_param); }

    "state:abort"     { RET_CONF_BOOL(state_abort); }
    "state:nextlabel" { RET_CONF_BOOL(state_next); }

    "flags:"? "bit-vectors"    | "flags:b"    { RET_CONF_FEATURE(bitmaps); }
    "flags:"? "debug-output"   | "flags:d"    { RET_CONF_BOOL(debug); }
    "flags:"? "computed-gotos" | "flags:g"    { RET_CONF_FEATURE(computed_gotos); }
    ("computed-gotos" | "cgoto") ":threshold" { RET_CONF_NUM_NONNEG(computed_gotos_threshold); }
    "flags:"? "nested-ifs"     | "flags:s"    { RET_CONF_FEATURE(nested_ifs); }
    "flags:"? "case-insensitive"              { RET_CONF_BOOL(case_insensitive); }
    "flags:"? "case-inverted"                 { RET_CONF_BOOL(case_inverted); }
    "flags:"? "case-ranges"                   { RET_CONF_FEATURE(case_ranges); }
    "flags:"? "unsafe"                        { RET_CONF_BOOL(unsafe); }
    "flags:"? "monadic"                       { RET_CONF_BOOL(monadic); }

    "encoding:ebcdic" | "flags:ecb"        | "flags:e" { RET_CONF_ENC(Enc::Type::EBCDIC); }
    "encoding:utf32"  | "flags:unicode"    | "flags:u" { RET_CONF_ENC(Enc::Type::UTF32); }
    "encoding:ucs2"   | "flags:wide-chars" | "flags:w" { RET_CONF_ENC(Enc::Type::UCS2); }
    "encoding:utf16"  | "flags:utf-16"     | "flags:x" { RET_CONF_ENC(Enc::Type::UTF16); }
    "encoding:utf8"   | "flags:utf-8"      | "flags:8" { RET_CONF_ENC(Enc::Type::UTF8); }

    "flags:"? "encoding-policy" { goto encoding_policy; }
    "flags:"? "empty-class"     { goto empty_class; }

    "indent:string" { RET_CONF_STR(indent_str); }
    "indent:top"    { RET_CONF_NUM_NONNEG(indent_top); }

    "label:prefix" | "labelprefix"                    { RET_CONF_STR(label_prefix); }
    "label:yyfill" | "label:yyFillLabel"              { RET_CONF_STR(label_fill); }
    "label:yyloop"                                    { RET_CONF_STR(label_loop); }
    "label:yyNext"                                    { RET_CONF_STR(label_next); }
    "label:start" | "startlabel" / conf_assign number { RET_CONF_BOOL(label_start_force); }
    "label:start" | "startlabel"                      { RET_CONF_STR(label_start); }

    [a-zA-Z0-9_:-]* {
        RET_FAIL(error_at_tok(
                "unrecognized configuration '%.*s'", static_cast<int>(cur - tok), tok));
    }
*/

input:
    CHECK_RET(lex_conf_assign());
/*!local:re2c
    * {
        RET_FAIL(error_at_cur("bad configuration value (expected: 'default', 'custom')"));
    }
    "default" { SETOPT(api, Api::DEFAULT); goto end; }
    "custom"  { SETOPT(api, Api::CUSTOM);  goto end; }
*/

api_style:
    CHECK_RET(lex_conf_assign());
/*!local:re2c
    * {
        RET_FAIL(error_at_cur("bad configuration value (expected: 'functions', 'free-form')"));
    }
    "functions" { SETOPT(api_style, ApiStyle::FUNCTIONS); goto end; }
    "free-form" { SETOPT(api_style, ApiStyle::FREEFORM);  goto end; }
*/

encoding_policy:
    CHECK_RET(lex_conf_assign());
/*!local:re2c
    * {
        RET_FAIL(error_at_cur(
                "bad configuration value (expected: 'ignore', 'substitute', 'fail')"));
    }
    "ignore"     { SETOPT(encoding_policy, Enc::Policy::IGNORE);     goto end; }
    "substitute" { SETOPT(encoding_policy, Enc::Policy::SUBSTITUTE); goto end; }
    "fail"       { SETOPT(encoding_policy, Enc::Policy::FAIL);       goto end; }
*/

empty_class:
    CHECK_RET(lex_conf_assign());
/*!local:re2c
    * {
        RET_FAIL(error_at_cur(
                "bad configuration value (expected: 'match-empty', 'match-none', 'error')"));
    }
    "match-empty" { SETOPT(empty_class, EmptyClass::MATCH_EMPTY); goto end; }
    "match-none"  { SETOPT(empty_class, EmptyClass::MATCH_NONE);  goto end; }
    "error"       { SETOPT(empty_class, EmptyClass::ERROR);       goto end; }
*/

char_lit:
    CHECK_RET(lex_conf_assign());
/*!local:re2c
    * {
        RET_FAIL(error_at_cur("bad configuration value (expected: 'char', 'hex', 'char_or_hex')"));
    }
    "char"        { SETOPT(char_literals, CharLit::CHAR);        goto end; }
    "hex"         { SETOPT(char_literals, CharLit::HEX);         goto end; }
    "char_or_hex" { SETOPT(char_literals, CharLit::CHAR_OR_HEX); goto end; }
*/

end:
    return lex_conf_semicolon();
}

#undef SETOPT
#undef RET_CONF_BOOL
#undef RET_CONF_FEATURE
#undef RET_CONF_STR
#undef RET_CONF_ENC
#undef RET_CONF_NUM_NONNEG
#undef RET_CONF_EOF

Ret Input::lex_conf_assign() {
/*!local:re2c
    *           { RET_FAIL(error_at_cur("missing '=' in configuration")); }
    conf_assign { return Ret::OK; }
*/
}

Ret Input::lex_conf_semicolon() {
/*!local:re2c
    *          { RET_FAIL(error_at_cur("missing ending ';' in configuration")); }
    space* ";" { return Ret::OK; }
*/
}

Ret Input::lex_conf_number(Opt& opts) {
    CHECK_RET(parse_conf(opts));
    if (conf_kind != ConfKind::NUM) {
        RET_FAIL(error_at_tok("configuration value should be a number"));
    }
    return Ret::OK;
}

inline Ret Input::lex_conf_bool(Opt& opts) {
    CHECK_RET(parse_conf(opts));
    if (conf_kind != ConfKind::NUM) {
        RET_FAIL(error_at_tok("configuration value should be a boolean value 0 or 1"));
    }
    return Ret::OK;
}

// Historically re2c allowed raw (unquoted) strings containing special symbols as configuration
// values in source files. In syntax files this is not allowed, as it would conflict with other
// parts of grammar (e.g. parentheses and question mark are used for conditionals). Therefore we
// have a legacy method for string configurations in source files.
Ret Input::lex_conf_string_legacy() {
    CHECK_RET(lex_conf_assign());
    tok = cur;
/*!local:re2c
    quotes { CHECK_RET(lex_conf_string_quoted(tok[0])); goto end; }
    naked  { tmp_str.assign(tok, cur); goto end; }
    ""     { tmp_str.clear(); goto end; }
*/
end:
    return lex_conf_semicolon();
}

Ret Input::lex_conf_string(Opt& opts) {
    if (!in_syntax_file) {
        return lex_conf_string_legacy();
    }

    CHECK_RET(parse_conf(opts));
    if (conf_kind != ConfKind::STR) {
        RET_FAIL(error_at_tok("configuration value should be a string"));
    }
    return Ret::OK;
}

Ret Input::lex_conf_list(Opt& opts) {
    CHECK_RET(parse_conf(opts));
    if (conf_kind != ConfKind::LIST) {
        RET_FAIL(error_at_tok("configuration value should be a list"));
    }
    return Ret::OK;
}

Ret Input::lex_conf_string_quoted(uint8_t quote) {
    AstChar c;
    bool stop;
    tmp_str.clear();
    for (;;) {
        CHECK_RET(lex_str_chr(quote, c, stop));
        if (stop) return Ret::OK;
        if (c.chr > 0xFF) {
            RET_FAIL(error_at(c.loc, "multibyte character in configuration string: 0x%X", c.chr));
        } else if (c.chr == '\n' && in_syntax_file) {
            RET_FAIL(error_at(c.loc, "newline in a string literal (use `nl` variable instead)"));
        }
        tmp_str += static_cast<char>(c.chr);
    }
}

#define RET_TOK(t) do { \
    token = t; \
    return Ret::OK; \
} while(0)

#define RET_COND(c) do { \
    token = CONF_COND; \
    yylval->cond = (c); \
    return Ret::OK; \
} while(0)

#define RET_GOPT(opt) do { \
    token = CONF_GOPT; \
    yylval->gopt = opt; \
    return Ret::OK; \
} while(0)

#define RET_LOPT(opt) do { \
    token = CONF_LOPT; \
    yylval->lopt = opt; \
    return Ret::OK; \
} while(0)

#define RET_VAR(v) do { \
    token = CONF_VAR; \
    yylval->var = v; \
    return Ret::OK; \
} while(0)

#define RET_CODE(conf) do { \
    token = CONF_CODE; \
    yylval->codeptr = const_cast<const StxCodes**>(&opts.glob.conf); \
    return Ret::OK; \
} while(0)

Ret Input::lex_conf_token(CONF_STYPE* yylval, int& token, Opt& opts) {
start:
    tok = cur;
/*!local:re2c
    semi { RET_TOK(CONF_EOF); }

    eof { RET_FAIL(error_at_cur("unexpected end of input in configuration")); }

    eol | comment { next_line(); goto start; }

    space+ { goto start; }

    number {
        if (!s_to_i32_unsafe(tok, cur, yylval->num)) {
            RET_FAIL(error_at_cur("configuration value overflow"));
        }
        RET_TOK(CONF_NUMBER);
    }

    quotes {
        CHECK_RET(lex_conf_string_quoted(cur[-1]));
        yylval->str = copystr(tmp_str, alc);
        RET_TOK(CONF_STRING);
    }

    [(] space* { goto opt; }

    [=?:,){}[\]] { RET_TOK(cur[-1]); }

    "code:var_local"            { RET_CODE(code_var_local); }
    "code:var_global"           { RET_CODE(code_var_global); }
    "code:const_local"          { RET_CODE(code_const_local); }
    "code:const_global"         { RET_CODE(code_const_global); }
    "code:array_local"          { RET_CODE(code_array_local); }
    "code:array_global"         { RET_CODE(code_array_global); }
    "code:array_elem"           { RET_CODE(code_array_elem); }
    "code:type_int"             { RET_CODE(code_type_int); }
    "code:type_uint"            { RET_CODE(code_type_uint); }
    "code:type_cond_enum"       { RET_CODE(code_type_cond_enum); }
    "code:type_yybm"            { RET_CODE(code_type_yybm); }
    "code:type_yytarget"        { RET_CODE(code_type_yytarget); }
    "code:assign"               { RET_CODE(code_assign); }
    "code:assign_op"            { RET_CODE(code_assign_op); }
    "code:if_then_else"         { RET_CODE(code_if_then_else); }
    "code:if_then_else_oneline" { RET_CODE(code_if_then_else_oneline); }
    "code:switch"               { RET_CODE(code_switch); }
    "code:switch_cases"         { RET_CODE(code_switch_cases); }
    "code:switch_cases_oneline" { RET_CODE(code_switch_cases_oneline); }
    "code:switch_case_range"    { RET_CODE(code_switch_case_range); }
    "code:switch_case_default"  { RET_CODE(code_switch_case_default); }
    "code:loop"                 { RET_CODE(code_loop); }
    "code:goto"                 { RET_CODE(code_goto); }
    "code:enum"                 { RET_CODE(code_enum); }
    "code:enum_elem"            { RET_CODE(code_enum_elem); }
    "code:fndecl"               { RET_CODE(code_fndecl); }
    "code:fndef"                { RET_CODE(code_fndef); }
    "code:fncall"               { RET_CODE(code_fncall); }
    "code:tailcall"             { RET_CODE(code_tailcall); }
    "code:recursive_functions"  { RET_CODE(code_recursive_functions); }
    "code:fingerprint"          { RET_CODE(code_fingerprint); }
    "code:line_info"            { RET_CODE(code_line_info); }
    "code:abort"                { RET_CODE(code_abort); }
    "code:yyaccept"             { RET_CODE(code_accept); }
    "code:yydebug"              { RET_CODE(code_debug); }
    "code:yypeek"               { RET_CODE(code_peek); }
    "code:yyskip"               { RET_CODE(code_skip); }
    "code:yybackup"             { RET_CODE(code_backup); }
    "code:yyskip_peek"          { RET_CODE(code_skip_peek); }
    "code:yypeek_skip"          { RET_CODE(code_peek_skip); }
    "code:yyskip_backup"        { RET_CODE(code_skip_backup); }
    "code:yybackup_skip"        { RET_CODE(code_backup_skip); }
    "code:yybackup_peek"        { RET_CODE(code_backup_peek); }
    "code:yyskip_backup_peek"   { RET_CODE(code_skip_backup_peek); }
    "code:yybackup_peek_skip"   { RET_CODE(code_backup_peek_skip); }

    "code:" [a-z0-9_]+ {
        RET_FAIL(error_at_tok("unknown configuration: '%.*s'", int(cur - tok), tok));
    }

    // local variables
    "arg"       { RET_VAR(StxVarId::ARG); }
    "argmods"   { RET_VAR(StxVarId::ARGMODS); }
    "argname"   { RET_VAR(StxVarId::ARGNAME); }
    "argtype"   { RET_VAR(StxVarId::ARGTYPE); }
    "array"     { RET_VAR(StxVarId::ARRAY); }
    "backup"    { RET_VAR(StxVarId::BACKUP); }
    "branch"    { RET_VAR(StxVarId::BRANCH); }
    "case"      { RET_VAR(StxVarId::CASE); }
    "char"      { RET_VAR(StxVarId::CHAR); }
    "cond"      { RET_VAR(StxVarId::COND); }
    "ctype"     { RET_VAR(StxVarId::CTYPE); }
    "cursor"    { RET_VAR(StxVarId::CURSOR); }
    "date"      { RET_VAR(StxVarId::DATE); }
    "debug"     { RET_VAR(StxVarId::DEBUG); }
    "elem"      { RET_VAR(StxVarId::ELEM); }
    "expr"      { RET_VAR(StxVarId::EXPR); }
    "fn"        { RET_VAR(StxVarId::FN); }
    "file"      { RET_VAR(StxVarId::FILE); }
    "fndecl"    { RET_VAR(StxVarId::FNDECL); }
    "fndef"     { RET_VAR(StxVarId::FNDEF); }
    "index"     { RET_VAR(StxVarId::INDEX); }
    "init"      { RET_VAR(StxVarId::INIT); }
    "label"     { RET_VAR(StxVarId::LABEL); }
    "lhs"       { RET_VAR(StxVarId::LHS); }
    "line"      { RET_VAR(StxVarId::LINE); }
    "marker"    { RET_VAR(StxVarId::MARKER); }
    "name"      { RET_VAR(StxVarId::NAME); }
    "num"       { RET_VAR(StxVarId::NUM); }
    "op"        { RET_VAR(StxVarId::OP); }
    "peek"      { RET_VAR(StxVarId::PEEK); }
    "retval"    { RET_VAR(StxVarId::RETVAL); }
    "rhs"       { RET_VAR(StxVarId::RHS); }
    "row"       { RET_VAR(StxVarId::ROW); }
    "size"      { RET_VAR(StxVarId::SIZE); }
    "skip"      { RET_VAR(StxVarId::SKIP); }
    "state"     { RET_VAR(StxVarId::STATE); }
    "stmt"      { RET_VAR(StxVarId::STMT); }
    "type"      { RET_VAR(StxVarId::TYPE); }
    "typecast"  { RET_VAR(StxVarId::TYPECAST); }
    "val"       { RET_VAR(StxVarId::VAL); }
    "var"       { RET_VAR(StxVarId::VAR); }
    "version"   { RET_VAR(StxVarId::VER); }

    // global variables
    "nl"        { RET_VAR(StxVarId::NEWLINE); }
    "indent"    { RET_VAR(StxVarId::INDENT); }
    "dedent"    { RET_VAR(StxVarId::DEDENT); }
    "topindent" { RET_VAR(StxVarId::TOPINDENT); }

    [a-z0-9_]+ { RET_FAIL(error_at_tok("unknown variable: '%.*s'", int(cur - tok), tok)); }

    * { RET_FAIL(error_at_tok("unexpected character: '%c'", cur[-1])); }
*/

opt:
    tok = cur;
/*!local:re2c
    // Global (immutable) conditionals.
    //
    // A subset of constant options that is exported for use in syntax files.
    // These options may be used both in `conf:*` configurations before the input file is parsed
    // and in `code:*` configurations that are evaluated during codegen.
    //
    // These options are part of the syntax file API.

    "code_model.goto_label"          { RET_COND(globopts->code_model == CodeModel::GOTO_LABEL); }
    "code_model.loop_switch"         { RET_COND(globopts->code_model == CodeModel::LOOP_SWITCH); }
    "code_model.recursive_functions" { RET_COND(globopts->code_model == CodeModel::REC_FUNC); }

    // Global (mutable) conditionals.
    //
    // A subset of options is exported for use in `code:*` configurations in syntax files.
    // Both constant and mutable options are allowed here, as they are used during codegen,
    // when block-level options are already known.
    //
    // These options are part of the syntax file API.

    "api.pointers"                   { RET_GOPT(StxGOpt::API_DEFAULT); }
    "api.generic"                    { RET_GOPT(StxGOpt::API_CUSTOM); }
    "api_style.functions"            { RET_GOPT(StxGOpt::API_STYLE_FUNCTIONS); }
    "api_style.freeform"             { RET_GOPT(StxGOpt::API_STYLE_FREEFORM); }
    "start_conditions"               { RET_GOPT(StxGOpt::START_CONDITIONS); }
    "storable_state"                 { RET_GOPT(StxGOpt::STORABLE_STATE); }
    "date"                           { RET_GOPT(StxGOpt::DATE); }
    "version"                        { RET_GOPT(StxGOpt::VER); }
    "case_ranges"                    { RET_GOPT(StxGOpt::CASE_RANGES); }
    "unsafe"                         { RET_GOPT(StxGOpt::UNSAFE); }
    "monadic"                        { RET_GOPT(StxGOpt::MONADIC); }
    "loop_label"                     { RET_GOPT(StxGOpt::LOOP_LABEL); }

    // Local conditionals (specific to each `code:*` configuration in syntax file).
    //
    // These options are part of the syntax file API.

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
#undef RET_OPT
#undef RET_GOPT
#undef RET_LOPT
#undef RET_VAR
#undef RET_CODE

#define SAVE_CONF_BOOL(conf) do { \
    CHECK_RET(lex_conf_bool(opts)); \
    opts.set_##conf(tmp_num != 0); \
    goto start; \
} while(0)

#define SAVE_CONF_LIST(conf) do { \
    CHECK_RET(lex_conf_list(opts)); \
    opts.set_##conf(tmp_list); \
    CHECK_RET(opts.check_##conf()); \
    tmp_list.clear(); \
    goto start; \
} while(0)

Ret Input::lex_syntax_file(Opt& opts) {
start:
    tok = cur;
    location = cur_loc();
/*!local:re2c
    eof { return Ret::OK; }

    eol | comment { next_line(); goto start; }

    space+ { goto start; }

    "conf:" { CHECK_RET(lex_conf(opts)); goto start; }

    "supported_apis"        { SAVE_CONF_LIST(supported_apis); }
    "supported_code_models" { SAVE_CONF_LIST(supported_code_models); }
    "supported_targets"     { SAVE_CONF_LIST(supported_targets); }
    "supported_features"    { SAVE_CONF_LIST(supported_features); }

    "semicolons"               { SAVE_CONF_BOOL(semicolons); }
    "implicit_bool_conversion" { SAVE_CONF_BOOL(implicit_bool_conversion); }
    "backtick_quoted_strings"  { SAVE_CONF_BOOL(backtick_quoted_strings); }
    "standalone_single_quotes" { SAVE_CONF_BOOL(standalone_single_quotes); }
    "indentation_sensitive"    { SAVE_CONF_BOOL(indentation_sensitive); }
    "wrap_blocks_in_braces"    { SAVE_CONF_BOOL(wrap_blocks_in_braces); }

    "" / "code:" { if (conf_parse(*this, opts) != 0) return Ret::FAIL; goto start; }

    * { RET_FAIL(error_at_tok("unexpected character: '%c'", cur[-1])); }
*/

    UNREACHABLE();
    return Ret::FAIL;
}

#undef SAVE_CONF_BOOL
#undef SAVE_CONF_LIST

#undef YYFILL

} // namespace re2c
