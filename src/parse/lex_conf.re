#include <stdint.h>
#include <string>

#include "src/encoding/enc.h"
#include "src/msg/msg.h"
#include "src/options/opt.h"
#include "src/parse/ast.h"
#include "src/parse/scanner.h"
#include "src/util/file_utils.h"
#include "src/util/string_utils.h"

namespace re2c {

#define YYFILL(n) if (!fill(n)) RET_FAIL(error("unexpected end of input in configuration"))

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

#define RET_CONF_NUM(conf) do { \
    CHECK_RET(lex_conf_number(n)); \
    opts.set_##conf(n); \
    return Ret::OK; \
} while(0)

#define RET_CONF_NUM_NONNEG(conf) do { \
    CHECK_RET(lex_conf_number(n)); \
    if (n < 0) RET_FAIL(msg.error(cur_loc(), "expected nonnegative value in configuration")); \
    opts.set_##conf(static_cast<uint32_t>(n)); \
    return Ret::OK; \
} while(0)

/*!re2c
    re2c:define:YYCTYPE     = "unsigned char";
    re2c:define:YYCURSOR    = cur;
    re2c:define:YYLIMIT     = lim;
    re2c:define:YYMARKER    = mar;
    re2c:define:YYCTXMARKER = ctx;

    // Source code is in ASCII: pointers have type `char*`,  but re2c makes an implicit assumption
    // that YYCTYPE is unsigned when it generates comparisons.
    re2c:yych:conversion = 1;

    space       = [ \t];
    conf_assign = space* "=" space*;
    naked_char  = [^\x00\n] \ (space | [;]);
    naked       = (naked_char \ ['"]) naked_char*;
    number      = "0" | ("-"? [1-9] [0-9]*);
*/

Ret Scanner::lex_conf(Opt& opts) {
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

    "eof"      { CHECK_RET(lex_conf_eof(u)); opts.set_eof(u);      return Ret::OK; }
    "sentinel" { CHECK_RET(lex_conf_eof(u)); opts.set_sentinel(u); return Ret::OK; }

    "yyfill:enable"    { RET_CONF_BOOL(fill_use); }
    "yyfill:parameter" { RET_CONF_BOOL(fill_arg_use); }
    "yyfill:check"     { RET_CONF_BOOL(fill_check); }

    "flags:"? "tags"           | "flags:T" { RET_CONF_BOOL(tags); }
    "flags:"? "posix-captures" | "flags:P" {
        CHECK_RET(lex_conf_bool(b));
        opts.set_posix_syntax(b);
        opts.set_posix_semantics(b);
        return Ret::OK;
    }
    "tags:prefix"     { RET_CONF_STR(tags_prefix); }
    "tags:expression" { RET_CONF_STR(tags_expression); }

    "define:YYBACKUP"             { RET_CONF_STR(yybackup); }
    "define:YYBACKUPCTX"          { RET_CONF_STR(yybackupctx); }
    "define:YYCONDTYPE"           { RET_CONF_STR(yycondtype); }
    "define:YYCTYPE"              { RET_CONF_STR(yyctype); }
    "define:YYCTXMARKER"          { RET_CONF_STR(yyctxmarker); }
    "define:YYCURSOR"             { RET_CONF_STR(yycursor); }
    "define:YYDEBUG"              { RET_CONF_STR(yydebug); }
    "define:YYFILL"               { RET_CONF_STR(fill); }
    "define:YYFILL@len"           { RET_CONF_STR(fill_arg); }
    "define:YYFILL:naked"         { RET_CONF_BOOL(fill_naked); }
    "define:YYGETCONDITION"       { RET_CONF_STR(cond_get); }
    "define:YYGETCONDITION:naked" { RET_CONF_BOOL(cond_get_naked); }
    "define:YYGETSTATE"           { RET_CONF_STR(state_get); }
    "define:YYGETSTATE:naked"     { RET_CONF_BOOL(state_get_naked); }
    "define:YYLESSTHAN"           { RET_CONF_STR(yylessthan); }
    "define:YYLIMIT"              { RET_CONF_STR(yylimit); }
    "define:YYMARKER"             { RET_CONF_STR(yymarker); }
    "define:YYMTAGN"              { RET_CONF_STR(yymtagn); }
    "define:YYMTAGP"              { RET_CONF_STR(yymtagp); }
    "define:YYPEEK"               { RET_CONF_STR(yypeek); }
    "define:YYRESTORE"            { RET_CONF_STR(yyrestore); }
    "define:YYRESTORECTX"         { RET_CONF_STR(yyrestorectx); }
    "define:YYRESTORETAG"         { RET_CONF_STR(yyrestoretag); }
    "define:YYSETCONDITION"       { RET_CONF_STR(cond_set); }
    "define:YYSETCONDITION@cond"  { RET_CONF_STR(cond_set_arg); }
    "define:YYSETCONDITION:naked" { RET_CONF_BOOL(cond_set_naked); }
    "define:YYSETSTATE"           { RET_CONF_STR(state_set); }
    "define:YYSETSTATE:naked"     { RET_CONF_BOOL(state_set_naked); }
    "define:YYSETSTATE@state"     { RET_CONF_STR(state_set_arg); }
    "define:YYSHIFT"              { RET_CONF_STR(yyshift); }
    "define:YYSHIFTSTAG"          { RET_CONF_STR(yyshiftstag); }
    "define:YYSHIFTMTAG"          { RET_CONF_STR(yyshiftmtag); }
    "define:YYSKIP"               { RET_CONF_STR(yyskip); }
    "define:YYSTAGN"              { RET_CONF_STR(yystagn); }
    "define:YYSTAGP"              { RET_CONF_STR(yystagp); }

    "variable:"  "yyctable"        { RET_CONF_STR(yyctable); }
    "variable:"  "yyaccept"        { RET_CONF_STR(yyaccept); }
    "variable:"  "yytarget"        { RET_CONF_STR(yytarget); }
    "variable:"  "yystate"         { RET_CONF_STR(yystate); }
    "variable:"  "yych"            { RET_CONF_STR(yych); }
    "variable:"? "yych:conversion" { RET_CONF_BOOL(yychConversion); }
    "variable:"? "yych:emit"       { RET_CONF_BOOL(bEmitYYCh); }
    "variable:"  "yybm"            { RET_CONF_STR(yybm); }
    "variable:"? "yybm:hex"        { RET_CONF_BOOL(yybmHexTable); }
    "variable:"  "yystable"        { return lex_conf_string(s); } // deprecated

    "cond:prefix" | "condprefix"         { RET_CONF_STR(condPrefix); }
    "cond:enumprefix" | "condenumprefix" { RET_CONF_STR(condEnumPrefix); }
    "cond:divider"                       { RET_CONF_STR(condDivider); }
    "cond:divider@cond"                  { RET_CONF_STR(condDividerParam); }
    "cond:goto"                          { RET_CONF_STR(condGoto); }
    "cond:goto@cond"                     { RET_CONF_STR(condGotoParam); }

    "state:abort"     { RET_CONF_BOOL(bUseStateAbort); }
    "state:nextlabel" { RET_CONF_BOOL(bUseStateNext); }

    "flags:"? "bit-vectors"    | "flags:b"    { RET_CONF_BOOL(bFlag); }
    "flags:"? "debug-output"   | "flags:d"    { RET_CONF_BOOL(dFlag); }
    "flags:"? "computed-gotos" | "flags:g"    { RET_CONF_BOOL(gFlag); }
    ("computed-gotos" | "cgoto") ":threshold" { RET_CONF_NUM_NONNEG(cGotoThreshold); }
    "flags:"? "nested-ifs"     | "flags:s"    { RET_CONF_BOOL(sFlag); }
    "flags:"? "case-insensitive"              { RET_CONF_BOOL(bCaseInsensitive); }
    "flags:"? "case-inverted"                 { RET_CONF_BOOL(bCaseInverted); }
    "flags:"? "case-ranges"                   { RET_CONF_BOOL(case_ranges); }
    "flags:"? "unsafe"                        { RET_CONF_BOOL(unsafe); }

    "encoding:ebcdic" | "flags:ecb"        | "flags:e" { RET_CONF_ENC(Enc::Type::EBCDIC); }
    "encoding:utf32"  | "flags:unicode"    | "flags:u" { RET_CONF_ENC(Enc::Type::UTF32); }
    "encoding:ucs2"   | "flags:wide-chars" | "flags:w" { RET_CONF_ENC(Enc::Type::UCS2); }
    "encoding:utf16"  | "flags:utf-16"     | "flags:x" { RET_CONF_ENC(Enc::Type::UTF16); }
    "encoding:utf8"   | "flags:utf-8"      | "flags:8" { RET_CONF_ENC(Enc::Type::UTF8); }

    "flags:"? "encoding-policy" { return lex_conf_encoding_policy(opts); }
    "flags:"? "empty-class"     { return lex_conf_empty_class(opts); }

    "indent:string" { RET_CONF_STR(indString); }
    "indent:top"    { RET_CONF_NUM_NONNEG(topIndent); }

    "label:prefix" | "labelprefix"                    { RET_CONF_STR(labelPrefix); }
    "label:yyfill" | "label:yyFillLabel"              { RET_CONF_STR(yyfilllabel); }
    "label:yyloop"                                    { RET_CONF_STR(yyloop); }
    "label:yyNext"                                    { RET_CONF_STR(yynext); }
    "label:start" | "startlabel" / conf_assign number { RET_CONF_BOOL(startlabel_force); }
    "label:start" | "startlabel"                      { RET_CONF_STR(startlabel); }

    [a-zA-Z0-9_:-]* {
        RET_FAIL(msg.error(tok_loc(), "unrecognized configuration '%.*s'", (int)(cur - tok), tok));
    }
*/
}

Ret Scanner::lex_conf_encoding_policy(Opt& opts) {
    CHECK_RET(lex_conf_assign());
/*!local:re2c
    * {
        RET_FAIL(msg.error(cur_loc(),
                           "bad configuration value (expected: 'ignore', 'substitute', 'fail')"));
    }
    "ignore"     { opts.set_encoding_policy(Enc::Policy::IGNORE);     goto end; }
    "substitute" { opts.set_encoding_policy(Enc::Policy::SUBSTITUTE); goto end; }
    "fail"       { opts.set_encoding_policy(Enc::Policy::FAIL);       goto end; }
*/
end:
    return lex_conf_semicolon();
}

Ret Scanner::lex_conf_input(Opt& opts) {
    CHECK_RET(lex_conf_assign());
/*!local:re2c
    * {
        RET_FAIL(msg.error(cur_loc(), "bad configuration value (expected: 'default', 'custom')"));
    }
    "default" { opts.set_input_api(Api::DEFAULT); goto end; }
    "custom"  { opts.set_input_api(Api::CUSTOM);  goto end; }
*/
end:
    return lex_conf_semicolon();
}

Ret Scanner::lex_conf_empty_class(Opt& opts) {
    CHECK_RET(lex_conf_assign());
/*!local:re2c
    * {
        RET_FAIL(msg.error(cur_loc(),
                           "bad configuration value (expected: 'match-empty', 'match-none', "
                           "'error')"));
    }
    "match-empty" { opts.set_empty_class_policy(EmptyClassPolicy::MATCH_EMPTY); goto end; }
    "match-none"  { opts.set_empty_class_policy(EmptyClassPolicy::MATCH_NONE);  goto end; }
    "error"       { opts.set_empty_class_policy(EmptyClassPolicy::ERROR);       goto end; }
*/
end:
    return lex_conf_semicolon();
}

Ret Scanner::lex_conf_api_style(Opt& opts) {
    CHECK_RET(lex_conf_assign());
/*!local:re2c
    * {
        RET_FAIL(msg.error(cur_loc(),
                           "bad configuration value (expected: 'functions', 'free-form')"));
    }
    "functions" { opts.set_api_style(ApiStyle::FUNCTIONS); goto end; }
    "free-form" { opts.set_api_style(ApiStyle::FREEFORM);  goto end; }
*/
end:
    return lex_conf_semicolon();
}

Ret Scanner::lex_conf_assign() {
/*!local:re2c
    *           { RET_FAIL(msg.error(cur_loc(), "missing '=' in configuration")); }
    conf_assign { return Ret::OK; }
*/
}

Ret Scanner::lex_conf_semicolon() {
/*!local:re2c
    *          { RET_FAIL(msg.error(cur_loc(), "missing ending ';' in configuration")); }
    space* ";" { return Ret::OK; }
*/
}

Ret Scanner::lex_conf_number(int32_t& n) {
    CHECK_RET(lex_conf_assign());
    tok = cur;
/*!local:re2c
    *      { RET_FAIL(msg.error(cur_loc(), "bad configuration value (expected number)")); }
    number {
        n = 0;
        if (!s_to_i32_unsafe (tok, cur, n)) {
            RET_FAIL(msg.error(cur_loc(), "configuration value overflow"));
        }
        return lex_conf_semicolon();
    }
*/
}

inline Ret Scanner::lex_conf_bool(bool& b) {
    int32_t n;
    CHECK_RET(lex_conf_number(n));
    b = n != 0;
    return Ret::OK;
}

Ret Scanner::lex_conf_string(std::string& s) {
    CHECK_RET(lex_conf_assign());
    s.clear();
    tok = cur;
/*!local:re2c
    ['"] {
        const char quote = tok[0];
        AstChar c;
        bool stop;
        for (;;) {
            CHECK_RET(lex_str_chr(quote, c, stop)); 
            if (stop) {
                goto end;
            } else if (c.chr > 0xFF) {
                RET_FAIL(msg.error(c.loc,
                                   "multibyte character in configuration string: 0x%X", c.chr));
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

Ret Scanner::lex_conf_eof(uint32_t& u) {
    int32_t n;
    CHECK_RET(lex_conf_number(n));
    u = n < 0 ? NOEOF : static_cast<uint32_t>(n);
    return Ret::OK;
}

#undef YYFILL
#undef RET_CONF_BOOL
#undef RET_CONF_STR
#undef RET_CONF_ENC

} // end namespace re2c
