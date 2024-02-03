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

#define YYFILL(n) if (!fill(n)) RET_FAIL(error_at_cur("unexpected end of input in configuration"))

#define RET_CONF_BOOL(conf) do { \
    CHECK_RET(lex_conf_bool()); \
    opts.set_##conf(tmp_num != 0); \
    return Ret::OK; \
} while(0)

#define RET_CONF_STR(conf) do { \
    CHECK_RET(lex_conf_string()); \
    opts.set_##conf(tmp_str); \
    return Ret::OK; \
} while(0)

#define RET_CONF_ENC(enc) do { \
    CHECK_RET(lex_conf_bool()); \
    opts.set_encoding(enc, tmp_num != 0); \
    return Ret::OK; \
} while(0)

#define RET_CONF_NUM_NONNEG(conf) do { \
    CHECK_RET(lex_conf_number()); \
    if (tmp_num < 0) RET_FAIL(error_at_cur("expected nonnegative value in configuration")); \
    opts.set_##conf(static_cast<uint32_t>(tmp_num)); \
    return Ret::OK; \
} while(0)

#define RET_CONF_EOF(conf) do { \
    CHECK_RET(lex_conf_number()); \
    opts.set_##conf(tmp_num < 0 ? NOEOF : static_cast<uint32_t>(tmp_num)); \
    return Ret::OK; \
} while(0)

#define RET_TOK(t) do { token = t; return Ret::OK; } while(0)

#define RET_OPT(b) do { token = CONF_OPTION; yylval->opt = (b); return Ret::OK; } while(0)

/*!re2c
    re2c:define:YYCTYPE     = uint8_t;
    re2c:define:YYCURSOR    = cur;
    re2c:define:YYLIMIT     = lim;
    re2c:define:YYMARKER    = mar;
    re2c:define:YYCTXMARKER = ctx;

    eof         = [\x00];
    eol         = [\n];
    space       = [ \t];
    semi        = [;];
    quotes      = ['"];
    special     = [:?,()[\]=];
    naked_char  = [^] \ (eof | eol | space | semi);
    naked       = (naked_char \ quotes) naked_char*;
    conf_assign = space* "=" space*;
    number      = "0" | ("-"? [1-9] [0-9]*);
*/

Ret Input::lex_conf(Opt& opts) {
/*!local:re2c
    "api" | "flags:input" { return lex_conf_input(opts); }
    "api:style"           { return lex_conf_api_style(opts); }
    "api:sigil"           { RET_CONF_STR(api_sigil); }

    // header filename in configuration is relative to the output file directory
    "header" | "flags:type-header" | "flags:t" {
        CHECK_RET(lex_conf_string());
        std::string path(opts.glob.output_file);
        get_dir(path);
        opts.set_header_file(path + tmp_str);
        return Ret::OK;
    }

    "eof"      { RET_CONF_EOF(fill_eof); }
    "sentinel" { RET_CONF_EOF(fill_sentinel); }

    "yyfill:enable"    { RET_CONF_BOOL(fill_enable); }
    "yyfill:parameter" { RET_CONF_BOOL(fill_param_enable); }
    "yyfill:check"     { RET_CONF_BOOL(fill_check); }

    "flags:"? "tags" | "flags:T"  { RET_CONF_BOOL(tags); }
    "flags:"? "leftmost-captures" { RET_CONF_BOOL(tags_posix_syntax); }
    "flags:"? "posix-captures" | "flags:P" {
        CHECK_RET(lex_conf_bool());
        opts.set_tags_posix_syntax(tmp_num != 0);
        opts.set_tags_posix_semantics(tmp_num != 0);
        return Ret::OK;
    }
    "tags:prefix"     { RET_CONF_STR(tags_prefix); }
    "tags:expression" { RET_CONF_STR(tags_expression); }
    "invert-captures" { RET_CONF_BOOL(invert_captures); }

    "define:YYBACKUP"             { RET_CONF_STR(api_backup); }
    "define:YYBACKUPCTX"          { RET_CONF_STR(api_backup_ctx); }
    "define:YYCONDTYPE"           { RET_CONF_STR(api_cond_type); }
    "define:YYCTYPE"              { RET_CONF_STR(api_char_type); }
    "define:YYCTXMARKER"          { RET_CONF_STR(api_ctxmarker); }
    "define:YYCURSOR"             { RET_CONF_STR(api_cursor); }
    "define:YYDEBUG"              { RET_CONF_STR(api_debug); }
    "define:YYFILL"               { RET_CONF_STR(api_fill); }
    "define:YYFILL@len"           { RET_CONF_STR(fill_param); }
    "define:YYFILL:naked"         { RET_CONF_BOOL(fill_naked); }
    "define:YYGETCONDITION"       { RET_CONF_STR(api_cond_get); }
    "define:YYGETCONDITION:naked" { RET_CONF_BOOL(cond_get_naked); }
    "define:YYGETSTATE"           { RET_CONF_STR(api_state_get); }
    "define:YYGETSTATE:naked"     { RET_CONF_BOOL(state_get_naked); }
    "define:YYLESSTHAN"           { RET_CONF_STR(api_less_than); }
    "define:YYLIMIT"              { RET_CONF_STR(api_limit); }
    "define:YYMARKER"             { RET_CONF_STR(api_marker); }
    "define:YYMTAGN"              { RET_CONF_STR(api_mtag_neg); }
    "define:YYMTAGP"              { RET_CONF_STR(api_mtag_pos); }
    "define:YYPEEK"               { RET_CONF_STR(api_peek); }
    "define:YYRESTORE"            { RET_CONF_STR(api_restore); }
    "define:YYRESTORECTX"         { RET_CONF_STR(api_restore_ctx); }
    "define:YYRESTORETAG"         { RET_CONF_STR(api_restore_tag); }
    "define:YYSETCONDITION"       { RET_CONF_STR(api_cond_set); }
    "define:YYSETCONDITION@cond"  { RET_CONF_STR(cond_set_param); }
    "define:YYSETCONDITION:naked" { RET_CONF_BOOL(cond_set_naked); }
    "define:YYSETSTATE"           { RET_CONF_STR(api_state_set); }
    "define:YYSETSTATE:naked"     { RET_CONF_BOOL(state_set_naked); }
    "define:YYSETSTATE@state"     { RET_CONF_STR(state_set_param); }
    "define:YYSHIFT"              { RET_CONF_STR(api_shift); }
    "define:YYSHIFTSTAG"          { RET_CONF_STR(api_shift_stag); }
    "define:YYSHIFTMTAG"          { RET_CONF_STR(api_shift_mtag); }
    "define:YYSKIP"               { RET_CONF_STR(api_skip); }
    "define:YYSTAGN"              { RET_CONF_STR(api_stag_neg); }
    "define:YYSTAGP"              { RET_CONF_STR(api_stag_pos); }

    "define:YYFN" {
        CHECK_RET(lex_conf_list());
        if (tmp_list.size() < 2 || tmp_list.size() % 2 != 0) {
            RET_FAIL(error_at_tok(
                "`re2c:define:YYFN` value should be a list of 2*(N+1) strings, where the first"
                " element is function name, second element is return type, and the remaining 2*N"
                " elements are type and name of each argument (if any)"));
        }
        opts.set_api_function(tmp_list);
        return Ret::OK;
    }

    "variable:"  "yyctable"        { RET_CONF_STR(var_cond_table); }
    "variable:"  "yyaccept"        { RET_CONF_STR(var_accept); }
    "variable:"  "yytarget"        { RET_CONF_STR(var_cgoto_table); }
    "variable:"  "yystate"         { RET_CONF_STR(var_state); }
    "variable:"  "yych"            { RET_CONF_STR(var_char); }
    "variable:"? "yych:conversion" { RET_CONF_BOOL(char_conv); }
    "variable:"? "yych:emit"       { RET_CONF_BOOL(char_emit); }
    "variable:"  "yybm"            { RET_CONF_STR(var_bitmaps); }
    "variable:"? "yybm:hex"        { RET_CONF_BOOL(bitmaps_hex); }
    "variable:"  "yystable"        { return lex_conf_string(); } // deprecated

    "cond:prefix" | "condprefix"         { RET_CONF_STR(cond_label_prefix); }
    "cond:enumprefix" | "condenumprefix" { RET_CONF_STR(cond_enum_prefix); }
    "cond:divider"                       { RET_CONF_STR(cond_div); }
    "cond:divider@cond"                  { RET_CONF_STR(cond_div_param); }
    "cond:goto"                          { RET_CONF_STR(cond_goto); }
    "cond:goto@cond"                     { RET_CONF_STR(cond_goto_param); }

    "state:abort"     { RET_CONF_BOOL(state_abort); }
    "state:nextlabel" { RET_CONF_BOOL(state_next); }

    "flags:"? "bit-vectors"    | "flags:b"    { RET_CONF_BOOL(bitmaps); }
    "flags:"? "debug-output"   | "flags:d"    { RET_CONF_BOOL(debug); }
    "flags:"? "computed-gotos" | "flags:g"    { RET_CONF_BOOL(cgoto); }
    ("computed-gotos" | "cgoto") ":threshold" { RET_CONF_NUM_NONNEG(cgoto_threshold); }
    "flags:"? "nested-ifs"     | "flags:s"    { RET_CONF_BOOL(nested_ifs); }
    "flags:"? "case-insensitive"              { RET_CONF_BOOL(case_insensitive); }
    "flags:"? "case-inverted"                 { RET_CONF_BOOL(case_inverted); }
    "flags:"? "case-ranges"                   { RET_CONF_BOOL(case_ranges); }
    "flags:"? "unsafe"                        { RET_CONF_BOOL(unsafe); }

    "encoding:ebcdic" | "flags:ecb"        | "flags:e" { RET_CONF_ENC(Enc::Type::EBCDIC); }
    "encoding:utf32"  | "flags:unicode"    | "flags:u" { RET_CONF_ENC(Enc::Type::UTF32); }
    "encoding:ucs2"   | "flags:wide-chars" | "flags:w" { RET_CONF_ENC(Enc::Type::UCS2); }
    "encoding:utf16"  | "flags:utf-16"     | "flags:x" { RET_CONF_ENC(Enc::Type::UTF16); }
    "encoding:utf8"   | "flags:utf-8"      | "flags:8" { RET_CONF_ENC(Enc::Type::UTF8); }

    "flags:"? "encoding-policy" { return lex_conf_encoding_policy(opts); }
    "flags:"? "empty-class"     { return lex_conf_empty_class(opts); }

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
}

Ret Input::lex_conf_encoding_policy(Opt& opts) {
    CHECK_RET(lex_conf_assign());
/*!local:re2c
    * {
        RET_FAIL(error_at_cur(
                "bad configuration value (expected: 'ignore', 'substitute', 'fail')"));
    }
    "ignore"     { opts.set_encoding_policy(Enc::Policy::IGNORE);     goto end; }
    "substitute" { opts.set_encoding_policy(Enc::Policy::SUBSTITUTE); goto end; }
    "fail"       { opts.set_encoding_policy(Enc::Policy::FAIL);       goto end; }
*/
end:
    return lex_conf_semicolon();
}

Ret Input::lex_conf_input(Opt& opts) {
    CHECK_RET(lex_conf_assign());
/*!local:re2c
    * {
        RET_FAIL(error_at_cur("bad configuration value (expected: 'default', 'custom')"));
    }
    "default" { opts.set_api(Api::DEFAULT); goto end; }
    "custom"  { opts.set_api(Api::CUSTOM);  goto end; }
*/
end:
    return lex_conf_semicolon();
}

Ret Input::lex_conf_empty_class(Opt& opts) {
    CHECK_RET(lex_conf_assign());
/*!local:re2c
    * {
        RET_FAIL(error_at_cur(
                "bad configuration value (expected: 'match-empty', 'match-none', 'error')"));
    }
    "match-empty" { opts.set_empty_class(EmptyClass::MATCH_EMPTY); goto end; }
    "match-none"  { opts.set_empty_class(EmptyClass::MATCH_NONE);  goto end; }
    "error"       { opts.set_empty_class(EmptyClass::ERROR);       goto end; }
*/
end:
    return lex_conf_semicolon();
}

Ret Input::lex_conf_api_style(Opt& opts) {
    CHECK_RET(lex_conf_assign());
/*!local:re2c
    * {
        RET_FAIL(error_at_cur("bad configuration value (expected: 'functions', 'free-form')"));
    }
    "functions" { opts.set_api_style(ApiStyle::FUNCTIONS); goto end; }
    "free-form" { opts.set_api_style(ApiStyle::FREEFORM);  goto end; }
*/
end:
    return lex_conf_semicolon();
}

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

Ret Input::lex_conf_number() {
    CHECK_RET(parse_conf());
    if (conf_kind != ConfKind::NUM) {
        RET_FAIL(error_at_tok("configuration value should be a number"));
    }
    return Ret::OK;
}

inline Ret Input::lex_conf_bool() {
    CHECK_RET(parse_conf());
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

Ret Input::lex_conf_string() {
    if (!in_syntax_file) {
        return lex_conf_string_legacy();
    }

    CHECK_RET(parse_conf());
    if (conf_kind != ConfKind::STR) {
        RET_FAIL(error_at_tok("configuration value should be a string"));
    }
    return Ret::OK;
}

Ret Input::lex_conf_list() {
    CHECK_RET(parse_conf());
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
        }
        tmp_str += static_cast<char>(c.chr);
    }
}

Ret Input::lex_conf_token(CONF_STYPE* yylval, int& token) {
start:
    tok = cur;
/*!local:re2c
    semi {
        RET_TOK(CONF_EOF);
    }
    eof {
        RET_FAIL(error_at_cur("unexpected end of input in configuration"));
    }
    eol {
        next_line();
        goto start;
    }
    special {
        RET_TOK(cur[-1]);
    }
    space+ {
        goto start;
    }
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
    "" / [a-z] {
        goto opt;
    }
    * {
        RET_FAIL(error_at_cur("unexpected character: '%c'", cur[-1]));
    }
*/

opt:
    tok = cur;
    // A subset of options is exported for use in `conf:*` configurations in syntax files.
    // Only constant options should be allowed here, as they will be used before the input file is
    // parsed and mutable options (block-level configurations) are known.
    //
    // These options are part of the syntax file API and should not be removed or changed.
/*!local:re2c
    "code_model.goto_label"          { RET_OPT(globopts->code_model == CodeModel::GOTO_LABEL); }
    "code_model.loop_switch"         { RET_OPT(globopts->code_model == CodeModel::LOOP_SWITCH); }
    "code_model.recursive_functions" { RET_OPT(globopts->code_model == CodeModel::REC_FUNC); }

    * { RET_FAIL(error_at_cur("unknown option '%.*s'", int(cur - tok), tok)); }
*/

    UNREACHABLE();
    return Ret::FAIL; // unreachable
}

#undef YYFILL
#undef RET_CONF_BOOL
#undef RET_CONF_STR
#undef RET_CONF_ENC
#undef RET_CONF_NUM_NONNEG
#undef RET_TOK
#undef RET_OPT

} // end namespace re2c
