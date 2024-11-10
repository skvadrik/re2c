#include <ctype.h>
#include <stdint.h>
#include <limits>
#include <string>
#include <utility>
#include <vector>

#include "src/codegen/helpers.h"
#include "src/codegen/output.h"
#include "src/encoding/enc.h"
#include "src/msg/location.h"
#include "src/msg/msg.h"
#include "src/msg/warn.h"
#include "src/options/opt.h"
#include "src/parse/ast.h"
#include "src/parse/input.h"
#include "src/parse/lexer.h"
#include "src/regexp/rule.h"
#include "src/util/check.h"
#include "src/util/string_utils.h"
#include "parser.h"

namespace re2c {

/*!max:re2c format = "size_t LexerState::maxfill_main() { return @@; }"; */

// Global re2c configurations and definitions.
/*!re2c
    // source code is in ASCII, but re2c assumes unsigned chars
    re2c:flags:type-header = "lexer.h";
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
    eoc        = "*" "/" | "%}";
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

struct LexerState {
    enum class LexMode: uint32_t { NORMAL, FLEX_NAME };

    LexMode mode;
    size_t BSIZE;
    uint8_t* bot, *lim, *cur, *mar, *ctx, *tok, *ptr, *pos, *eof;
    /*!stags:re2c format = "uint8_t* @@;"; */

    inline LexerState()
        : mode(LexMode::NORMAL),
          BSIZE(8192),
          bot(new uint8_t[BSIZE + maxfill()]),
          lim(bot + BSIZE),
          cur(lim),
          mar(lim),
          ctx(lim),
          tok(lim),
          ptr(lim),
          pos(lim),
          eof(nullptr)
          /*!stags:re2c format = ", @@(lim)"; */ {
        memset(lim, 0, maxfill());
    }

    inline ~LexerState() {
        delete[] bot;
    }

    inline void reset_ptrs() {
        // reset lexer back to its initial state
        cur = mar = ctx = tok = ptr = pos = lim = bot + BSIZE;
        memset(lim, 0, maxfill());
        eof = nullptr;
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

    static size_t maxfill() {
        return std::max(maxfill_main(), maxfill_conf());
    }

  private:
    static size_t maxfill_main();
    static size_t maxfill_conf();

    FORBID_COPY(LexerState);
};

} // namespace re2c

#endif // _RE2C_PARSE_LEX_
/*!header:re2c:off*/

#define RET_BLOCK(k) do { kind = k; return Ret::OK; } while(0)

Ret Input::lex_program(Output& out, std::string& block_name, InputBlock& kind) {
    const opt_t* opts = out.block().opts;
    const uint8_t* x, *y;

    if (is_eof()) RET_BLOCK(InputBlock::END);

next:
    tok = cur;
loop:
    location = cur_loc();
    ptr = cur;
/*!local:re2c
    "%{" / eol {
        out.gen_raw(tok, ptr);
        CHECK_RET(lex_opt_name(block_name));
        RET_BLOCK(InputBlock::GLOBAL);
    }

    "/*!re2c" {
        out.gen_raw(tok, ptr);
        CHECK_RET(lex_opt_name(block_name));
        RET_BLOCK(InputBlock::GLOBAL);
    }

    "/*!local:re2c" | "%{local" {
        out.gen_raw(tok, ptr);
        CHECK_RET(lex_opt_name(block_name));
        RET_BLOCK(InputBlock::LOCAL);
    }

    "/*!rules:re2c" | "%{rules" {
        out.gen_raw(tok, ptr);
        CHECK_RET(lex_opt_name(block_name));
        RET_BLOCK(InputBlock::RULES);
    }

    "/*!use:re2c" | "%{use" {
        out.gen_raw(tok, ptr);
        CHECK_RET(lex_opt_name(block_name));
        RET_BLOCK(InputBlock::USE);
    }

    "/*!max:re2c" | "%{max" {
        CHECK_RET(lex_special_block(out, CodeKind::MAXFILL, DCONF_FORMAT));
        goto next;
    }

    "/*!maxnmatch:re2c" | "%{maxnmatch" {
        CHECK_RET(lex_special_block(out, CodeKind::MAXNMATCH, DCONF_FORMAT));
        goto next;
    }

    "/*!stags:re2c" | "%{stags" {
        uint32_t allow = DCONF_FORMAT | DCONF_SEPARATOR;
        CHECK_RET(lex_special_block(out, CodeKind::STAGS, allow));
        goto next;
    }

    "/*!mtags:re2c" | "%{mtags" {
        uint32_t allow = DCONF_FORMAT | DCONF_SEPARATOR;
        CHECK_RET(lex_special_block(out, CodeKind::MTAGS, allow));
        goto next;
    }

    "/*!svars:re2c" | "%{svars" {
        uint32_t allow = DCONF_FORMAT | DCONF_SEPARATOR;
        CHECK_RET(lex_special_block(out, CodeKind::SVARS, allow));
        goto next;
    }

    "/*!mvars:re2c" | "%{mvars" {
        uint32_t allow = DCONF_FORMAT | DCONF_SEPARATOR;
        CHECK_RET(lex_special_block(out, CodeKind::MVARS, allow));
        goto next;
    }

    "/*!conditions:re2c" | "/*!types:re2c" | "%{conditions" {
        out.cond_enum_autogen = false;
        out.warn_condition_order = false; // see note [condition order]
        uint32_t allow = DCONF_FORMAT | DCONF_SEPARATOR;
        CHECK_RET(lex_special_block(out, CodeKind::COND_ENUM, allow));
        goto next;
    }

    "/*!getstate:re2c" | "%{getstate" {
        out.state_goto = true;
        if (!opts->storable_state) {
            RET_FAIL(error_at_cur("`getstate` without `-f --storable-state` option"));
        } else if (opts->code_model == CodeModel::LOOP_SWITCH) {
            RET_FAIL(error_at_cur(
                    "`getstate` is incompatible with --loop-switch code model, it requires"
                    " cross-block `goto` transitions or function calls"));
        }
        CHECK_RET(lex_special_block(out, CodeKind::STATE_GOTO, 0));
        goto next;
    }

    "/*!header:re2c:on" | "%{header:on" {
        out.gen_raw(tok, ptr);
        out.header_mode(true);
        out.need_header = true;
        CHECK_RET(lex_block_end(out));
        goto next;
    }

    "/*!header:re2c:off" | "%{header:off" {
        out.gen_raw(tok, ptr);
        out.header_mode(false);
        if (globopts->line_dirs) out.gen_stmt(code_line_info_input(alc, cur_loc()));
        CHECK_RET(lex_block_end(out));
        goto next;
    }
    "/*!header:re2c" | "%{header" {
        RET_FAIL(error_at_cur("ill-formed `header` block: expected `:on` or `:off`"));
    }

    ("/*!include:re2c" | "%{include") space+ @x dstring @y / ws_or_eoc {
        out.gen_raw(tok, ptr);
        CHECK_RET(lex_block_end(out));
        CHECK_RET(include(getstr(x + 1, y - 1), ptr));
        if (globopts->line_dirs) out.gen_stmt(code_line_info_input(alc, cur_loc()));
        goto next;
    }
    "/*!include:re2c" | "%{include" {
        RET_FAIL(error_at_cur("ill-formed `include` block: expected filename in quotes"));
    }

    ("/*!ignore:re2c" | "%{ignore") / ws_or_eoc {
        out.gen_raw(tok, ptr);
        // allows arbitrary garbage before the end of the comment
        CHECK_RET(lex_block_end(out, true));
        goto next;
    }
    "/*!ignore:re2c" | "%{ignore" {
        RET_FAIL(error_at_cur(
                "ill-formed `ignore` block: expected a space, a newline, or the end of block"));
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
                "ill-formed start of a block: expected a space, a newline, a colon "
                "followed by a block name, or the end of block"));
    }

    ""       / ws_or_eoc { name.clear();              return Ret::OK; }
    ":" name / ws_or_eoc { name.assign(tok + 1, cur); return Ret::OK; }
*/
}

Ret Input::lex_name_list(BlockNameList** ptail) {
    BlockNameList** phead = ptail;
loop:
    tok = cur;
/*!local:re2c
    "" {
        RET_FAIL(error_at_cur(
                "ill-formed start of a block: expected a space, a newline, a colon "
                "followed by a list of colon-separated block names, or the end of block"));
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
                RET_FAIL(error_at_cur("duplicate block `%s` on the list", p->name));
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
            "ill-formed block: expected optional whitespaces followed by the end of block"));
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
    const char* fmt = nullptr, *sep = nullptr;
    BlockNameList* blocks;

    out.gen_raw(tok, ptr, globopts->line_dirs);
    CHECK_RET(lex_name_list(&blocks));

loop: /*!local:re2c
    * {
        RET_FAIL(error_at_cur(
            "ill-formed block: expected optional configurations followed by the end of block"));
    }

    "format" {
        if ((mask & DCONF_FORMAT) == 0) {
            RET_FAIL(error_at_cur("unexpected configuration 'format'"));
        }
        CHECK_RET(lex_conf_string_legacy());
        fmt = copystr(tmp_str, alc);
        goto loop;
    }

    "separator" {
        if ((mask & DCONF_SEPARATOR) == 0) {
            RET_FAIL(error_at_cur("unexpected configuration 'separator'"));
        }
        CHECK_RET(lex_conf_string_legacy());
        sep = copystr(tmp_str, alc);
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

Ret Input::lex_block(RE2C_STYPE* yylval, Ast& ast, int& token) {
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

    [0-9] {
        if (!globopts->flex_syntax) {
            RET_FAIL(error_at_tok("unexpected character: '%c'", *tok));
        }
        ast.temp_chars.push_back({*tok, tok_loc()});
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

Ret Input::process_semact(RE2C_STYPE* yylval, Ast& ast, const uint8_t* p, const uint8_t* q) {
    const char* text = "";
    if (globopts->indentation_sensitive) {
        // Cut off any leading or trailing newlines to make the code uniform.
        while (p <= q && *p == '\n') ++p;
        while (p <= q && *q == '\n') --q;

        if (p <= q) {
            // Split semantic action by newlines (note: last character `*q` is not a newline).
            // Drop blank lines (this simplifies the code below that removes indentation).
            auto is_blank = [](const uint8_t* s, const uint8_t* e) {
                while (s < e && is_space(*s)) ++s;
                return s == e;
            };
            tmp_list.clear();
            for (const uint8_t* s = p; s < q; ++s) {
                if (*s == '\n') {
                    if (!is_blank(p, s)) tmp_list.push_back(std::string(p, s + 1));
                    p = s + 1;
                }
            }
            if (!is_blank(p, q + 1)) tmp_list.push_back(std::string(p, q + 1) + "\n");

            if (!tmp_list.empty()) {
                // Find first line indentation and use it as base indentation.
                const std::string& first = tmp_list[0];
                uint32_t indent = 0;
                while (is_space_nonl(static_cast<uint8_t>(first[indent]))) ++indent;
                std::string indstr = first.substr(0, indent);

                // Cut off base indentation from every line and glue them together.
                tmp_str.clear();
                for (std::string& line: tmp_list) {
                    if (line.compare(0, indent, indstr) == 0) {
                        tmp_str += line.substr(indent, std::string::npos); // remove indent
                    } else {
                        RET_FAIL(error_at_tok("inconsistent indentation in semantic action"));
                    }
                }
                text = copystr(tmp_str, alc);
            }
        }
    } else {
        // copy the entire semantic action verbatim
        text = ast.cstr_global(p, q + 1);
    }

    yylval->semact = ast.sem_act(tok_loc(), text, nullptr, false);
    return Ret::OK;
}

Ret Input::lex_code_indented(RE2C_STYPE* yylval, Ast& ast) {
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
        const uint8_t* p = tok, *q = cur - 1;
        if (!globopts->indentation_sensitive) {
            while (p <= q && is_space(*p)) ++p;
            while (p <= q && is_space(*q)) --q;
        }
        return process_semact(yylval, ast, p, q);
    }
*/
}

Ret Input::lex_code_in_braces(RE2C_STYPE* yylval, Ast& ast) {
    uint32_t depth = 1;
code: /*!re2c
    "}" {
        --depth;
        if (depth > 0) goto code;

        const uint8_t* p = tok, *q = cur - 1;
        if (globopts->code_model == CodeModel::REC_FUNC || !globopts->wrap_blocks_in_braces) {
            // Strip curly braces and adjacent whitespace. In rec/func mode it is always safe
            // to do, as the code is in a separate function and won't cause name collisions.
            ++p; --q; // skip '{' and '}'
            while (p <= q && is_space_nonl(*p)) ++p;
            while (p <= q && is_space_nonl(*q)) --q;
        }
        return process_semact(yylval, ast, p, q);
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

Ret Input::lex_dqstring_in_code() {
loop: /*!re2c
    ["]       { return Ret::OK; }
    esc [\\"] { goto loop; }
    eol       { next_line(); goto loop; }
    *         { goto loop; }
*/
}

Ret Input::lex_sqstring_in_code() {
loop: /*!re2c
    [']       { return Ret::OK; }
    esc [\\'] { goto loop; }
    eol       { next_line(); goto loop; }
    *         { goto loop; }
*/
}

Ret Input::lex_bqstring_in_code() {
loop: /*!re2c
    [`] { return Ret::OK; }
    eol { next_line(); goto loop; }
    *   { goto loop; }
*/
}

// Generalized rule for char literals (covering various languages).
///
// Char literals may contain closing curly brace, e.g. '}'. We must lex all possible forms of
// char literals, otherwise we might erroneously lex closing single quote as the beginning of
// another literal and overlook a real closing brace (e.g. in 'a'}'b' we might recognize '}'
// as a literal).
//
/*!rules:re2c:char_lit
    re2c:flags:utf-8 = 1;
    char_lit =
        esc [ux][{] hex_digit+ [}] | // hex escape \u{X...X}
        esc [x] hex_digit{2}       | // 2-byte hex escape
        esc [u] hex_digit{4}       | // 4-byte hex escape \uXXXX
        esc [U] hex_digit{8}       | // 8-byte hex escape \UXXXXXXXX
        esc [o][{] oct_digit+ [}]  | // octal escape \o{X...X}
        esc oct_digit{3}           | // octal escape \XXX
        esc ['\\?abfnrtv0]         | // special escape sequences
        [^]                        ; // any UTF-8 encoded Unicode symbol, unescaped
*/

Ret Input::lex_sqchar_or_standalone_in_code() {
/*!local:re2c
    !use:char_lit;
    char_lit ['] { return Ret::OK; }
    ""           { return Ret::OK; } // standalone single quote => ignore
*/
}

Ret Input::lex_bqchar_or_standalone_in_code() {
/*!local:re2c
    !use:char_lit;
    char_lit [`] { return Ret::OK; }
    ""           { return Ret::OK; } // standalone backtick => ignore
*/
}

Ret Input::try_lex_literal_in_code(uint8_t quote) {
    // We need to lex string and char literals in code blocks because they may contain closing
    // brace or newline that would otherwise be erroneously lexed as block terminator symbols.
    switch (quote) {
    case '"':
        return lex_dqstring_in_code();
    case '\'':
        return globopts->single_quoted_strings
            ? lex_sqstring_in_code()
            : lex_sqchar_or_standalone_in_code();
    case '`':
        return globopts->backtick_quoted_strings
            ? lex_bqstring_in_code()
            : lex_bqchar_or_standalone_in_code();
    default:
        return Ret::FAIL;
    }
}

Ret Input::lex_c_comment() {
loop: /*!re2c
    "*" "/" { return Ret::OK; }
    eol     { next_line(); goto loop; }
    *       { goto loop; }
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
