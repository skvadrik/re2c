#include <stdint.h>
#include <string>

#include "src/encoding/enc.h"
#include "src/msg/msg.h"
#include "src/options/opt.h"
#include "src/parse/ast.h"
#include "src/parse/scanner.h"
#include "src/util/file_utils.h"
#include "src/util/s_to_n32_unsafe.h"
#include "src/util/string_utils.h"


namespace re2c {

#define YYFILL(n) \
    do { if (!fill(n)) { error("unexpected end of input"); exit(1); }} while(0)
#define RET_CONF_BOOL(conf) \
    do { opts.set_##conf(lex_conf_bool()); return; } while(0)
#define RET_CONF_STR(conf) \
    do { opts.set_##conf(lex_conf_string()); return; } while(0)
#define RET_CONF_ENC(enc) \
    do { opts.set_encoding(enc, lex_conf_bool()); return; } while(0)
#define RET_CONF_NUM(conf) \
    do { opts.set_##conf(lex_conf_number()); return; } while(0)
#define RET_CONF_NUM_NONNEG(conf) \
    do { \
        const int32_t n = lex_conf_number(); \
        if (n < 0) { \
            msg.error(cur_loc(), "expected nonnegative value in configuration"); \
            exit(1); \
        } \
        opts.set_##conf(static_cast<uint32_t>(n)); \
        return; \
    } while(0)

/*!re2c
    re2c:define:YYCTYPE     = "unsigned char";
    re2c:define:YYCURSOR    = cur;
    re2c:define:YYLIMIT     = lim;
    re2c:define:YYMARKER    = mar;
    re2c:define:YYCTXMARKER = ctx;

    // source code is in ASCII: pointers have type 'char *'
    // but re2c makes an implicit assumption that YYCTYPE is unsigned
    // when it generates comparisons
    re2c:yych:conversion = 1;

    space       = [ \t];
    conf_assign = space* "=" space*;
    naked_char  = [^\x00\n] \ (space | [;]);
    naked       = (naked_char \ ['"]) naked_char*;
    number      = "0" | ("-"? [1-9] [0-9]*);
*/

void Scanner::lex_conf(Opt &opts) {
    tok = cur;
/*!local:re2c
    "api" | "flags:input" { lex_conf_input(opts); return; }
    "api:style"           { lex_conf_api_style(opts); return; }
    "api:sigil"           { RET_CONF_STR(api_sigil); }

    // header filename in configuration is relative to the output file directory
    "header" | "flags:type-header" | "flags:t" {
        std::string name(lex_conf_string());
        std::string path(opts.glob.output_file);
        get_dir(path);
        opts.set_header_file(path + name);
        return;
    }

    "eof"      { opts.set_eof(lex_conf_eof()); return; }
    "sentinel" { opts.set_sentinel(lex_conf_eof()); return; }

    "yyfill:enable"    { RET_CONF_BOOL(fill_use); }
    "yyfill:parameter" { RET_CONF_BOOL(fill_arg_use); }
    "yyfill:check"     { RET_CONF_BOOL(fill_check); }

    "flags:"? "tags"           | "flags:T" { RET_CONF_BOOL(tags); }
    "flags:"? "posix-captures" | "flags:P" {
        bool b = lex_conf_bool();
        opts.set_posix_syntax(b);
        opts.set_posix_semantics(b);
        return;
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
    "variable:"  "yystable"        { lex_conf_string(); return; } // deprecated

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

    "encoding:ebcdic" | "flags:ecb"        | "flags:e" { RET_CONF_ENC(Enc::EBCDIC); }
    "encoding:utf32"  | "flags:unicode"    | "flags:u" { RET_CONF_ENC(Enc::UTF32); }
    "encoding:ucs2"   | "flags:wide-chars" | "flags:w" { RET_CONF_ENC(Enc::UCS2); }
    "encoding:utf16"  | "flags:utf-16"     | "flags:x" { RET_CONF_ENC(Enc::UTF16); }
    "encoding:utf8"   | "flags:utf-8"      | "flags:8" { RET_CONF_ENC(Enc::UTF8); }

    "flags:"? "encoding-policy" { lex_conf_encoding_policy(opts); return; }
    "flags:"? "empty-class"     { lex_conf_empty_class(opts); return; }

    "indent:string" { RET_CONF_STR(indString); }
    "indent:top"    { RET_CONF_NUM_NONNEG(topIndent); }

    "label:prefix" | "labelprefix"                    { RET_CONF_STR(labelPrefix); }
    "label:yyfill" | "label:yyFillLabel"              { RET_CONF_STR(yyfilllabel); }
    "label:yyloop"                                    { RET_CONF_STR(yyloop); }
    "label:yyNext"                                    { RET_CONF_STR(yynext); }
    "label:start" | "startlabel" / conf_assign number { RET_CONF_BOOL(startlabel_force); }
    "label:start" | "startlabel"                      { RET_CONF_STR(startlabel); }

    [a-zA-Z0-9_:-]* {
        msg.error(tok_loc(), "unrecognized configuration '%.*s'", (int)(cur - tok), tok);
        exit(1);
    }
*/
}

void Scanner::lex_conf_encoding_policy(Opt &opts)
{
    lex_conf_assign ();
/*!local:re2c
    * {
        msg.error(cur_loc(),
            "bad configuration value (expected: 'ignore', 'substitute', 'fail')");
        exit(1);
    }
    "ignore"     { opts.set_encoding_policy(Enc::POLICY_IGNORE);     goto end; }
    "substitute" { opts.set_encoding_policy(Enc::POLICY_SUBSTITUTE); goto end; }
    "fail"       { opts.set_encoding_policy(Enc::POLICY_FAIL);       goto end; }
*/
end:
    lex_conf_semicolon();
}

void Scanner::lex_conf_input(Opt &opts)
{
    lex_conf_assign ();
/*!local:re2c
    * {
        msg.error(cur_loc(),
            "bad configuration value (expected: 'default', 'custom')");
        exit(1);
    }
    "default" { opts.set_input_api(INPUT_DEFAULT); goto end; }
    "custom"  { opts.set_input_api(INPUT_CUSTOM);  goto end; }
*/
end:
    lex_conf_semicolon();
}

void Scanner::lex_conf_empty_class(Opt &opts)
{
    lex_conf_assign ();
/*!local:re2c
    * {
        msg.error(cur_loc(),
            "bad configuration value (expected: 'match-empty', 'match-none', 'error')");
        exit(1);
    }
    "match-empty" { opts.set_empty_class_policy(EMPTY_CLASS_MATCH_EMPTY); goto end; }
    "match-none"  { opts.set_empty_class_policy(EMPTY_CLASS_MATCH_NONE);  goto end; }
    "error"       { opts.set_empty_class_policy(EMPTY_CLASS_ERROR);       goto end; }
*/
end:
    lex_conf_semicolon();
}

void Scanner::lex_conf_api_style(Opt &opts)
{
    lex_conf_assign ();
/*!local:re2c
    * {
        msg.error(cur_loc(),
            "bad configuration value (expected: 'functions', 'free-form')");
        exit(1);
    }
    "functions" { opts.set_api_style(API_FUNCTIONS); goto end; }
    "free-form" { opts.set_api_style(API_FREEFORM);  goto end; }
*/
end:
    lex_conf_semicolon();
}

void Scanner::lex_conf_assign ()
{
/*!local:re2c
    * {
        msg.error(cur_loc(), "missing '=' in configuration");
        exit(1);
    }
    conf_assign { return; }
*/
}

void Scanner::lex_conf_semicolon ()
{
/*!local:re2c
    * {
        msg.error(cur_loc(), "missing ending ';' in configuration");
        exit(1);
    }
    space* ";" { return; }
*/
}

int32_t Scanner::lex_conf_number ()
{
    lex_conf_assign ();
    tok = cur;
/*!local:re2c
    * {
        msg.error(cur_loc(), "bad configuration value (expected number)");
        exit(1);
    }
    number {
        int32_t n = 0;
        if (!s_to_i32_unsafe (tok, cur, n)) {
            msg.error(cur_loc(), "configuration value overflow");
            exit(1);
        }
        lex_conf_semicolon ();
        return n;
    }
*/
}

std::string Scanner::lex_conf_string ()
{
    lex_conf_assign ();
    std::string s;
    tok = cur;
/*!local:re2c
    ['"] {
        const char quote = tok[0];
        for (;;) {
            ASTChar c;
            if (!lex_str_chr(quote, c)) {
                goto end;
            }
            if (c.chr > 0xFF) {
                msg.error(c.loc
                    , "multibyte character in configuration string: 0x%X"
                    , c.chr);
                exit(1);
            } else {
                s += static_cast<char>(c.chr);
            }
        }
    }
    naked {
        s = getstr(tok, cur);
        goto end;
    }
    "" { goto end; }
*/
end:
    lex_conf_semicolon ();
    return s;
}

#undef YYFILL
#undef RET_CONF_BOOL
#undef RET_CONF_STR
#undef RET_CONF_ENC

} // end namespace re2c
