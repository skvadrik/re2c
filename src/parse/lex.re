#include <ctype.h>
#include "src/util/c99_stdint.h"
#include <limits>
#include <string>
#include <utility>
#include <vector>

#include "src/codegen/code.h"
#include "src/encoding/enc.h"
#include "src/msg/location.h"
#include "src/msg/msg.h"
#include "src/msg/warn.h"
#include "src/options/opt.h"
#include "src/parse/ast.h"
#include "src/parse/input.h"
#include "src/parse/lex.h"
#include "src/parse/scanner.h"
#include "src/parse/parse.h" // needed by "parser.h"
#include "src/parse/unescape.h"
#include "src/regexp/rule.h"
#include "src/util/file_utils.h"
#include "src/util/s_to_n32_unsafe.h"
#include "src/util/string_utils.h"
#include "parser.h"


extern YYSTYPE yylval;

namespace re2c {

// Global re2c configurations and definitions.
/*!re2c
    // source code is in ASCII, but re2c assumes unsigned chars
    re2c:yych:conversion = 1;
    re2c:flags:type-header = "lex.h";
    re2c:flags:tags = 1;
    re2c:api:style = free-form;

    re2c:define:YYCTYPE  = "unsigned char";
    re2c:define:YYCURSOR = "cur";
    re2c:define:YYLIMIT  = "lim";
    re2c:define:YYMARKER = "mar";
    re2c:define:YYFILL   = '{ if (!fill(@@)) { error("unexpected end of input"); exit(1); } }';

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

struct ScannerState
{
    enum lexer_state_t {LEX_NORMAL, LEX_FLEX_NAME};
    lexer_state_t lexer_state;

    size_t BSIZE;
    char *bot, *lim, *cur, *mar, *ctx, *tok, *ptr, *pos, *eof;
    /*!stags:re2c format = "char *@@;"; */

    inline ScannerState()
        : lexer_state (LEX_NORMAL)
        , BSIZE(8192)
        , bot(new char[BSIZE + YYMAXFILL])
        , lim(bot + BSIZE)
        , cur(lim)
        , mar(lim)
        , ctx(lim)
        , tok(lim)
        , ptr(lim)
        , pos(lim)
        , eof(NULL)
        /*!stags:re2c format = ", @@(lim)"; */
    {
        memset(lim, 0, YYMAXFILL);
    }

    inline ~ScannerState() { delete[] bot; }

    inline void shift_ptrs(ptrdiff_t offs)
    {
        lim += offs;
        cur += offs;
        mar += offs;
        ctx += offs;
        tok += offs;
        ptr += offs;
        pos += offs;
        /*!stags:re2c format = "if (@@) { @@ += offs; }"; */
    }

    FORBID_COPY(ScannerState);
};
} // namespace re2c

#endif // _RE2C_PARSE_LEX_
/*!header:re2c:off*/

InputBlockKind Scanner::echo(Output &out, std::string &block_name)
{
    const opt_t *opts = out.block().opts;
    code_alc_t &alc = out.allocator;
    const char *x, *y;

    if (is_eof()) return INPUT_END;

next:
    tok = cur;
loop:
    location = cur_loc();
    ptr = cur;
/*!local:re2c
    "%{" {
        out.wraw(tok, ptr);
        block_name.clear();
        return INPUT_GLOBAL;
    }

    "/*!re2c" {
        out.wraw(tok, ptr);
        if (!lex_opt_name(block_name)) return INPUT_ERROR;
        return INPUT_GLOBAL;
    }

    "/*!local:re2c" {
        out.wraw(tok, ptr);
        if (!lex_opt_name(block_name)) return INPUT_ERROR;
        return INPUT_LOCAL;
    }

    "/*!rules:re2c" {
        out.wraw(tok, ptr);
        if (!lex_opt_name(block_name)) return INPUT_ERROR;
        return INPUT_RULES;
    }

    "/*!use:re2c" {
        out.wraw(tok, ptr);
        if (!lex_opt_name(block_name)) return INPUT_ERROR;
        return INPUT_USE;
    }

    "/*!max:re2c" {
        if (!lex_block(out, CODE_MAXFILL, 0, DCONF_FORMAT)) return INPUT_ERROR;
        goto next;
    }

    "/*!maxnmatch:re2c" {
        if (!lex_block(out, CODE_MAXNMATCH, 0, DCONF_FORMAT)) return INPUT_ERROR;
        goto next;
    }

    "/*!stags:re2c" {
        uint32_t allow = DCONF_FORMAT | DCONF_SEPARATOR;
        if (!lex_block(out, CODE_STAGS, 0, allow)) return INPUT_ERROR;
        goto next;
    }

    "/*!mtags:re2c" {
        uint32_t allow = DCONF_FORMAT | DCONF_SEPARATOR;
        if (!lex_block(out, CODE_MTAGS, 0, allow)) return INPUT_ERROR;
        goto next;
    }

    "/*!types:re2c" {
        out.cond_enum_in_hdr = out.in_header();
        out.warn_condition_order = false; // see note [condition order]
        uint32_t allow = DCONF_FORMAT | DCONF_SEPARATOR;
        if (!lex_block(out, CODE_COND_ENUM, opts->topIndent, allow)) return INPUT_ERROR;
        goto next;
    }

    "/*!getstate:re2c" {
        out.state_goto = true;
        if (!opts->fFlag) {
            msg.error(cur_loc(), "`getstate:re2c` without `-f --storable-state` option");
            return INPUT_ERROR;
        }
        if (!lex_block(out, CODE_STATE_GOTO, opts->topIndent, 0)) return INPUT_ERROR;
        goto next;
    }

    "/*!header:re2c:on" {
        out.wraw(tok, ptr);
        out.header_mode(true);
        out.need_header = opts->target == TARGET_CODE;
        if (!lex_block_end(out)) return INPUT_ERROR;
        goto next;
    }

    "/*!header:re2c:off" {
        out.wraw(tok, ptr);
        out.header_mode(false);
        out.wdelay_stmt(0, code_line_info_input(alc, cur_loc()));
        if (!lex_block_end(out)) return INPUT_ERROR;
        goto next;
    }
    "/*!header:re2c" {
        msg.error(cur_loc(), "ill-formed header directive: expected"
            " `/*!header:re2c:<on|off>` followed by a space, a newline or the"
            " end of block `*" "/`");
        return INPUT_ERROR;
    }

    "/*!include:re2c" space+ @x dstring @y / ws_or_eoc {
        out.wraw(tok, ptr);
        if (!lex_block_end(out)) return INPUT_ERROR;
        include(getstr(x + 1, y - 1));
        goto next;
    }
    "/*!include:re2c" {
        msg.error(cur_loc(), "ill-formed include directive: expected"
            " `/*!include:re2c \"<file>\" *" "/`");
        return INPUT_ERROR;
    }

    "/*!ignore:re2c" / ws_or_eoc {
        out.wraw(tok, ptr);
        // allows arbitrary garbage before the end of the comment
        if (!lex_block_end(out, true)) return INPUT_ERROR;
        goto next;
    }
    "/*!ignore:re2c" {
        msg.error(cur_loc(), "ill-formed start of `ignore:re2c` block: expected"
            " a space, a newline, or the end of block `*" "/`");
        return INPUT_ERROR;
    }

    eof {
        if (is_eof()) {
            out.wraw(tok, ptr);
            return INPUT_END;
        }
        goto loop;
    }

    linedir / lineinf {
        out.wraw(tok, ptr);
        out.wdelay_stmt(0, code_newline(alc));
        set_sourceline();
        goto next;
    }

    eol {
        next_line();
        goto loop;
    }

    * { goto loop; }
*/
}

bool Scanner::lex_opt_name(std::string &name)
{
    tok = cur;
/*!local:re2c
    "" {
        msg.error(cur_loc(), "ill-formed start of a block: expected a space, a"
            " newline, a colon followed by a block name, or the end of block `*"
            "/`");
        return false;
    }

    ""       / ws_or_eoc { name.clear();              return true; }
    ":" name / ws_or_eoc { name.assign(tok + 1, cur); return true; }
*/
}

bool Scanner::lex_name_list(code_alc_t &alc, BlockNameList **ptail)
{
    BlockNameList **phead = ptail;
loop:
    tok = cur;
/*!local:re2c
    "" {
        msg.error(cur_loc(), "ill-formed start of a block: expected a space, a"
            " newline, a colon followed by a list of colon-separated block"
            " names, or the end of block `*" "/`");
        return false;
    }

    "" / ws_or_eoc {
        *ptail = NULL;
        return true;
    }

    ":" name {
        BlockNameList *l = alc.alloct<BlockNameList>(1);
        l->name = newcstr(tok + 1, cur, alc);
        l->next = NULL;
        *ptail = l;
        ptail = &l->next;

        // Check that the added name is unique.
        for (const BlockNameList *p = *phead; p != l; p = p->next) {
            if (strcmp(p->name, l->name) == 0) {
                msg.error(cur_loc(), "duplicate block '%s' on the list", p->name);
                return false;
            }
        }

        goto loop;
    }
*/
}

bool Scanner::lex_block_end(Output &out, bool allow_garbage)
{
    bool multiline = false;
loop:
/*!local:re2c
    * {
        if (allow_garbage && !is_eof()) goto loop;
        msg.error(cur_loc(), "ill-formed end of block: expected optional"
            " whitespaces followed by `*" "/`");
        return false;
    }
    eoc {
        if (multiline) out.wdelay_stmt(0, code_line_info_input(out.allocator, cur_loc()));
        return true;
    }
    space+ { goto loop; }
    eol    { next_line(); multiline = true; goto loop; }
*/
}

bool Scanner::lex_block(Output &out, CodeKind kind, uint32_t indent, uint32_t mask)
{
    code_alc_t &alc = out.allocator;
    const char *fmt = NULL, *sep = NULL;
    BlockNameList *blocks;

    out.wraw(tok, ptr, !globopts->iFlag);
    if (!lex_name_list(alc, &blocks)) return false;

loop:
/*!local:re2c
    * {
        msg.error(cur_loc(), "ill-formed directive: expected optional "
            "configurations followed by the end of block `*" "/`");
        return false;
    }

    "format" {
        if ((mask & DCONF_FORMAT) == 0) {
            msg.error(cur_loc(), "unexpected configuration 'format'");
            return false;
        }
        fmt = copystr(lex_conf_string(), alc);
        goto loop;
    }

    "separator" {
        if ((mask & DCONF_SEPARATOR) == 0) {
            msg.error(cur_loc(), "unexpected configuration 'separator'");
            return false;
        }
        sep = copystr(lex_conf_string(), alc);
        goto loop;
    }

    space+ { goto loop; }

    eol { next_line(); goto loop; }

    eoc {
        out.wdelay_stmt(0, code_line_info_output(alc));
        out.wdelay_stmt(indent, code_fmt(alc, kind, blocks, fmt, sep));
        out.wdelay_stmt(0, code_line_info_input(alc, cur_loc()));
        return true;
    }
*/
}

int Scanner::scan()
{
    const char *p, *x, *y;
scan:
    tok = cur;
    location = cur_loc();
/*!local:re2c

    "{"  { lex_code_in_braces(); return TOKEN_CODE; }
    ":=" { lex_code_indented(); return TOKEN_CODE; }

    ":"? "=>" space* @p name {
        yylval.str = newstr(p, cur);
        return tok[0] == ':' ? TOKEN_CJUMP : TOKEN_CNEXT;
    }

    "<" { return lex_clist(); }

    "//" { lex_cpp_comment(); goto scan; }
    "/*" { lex_c_comment(); goto scan; }

    "%}" | "*""/" { tok = cur; return 0; }

    "'"  { yylval.regexp = lex_str('\''); return TOKEN_REGEXP; }
    "\"" { yylval.regexp = lex_str('"'); return TOKEN_REGEXP; }
    "["  { yylval.regexp = lex_cls(false); return TOKEN_REGEXP; }
    "[^" { yylval.regexp = lex_cls(true);  return TOKEN_REGEXP; }

    [@#] name {
        yylval.regexp = ast_tag(tok_loc(), newstr(tok + 1, cur), tok[0] == '#');
        return TOKEN_REGEXP;
    }

    [*+?()|;/\\=$] { return *tok; }

    "{" [0-9]+ "}" {
        if (!s_to_u32_unsafe (tok + 1, cur - 1, yylval.bounds.min)) {
            msg.error(tok_loc(), "repetition count overflow");
            exit(1);
        }
        yylval.bounds.max = yylval.bounds.min;
        return TOKEN_CLOSESIZE;
    }

    "{" [0-9]+ @p "," [0-9]+ "}" {
        if (!s_to_u32_unsafe (tok + 1, p, yylval.bounds.min)) {
            msg.error(tok_loc(), "repetition lower bound overflow");
            exit(1);
        }
        if (!s_to_u32_unsafe (p + 1, cur - 1, yylval.bounds.max)) {
            msg.error(tok_loc(), "repetition upper bound overflow");
            exit(1);
        }
        return TOKEN_CLOSESIZE;
    }

    "{" [0-9]+ ",}" {
        if (!s_to_u32_unsafe (tok + 1, cur - 2, yylval.bounds.min)) {
            msg.error(tok_loc(), "repetition lower bound overflow");
            exit(1);
        }
        yylval.bounds.max = std::numeric_limits<uint32_t>::max();
        return TOKEN_CLOSESIZE;
    }

    "{" [0-9]* "," {
        msg.error(tok_loc(), "illegal closure form, use '{n}', '{n,}', '{n,m}' "
            "where n and m are numbers");
        exit(1);
    }

    "{" name "}" {
        if (!globopts->FFlag) {
            msg.error(tok_loc(), "curly braces for names only allowed with -F switch");
            exit(1);
        }
        yylval.str = newstr(tok + 1, cur - 1);
        return TOKEN_ID;
    }

    "re2c:" { return TOKEN_CONF; }

    name {
        if (!globopts->FFlag || lex_namedef_context_re2c()) {
            yylval.str = newstr(tok, cur);
            return TOKEN_ID;
        }
        else if (lex_namedef_context_flex()) {
            yylval.str = newstr(tok, cur);
            lexer_state = LEX_FLEX_NAME;
            return TOKEN_FID;
        }
        else {
            // consume one character, otherwise we risk breaking operator
            // precedence in cases like ab*: it should be a(b)*, not (ab)*
            cur = tok + 1;

            ASTChar c = {static_cast<uint8_t>(tok[0]), tok_loc()};
            std::vector<ASTChar> *str = new std::vector<ASTChar>;
            str->push_back(c);
            yylval.regexp = ast_str(tok_loc(), str, false);
            return TOKEN_REGEXP;
        }
    }

    "!include" space+ @x dstring @y space* ";" / ws_or_eoc {
        include(getstr(x + 1, y - 1));
        goto scan;
    }
    "!include" {
        msg.error(tok_loc(), "ill-formed include directive: expected `!include`"
            " followed by spaces, a double-quoted file path, optional spaces, a"
            " semicolon, and finally a space, a newline, or the end of block");
        exit(1);
    }

    "!use:" @x name @y space* ";" / ws_or_eoc {
        yylval.str = newstr(x, y); // save the name of the used block
        return TOKEN_BLOCK;
    }
    "!use" {
        msg.error(tok_loc(), "ill-formed use directive: expected `!use`"
            " followed by a colon, a block name, optional spaces, a semicolon,"
            " and finally a space, a newline, or the end of block");
        exit(1);
    }

    "." {
        yylval.regexp = ast_dot(tok_loc());
        return TOKEN_REGEXP;
    }

    space+ { goto scan; }

    linedir / lineinf {
        set_sourceline ();
        return TOKEN_LINE_INFO;
    }

    eol {
        next_line();
        if (lexer_state == LEX_FLEX_NAME) {
            lexer_state = LEX_NORMAL;
            return TOKEN_FID_END;
        }
        else {
            goto scan;
        }
    }

    * {
        msg.error(tok_loc(), "unexpected character: '%c'", *tok);
        exit(1);
    }
*/
}

bool Scanner::lex_namedef_context_re2c()
{
/*!re2c
    "" / space* "=" [^>] { return true; }
    ""                   { return false; }
*/
}

bool Scanner::lex_namedef_context_flex()
{
/*!re2c
    "" / space+ [=:{] { return false; } // exclude lookahead ("=" | "=>" | ":=>" | ":=" | "{")
    "" / space+       { return true; }
    ""                { return false; }
*/
}

int Scanner::lex_clist()
{
    int kind = TOKEN_CLIST;
    CondList *cl = new CondList;
/*!re2c
    space* "!" space* { kind = TOKEN_CSETUP; goto cond; }
    space* ">"        { kind = TOKEN_CZERO; goto end; }
    space*            { goto cond; }
*/
cond:
    tok = cur;
/*!re2c
    name { cl->insert(getstr(tok, cur)); goto next; }
    "*"  { if (!cl->empty()) goto error; cl->insert("*"); goto next; }
    *    { goto error; }
*/
next:
/*!re2c
    space* "," space* { goto cond; }
    space* ">"        { goto end; }
    *                 { goto error; }
*/
end:
    yylval.clist = cl;
    return kind;
error:
    delete cl;
    msg.error(cur_loc(), "syntax error in condition list");
    exit(1);
}

void Scanner::lex_code_indented()
{
    const loc_t &loc = tok_loc();
    tok = cur;
code:
/*!re2c
    eol / ws { next_line(); goto code; }
    eol {
        next_line();
        while (isspace(tok[0])) ++tok;
        char *p = cur;
        while (p > tok && isspace(p[-1])) --p;
        yylval.semact = new SemAct(loc, getstr(tok, p));
        return;
    }

    eof  { fail_if_eof(); goto code; }
    [{}] {
        msg.error(cur_loc(), "Curly braces are not allowed after ':='");
        exit(1);
    }
    "/*" { lex_c_comment(); goto code; }
    "//" { lex_cpp_comment(); goto code; }
    ["'] { lex_string(cur[-1]); goto code; }
    *    { goto code; }
*/
}

void Scanner::lex_code_in_braces()
{
    const loc_t &loc = tok_loc();
    uint32_t depth = 1;
code:
/*!re2c
    "}" {
        if (--depth == 0) {
            yylval.semact = new SemAct(loc, getstr(tok, cur));
            return;
        }
        goto code;
    }

    "{"               { ++depth; goto code; }
    linedir / lineinf { set_sourceline (); goto code; }
    eol               { next_line(); goto code; }
    eof               { fail_if_eof(); goto code; }
    "/*"              { lex_c_comment(); goto code; }
    "//"              { lex_cpp_comment(); goto code; }
    ["']              { lex_string(cur[-1]); goto code; }
    *                 { goto code; }
*/
}

void Scanner::lex_string(char delim)
{
loop:
/*!re2c
    ["']       { if (cur[-1] == delim) return; else goto loop; }
    esc [\\"'] { goto loop; }
    eol        { next_line(); goto loop; }
    eof        { fail_if_eof(); goto loop; }
    *          { goto loop; }
*/
}

void Scanner::lex_c_comment()
{
loop:
/*!re2c
    eoc { return; }
    eol { next_line(); goto loop; }
    eof { fail_if_eof(); goto loop; }
    *   { goto loop; }
*/
}

void Scanner::lex_cpp_comment()
{
loop:
/*!re2c
    eol { next_line(); return; }
    eof { fail_if_eof(); goto loop; }
    *   { goto loop; }
*/
}

const AST *Scanner::lex_cls(bool neg)
{
    std::vector<ASTRange> *cls = new std::vector<ASTRange>;
    uint32_t u, l;
    const loc_t &loc0 = tok_loc();
    loc_t loc = cur_loc();
fst:
    tok = cur;
/*!re2c
    "]" { return ast_cls(loc0, cls, neg); }
    ""  { l = lex_cls_chr(); goto snd; }
*/
snd:
/*!re2c
    ""          { u = l; goto add; }
    "-" / [^\]] {
        u = lex_cls_chr();
        if (l > u) {
            msg.warn.swapped_range(loc, l, u);
            std::swap(l, u);
        }
        goto add;
    }
*/
add:
    cls->push_back(ASTRange(l, u, loc));
    loc = cur_loc();
    goto fst;
}

uint32_t Scanner::lex_cls_chr()
{
    tok = cur;
    const loc_t &loc = cur_loc();
    /*!rules:re2c:cls_chr

    esc? eol   { msg.error(loc, "newline in character class"); exit(1); }
    esc [xXuU] { msg.error(loc, "syntax error in hexadecimal escape sequence"); exit(1); }
    esc [0-7]  { msg.error(loc, "syntax error in octal escape sequence"); exit(1); }
    esc        { msg.error(loc, "syntax error in escape sequence"); exit(1); }
    *          { msg.error(loc, "syntax error"); exit(1); }

    eof        { fail_if_eof(); return 0; }

    . \ esc    { return decode(tok); }
    esc_hex    { return unesc_hex(tok, cur); }
    esc_oct    { return unesc_oct(tok, cur); }
    esc "a"    { return static_cast<uint8_t>('\a'); }
    esc "b"    { return static_cast<uint8_t>('\b'); }
    esc "f"    { return static_cast<uint8_t>('\f'); }
    esc "n"    { return static_cast<uint8_t>('\n'); }
    esc "r"    { return static_cast<uint8_t>('\r'); }
    esc "t"    { return static_cast<uint8_t>('\t'); }
    esc "v"    { return static_cast<uint8_t>('\v'); }
    esc "\\"   { return static_cast<uint8_t>('\\'); }
    esc "-"    { return static_cast<uint8_t>('-'); }
    esc "]"    { return static_cast<uint8_t>(']'); }
    esc (.\eof){
        msg.warn.useless_escape(loc, tok, cur);
        return decode(tok + 1);
    }
    */
    if (globopts->input_encoding == Enc::ASCII) {
        /*!local:re2c !use:cls_chr; */
    }
    else {
        /*!local:re2c !use:cls_chr; re2c:flags:8 = 1; */
    }
}

bool Scanner::lex_str_chr(char quote, ASTChar &ast)
{
    tok = cur;
    ast.loc = cur_loc();
    /*!rules:re2c:str_chr

    esc? eol   { msg.error(ast.loc, "newline in character string"); exit(1); }
    esc [xXuU] { msg.error(ast.loc, "syntax error in hexadecimal escape sequence"); exit(1); }
    esc [0-7]  { msg.error(ast.loc, "syntax error in octal escape sequence"); exit(1); }
    esc        { msg.error(ast.loc, "syntax error in escape sequence"); exit(1); }
    *          { msg.error(ast.loc, "syntax error"); exit(1); }

    eof        { fail_if_eof(); ast.chr = 0; return true; }

    . \ esc    { ast.chr = decode(tok); return tok[0] != quote; }
    esc_hex    { ast.chr = unesc_hex(tok, cur); return true; }
    esc_oct    { ast.chr = unesc_oct(tok, cur); return true; }
    esc "a"    { ast.chr = static_cast<uint8_t>('\a'); return true; }
    esc "b"    { ast.chr = static_cast<uint8_t>('\b'); return true; }
    esc "f"    { ast.chr = static_cast<uint8_t>('\f'); return true; }
    esc "n"    { ast.chr = static_cast<uint8_t>('\n'); return true; }
    esc "r"    { ast.chr = static_cast<uint8_t>('\r'); return true; }
    esc "t"    { ast.chr = static_cast<uint8_t>('\t'); return true; }
    esc "v"    { ast.chr = static_cast<uint8_t>('\v'); return true; }
    esc "\\"   { ast.chr = static_cast<uint8_t>('\\'); return true; }
    esc (.\eof){
        ast.chr = decode(tok + 1);
        if (tok[1] != quote) msg.warn.useless_escape(ast.loc, tok, cur);
        return true;
    }
    */
    if (globopts->input_encoding == Enc::ASCII) {
        /*!local:re2c !use:str_chr; */
    }
    else {
        /*!local:re2c !use:str_chr; re2c:flags:8 = 1; */
    }
}

const AST *Scanner::lex_str(char quote)
{
    const loc_t &loc = tok_loc();
    std::vector<ASTChar> *str = new std::vector<ASTChar>;
    ASTChar c;
    for (;;) {
        if (!lex_str_chr(quote, c)) {
            return ast_str(loc, str, quote == '\'');
        }
        str->push_back(c);
    }
}

void Scanner::set_sourceline ()
{
sourceline:
    tok = cur;
/*!local:re2c
    lineno {
        uint32_t l;
        if (!s_to_u32_unsafe(tok, cur, l)) {
            msg.error(tok_loc(), "line number overflow");
            exit(1);
        }
        set_line(l);
        goto sourceline;
    }

    dstring {
        Input &in = get_input();
        std::string &name = in.escaped_name;
        name = escape_backslashes(getstr(tok + 1, cur - 1));
        in.fidx = static_cast<uint32_t>(msg.filenames.size());
        msg.filenames.push_back(name);
        goto sourceline;
    }

    eol { pos = tok = cur; return; }
    eof { --cur; return; }
    *   { goto sourceline; }
*/
}

void Scanner::fail_if_eof() const
{
    if (is_eof()) {
        msg.error(cur_loc(), "unexpected end of input");
        exit(1);
    }
}

#undef YYCTYPE
#undef YYCURSOR
#undef YYLIMIT
#undef YYMARKER
#undef YYFILL

} // end namespace re2c
