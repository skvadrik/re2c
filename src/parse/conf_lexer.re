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

// Immutable options are only allowed in syntax files.
#define SETCONOPT(opt, val) do { \
    if (!in_syntax_file) { \
        RET_FAIL(error_at_cur("this configuration is only allowed in syntax files")); \
    } \
    const_cast<conopt_t&>(opts.glob).init_##opt(val); \
} while (0)

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
    SETOPT(conf, tmp_bool); \
    return Ret::OK; \
} while(0)

#define RET_STXCONF_BOOL(conf) do { \
    CHECK_RET(lex_conf_bool(opts)); \
    SETCONOPT(conf, tmp_bool); \
    return Ret::OK; \
} while(0)

#define RET_CONF_FEAT(conf, name) do { \
    CHECK_RET(lex_conf_bool(opts)); \
    if (tmp_bool && !opts.glob.supported_features_contains(name)) { \
        RET_FAIL(error_at_cur("`%s` feature is not supported for this backend", name)); \
    } \
    SETOPT(conf, tmp_bool); \
    return Ret::OK; \
} while(0)

#define RET_CONF_STR(conf) do { \
    CHECK_RET(lex_conf_string(opts)); \
    SETOPT(conf, tmp_str); \
    return Ret::OK; \
} while(0)

#define RET_CONF_CODE(conf) do { \
    CHECK_RET(lex_conf_code(opts)); \
    SETOPT(conf, tmp_code); \
    return Ret::OK; \
} while(0)

#define RET_CONF_ENC(enc) do { \
    CHECK_RET(lex_conf_bool(opts)); \
    if (in_syntax_file) { \
        opts.init_encoding(enc, tmp_bool); \
    } else { \
        opts.set_encoding(enc, tmp_bool); \
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

    eof        = [\x00];
    eol        = [\n];
    space      = [ \t\r];
    semi       = [;];
    quotes     = ['"];
    naked_char = [^] \ (eof | eol | space | semi);
    naked      = (naked_char \ quotes) naked_char*;
    number     = "0" | ("-"? [1-9] [0-9]*);
    comment    = "//" [^\x00\n]* eol;
*/

Ret Input::lex_conf(Opt& opts) {
/*!local:re2c
    // immutable configurations (syntax file only)

    "target"         { goto target; }
    "code-model"     { goto code_model; }
    "input-encoding" { goto input_enc; }
    "date"           { RET_STXCONF_BOOL(date); }
    "version"        { RET_STXCONF_BOOL(version); }
    "conditions"     { RET_STXCONF_BOOL(start_conditions); }
    "storable-state" { RET_STXCONF_BOOL(storable_state); }
    "flex-syntax"    { RET_STXCONF_BOOL(flex_syntax); }
    "verbose"        { RET_STXCONF_BOOL(verbose); }
    "line-dirs"      { RET_STXCONF_BOOL(line_dirs); }

    // mutable configurations (syntax file and source file)

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

    "flags:"? "tags" | "flags:T" {
        RET_CONF_BOOL(tags);
    }
    "flags:"? "leftmost-"? "captures" {
        CHECK_RET(lex_conf_bool(opts));
        SETOPT(captures, tmp_bool);
        SETOPT(captures_array, true);
        return Ret::OK;
    }
    "flags:"? "posix-captures" | "flags:P" {
        CHECK_RET(lex_conf_bool(opts));
        SETOPT(captures, tmp_bool);
        SETOPT(captures_posix, tmp_bool);
        SETOPT(captures_array, true);
        return Ret::OK;
    }
    "leftmost-"? "captvars" {
        CHECK_RET(lex_conf_bool(opts));
        SETOPT(captures, tmp_bool);
        SETOPT(captures_array, false);
        return Ret::OK;
    }
    "posix-captvars" {
        CHECK_RET(lex_conf_bool(opts));
        SETOPT(captures, tmp_bool);
        SETOPT(captures_posix, tmp_bool);
        SETOPT(captures_array, false);
        return Ret::OK;
    }
    "tags:prefix"     { RET_CONF_STR(tags_prefix); }
    "tags:expression" { RET_CONF_CODE(tags_expression); }
    "tags:negative"   { RET_CONF_CODE(tags_negative); }
    "invert-captures" { RET_CONF_BOOL(captures_invert); }

    "define:"? "YYBACKUP"                    { RET_CONF_CODE(api_backup); }
    "define:"? "YYBACKUPCTX"                 { RET_CONF_CODE(api_backup_ctx); }
    "define:"? "YYCONDTYPE"                  { RET_CONF_CODE(api_cond_type); }
    "define:"? "YYCOPYMTAG"                  { RET_CONF_CODE(api_mtag_copy); }
    "define:"? "YYCOPYSTAG"                  { RET_CONF_CODE(api_stag_copy); }
    "define:"? "YYCTYPE"                     { RET_CONF_CODE(api_char_type); }
    "define:"? "YYCTXMARKER"                 { RET_CONF_CODE(api_ctxmarker); }
    "define:"? "YYINPUT"                     { RET_CONF_CODE(api_input); }
    "define:"? "YYCURSOR"                    { RET_CONF_CODE(api_cursor); }
    "define:"? "YYDEBUG"                     { RET_CONF_CODE(api_debug); }
    "define:"? "YYFILL"                      { RET_CONF_CODE(api_fill); }
    "define:"? "YYFILL@len"                  { RET_CONF_STR(fill_param); }
    "define:"? "YYFILL:naked"                { RET_CONF_BOOL(fill_naked); }
    "define:"? "YYGETACCEPT"                 { RET_CONF_CODE(api_accept_get); }
    "define:"? "YYGETCOND" "ITION"?          { RET_CONF_CODE(api_cond_get); }
    "define:"? "YYGETCOND" "ITION"? ":naked" { RET_CONF_BOOL(cond_get_naked); }
    "define:"? "YYGETSTATE"                  { RET_CONF_CODE(api_state_get); }
    "define:"? "YYGETSTATE:naked"            { RET_CONF_BOOL(state_get_naked); }
    "define:"? "YYLESSTHAN"                  { RET_CONF_CODE(api_less_than); }
    "define:"? "YYLIMIT"                     { RET_CONF_CODE(api_limit); }
    "define:"? "YYMARKER"                    { RET_CONF_CODE(api_marker); }
    "define:"? "YYMAXFILL"                   { RET_CONF_CODE(api_maxfill); }
    "define:"? "YYMAXNMATCH"                 { RET_CONF_CODE(api_maxnmatch); }
    "define:"? "YYMTAGN"                     { RET_CONF_CODE(api_mtag_neg); }
    "define:"? "YYMTAGP"                     { RET_CONF_CODE(api_mtag_pos); }
    "define:"? "YYPEEK"                      { RET_CONF_CODE(api_peek); }
    "define:"? "YYRESTORE"                   { RET_CONF_CODE(api_restore); }
    "define:"? "YYRESTORECTX"                { RET_CONF_CODE(api_restore_ctx); }
    "define:"? "YYRESTORETAG"                { RET_CONF_CODE(api_restore_tag); }
    "define:"? "YYSETACCEPT"                 { RET_CONF_CODE(api_accept_set); }
    "define:"? "YYSETCOND" "ITION"?          { RET_CONF_CODE(api_cond_set); }
    "define:"? "YYSETCOND" "ITION"? "@cond"  { RET_CONF_STR(cond_set_param); }
    "define:"? "YYSETCOND" "ITION"? ":naked" { RET_CONF_BOOL(cond_set_naked); }
    "define:"? "YYSETSTATE"                  { RET_CONF_CODE(api_state_set); }
    "define:"? "YYSETSTATE:naked"            { RET_CONF_BOOL(state_set_naked); }
    "define:"? "YYSETSTATE@state"            { RET_CONF_STR(state_set_param); }
    "define:"? "YYSHIFT"                     { RET_CONF_CODE(api_shift); }
    "define:"? "YYSHIFTSTAG"                 { RET_CONF_CODE(api_stag_shift); }
    "define:"? "YYSHIFTMTAG"                 { RET_CONF_CODE(api_mtag_shift); }
    "define:"? "YYSKIP"                      { RET_CONF_CODE(api_skip); }
    "define:"? "YYSTAGN"                     { RET_CONF_CODE(api_stag_neg); }
    "define:"? "YYSTAGP"                     { RET_CONF_CODE(api_stag_pos); }
    "define:"? "YYFN" {
        CHECK_RET(lex_conf_list(opts));
        if (tmp_list.size() < 1) {
            RET_FAIL(error_at_tok(
                "`re2c:YYFN` configuration value should be a nonempty list of strings"));
        }
        SETOPT(api_fn, tmp_list);
        return Ret::OK;
    }

    "variable:"? "yycond"          { RET_CONF_STR(var_cond); }
    "variable:"? "yyctable"        { RET_CONF_STR(var_cond_table); }
    "variable:"? "yyaccept"        { RET_CONF_STR(var_accept); }
    "variable:"? "yytarget"        { RET_CONF_STR(var_computed_gotos_table); }
    "variable:"? "yystate"         { RET_CONF_STR(var_state); }
    "variable:"? "yynmatch"        { RET_CONF_STR(var_nmatch); }
    "variable:"? "yypmatch"        { RET_CONF_STR(var_pmatch); }
    "variable:"? "yyrecord"        { RET_CONF_STR(var_record); }
    "variable:"? "yych"            { RET_CONF_STR(var_char); }
    "variable:"? "yych:conversion" { RET_CONF_BOOL(char_conv); }
    "variable:"? "yych:literals"   { goto char_lit; }
    "variable:"? "yych:emit"       { RET_CONF_BOOL(char_emit); }
    "variable:"? "yybm"            { RET_CONF_STR(var_bitmaps); }
    "variable:"? "yybm:hex"        { RET_CONF_BOOL(bitmaps_hex); }
    "variable:"? "yyfill"          { RET_CONF_STR(var_fill); }
    "variable:"? "yystable"        { return lex_conf_string(opts); } // deprecated

    "cond:abort"                         { RET_CONF_BOOL(cond_abort); }
    "cond:prefix" | "condprefix"         { RET_CONF_STR(cond_label_prefix); }
    "cond:enumprefix" | "condenumprefix" { RET_CONF_STR(cond_enum_prefix); }
    "cond:divider"                       { RET_CONF_CODE(cond_div); }
    "cond:divider@cond"                  { RET_CONF_STR(cond_div_param); }
    "cond:goto"                          { RET_CONF_CODE(cond_goto); }
    "cond:goto@cond"                     { RET_CONF_STR(cond_goto_param); }

    "state:abort"     { RET_CONF_BOOL(state_abort); }
    "state:nextlabel" { RET_CONF_BOOL(state_next); }

    "flags:"? "bit-vectors"    | "flags:b"    { RET_CONF_FEAT(bitmaps, "bitmaps"); }
    "flags:"? "debug-output"   | "flags:d"    { RET_CONF_BOOL(debug); }
    "flags:"? "computed-gotos" | "flags:g"    { RET_CONF_FEAT(computed_gotos, "computed-gotos"); }
    ("computed-gotos" | "cgoto") ":threshold" { RET_CONF_NUM_NONNEG(computed_gotos_threshold); }
    "flags:"? "nested-ifs"     | "flags:s"    { RET_CONF_FEAT(nested_ifs, "nested-ifs"); }
    "flags:"? "case-insensitive"              { RET_CONF_BOOL(case_insensitive); }
    "flags:"? "case-inverted"                 { RET_CONF_BOOL(case_inverted); }
    "flags:"? "case-ranges"                   { RET_CONF_FEAT(case_ranges, "case-ranges"); }
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

    "label:prefix" | "labelprefix"       { RET_CONF_STR(label_prefix); }
    "label:yyfill" | "label:yyFillLabel" { RET_CONF_STR(label_fill); }
    "label:yyloop"                       { RET_CONF_STR(label_loop); }
    "label:yyNext"                       { RET_CONF_STR(label_next); }
    "label:start" | "startlabel" / space* "=" space* number { RET_CONF_BOOL(label_start_force); }
    "label:start" | "startlabel"         { RET_CONF_STR(label_start); }

    [a-zA-Z0-9_:-]* {
        RET_FAIL(error_at_tok(
                "unrecognized configuration '%.*s'", static_cast<int>(cur - tok), tok));
    }
*/

target:
    CHECK_RET(lex_conf_assign());
/*!local:re2c
    * {
        RET_FAIL(error_at_cur("bad configuration value (expected: 'code', 'skeleton', 'dot')"));
    }
    "code"     { SETCONOPT(target, Target::CODE);     goto end; }
    "skeleton" { SETCONOPT(target, Target::SKELETON); goto end; }
    "dot"      { SETCONOPT(target, Target::DOT);      goto end; }
*/

code_model:
    CHECK_RET(lex_conf_assign());
/*!local:re2c
    * {
        RET_FAIL(error_at_cur("bad configuration value"
            " (expected: 'goto-label', 'loop-switch', 'recursive-functions')"));
    }
    "goto-label"          { SETCONOPT(code_model, CodeModel::GOTO_LABEL);  goto end; }
    "loop-switch"         { SETCONOPT(code_model, CodeModel::LOOP_SWITCH); goto end; }
    "recursive-functions" { SETCONOPT(code_model, CodeModel::REC_FUNC);    goto end; }
*/

input_enc:
    CHECK_RET(lex_conf_assign());
/*!local:re2c
    * {
        RET_FAIL(error_at_cur("bad configuration value (expected: 'ascii', 'utf8')"));
    }
    "ascii" { SETCONOPT(input_encoding, Enc::Type::ASCII); goto end; }
    "utf8"  { SETCONOPT(input_encoding, Enc::Type::UTF8);  goto end; }
*/

input:
    CHECK_RET(lex_conf_assign());
/*!local:re2c
    * {
        RET_FAIL(error_at_cur("bad configuration value (expected: 'simple', 'generic', 'record')"));
    }
    "simple" | "default" { SETOPT(api, Api::SIMPLE);  goto end; }
    "generic" | "custom" { SETOPT(api, Api::GENERIC); goto end; }
    "record"             { SETOPT(api, Api::RECORD);  goto end; }
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
        RET_FAIL(error_at_cur("bad configuration value (expected: 'char', 'hex', 'char-or-hex')"));
    }
    "char"        { SETOPT(char_literals, CharLit::CHAR);        goto end; }
    "hex"         { SETOPT(char_literals, CharLit::HEX);         goto end; }
    "char-or-hex" { SETOPT(char_literals, CharLit::CHAR_OR_HEX); goto end; }
*/

end:
    return lex_conf_semicolon();
}

#undef SETOPT
#undef RET_CONF_BOOL
#undef RET_CONF_FEAT
#undef RET_CONF_STR
#undef RET_CONF_ENC
#undef RET_CONF_NUM_NONNEG
#undef RET_CONF_EOF

Ret Input::lex_spaces() {
loop: /*!local:re2c
    eol    { next_line(); goto loop; }
    space  { goto loop; }
    ""     { return Ret::OK; }
*/
}

Ret Input::lex_conf_assign() {
    CHECK_RET(lex_spaces());
/*!local:re2c
    [=] { return lex_spaces(); }
    *   { RET_FAIL(error_at_cur("missing '=' in configuration")); }
*/
}

Ret Input::lex_conf_semicolon() {
    CHECK_RET(lex_spaces());
/*!local:re2c
    [;] { return Ret::OK; }
    *   { RET_FAIL(error_at_cur("missing ending ';' in configuration")); }
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
    naked       { tmp_str.assign(tok, cur); goto end; }
    "" / quotes { tmp_str.clear(); goto loop; }
    ""          { tmp_str.clear(); goto end; }
*/
loop: // lex one or more double-quoted strings separated with spaces or newlines
    tok = cur;
/*!local:re2c
    quotes { CHECK_RET(lex_conf_string_quoted(tok[0])); goto loop; }
    eol    { next_line(); goto loop; }
    space  { goto loop; }
    ""     { goto end; }
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

Ret Input::lex_conf_code(Opt& opts) {
    if (in_syntax_file) {
        conf_kind = ConfKind::CODE;
        CHECK_RET(parse_conf(opts));
    } else {
        CHECK_RET(lex_conf_string(opts));
        tmp_code = opts.make_api(tmp_str);
    }
    return Ret::OK;
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
    if (conf_kind == ConfKind::CODE) { // one of pre-lexed `conf:` configuratins
        conf_kind = ConfKind::NONE;
        yylval->codeptr = &tmp_code;
        RET_TOK(CONF_CODE);
    }
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
        tmp_str.clear();
        CHECK_RET(lex_conf_string_quoted(cur[-1]));
        yylval->str = copystr(tmp_str, alc);
        RET_TOK(CONF_STRING);
    }

    [=?!&|:,(){}[\]] { RET_TOK(cur[-1]); }

    "code:var_local"              { RET_CODE(code_var_local); }
    "code:var_global"             { RET_CODE(code_var_global); }
    "code:const_local"            { RET_CODE(code_const_local); }
    "code:const_global"           { RET_CODE(code_const_global); }
    "code:array_local"            { RET_CODE(code_array_local); }
    "code:array_global"           { RET_CODE(code_array_global); }
    "code:array_elem"             { RET_CODE(code_array_elem); }
    "code:type_int"               { RET_CODE(code_type_int); }
    "code:type_uint"              { RET_CODE(code_type_uint); }
    "code:type_yybm"              { RET_CODE(code_type_yybm); }
    "code:type_yytarget"          { RET_CODE(code_type_yytarget); }
    "code:assign"                 { RET_CODE(code_assign); }
    "code:cmp_eq"                 { RET_CODE(code_cmp_eq); }
    "code:cmp_ne"                 { RET_CODE(code_cmp_ne); }
    "code:cmp_lt"                 { RET_CODE(code_cmp_lt); }
    "code:cmp_gt"                 { RET_CODE(code_cmp_gt); }
    "code:cmp_le"                 { RET_CODE(code_cmp_le); }
    "code:cmp_ge"                 { RET_CODE(code_cmp_ge); }
    "code:if_then_else"           { RET_CODE(code_if_then_else); }
    "code:if_then_else_oneline"   { RET_CODE(code_if_then_else_oneline); }
    "code:switch"                 { RET_CODE(code_switch); }
    "code:switch_cases"           { RET_CODE(code_switch_cases); }
    "code:switch_cases_oneline"   { RET_CODE(code_switch_cases_oneline); }
    "code:switch_case_range"      { RET_CODE(code_switch_case_range); }
    "code:switch_case_default"    { RET_CODE(code_switch_case_default); }
    "code:loop"                   { RET_CODE(code_loop); }
    "code:continue"               { RET_CODE(code_continue); }
    "code:goto"                   { RET_CODE(code_goto); }
    "code:enum"                   { RET_CODE(code_enum); }
    "code:enum_elem"              { RET_CODE(code_enum_elem); }
    "code:fndecl"                 { RET_CODE(code_fndecl); }
    "code:fndef"                  { RET_CODE(code_fndef); }
    "code:fncall"                 { RET_CODE(code_fncall); }
    "code:tailcall"               { RET_CODE(code_tailcall); }
    "code:recursive_functions"    { RET_CODE(code_recursive_functions); }
    "code:fingerprint"            { RET_CODE(code_fingerprint); }
    "code:line_info"              { RET_CODE(code_line_info); }
    "code:abort"                  { RET_CODE(code_abort); }
    "code:yydebug"                { RET_CODE(code_yydebug); }
    "code:yypeek"                 { RET_CODE(code_yypeek); }
    "code:yyskip"                 { RET_CODE(code_yyskip); }
    "code:yybackup"               { RET_CODE(code_yybackup); }
    "code:yybackupctx"            { RET_CODE(code_yybackupctx); }
    "code:yyrestore"              { RET_CODE(code_yyrestore); }
    "code:yyrestorectx"           { RET_CODE(code_yyrestorectx); }
    "code:yyrestoretag"           { RET_CODE(code_yyrestoretag); }
    "code:yyshift"                { RET_CODE(code_yyshift); }
    "code:yyshiftmtag"            { RET_CODE(code_yyshiftmtag); }
    "code:yyshiftstag"            { RET_CODE(code_yyshiftstag); }
    "code:yystagn"                { RET_CODE(code_yystagn); }
    "code:yymtagn"                { RET_CODE(code_yymtagn); }
    "code:yystagp"                { RET_CODE(code_yystagp); }
    "code:yymtagp"                { RET_CODE(code_yymtagp); }
    "code:yycopymtag"             { RET_CODE(code_yycopymtag); }
    "code:yycopystag"             { RET_CODE(code_yycopystag); }
    "code:yyskip_yypeek"          { RET_CODE(code_yyskip_yypeek); }
    "code:yypeek_yyskip"          { RET_CODE(code_yypeek_yyskip); }
    "code:yyskip_yybackup"        { RET_CODE(code_yyskip_yybackup); }
    "code:yybackup_yyskip"        { RET_CODE(code_yybackup_yyskip); }
    "code:yybackup_yypeek"        { RET_CODE(code_yybackup_yypeek); }
    "code:yyskip_yybackup_yypeek" { RET_CODE(code_yyskip_yybackup_yypeek); }
    "code:yybackup_yypeek_yyskip" { RET_CODE(code_yybackup_yypeek_yyskip); }
    "code:yygetaccept"            { RET_CODE(code_yygetaccept); }
    "code:yysetaccept"            { RET_CODE(code_yysetaccept); }
    "code:yygetcond"              { RET_CODE(code_yygetcond); }
    "code:yysetcond"              { RET_CODE(code_yysetcond); }
    "code:yygetstate"             { RET_CODE(code_yygetstate); }
    "code:yysetstate"             { RET_CODE(code_yysetstate); }
    "code:yylessthan"             { RET_CODE(code_yylessthan); }
    "code:yybm_filter"            { RET_CODE(code_yybm_filter); }
    "code:yybm_match"             { RET_CODE(code_yybm_match); }

    "code:" [a-z0-9_]+ {
        RET_FAIL(error_at_tok("unknown code template: '%.*s'", int(cur - tok), tok));
    }

    // local variables
    "arg"          { RET_VAR(StxVarId::ARG); }
    "argname"      { RET_VAR(StxVarId::ARGNAME); }
    "argtype"      { RET_VAR(StxVarId::ARGTYPE); }
    "array"        { RET_VAR(StxVarId::ARRAY); }
    "branch"       { RET_VAR(StxVarId::BRANCH); }
    "case"         { RET_VAR(StxVarId::CASE); }
    "cond"         { RET_VAR(StxVarId::COND); }
    "date"         { RET_VAR(StxVarId::DATE); }
    "elem"         { RET_VAR(StxVarId::ELEM); }
    "expr"         { RET_VAR(StxVarId::EXPR); }
    "fn"           { RET_VAR(StxVarId::FN); }
    "file"         { RET_VAR(StxVarId::FILE); }
    "fndecl"       { RET_VAR(StxVarId::FNDECL); }
    "fndef"        { RET_VAR(StxVarId::FNDEF); }
    "index"        { RET_VAR(StxVarId::INDEX); }
    "init"         { RET_VAR(StxVarId::INIT); }
    "label"        { RET_VAR(StxVarId::LABEL); }
    "lhs"          { RET_VAR(StxVarId::LHS); }
    "line"         { RET_VAR(StxVarId::LINE); }
    "mask"         { RET_VAR(StxVarId::MASK); }
    "name"         { RET_VAR(StxVarId::NAME); }
    "neg"          { RET_VAR(StxVarId::NEG); }
    "need"         { RET_VAR(StxVarId::NEED); }
    "offset"       { RET_VAR(StxVarId::OFFSET); }
    "retval"       { RET_VAR(StxVarId::RETVAL); }
    "rhs"          { RET_VAR(StxVarId::RHS); }
    "row"          { RET_VAR(StxVarId::ROW); }
    "sigil"        { RET_VAR(StxVarId::SIGIL); }
    "size"         { RET_VAR(StxVarId::SIZE); }
    "state"        { RET_VAR(StxVarId::STATE); }
    "stmt"         { RET_VAR(StxVarId::STMT); }
    "tag"          { RET_VAR(StxVarId::TAG); }
    "type"         { RET_VAR(StxVarId::TYPE); }
    "val"          { RET_VAR(StxVarId::VAL); }
    "var"          { RET_VAR(StxVarId::VAR); }
    "version"      { RET_VAR(StxVarId::VER); }
    // local variables for API primitives
    "YYBACKUP"     { RET_VAR(StxVarId::BACKUP); }
    "YYBACKUPCTX"  { RET_VAR(StxVarId::BACKUPCTX); }
    "yybm"         { RET_VAR(StxVarId::BITMAP); }
    "yych"         { RET_VAR(StxVarId::CHAR); }
    "YYCOPYMTAG"   { RET_VAR(StxVarId::COPYMTAG); }
    "YYCOPYSTAG"   { RET_VAR(StxVarId::COPYSTAG); }
    "YYCTYPE"      { RET_VAR(StxVarId::CTYPE); }
    "YYCTXMARKER"  { RET_VAR(StxVarId::CTXMARKER); }
    "YYCURSOR"     { RET_VAR(StxVarId::CURSOR); }
    "YYDEBUG"      { RET_VAR(StxVarId::DEBUG); }
    "YYGETACCEPT"  { RET_VAR(StxVarId::GETACCEPT); }
    "YYGETCOND"    { RET_VAR(StxVarId::GETCOND); }
    "YYGETSTATE"   { RET_VAR(StxVarId::GETSTATE); }
    "YYINPUT"      { RET_VAR(StxVarId::INPUT); }
    "YYLESSTHAN"   { RET_VAR(StxVarId::LESSTHAN); }
    "YYLIMIT"      { RET_VAR(StxVarId::LIMIT); }
    "YYMARKER"     { RET_VAR(StxVarId::MARKER); }
    "YYMTAGN"      { RET_VAR(StxVarId::MTAGN); }
    "YYMTAGP"      { RET_VAR(StxVarId::MTAGP); }
    "YYPEEK"       { RET_VAR(StxVarId::PEEK); }
    "yyrecord"     { RET_VAR(StxVarId::RECORD); }
    "YYRESTORE"    { RET_VAR(StxVarId::RESTORE); }
    "YYRESTORECTX" { RET_VAR(StxVarId::RESTORECTX); }
    "YYRESTORETAG" { RET_VAR(StxVarId::RESTORETAG); }
    "YYSETACCEPT"  { RET_VAR(StxVarId::SETACCEPT); }
    "YYSETCOND"    { RET_VAR(StxVarId::SETCOND); }
    "YYSETSTATE"   { RET_VAR(StxVarId::SETSTATE); }
    "YYSHIFT"      { RET_VAR(StxVarId::SHIFT); }
    "YYSHIFTMTAG"  { RET_VAR(StxVarId::SHIFTMTAG); }
    "YYSHIFTSTAG"  { RET_VAR(StxVarId::SHIFTSTAG); }
    "YYSKIP"       { RET_VAR(StxVarId::SKIP); }
    "YYSTAGN"      { RET_VAR(StxVarId::STAGN); }
    "YYSTAGP"      { RET_VAR(StxVarId::STAGP); }

    // global variables
    "nl"        { RET_VAR(StxVarId::NEWLINE); }
    "indent"    { RET_VAR(StxVarId::INDENT); }
    "dedent"    { RET_VAR(StxVarId::DEDENT); }
    "topindent" { RET_VAR(StxVarId::TOPINDENT); }

    // special undefined value
    "<undefined>" { RET_TOK(CONF_UD); }

    // Global (immutable) conditionals.
    //
    // A subset of constant options that is exported for use in syntax files.
    // These options may be used both in configurations before the input file is parsed and
    // in code templates that are evaluated during codegen.
    //
    // These options are part of the syntax file API.

    ".code_model.goto_label"          { RET_COND(globopts->code_model == CodeModel::GOTO_LABEL); }
    ".code_model.loop_switch"         { RET_COND(globopts->code_model == CodeModel::LOOP_SWITCH); }
    ".code_model.recursive_functions" { RET_COND(globopts->code_model == CodeModel::REC_FUNC); }

    // Global (mutable) conditionals.
    //
    // A subset of options is exported for use in code templates in syntax files.
    // Both constant and mutable options are allowed here, as they are used during codegen,
    // when block-level options are already known.
    //
    // These options are part of the syntax file API.

    ".api.simple"          { RET_GOPT(StxGOpt::API_SIMPLE); }
    ".api.generic"         { RET_GOPT(StxGOpt::API_GENERIC); }
    ".api.record"          { RET_GOPT(StxGOpt::API_RECORD); }
    ".api_style.functions" { RET_GOPT(StxGOpt::API_STYLE_FUNCTIONS); }
    ".api_style.freeform"  { RET_GOPT(StxGOpt::API_STYLE_FREEFORM); }
    ".start_conditions"    { RET_GOPT(StxGOpt::START_CONDITIONS); }
    ".storable_state"      { RET_GOPT(StxGOpt::STORABLE_STATE); }
    ".date"                { RET_GOPT(StxGOpt::DATE); }
    ".version"             { RET_GOPT(StxGOpt::VER); }
    ".case_ranges"         { RET_GOPT(StxGOpt::CASE_RANGES); }
    ".unsafe"              { RET_GOPT(StxGOpt::UNSAFE); }
    ".monadic"             { RET_GOPT(StxGOpt::MONADIC); }
    ".loop_label"          { RET_GOPT(StxGOpt::LOOP_LABEL); }

    // Local conditionals (specific to each code template in syntax file).
    //
    // These options are part of the syntax file API.

    ".cast"                { RET_LOPT(StxLOpt::CAST); }
    ".char_literals"       { RET_LOPT(StxLOpt::CHAR_LITERALS); }
    ".args"                { RET_LOPT(StxLOpt::ARGS); }
    ".cond"                { RET_LOPT(StxLOpt::COND); }
    ".init"                { RET_LOPT(StxLOpt::INIT); }
    ".retval"              { RET_LOPT(StxLOpt::RETVAL); }
    ".type"                { RET_LOPT(StxLOpt::TYPE); }
    ".many"                { RET_LOPT(StxLOpt::MANY); }
    ".nested"              { RET_LOPT(StxLOpt::NESTED); }

    "." [a-z0-9_.]+ {
        RET_FAIL(error_at_tok("unknown conditional: '%.*s'", int(cur - tok), tok));
    }

    [a-z0-9_]+ {
        RET_FAIL(error_at_tok("unknown variable: '%.*s'", int(cur - tok), tok));
    }

    * { RET_FAIL(error_at_tok("unexpected character: '%c'", cur[-1])); }
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
    opts.set_##conf(tmp_bool); \
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

    "re2c:" { CHECK_RET(lex_conf(opts)); goto start; }

    "" / "code:" { if (conf_parse(*this, opts) != 0) return Ret::FAIL; goto start; }

    "supported_apis"        { SAVE_CONF_LIST(supported_apis); }
    "supported_api_styles"  { SAVE_CONF_LIST(supported_api_styles); }
    "supported_code_models" { SAVE_CONF_LIST(supported_code_models); }
    "supported_targets"     { SAVE_CONF_LIST(supported_targets); }
    "supported_features"    { SAVE_CONF_LIST(supported_features); }

    "semicolons"              { SAVE_CONF_BOOL(semicolons); }
    "backtick_quoted_strings" { SAVE_CONF_BOOL(backtick_quoted_strings); }
    "single_quoted_strings"   { SAVE_CONF_BOOL(single_quoted_strings); }
    "indentation_sensitive"   { SAVE_CONF_BOOL(indentation_sensitive); }
    "wrap_blocks_in_braces"   { SAVE_CONF_BOOL(wrap_blocks_in_braces); }


    * { RET_FAIL(error_at_tok("unexpected character: '%c'", cur[-1])); }
*/

    UNREACHABLE();
    return Ret::FAIL;
}

#undef SAVE_CONF_BOOL
#undef SAVE_CONF_LIST

#undef YYFILL

} // namespace re2c
