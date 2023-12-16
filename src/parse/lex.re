#include <ctype.h>
#include <stdint.h>
#include <limits>
#include <string>
#include <utility>
#include <vector>

#include "src/codegen/output.h"
#include "src/encoding/enc.h"
#include "src/msg/location.h"
#include "src/msg/msg.h"
#include "src/msg/warn.h"
#include "src/options/opt.h"
#include "src/parse/ast.h"
#include "src/parse/input.h"
#include "src/parse/lex.h"
#include "src/regexp/rule.h"
#include "src/util/check.h"
#include "src/util/string_utils.h"
#include "parser.h"

namespace re2c {

// Global re2c configurations and definitions.
/*!re2c
    // source code is in ASCII, but re2c assumes unsigned chars
    re2c:flags:type-header = "lex.h";
    re2c:flags:tags = 1;
    re2c:api:style = free-form;

    re2c:define:YYCTYPE  = "uint8_t";
    re2c:define:YYCURSOR = "cur";
    re2c:define:YYLIMIT  = "lim";
    re2c:define:YYMARKER = "mar";
    re2c:define:YYFILL   = 'if (!fill(@@)) RET_FAIL(error_at_cur("unexpected end of input"));';

    eof        = "\000";
    dstring    = "\"" ([^\x00\n\\"] | "\\" [^\x00\n])* "\"";
    sstring    = "'"  ([^\x00\n\\'] | "\\" [^\x00\n])* "'" ;
    letter     = [a-zA-Z];
    digit      = [0-9];
    lineno     = [1-9] digit*;
    name       = (letter|"_") (letter|digit|"_")*;
    space      = [ \t];
    ws         = (space | [\r\n]);
    eol        = "\r"? "\n";
    eoc        = "*" "/";
    ws_or_eoc  = ws | eoc;
    linedir    = eol space* "#" space* "line" space+;
    lineinf    = lineno (space+ dstring)? eol;
    esc        = "\\";
    oct_digit  = [0-7];
    hex_digit  = [0-9a-fA-F];
    esc_hex    = esc ("x" hex_digit{2} | [uX] hex_digit{4} | "U" hex_digit{8});
    esc_oct    = esc [0-3] [0-7]{2}; // max 1-byte octal value is '\377'
    esc_simple = esc [abfnrtv\\];
*/

/*!header:re2c:on*/
#ifndef _RE2C_PARSE_LEX_
#define _RE2C_PARSE_LEX_

#include <stddef.h>
#include <string.h>
#include "src/util/forbid_copy.h"

namespace re2c {

/*!max:re2c*/

struct LexerState {
    enum class LexMode: uint32_t { NORMAL, FLEX_NAME };

    LexMode mode;
    size_t BSIZE;
    uint8_t* bot, *lim, *cur, *mar, *ctx, *tok, *ptr, *pos, *eof;
    /*!stags:re2c format = "uint8_t* @@;"; */

    inline LexerState()
        : mode(LexMode::NORMAL),
          BSIZE(8192),
          bot(new uint8_t[BSIZE + YYMAXFILL]),
          lim(bot + BSIZE),
          cur(lim),
          mar(lim),
          ctx(lim),
          tok(lim),
          ptr(lim),
          pos(lim),
          eof(nullptr)
          /*!stags:re2c format = ", @@(lim)"; */ {
        memset(lim, 0, YYMAXFILL);
    }

    inline ~LexerState() {
        delete[] bot;
    }

    inline void shift_ptrs(ptrdiff_t offs) {
        lim += offs;
        cur += offs;
        mar += offs;
        ctx += offs;
        tok += offs;
        ptr += offs;
        pos += offs;
        /*!stags:re2c format = "if (@@) { @@ += offs; }"; */
    }

    FORBID_COPY(LexerState);
};

} // namespace re2c

#endif // _RE2C_PARSE_LEX_
/*!header:re2c:off*/

#define RET_BLOCK(k) do { kind = k; return Ret::OK; } while(0)

Ret Input::lex_program(Output& out, std::string& block_name, InputBlock& kind) {
    const opt_t* opts = out.block().opts;
    OutAllocator& alc = out.allocator;
    const uint8_t* x, *y;

    if (is_eof()) RET_BLOCK(InputBlock::END);

next:
    tok = cur;
loop:
    location = cur_loc();
    ptr = cur;
/*!local:re2c
    space* "%{" {
        if (pos != ptr) {
            // re2c does not parse user-defined code outside of re2c blocks, therefore it can
            // confuse `%{` in the middle of a string or a comment with a block start. To avoid this
            // recognize `%{` as a block start only on a new line, possibly preceded by whitespaces.
            goto loop;
        }
        out.gen_raw(tok, ptr);
        block_name.clear();
        RET_BLOCK(InputBlock::GLOBAL);
    }

    "/*!re2c" {
        out.gen_raw(tok, ptr);
        CHECK_RET(lex_opt_name(block_name));
        if (block_name == "local") {
            RET_FAIL(error_at_cur("ill-formed local block, expected `local:re2c`"));
        }
        RET_BLOCK(InputBlock::GLOBAL);
    }

    "/*!local:re2c" {
        out.gen_raw(tok, ptr);
        CHECK_RET(lex_opt_name(block_name));
        RET_BLOCK(InputBlock::LOCAL);
    }

    "/*!rules:re2c" {
        out.gen_raw(tok, ptr);
        CHECK_RET(lex_opt_name(block_name));
        RET_BLOCK(InputBlock::RULES);
    }

    "/*!use:re2c" {
        out.gen_raw(tok, ptr);
        CHECK_RET(lex_opt_name(block_name));
        RET_BLOCK(InputBlock::USE);
    }

    "/*!max:re2c" {
        CHECK_RET(lex_special_block(out, CodeKind::MAXFILL, DCONF_FORMAT));
        goto next;
    }

    "/*!maxnmatch:re2c" {
        CHECK_RET(lex_special_block(out, CodeKind::MAXNMATCH, DCONF_FORMAT));
        goto next;
    }

    "/*!stags:re2c" {
        uint32_t allow = DCONF_FORMAT | DCONF_SEPARATOR;
        CHECK_RET(lex_special_block(out, CodeKind::STAGS, allow));
        goto next;
    }

    "/*!mtags:re2c" {
        uint32_t allow = DCONF_FORMAT | DCONF_SEPARATOR;
        CHECK_RET(lex_special_block(out, CodeKind::MTAGS, allow));
        goto next;
    }

    "/*!conditions:re2c" | "/*!types:re2c" {
        out.cond_enum_autogen = false;
        out.warn_condition_order = false; // see note [condition order]
        uint32_t allow = DCONF_FORMAT | DCONF_SEPARATOR;
        CHECK_RET(lex_special_block(out, CodeKind::COND_ENUM, allow));
        goto next;
    }

    "/*!getstate:re2c" {
        out.state_goto = true;
        if (!opts->storable_state) {
            RET_FAIL(error_at_cur("`getstate:re2c` without `-f --storable-state` option"));
        } else if (opts->loop_switch) {
            RET_FAIL(error_at_cur(
                    "`getstate:re2c` is incompatible with the --loop-switch option, as it requires"
                    " cross-block transitions that are unsupported without the `goto` statement"));
        }
        CHECK_RET(lex_special_block(out, CodeKind::STATE_GOTO, 0));
        goto next;
    }

    "/*!header:re2c:on" {
        out.gen_raw(tok, ptr);
        out.header_mode(true);
        out.need_header = true;
        CHECK_RET(lex_block_end(out));
        goto next;
    }

    "/*!header:re2c:off" {
        out.gen_raw(tok, ptr);
        out.header_mode(false);
        if (globopts->line_dirs) out.gen_stmt(code_line_info_input(alc, cur_loc()));
        CHECK_RET(lex_block_end(out));
        goto next;
    }
    "/*!header:re2c" {
        RET_FAIL(error_at_cur(
                "ill-formed header directive: expected `/*!header:re2c:<on|off>` followed by a"
                " space, a newline or the end of block `*" "/`"));
    }

    "/*!include:re2c" space+ @x dstring @y / ws_or_eoc {
        out.gen_raw(tok, ptr);
        CHECK_RET(lex_block_end(out));
        CHECK_RET(include(getstr(x + 1, y - 1), ptr));
        if (globopts->line_dirs) out.gen_stmt(code_line_info_input(alc, cur_loc()));
        goto next;
    }
    "/*!include:re2c" {
        RET_FAIL(error_at_cur(
                "ill-formed include directive: expected `/*!include:re2c \"<file>\" *" "/`"));
    }

    "/*!ignore:re2c" / ws_or_eoc {
        out.gen_raw(tok, ptr);
        // allows arbitrary garbage before the end of the comment
        CHECK_RET(lex_block_end(out, true));
        goto next;
    }
    "/*!ignore:re2c" {
        RET_FAIL(error_at_cur(
                "ill-formed start of `ignore:re2c` block: expected a space, a newline, or the end"
                " of block `*" "/`"));
    }

    eof {
        if (is_eof()) {
            out.gen_raw(tok, ptr);
            RET_BLOCK(InputBlock::END);
        }
        goto loop;
    }

    linedir / lineinf {
        out.gen_raw(tok, ptr);
        out.gen_stmt(code_newline(alc));
        CHECK_RET(set_sourceline());
        goto next;
    }

    eol {
        next_line();
        goto loop;
    }

    * { goto loop; }
*/
}

#undef RET_BLOCK

Ret Input::lex_opt_name(std::string& name) {
    tok = cur;
/*!local:re2c
    "" {
        RET_FAIL(error_at_cur(
                "ill-formed start of a block: expected a space, a newline, a colon followed by a"
                " block name, or the end of block `*" "/`"));
    }

    ""       / ws_or_eoc { name.clear();              return Ret::OK; }
    ":" name / ws_or_eoc { name.assign(tok + 1, cur); return Ret::OK; }
*/
}

Ret Input::lex_name_list(OutAllocator& alc, BlockNameList** ptail) {
    BlockNameList** phead = ptail;
loop:
    tok = cur;
/*!local:re2c
    "" {
        RET_FAIL(error_at_cur(
                "ill-formed start of a block: expected a space, a newline, a colon followed by a"
                " list of colon-separated block names, or the end of block `*" "/`"));
    }

    "" / ws_or_eoc { *ptail = nullptr; return Ret::OK; }

    ":" name {
        BlockNameList *l = alc.alloct<BlockNameList>(1);
        l->name = newcstr(tok + 1, cur, alc);
        l->next = nullptr;
        *ptail = l;
        ptail = &l->next;

        // Check that the added name is unique.
        for (const BlockNameList *p = *phead; p != l; p = p->next) {
            if (strcmp(p->name, l->name) == 0) {
                RET_FAIL(error_at_cur("duplicate block '%s' on the list", p->name));
            }
        }

        goto loop;
    }
*/
}

Ret Input::lex_block_end(Output& out, bool allow_garbage) {
    bool multiline = false;
loop: /*!local:re2c
    * {
        if (allow_garbage && !is_eof()) goto loop;
        RET_FAIL(error_at_cur(
                "ill-formed end of block: expected optional whitespaces followed by `*" "/`"));
    }
    eoc {
        if (multiline && globopts->line_dirs) {
            out.gen_stmt(code_line_info_input(out.allocator, cur_loc()));
        }
        return Ret::OK;
    }
    space+ { goto loop; }
    eol    { next_line(); multiline = true; goto loop; }
*/
}

Ret Input::lex_special_block(Output& out, CodeKind kind, uint32_t mask) {
    OutAllocator& alc = out.allocator;
    const char* fmt = nullptr, *sep = nullptr;
    BlockNameList* blocks;
    std::string s;

    out.gen_raw(tok, ptr, globopts->line_dirs);
    CHECK_RET(lex_name_list(alc, &blocks));

loop: /*!local:re2c
    * {
        RET_FAIL(error_at_cur(
                "ill-formed directive: expected optional configurations followed by the end of"
                " block `*" "/`"));
    }

    "format" {
        if ((mask & DCONF_FORMAT) == 0) {
            RET_FAIL(error_at_cur("unexpected configuration 'format'"));
        }
        CHECK_RET(lex_conf_string(s));
        fmt = copystr(s, alc);
        goto loop;
    }

    "separator" {
        if ((mask & DCONF_SEPARATOR) == 0) {
            RET_FAIL(error_at_cur("unexpected configuration 'separator'"));
        }
        CHECK_RET(lex_conf_string(s));
        sep = copystr(s, alc);
        goto loop;
    }

    space+ { goto loop; }

    eol { next_line(); goto loop; }

    eoc {
        if (globopts->line_dirs) out.gen_stmt(code_line_info_output(alc));
        out.gen_stmt(code_fmt(alc, kind, blocks, fmt, sep));
        if (globopts->line_dirs) out.gen_stmt(code_line_info_input(alc, cur_loc()));
        return Ret::OK;
    }
*/
}

#define RET_TOK(t) do { token = t; return Ret::OK; } while(0)

Ret Input::lex_block(YYSTYPE* yylval, Ast& ast, int& token) {
    const uint8_t* p, *x, *y;
scan:
    tok = cur;
    location = cur_loc();
/*!local:re2c

    "{"  { CHECK_RET(lex_code_in_braces(yylval, ast)); RET_TOK(TOKEN_CODE); }
    ":=" { CHECK_RET(lex_code_indented(yylval, ast));  RET_TOK(TOKEN_CODE); }

    ":"? "=>" space* @p name {
        yylval->cstr = ast.cstr_global(p, cur);
        RET_TOK(tok[0] == ':' ? TOKEN_CJUMP : TOKEN_CNEXT);
    }

    "<" { return lex_clist(ast, token); }

    "//" { CHECK_RET(lex_cpp_comment()); goto scan; }
    "/*" { CHECK_RET(lex_c_comment());   goto scan; }

    "%}" | "*""/" { tok = cur; RET_TOK(0); }

    "'"  { CHECK_RET(lex_str(ast, '\'',  yylval->regexp)); RET_TOK(TOKEN_REGEXP); }
    "\"" { CHECK_RET(lex_str(ast, '"',   yylval->regexp)); RET_TOK(TOKEN_REGEXP); }
    "["  { CHECK_RET(lex_cls(ast, false, yylval->regexp)); RET_TOK(TOKEN_REGEXP); }
    "[^" { CHECK_RET(lex_cls(ast, true,  yylval->regexp)); RET_TOK(TOKEN_REGEXP); }

    [@#] name {
        yylval->regexp = ast.tag(tok_loc(), ast.cstr_global(tok + 1, cur), tok[0] == '#');
        RET_TOK(TOKEN_REGEXP);
    }

    [*+?!()|;/\\=$] { RET_TOK(*tok); }

    "{" [0-9]+ "}" {
        if (!s_to_u32_unsafe (tok + 1, cur - 1, yylval->bounds.min)) {
            RET_FAIL(error_at_tok("repetition count overflow"));
        }
        yylval->bounds.max = yylval->bounds.min;
        RET_TOK(TOKEN_CLOSESIZE);
    }

    "{" [0-9]+ @p "," [0-9]+ "}" {
        if (!s_to_u32_unsafe(tok + 1, p, yylval->bounds.min)) {
            RET_FAIL(error_at_tok("repetition lower bound overflow"));
        } else if (!s_to_u32_unsafe(p + 1, cur - 1, yylval->bounds.max)) {
            RET_FAIL(error_at_tok("repetition upper bound overflow"));
        } else if (yylval->bounds.min > yylval->bounds.max) {
            RET_FAIL(error_at_tok("repetition lower bound exceeds upper bound"));
        }
        RET_TOK(TOKEN_CLOSESIZE);
    }

    "{" [0-9]+ ",}" {
        if (!s_to_u32_unsafe (tok + 1, cur - 2, yylval->bounds.min)) {
            RET_FAIL(error_at_tok("repetition lower bound overflow"));
        }
        yylval->bounds.max = std::numeric_limits<uint32_t>::max();
        RET_TOK(TOKEN_CLOSESIZE);
    }

    "{" [0-9]* "," {
        RET_FAIL(error_at_tok(
                "illegal closure form, use '{n}', '{n,}', '{n,m}' where n and m are numbers"));
    }

    "{" name "}" {
        if (!globopts->flex_syntax) {
            RET_FAIL(error_at_tok("curly braces for names only allowed with -F switch"));
        }
        yylval->cstr = ast.cstr_local(tok + 1, cur - 1);
        RET_TOK(TOKEN_ID);
    }

    "re2c:" { RET_TOK(TOKEN_CONF); }

    name {
        bool yes;
        CHECK_RET(lex_namedef_context_re2c(yes));
        if (!globopts->flex_syntax || yes) {
            yylval->cstr = ast.cstr_local(tok, cur);
            RET_TOK(TOKEN_ID);
        }
        CHECK_RET(lex_namedef_context_flex(yes));
        if (yes) {
            yylval->cstr = ast.cstr_local(tok, cur);
            mode = LexMode::FLEX_NAME;
            RET_TOK(TOKEN_FID);
        }
        // consume one character, otherwise we risk breaking operator precedence in cases like
        // `ab*`: it should be `a(b)*`, not `(ab)*`
        cur = tok + 1;
        ast.temp_chars.push_back({tok[0], tok_loc()});
        yylval->regexp = ast.str(tok_loc(), false);
        RET_TOK(TOKEN_REGEXP);
    }

    "!include" space+ @x dstring @y space* ";" / ws_or_eoc {
        CHECK_RET(include(getstr(x + 1, y - 1), tok));
        goto scan;
    }
    "!include" {
        RET_FAIL(error_at_tok(
                "ill-formed include directive: expected `!include` followed by spaces, a"
                " double-quoted file path, optional spaces, a semicolon, and finally a space, a"
                " newline, or the end of block"));
    }

    "!use:" @x name @y space* ";" / ws_or_eoc {
        // Save the name of the used block in a temporary buffer (ensure it is empty).
        CHECK(ast.temp_blockname.empty());
        ast.temp_blockname.assign(x, y);
        RET_TOK(TOKEN_BLOCK);
    }
    "!use" {
        RET_FAIL(error_at_tok(
                "ill-formed use directive: expected `!use` followed by a colon, a block name,"
                " optional spaces, a semicolon, and finally a space, a newline, or the end of"
                " block"));
    }

    "." { yylval->regexp = ast.dot(tok_loc()); RET_TOK(TOKEN_REGEXP); }

    space+ { goto scan; }

    linedir / lineinf { CHECK_RET(set_sourceline()); RET_TOK(TOKEN_LINE_INFO); }

    eol {
        next_line();
        if (mode == LexMode::FLEX_NAME) {
            mode = LexMode::NORMAL;
            RET_TOK(TOKEN_FID_END);
        }
        goto scan;
    }

    * {
        if (globopts->flex_syntax && globopts->input_encoding == Enc::Type::UTF8) {
            // Try to lex this as a raw UTF-8 code point (not captured by the `name` rule above
            // because it is restricted to alphanumeric ASCII characters and underscore).
            --cur;
            uint32_t c;
            CHECK_RET(lex_cls_chr(c));
            ast.temp_chars.push_back({c, tok_loc()});
            yylval->regexp = ast.str(tok_loc(), false);
            RET_TOK(TOKEN_REGEXP);
        }
        RET_FAIL(error_at_tok("unexpected character: '%c'", *tok));
    }
*/
}

#undef RET_TOK

Ret Input::lex_namedef_context_re2c(bool& yes) {
/*!re2c
    "" / space* "=" [^>] { yes = true;  return Ret::OK; }
    ""                   { yes = false; return Ret::OK; }
*/
}

Ret Input::lex_namedef_context_flex(bool& yes) {
/*!re2c
    "" / space+ [=:{] { yes = false; return Ret::OK; } // exclude `=`, `=>`, `:=>`, `:=`, `{`
    "" / space+       { yes = true;  return Ret::OK; }
    ""                { yes = false; return Ret::OK; }
*/
}

Ret Input::lex_clist(Ast& ast, int& token) {
    token = TOKEN_CLIST;
    std::set<std::string>& cl = ast.temp_condlist;
    // Due to the re2c grammar parser must reduce each condition list before shifing a new one.
    CHECK(cl.empty());
/*!re2c
    space* "!" space* { token = TOKEN_CSETUP; goto cond; }
    space* ">"        { token = TOKEN_CZERO;  goto end; }
    space*            { goto cond; }
*/
cond:
    tok = cur;
/*!re2c
    name { cl.insert(getstr(tok, cur)); goto next; }
    "*"  { if (!cl.empty()) goto error; cl.insert("*"); goto next; }
    *    { goto error; }
*/
next: /*!re2c
    space* "," space* { goto cond; }
    space* ">"        { goto end; }
    *                 { goto error; }
*/
end:
    // semantic value `yylval` is implicitly passed in temporary condition list
    return Ret::OK;
error:
    cl.clear();
    RET_FAIL(error_at_cur("syntax error in condition list"));
}

Ret Input::lex_code_indented(YYSTYPE* yylval, Ast& ast) {
    const loc_t& loc = tok_loc();
    tok = cur;
code: /*!re2c
    eol   { next_line(); goto indent; }
    "//"  { CHECK_RET(lex_cpp_comment()); goto indent; }
    "/*"  { CHECK_RET(lex_c_comment()); goto code; }
    ["'`] { CHECK_RET(try_lex_literal_in_code(cur[-1])); goto code; }
    [{}]  { RET_FAIL(error_at_cur("Curly braces are not allowed after ':='")); }
    *     { goto code; }
*/
indent: /*!re2c
    "" / ws { goto code; } // indent after newline => still in semantic action
    "" {
        while (isspace(tok[0])) ++tok;
        uint8_t* p = cur;
        while (p > tok && isspace(p[-1])) --p;
        yylval->semact = ast.sem_act(loc, ast.cstr_global(tok, p), nullptr, false);
        return Ret::OK;
    }
*/
}

Ret Input::lex_code_in_braces(YYSTYPE* yylval, Ast& ast) {
    const loc_t& loc = tok_loc();
    uint32_t depth = 1;
code: /*!re2c
    "}" {
        if (--depth == 0) {
            yylval->semact = ast.sem_act(loc, ast.cstr_global(tok, cur), nullptr, false);
            return Ret::OK;
        }
        goto code;
    }

    "{"               { ++depth; goto code; }
    linedir / lineinf { CHECK_RET(set_sourceline()); goto code; }
    eol               { next_line(); goto code; }
    "/*"              { CHECK_RET(lex_c_comment()); goto code; }
    "//"              { CHECK_RET(lex_cpp_comment()); goto code; }
    ["'`]             { CHECK_RET(try_lex_literal_in_code(cur[-1])); goto code; }
    *                 { goto code; }
*/
}

Ret Input::try_lex_literal_in_code(uint8_t quote) {
    // We need to lex string and char literals in code blocks because they may contain closing
    // brace or newline that would otherwise be erroneously lexed as block terminator symbols.
    if (quote == '"') {
loop_dquote: /*!re2c
        ["]       { return Ret::OK; }
        esc [\\"] { goto loop_dquote; }
        eol       { next_line(); goto loop_dquote; }
        *         { goto loop_dquote; }
    */
    } else if (quote == '`' && globopts->eval_bool_conf("backtick_quoted_strings")) {
loop_backtick: /*!re2c
        [`] { return Ret::OK; }
        eol { next_line(); goto loop_backtick; }
        *   { goto loop_backtick; }
    */
    } else if (quote == '\'') {
        // Single-quoted char literals may contain closing curly brace, e.g. '}'.
        // We must lex all possible forms (not only those with a closing brace), as otherwise we
        // might erroneously lex the closing single quote as the beginning of another literal, e.g.
        // in 'a'}'b' we would recognize '}' as a literal rather than the closing brace of a block.
    /*!local:re2c
        re2c:flags:utf-8 = 1;

        // Generalized rules for single-quoted char literals (covering various languages).
        esc [ux][{] hex_digit+ [}]['] | // hex escape \u{X...X}
        esc [x] hex_digit{2}      ['] | // 2-byte hex escape
        esc [u] hex_digit{4}      ['] | // 4-byte hex escape \uXXXX
        esc [U] hex_digit{8}      ['] | // 8-byte hex escape \UXXXXXXXX
        esc [o][{] oct_digit+ [}] ['] | // octal escape \o{X...X}
        esc oct_digit{3}          ['] | // octal escape \XXX
        esc ['\\?abfnrtv0]        ['] | // special escape sequences
        [^]                       ['] { // any UTF-8 encoded Unicode symbol, unescaped
            return Ret::OK;
        }
        "" { return globopts->eval_bool_conf("standalone_single_quotes") ? Ret::OK : Ret::FAIL; }
    */
    }
    return Ret::FAIL;
}

Ret Input::lex_c_comment() {
loop: /*!re2c
    eoc { return Ret::OK; }
    eol { next_line(); goto loop; }
    *   { goto loop; }
*/
}

Ret Input::lex_cpp_comment() {
loop: /*!re2c
    eol { next_line(); return Ret::OK; }
    *   { goto loop; }
*/
}

Ret Input::lex_cls(Ast& ast, bool neg, const AstNode*& a) {
    uint32_t u, l;
    const loc_t& loc0 = tok_loc();
    loc_t loc = cur_loc();
fst:
    tok = cur;
/*!re2c
    "]" { a = ast.cls(loc0, neg); return Ret::OK; }
    ""  { CHECK_RET(lex_cls_chr(l)); goto snd; }
*/
snd: /*!re2c
    "" { u = l; goto add; }
    "-" / [^\]] {
        CHECK_RET(lex_cls_chr(u));
        if (l > u) {
            msg.warn.swapped_range(loc, l, u);
            std::swap(l, u);
        }
        goto add;
    }
*/
add:
    ast.temp_ranges.push_back(AstRange(l, u, loc));
    loc = cur_loc();
    goto fst;
}

Ret Input::lex_cls_chr(uint32_t& c) {
    tok = cur;
    const loc_t& loc = cur_loc();
/*!rules:re2c:cls_chr
    esc? eol    { RET_FAIL(error_at(loc, "newline in character class")); }
    esc [xXuU]  { RET_FAIL(error_at(loc, "syntax error in hexadecimal escape sequence")); }
    esc [0-7]   { RET_FAIL(error_at(loc, "syntax error in octal escape sequence")); }
    esc         { RET_FAIL(error_at(loc, "syntax error in escape sequence")); }
    *           { RET_FAIL(error_at(loc, "syntax error")); }

    . \ esc     { c = decode(tok); return Ret::OK; }
    esc_hex     { c = unesc_hex(tok, cur); return Ret::OK; }
    esc_oct     { c = unesc_oct(tok, cur); return Ret::OK; }
    esc "a"     { c = '\a'_u8; return Ret::OK; }
    esc "b"     { c = '\b'_u8; return Ret::OK; }
    esc "f"     { c = '\f'_u8; return Ret::OK; }
    esc "n"     { c = '\n'_u8; return Ret::OK; }
    esc "r"     { c = '\r'_u8; return Ret::OK; }
    esc "t"     { c = '\t'_u8; return Ret::OK; }
    esc "v"     { c = '\v'_u8; return Ret::OK; }
    esc "\\"    { c = '\\'_u8; return Ret::OK; }
    esc "-"     { c = '-'_u8; return Ret::OK; }
    esc "]"     { c = ']'_u8; return Ret::OK; }
    esc (.\eof) {
        msg.warn.useless_escape(loc, tok, cur);
        c = decode(tok + 1);
        return Ret::OK;
    }
*/
    if (globopts->input_encoding == Enc::Type::ASCII) {
        /*!local:re2c !use:cls_chr; */
    } else {
        /*!local:re2c !use:cls_chr; re2c:flags:8 = 1; */
    }
}

Ret Input::lex_str_chr(uint8_t quote, AstChar& ast, bool& stop) {
    tok = cur;
    stop = false;
    ast.loc = cur_loc();
/*!rules:re2c:str_chr
    esc? eol    { RET_FAIL(error_at(ast.loc, "newline in character string")); }
    esc [xXuU]  { RET_FAIL(error_at(ast.loc, "syntax error in hexadecimal escape sequence")); }
    esc [0-7]   { RET_FAIL(error_at(ast.loc, "syntax error in octal escape sequence")); }
    esc         { RET_FAIL(error_at(ast.loc, "syntax error in escape sequence")); }
    *           { RET_FAIL(error_at(ast.loc, "syntax error")); }

    . \ esc     { ast.chr = decode(tok); stop = (tok[0] == quote); return Ret::OK; }
    esc_hex     { ast.chr = unesc_hex(tok, cur); return Ret::OK; }
    esc_oct     { ast.chr = unesc_oct(tok, cur); return Ret::OK; }
    esc "a"     { ast.chr = '\a'_u8; return Ret::OK; }
    esc "b"     { ast.chr = '\b'_u8; return Ret::OK; }
    esc "f"     { ast.chr = '\f'_u8; return Ret::OK; }
    esc "n"     { ast.chr = '\n'_u8; return Ret::OK; }
    esc "r"     { ast.chr = '\r'_u8; return Ret::OK; }
    esc "t"     { ast.chr = '\t'_u8; return Ret::OK; }
    esc "v"     { ast.chr = '\v'_u8; return Ret::OK; }
    esc "\\"    { ast.chr = '\\'_u8; return Ret::OK; }
    esc (.\eof) {
        ast.chr = decode(tok + 1);
        if (tok[1] != quote) msg.warn.useless_escape(ast.loc, tok, cur);
        return Ret::OK;
    }
*/
    if (globopts->input_encoding == Enc::Type::ASCII) {
        /*!local:re2c !use:str_chr; */
    } else {
        /*!local:re2c !use:str_chr; re2c:flags:8 = 1; */
    }
}

Ret Input::lex_str(Ast& ast, uint8_t quote, const AstNode*& a) {
    const loc_t& loc = tok_loc();
    AstChar c;
    bool stop;
    for (;;) {
        CHECK_RET(lex_str_chr(quote, c, stop));
        if (stop) {
            a = ast.str(loc, quote == '\'');
            return Ret::OK;
        }
        ast.temp_chars.push_back(c);
    }
}

Ret Input::set_sourceline() {
sourceline:
    tok = cur;
/*!local:re2c
    lineno {
        uint32_t l;
        if (!s_to_u32_unsafe(tok, cur, l)) {
            RET_FAIL(error_at_tok("line number overflow"));
        }
        set_line(l);
        goto sourceline;
    }

    dstring {
        InputFile &in = get_input();
        std::string &name = in.escaped_name;
        name = escape_backslashes(getstr(tok + 1, cur - 1));
        in.fidx = static_cast<uint32_t>(msg.filenames.size());
        msg.filenames.push_back(name);
        goto sourceline;
    }

    eol { pos = tok = cur; return Ret::OK; }
    eof { --cur; return Ret::OK; }
    *   { goto sourceline; }
*/
}

#undef YYFILL

} // end namespace re2c
