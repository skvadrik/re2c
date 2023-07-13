#include <stdint.h>
#include <string>

#include "src/encoding/enc.h"
#include "src/msg/msg.h"
#include "src/options/opt.h"
#include "src/parse/ast.h"
#include "src/parse/input.h"
#include "src/util/file_utils.h"
#include "src/util/string_utils.h"

namespace re2c {

#define YYFILL(n) if (!fill(n)) RET_FAIL(error_at_cur("unexpected end of input in configuration"))

#define RET_CONF_BOOL(conf) do { \
    CHECK_RET(lex_conf_bool(b)); \
    opts.set_##conf(b); \
    return Ret::OK; \
} while(0)

#define RET_CONF_STR(conf) do { \
    CHECK_RET(lex_conf_string(s)); \
    opts.set_##conf(s); \
    return Ret::OK; \
} while(0)

#define RET_CONF_ENC(enc) do { \
    CHECK_RET(lex_conf_bool(b)); \
    opts.set_encoding(enc, b); \
    return Ret::OK; \
} while(0)

#define RET_CONF_NUM_NONNEG(conf) do { \
    CHECK_RET(lex_conf_number(n)); \
    if (n < 0) RET_FAIL(error_at_cur("expected nonnegative value in configuration")); \
    opts.set_##conf(static_cast<uint32_t>(n)); \
    return Ret::OK; \
} while(0)

/*!re2c
    re2c:define:YYCTYPE     = uint8_t;
    re2c:define:YYCURSOR    = cur;
    re2c:define:YYLIMIT     = lim;
    re2c:define:YYMARKER    = mar;
    re2c:define:YYCTXMARKER = ctx;

    space       = [ \t];
    conf_assign = space* "=" space*;
    naked_char  = [^\x00\n] \ (space | [;]);
    naked       = (naked_char \ ['"]) naked_char*;
    number      = "0" | ("-"? [1-9] [0-9]*);
*/

Ret Input::lex_conf(Opt& opts) {
    bool b;
    int32_t n;
    uint32_t u;
    std::string s;

    tok = cur;
/*!local:re2c
    "api" | "flags:input" { return lex_conf_input(opts); }
    "api:style"           { return lex_conf_api_style(opts); }
    "api:sigil"           { RET_CONF_STR(api_sigil); }

    // header filename in configuration is relative to the output file directory
    "header" | "flags:type-header" | "flags:t" {
        CHECK_RET(lex_conf_string(s));
        std::string path(opts.glob.output_file);
        get_dir(path);
        opts.set_header_file(path + s);
        return Ret::OK;
    }

    "eof"      { CHECK_RET(lex_conf_eof(u)); opts.set_fill_eof(u);      return Ret::OK; }
    "sentinel" { CHECK_RET(lex_conf_eof(u)); opts.set_fill_sentinel(u); return Ret::OK; }

    "yyfill:enable"    { RET_CONF_BOOL(fill_enable); }
    "yyfill:parameter" { RET_CONF_BOOL(fill_param_enable); }
    "yyfill:check"     { RET_CONF_BOOL(fill_check); }

    "flags:"? "tags" | "flags:T" { RET_CONF_BOOL(tags); }
    "flags:"? "leftmost-captures" {
        CHECK_RET(lex_conf_bool(b));
        opts.set_tags_posix_syntax(b);
        return Ret::OK;
    }
    "flags:"? "posix-captures" | "flags:P" {
        CHECK_RET(lex_conf_bool(b));
        opts.set_tags_posix_syntax(b);
        opts.set_tags_posix_semantics(b);
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

    "variable:"  "yyctable"        { RET_CONF_STR(var_cond_table); }
    "variable:"  "yyaccept"        { RET_CONF_STR(var_accept); }
    "variable:"  "yytarget"        { RET_CONF_STR(var_cgoto_table); }
    "variable:"  "yystate"         { RET_CONF_STR(var_state); }
    "variable:"  "yych"            { RET_CONF_STR(var_char); }
    "variable:"? "yych:conversion" { RET_CONF_BOOL(char_conv); }
    "variable:"? "yych:emit"       { RET_CONF_BOOL(char_emit); }
    "variable:"  "yybm"            { RET_CONF_STR(var_bitmaps); }
    "variable:"? "yybm:hex"        { RET_CONF_BOOL(bitmaps_hex); }
    "variable:"  "yystable"        { return lex_conf_string(s); } // deprecated

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

Ret Input::lex_conf_number(int32_t& n) {
    CHECK_RET(lex_conf_assign());
    tok = cur;
/*!local:re2c
    *      { RET_FAIL(error_at_cur("bad configuration value (expected number)")); }
    number {
        n = 0;
        if (!s_to_i32_unsafe (tok, cur, n)) {
            RET_FAIL(error_at_cur("configuration value overflow"));
        }
        return lex_conf_semicolon();
    }
*/
}

inline Ret Input::lex_conf_bool(bool& b) {
    int32_t n;
    CHECK_RET(lex_conf_number(n));
    b = n != 0;
    return Ret::OK;
}

Ret Input::lex_conf_string(std::string& s) {
    CHECK_RET(lex_conf_assign());
    s.clear();
    tok = cur;
/*!local:re2c
    ['"] {
        const uint8_t quote = tok[0];
        AstChar c;
        bool stop;
        for (;;) {
            CHECK_RET(lex_str_chr(quote, c, stop)); 
            if (stop) {
                goto end;
            } else if (c.chr > 0xFF) {
                RET_FAIL(error_at(
                        c.loc, "multibyte character in configuration string: 0x%X", c.chr));
            } else {
                s += static_cast<char>(c.chr);
            }
        }
    }
    naked { s.assign(tok, cur); goto end; }
    ""    { goto end; }
*/
end:
    return lex_conf_semicolon();
}

Ret Input::lex_conf_eof(uint32_t& u) {
    int32_t n;
    CHECK_RET(lex_conf_number(n));
    u = n < 0 ? NOEOF : static_cast<uint32_t>(n);
    return Ret::OK;
}

#undef YYFILL
#undef RET_CONF_BOOL
#undef RET_CONF_STR
#undef RET_CONF_ENC
#undef RET_CONF_NUM_NONNEG

} // end namespace re2c
